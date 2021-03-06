// Copyright 2014 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Defines PageAllocator. This is a simple allocator that grabs pages of
// memory of a fixed specified size and hands out fixed size regions from head
// to tail within that page. Regions of pages that have been freed are kept
// track of in a simple linked list, and returned regions are aggressively
// reused before a new page is allocated.
//
// Since memory is not actively recovered at runtime this allocator will always
// use as much memory as the 'high waterline'. Thus, it is not suitable for
// managing bursty objects. Rather, it should be used for pools that tend to
// grow monotonically to a stable maximum size.

#ifndef SYZYGY_AGENT_ASAN_PAGE_ALLOCATOR_H_
#define SYZYGY_AGENT_ASAN_PAGE_ALLOCATOR_H_

#include "base/synchronization/lock.h"

namespace agent {
namespace asan {

// Forward declarations. These are all defined in the corresponding _impl.h.
struct PageAllocatorStatistics;
namespace detail {
template<bool kKeepStats> struct PageAllocatorStatisticsHelper;
template<size_t kObjectSize, size_t kPageSize> struct PageAllocatorPage;
}  // namespace detail


// NOTE: If you want these to be optimally packed, please use #pragma pack(1)!
//       Otherwise, the default compiler alignment will kick in, and the
//       objects will be rounded up in size to be 4-byte aligned.


// An untyped PageAllocator. Thread safety is provided by this object.
// @tparam kObjectSize The size of objects returned by the allocator,
//     in bytes. Objects will be tightly packed so any alignment constraints
//     should be reflected in this size. Must be at least as big as a pointer.
// @tparam kMaxObjectCount The maximum number of consecutive objects that
//     will be requested at once by the allocator. The allocator will
//     ensure that this is possible, and will maintain separate free lists
//     for each possible length from 1 to kMaxObjectCount.
// @tparam kPageSize The amount of memory to be allocated at a time as
//     the pool grows. This will be rounded up to a multiple of the OS page
//     size that is a divisor of the allocation granularity, or a multiple of
//     the allocation granularity. This ensures efficient memory use and
//     minimal fragmentation.
// @tparam kKeepStats If true, then statistics will be collected.
template<size_t kObjectSize,
         size_t kMaxObjectCount,
         size_t kPageSize,
         bool kKeepStats>
class PageAllocator {
 public:
  typedef detail::PageAllocatorPage<kObjectSize, kPageSize> Page;
  typedef typename Page::Object Object;

  // Constructor.
  PageAllocator();

  // Destructor.
  ~PageAllocator();

  // Allocates @p count objects of the configured size.
  // @param count The number of objects to allocate. Must be > 0.
  // @returns A pointer to the allocated objects, or NULL on failure.
  void* Allocate(size_t count);

  // Allocates at least @p count objects of the configured size, indicating
  // how many were actually returned via @p received. This helps to keep
  // fragmentation lower by keeping larger allocations intact.
  // @param count The number of objects to allocate. Must be > 0.
  // @param received Will be set to the number of object actually
  //     allocated. This must be the value that is passed to the corresponding
  //     call to free.
  // @returns A pointer to the allocated objects, or NULL on failure.
  void* Allocate(size_t count, size_t* received);

  // Frees the given objects.
  // @param object The object to be returned.
  // @param count The number of objects to return. This must match the
  //     number of objects originally allocated.
  void Free(void* object, size_t count);

  // Returns current statistics. If kKeepStats is false this is a noop and
  // does not set any meaningful data.
  // @param stats The statistics data to be populated.
  void GetStatistics(PageAllocatorStatistics* stats);

  // Determines if an allocation is currently handed out by this allocator.
  // @param object The object to be checked.
  // @param count The number of objects in the allocation.
  // @returns true if the given object was handed out by this allocator.
  // @note Handles locking, so no locks must already be held.
  bool Allocated(const void* object, size_t count) {
    return AllocationStatus(object, count) == 1;
  }

  // Determines if an allocation is currently freed by this allocator.
  // @param object The object to be checked.
  // @param count The number of objects in the allocation. If this is zero then
  //     all freed size classes will be checked, otherwise only the exact
  //     specified size class will be checked.
  // @returns true if the given object is the first object in a range that was
  //     freed by the allocator.
  // @note Handles locking, so no locks must already be held.
  bool Freed(const void* object, size_t count) {
    return AllocationStatus(object, count) == 0;
  }

 protected:
  // Tri-state allocation status function, determining if the given object
  // is currently allocated by this allocator (1), currently freed (0), or
  // isn't under management by it (-1).
  // @returns 1 if the object was allocated, 0 if it has since been freed, or
  //     -1 if the object is not under management by this allocator.
  // @note This is a very costly O(memory under management) function!
  int AllocationStatus(const void* object, size_t count);

  // Determines if an allocation was handed out by this allocator. The object
  // may since have been freed.
  // @param object The object to be checked.
  // @param count The number of objects in the allocation.
  // @returns true if the given object was handed out by this allocator.
  // @note Handles locking, so no locks must already be held.
  bool WasOnceAllocated(const void* object, size_t count);

