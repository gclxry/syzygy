// Copyright 2015 Google Inc. All Rights Reserved.
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

// This file is generated by generate_type_info_records.py, DO NOT MODIFY.

#ifndef SYZYGY_PDB_GEN_PDB_TYPE_INFO_RECORDS_H_
#define SYZYGY_PDB_GEN_PDB_TYPE_INFO_RECORDS_H_

#include "base/strings/string16.h"
#include "syzygy/pdb/pdb_stream_record.h"
#include "syzygy/pe/cvinfo_ext.h"

namespace pdb {

// Forward declaration.
class PdbStream;

class LeafArgList {
 public:
  LeafArgList();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafArgList& body() const { return body_; }
  // @}

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafArgList body_;
};

class LeafArray {
 public:
  LeafArray();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafArray& body() const { return body_; }
  uint64_t size() const { return size_; }
  const base::string16& name() const { return name_; }
  // @}

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafArray body_;

  // Additional fields parsed from the pdb stream.
  uint64_t size_;
  base::string16 name_;
};

class LeafBClass {
 public:
  LeafBClass();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafBClass& body() const { return body_; }
  uint64_t offset() const { return offset_; }
  LeafMemberAttributeField attr() const { return {body_.attr}; }
  // @}

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafBClass body_;

  // Additional fields parsed from the pdb stream.
  uint64_t offset_;
};

class LeafBitfield {
 public:
  LeafBitfield();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafBitfield& body() const { return body_; }
  // @}

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafBitfield body_;
};

class LeafClass {
 public:
  LeafClass();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafClass& body() const { return body_; }
  uint64_t size() const { return size_; }
  const base::string16& name() const { return name_; }
  const base::string16& decorated_name() const { return decorated_name_; }
  LeafPropertyField property() const { return {body_.property}; }
  // @}

  bool has_decorated_name() const {
    return (property().decorated_name_present != 0);
  }

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafClass body_;

  // Additional fields parsed from the pdb stream.
  uint64_t size_;
  base::string16 name_;
  base::string16 decorated_name_;
};

class LeafEnum {
 public:
  LeafEnum();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafEnum& body() const { return body_; }
  const base::string16& name() const { return name_; }
  const base::string16& decorated_name() const { return decorated_name_; }
  LeafPropertyField property() const { return {body_.property}; }
  // @}

  bool has_decorated_name() const {
    return (property().decorated_name_present != 0);
  }

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafEnum body_;

  // Additional fields parsed from the pdb stream.
  base::string16 name_;
  base::string16 decorated_name_;
};

class LeafEnumerate {
 public:
  LeafEnumerate();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafEnumerate& body() const { return body_; }
  const NumericConstant& value() const { return value_; }
  const base::string16& name() const { return name_; }
  LeafMemberAttributeField attr() const { return {body_.attr}; }
  // @}

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafEnumerate body_;

  // Additional fields parsed from the pdb stream.
  NumericConstant value_;
  base::string16 name_;
};

class LeafFriendCls {
 public:
  LeafFriendCls();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafFriendCls& body() const { return body_; }
  // @}

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafFriendCls body_;
};

class LeafFriendFcn {
 public:
  LeafFriendFcn();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafFriendFcn& body() const { return body_; }
  const base::string16& name() const { return name_; }
  // @}

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafFriendFcn body_;

  // Additional fields parsed from the pdb stream.
  base::string16 name_;
};

class LeafIndex {
 public:
  LeafIndex();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafIndex& body() const { return body_; }
  // @}

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafIndex body_;
};

class LeafMember {
 public:
  LeafMember();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafMember& body() const { return body_; }
  uint64_t offset() const { return offset_; }
  const base::string16& name() const { return name_; }
  LeafMemberAttributeField attr() const { return {body_.attr}; }
  // @}

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafMember body_;

  // Additional fields parsed from the pdb stream.
  uint64_t offset_;
  base::string16 name_;
};

class LeafMethod {
 public:
  LeafMethod();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafMethod& body() const { return body_; }
  const base::string16& name() const { return name_; }
  // @}

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafMethod body_;

  // Additional fields parsed from the pdb stream.
  base::string16 name_;
};

class LeafMFunction {
 public:
  LeafMFunction();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafMFunc& body() const { return body_; }
  // @}

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafMFunc body_;
};

class LeafModifier {
 public:
  LeafModifier();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafModifier& body() const { return body_; }
  LeafModifierAttribute attr() const { return attr_; }
  // @}

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafModifier body_;

  // Additional fields parsed from the pdb stream.
  LeafModifierAttribute attr_;
};

class LeafNestType {
 public:
  LeafNestType();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafNestTypeEx& body() const { return body_; }
  const base::string16& name() const { return name_; }
  LeafMemberAttributeField attr() const { return {body_.attr}; }
  // @}

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafNestTypeEx body_;