  // Determines if an allocation is currently in the freed list of this
  // allocator.
  // @param object The object to be checked.
  // @param count The number of objects in the allocation. If this is zero then
  //     all freed size classes will be checked, otherwise only the exact
  //     specified size class will be checked.
  // @returns true if the given object is the first object in a range that was
  //     freed by the allocator.
  // @note Handles locking, so no locks must already be held.
  bool IsInFreeList(const void* object, size_t count);

  // Pops the top item from the given free list.
  // @param count The size class.
  // @returns a pointer to the popped item, NULL if there was none.
  // @note Handles locking, so no free_lock_ should be already held.
  Object* FreePop(size_t count);

  // Pushes the given object to the specified free list. Directives as to
  // statistics keeping are provided directly here to minimize the number of
  // times the statistics lock needs to be taken.
  // @param object The objects to free.
  // @param count The number of objects to free.
  // @param decr_alloc_groups If true then decrements allocated_groups.
  // @param decr_alloc_objects If true then decrements allocated_object.
  // @note Handles locking, so no free_lock_ should be already held.
  void FreePush(Object* object, size_t count,
                bool decr_alloc_groups, bool decr_alloc_objects);

  // Reserves a new page of objects, modifying current_page_ and
  // current_object_. Any remaining unallocated objects are stuffed into the
  // appropriate freed list. There may be no more than kMaxObjectCount of them.
  // @returns true if the allocation was successful, false otherwise.
  // @note Assumes the lock_ has already been acquired.
  bool AllocatePageLocked();

  // The number of pages that have been allocated. Under lock_.
  size_t page_count_;

  // The current slab of reserved memory we are working from  Under lock_.
  Page* slab_;
  Page* slab_cursor_;

  // The currently active page. Under lock_.
  Page* page_;

  // The next object to be allocated in the current page. Under lock_.
  Object* object_;

  // A singly linked list of freed objects, one per possible size category.
  // These are under the corresponding free_lock_.
  Object* free_[kMaxObjectCount];

  // Locks for the freed lists. This keeps contention down while freeing.
  base::Lock free_lock_[kMaxObjectCount];

  // The global lock for the allocator.
  base::Lock lock_;

  // For keeping statistics. If kKeepStats == 0 this is an empty struct with
  // noop routines.
  detail::PageAllocatorStatisticsHelper<kKeepStats> stats_;

 private:
  DISALLOW_COPY_AND_ASSIGN(PageAllocator);
};

// A templated PageAllocator with convenience functions for allocating and
// freeing typed objects.
// @tparam ObjectType The type of object that is returned by the allocator.
// @tparam kMaxObjectCount The maximum number of consecutive objects that
//     will be requested at once by the allocator. The allocator will
//     ensure that this is possible, and will maintain separate free lists
//     for each possible length from 1 to kMaxObjectCount.
// @tparam kPageSize The amount of memory to be allocated at a time as
//     the pool grows.
// @tparam kKeepStats If true, then statistics will be collected.
template<typename ObjectType,
         size_t kMaxObjectCount,
         size_t kPageSize,
         bool kKeepStats>
class TypedPageAllocator
    : public PageAllocator<sizeof(ObjectType),
                           kMaxObjectCount,
                           kPageSize,
                           kKeepStats> {
 public:
  // The parent type for this class.
  typedef PageAllocator<sizeof(ObjectType), kMaxObjectCount, kPageSize,
                        kKeepStats> Super;

  // Constructor.
  TypedPageAllocator() { }

  // Destructor.
  ~TypedPageAllocator() { }

  // Allocates objects.
  // @param count The number of objects to allocate. Must be > 0.
  // @returns A pointer to the allocated object, or NULL on failure.
  ObjectType* Allocate(size_t count);

  // Allocates at least the requested number of objects, possibly returning
  // more. This allocator is preferred as it results in less fragmentation.
  // @param count The number of objects to allocate. Must be > 0.
  // @param received Will be set to the number of object actually
  //     allocated. This must be the value that is passed to the corresponding
  //     call to free.
  // @returns A pointer to the allocated objects, or NULL on failure.
  ObjectType* Allocate(size_t count, size_t* received);

  // Frees the given object.
  // @param object The object to be returned.
  // @param count The number of objects to return. This must match the
  //     number of objects originally allocated.
  void Free(ObjectType* object, size_t count);

 private:
  DISALLOW_COPY_AND_ASSIGN(TypedPageAllocator);
};

// A structure used for collecting statistics aggregated by a page allocator.
struct PageAllocatorStatistics {
  // The number of pages allocated.
  size_t page_count;
  // The number of groups of objects handed out.
  size_t allocated_groups;
  // The total number of objects handed out.
  size_t allocated_objects;
  // The number of groups of objects living in free lists.
  size_t freed_groups;
  // The total number of objects living in free lists.
  size_t freed_objects;
};

}  // namespace asan
}  // namespace agent

#include "syzygy/agent/asan/page_allocator_impl.h"

#endif  // SYZYGY_AGENT_ASAN_PAGE_ALLOCATOR_H_