  // Additional fields parsed from the pdb stream.
  base::string16 name_;
};

class LeafOneMethod {
 public:
  LeafOneMethod();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafOneMethod& body() const { return body_; }
  uint32_t vbaseoff() const { return vbaseoff_; }
  const base::string16& name() const { return name_; }
  LeafMemberAttributeField attr() const { return {body_.attr}; }
  // @}

  bool has_vbaseoff() const {
    return (attr().mprop == Microsoft_Cci_Pdb::CV_MTintro ||
            attr().mprop == Microsoft_Cci_Pdb::CV_MTpureintro);
  }

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafOneMethod body_;

  // Additional fields parsed from the pdb stream.
  uint32_t vbaseoff_;
  base::string16 name_;
};

class LeafPointer {
 public:
  LeafPointer();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafPointer::LeafPointerBody& body() const { return body_; }
  LeafPointerAttribute attr() const { return attr_; }
  uint32_t containing_class() const { return containing_class_; }
  uint16_t pmtype() const { return pmtype_; }
  // @}

  bool has_containing_class() const {
    return (attr().ptrmode == Microsoft_Cci_Pdb::CV_PTR_MODE_PMEM ||
            attr().ptrmode == Microsoft_Cci_Pdb::CV_PTR_MODE_PMFUNC);
  }

  bool has_pmtype() const {
    return (attr().ptrmode == Microsoft_Cci_Pdb::CV_PTR_MODE_PMEM ||
            attr().ptrmode == Microsoft_Cci_Pdb::CV_PTR_MODE_PMFUNC);
  }

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafPointer::LeafPointerBody body_;

  // Additional fields parsed from the pdb stream.
  LeafPointerAttribute attr_;
  uint32_t containing_class_;
  uint16_t pmtype_;
};

class LeafProcedure {
 public:
  LeafProcedure();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafProc& body() const { return body_; }
  // @}

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafProc body_;
};

class LeafSTMember {
 public:
  LeafSTMember();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafSTMember& body() const { return body_; }
  const base::string16& name() const { return name_; }
  LeafMemberAttributeField attr() const { return {body_.attr}; }
  // @}

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafSTMember body_;

  // Additional fields parsed from the pdb stream.
  base::string16 name_;
};

class LeafUnion {
 public:
  LeafUnion();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafUnion& body() const { return body_; }
  uint64_t size() const { return size_; }
  const base::string16& name() const { return name_; }
  const base::string16& decorated_name() const { return decorated_name_; }
  LeafPropertyField property() const { return {body_.property}; }
  // @}

  bool has_decorated_name() const {
    return (property().decorated_name_present != 0);
  }

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafUnion body_;

  // Additional fields parsed from the pdb stream.
  uint64_t size_;
  base::string16 name_;
  base::string16 decorated_name_;
};

class LeafVBClass {
 public:
  LeafVBClass();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafVBClass& body() const { return body_; }
  uint64_t vbpoff() const { return vbpoff_; }
  uint64_t vboff() const { return vboff_; }
  LeafMemberAttributeField attr() const { return {body_.attr}; }
  // @}

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafVBClass body_;

  // Additional fields parsed from the pdb stream.
  uint64_t vbpoff_;
  uint64_t vboff_;
};

class LeafVFuncOff {
 public:
  LeafVFuncOff();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafVFuncOff& body() const { return body_; }
  uint32_t type() const { return type_; }
  uint32_t offset() const { return offset_; }
  // @}

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafVFuncOff body_;

  // Additional fields parsed from the pdb stream.
  uint32_t type_;
  uint32_t offset_;
};

class LeafVFuncTab {
 public:
  LeafVFuncTab();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafVFuncTab& body() const { return body_; }
  uint32_t index() const { return index_; }
  // @}

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafVFuncTab body_;

  // Additional fields parsed from the pdb stream.
  uint32_t index_;
};

class LeafVTShape {
 public:
  LeafVTShape();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::LeafVTShape& body() const { return body_; }
  // @}

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::LeafVTShape body_;
};

class MethodListRecord {
 public:
  MethodListRecord();

  // @name Accessors.
  // @{
  const Microsoft_Cci_Pdb::mlMethod& body() const { return body_; }
  uint32_t vbaseoff() const { return vbaseoff_; }
  LeafMemberAttributeField attr() const { return {body_.attr}; }
  // @}

  bool has_vbaseoff() const {
    return (attr().mprop == Microsoft_Cci_Pdb::CV_MTintro ||
            attr().mprop == Microsoft_Cci_Pdb::CV_MTpureintro);
  }

  // Initializes the class from the given pdb stream.
  // @param stream pointer to the pdb stream.
  // @returns true on success, false on failure.
  bool Initialize(PdbStream* stream);

 private:
  // The struct from CVInfo.h which represents this record.
  Microsoft_Cci_Pdb::mlMethod body_;

  // Additional fields parsed from the pdb stream.
  uint32_t vbaseoff_;
};

}  // namespace pdb

#endif  // SYZYGY_PDB_GEN_PDB_TYPE_INFO_RECORDS_H_
