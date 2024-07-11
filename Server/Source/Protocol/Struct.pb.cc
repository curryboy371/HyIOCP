// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Struct.proto

#include "Struct.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace Protocol {
PROTOBUF_CONSTEXPR hyps_user_info::hyps_user_info(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.name_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.id_)*/uint64_t{0u}
  , /*decltype(_impl_.user_type_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct hyps_user_infoDefaultTypeInternal {
  PROTOBUF_CONSTEXPR hyps_user_infoDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~hyps_user_infoDefaultTypeInternal() {}
  union {
    hyps_user_info _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 hyps_user_infoDefaultTypeInternal _hyps_user_info_default_instance_;
PROTOBUF_CONSTEXPR hyps_pos_info::hyps_pos_info(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.object_id_)*/uint64_t{0u}
  , /*decltype(_impl_.x_)*/0
  , /*decltype(_impl_.y_)*/0
  , /*decltype(_impl_.z_)*/0
  , /*decltype(_impl_.yaw_)*/0
  , /*decltype(_impl_.move_state_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct hyps_pos_infoDefaultTypeInternal {
  PROTOBUF_CONSTEXPR hyps_pos_infoDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~hyps_pos_infoDefaultTypeInternal() {}
  union {
    hyps_pos_info _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 hyps_pos_infoDefaultTypeInternal _hyps_pos_info_default_instance_;
PROTOBUF_CONSTEXPR hyps_object_info::hyps_object_info(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.pos_info_)*/nullptr
  , /*decltype(_impl_.object_id_)*/uint64_t{0u}
  , /*decltype(_impl_.object_type_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct hyps_object_infoDefaultTypeInternal {
  PROTOBUF_CONSTEXPR hyps_object_infoDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~hyps_object_infoDefaultTypeInternal() {}
  union {
    hyps_object_info _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 hyps_object_infoDefaultTypeInternal _hyps_object_info_default_instance_;
}  // namespace Protocol
static ::_pb::Metadata file_level_metadata_Struct_2eproto[3];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_Struct_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_Struct_2eproto = nullptr;

const uint32_t TableStruct_Struct_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::hyps_user_info, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Protocol::hyps_user_info, _impl_.id_),
  PROTOBUF_FIELD_OFFSET(::Protocol::hyps_user_info, _impl_.name_),
  PROTOBUF_FIELD_OFFSET(::Protocol::hyps_user_info, _impl_.user_type_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::hyps_pos_info, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Protocol::hyps_pos_info, _impl_.object_id_),
  PROTOBUF_FIELD_OFFSET(::Protocol::hyps_pos_info, _impl_.x_),
  PROTOBUF_FIELD_OFFSET(::Protocol::hyps_pos_info, _impl_.y_),
  PROTOBUF_FIELD_OFFSET(::Protocol::hyps_pos_info, _impl_.z_),
  PROTOBUF_FIELD_OFFSET(::Protocol::hyps_pos_info, _impl_.yaw_),
  PROTOBUF_FIELD_OFFSET(::Protocol::hyps_pos_info, _impl_.move_state_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::hyps_object_info, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Protocol::hyps_object_info, _impl_.object_id_),
  PROTOBUF_FIELD_OFFSET(::Protocol::hyps_object_info, _impl_.object_type_),
  PROTOBUF_FIELD_OFFSET(::Protocol::hyps_object_info, _impl_.pos_info_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::Protocol::hyps_user_info)},
  { 9, -1, -1, sizeof(::Protocol::hyps_pos_info)},
  { 21, -1, -1, sizeof(::Protocol::hyps_object_info)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::Protocol::_hyps_user_info_default_instance_._instance,
  &::Protocol::_hyps_pos_info_default_instance_._instance,
  &::Protocol::_hyps_object_info_default_instance_._instance,
};

const char descriptor_table_protodef_Struct_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\014Struct.proto\022\010Protocol\032\nEnum.proto\"R\n\016"
  "hyps_user_info\022\n\n\002id\030\001 \001(\004\022\014\n\004name\030\002 \001(\t"
  "\022&\n\tuser_type\030\003 \001(\0162\023.Protocol.hype_user"
  "\"\177\n\rhyps_pos_info\022\021\n\tobject_id\030\001 \001(\004\022\t\n\001"
  "x\030\002 \001(\002\022\t\n\001y\030\003 \001(\002\022\t\n\001z\030\004 \001(\002\022\013\n\003yaw\030\005 \001"
  "(\002\022-\n\nmove_state\030\006 \001(\0162\031.Protocol.hype_m"
  "ove_state\"\201\001\n\020hyps_object_info\022\021\n\tobject"
  "_id\030\001 \001(\004\022/\n\013object_type\030\002 \001(\0162\032.Protoco"
  "l.hype_object_type\022)\n\010pos_info\030\003 \001(\0132\027.P"
  "rotocol.hyps_pos_infob\006proto3"
  ;
static const ::_pbi::DescriptorTable* const descriptor_table_Struct_2eproto_deps[1] = {
  &::descriptor_table_Enum_2eproto,
};
static ::_pbi::once_flag descriptor_table_Struct_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_Struct_2eproto = {
    false, false, 389, descriptor_table_protodef_Struct_2eproto,
    "Struct.proto",
    &descriptor_table_Struct_2eproto_once, descriptor_table_Struct_2eproto_deps, 1, 3,
    schemas, file_default_instances, TableStruct_Struct_2eproto::offsets,
    file_level_metadata_Struct_2eproto, file_level_enum_descriptors_Struct_2eproto,
    file_level_service_descriptors_Struct_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_Struct_2eproto_getter() {
  return &descriptor_table_Struct_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_Struct_2eproto(&descriptor_table_Struct_2eproto);
namespace Protocol {

// ===================================================================

class hyps_user_info::_Internal {
 public:
};

hyps_user_info::hyps_user_info(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Protocol.hyps_user_info)
}
hyps_user_info::hyps_user_info(const hyps_user_info& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  hyps_user_info* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.name_){}
    , decltype(_impl_.id_){}
    , decltype(_impl_.user_type_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.name_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_name().empty()) {
    _this->_impl_.name_.Set(from._internal_name(), 
      _this->GetArenaForAllocation());
  }
  ::memcpy(&_impl_.id_, &from._impl_.id_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.user_type_) -
    reinterpret_cast<char*>(&_impl_.id_)) + sizeof(_impl_.user_type_));
  // @@protoc_insertion_point(copy_constructor:Protocol.hyps_user_info)
}

inline void hyps_user_info::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.name_){}
    , decltype(_impl_.id_){uint64_t{0u}}
    , decltype(_impl_.user_type_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.name_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

hyps_user_info::~hyps_user_info() {
  // @@protoc_insertion_point(destructor:Protocol.hyps_user_info)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void hyps_user_info::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.name_.Destroy();
}

void hyps_user_info::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void hyps_user_info::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.hyps_user_info)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.name_.ClearToEmpty();
  ::memset(&_impl_.id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.user_type_) -
      reinterpret_cast<char*>(&_impl_.id_)) + sizeof(_impl_.user_type_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* hyps_user_info::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint64 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string name = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_name();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "Protocol.hyps_user_info.name"));
        } else
          goto handle_unusual;
        continue;
      // .Protocol.hype_user user_type = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_user_type(static_cast<::Protocol::hype_user>(val));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* hyps_user_info::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.hyps_user_info)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint64 id = 1;
  if (this->_internal_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt64ToArray(1, this->_internal_id(), target);
  }

  // string name = 2;
  if (!this->_internal_name().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_name().data(), static_cast<int>(this->_internal_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Protocol.hyps_user_info.name");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_name(), target);
  }

  // .Protocol.hype_user user_type = 3;
  if (this->_internal_user_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
      3, this->_internal_user_type(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.hyps_user_info)
  return target;
}

size_t hyps_user_info::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.hyps_user_info)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string name = 2;
  if (!this->_internal_name().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_name());
  }

  // uint64 id = 1;
  if (this->_internal_id() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_id());
  }

  // .Protocol.hype_user user_type = 3;
  if (this->_internal_user_type() != 0) {
    total_size += 1 +
      ::_pbi::WireFormatLite::EnumSize(this->_internal_user_type());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData hyps_user_info::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    hyps_user_info::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*hyps_user_info::GetClassData() const { return &_class_data_; }


void hyps_user_info::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<hyps_user_info*>(&to_msg);
  auto& from = static_cast<const hyps_user_info&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Protocol.hyps_user_info)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_name().empty()) {
    _this->_internal_set_name(from._internal_name());
  }
  if (from._internal_id() != 0) {
    _this->_internal_set_id(from._internal_id());
  }
  if (from._internal_user_type() != 0) {
    _this->_internal_set_user_type(from._internal_user_type());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void hyps_user_info::CopyFrom(const hyps_user_info& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.hyps_user_info)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool hyps_user_info::IsInitialized() const {
  return true;
}

void hyps_user_info::InternalSwap(hyps_user_info* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.name_, lhs_arena,
      &other->_impl_.name_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(hyps_user_info, _impl_.user_type_)
      + sizeof(hyps_user_info::_impl_.user_type_)
      - PROTOBUF_FIELD_OFFSET(hyps_user_info, _impl_.id_)>(
          reinterpret_cast<char*>(&_impl_.id_),
          reinterpret_cast<char*>(&other->_impl_.id_));
}

::PROTOBUF_NAMESPACE_ID::Metadata hyps_user_info::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Struct_2eproto_getter, &descriptor_table_Struct_2eproto_once,
      file_level_metadata_Struct_2eproto[0]);
}

// ===================================================================

class hyps_pos_info::_Internal {
 public:
};

hyps_pos_info::hyps_pos_info(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Protocol.hyps_pos_info)
}
hyps_pos_info::hyps_pos_info(const hyps_pos_info& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  hyps_pos_info* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.object_id_){}
    , decltype(_impl_.x_){}
    , decltype(_impl_.y_){}
    , decltype(_impl_.z_){}
    , decltype(_impl_.yaw_){}
    , decltype(_impl_.move_state_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&_impl_.object_id_, &from._impl_.object_id_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.move_state_) -
    reinterpret_cast<char*>(&_impl_.object_id_)) + sizeof(_impl_.move_state_));
  // @@protoc_insertion_point(copy_constructor:Protocol.hyps_pos_info)
}

inline void hyps_pos_info::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.object_id_){uint64_t{0u}}
    , decltype(_impl_.x_){0}
    , decltype(_impl_.y_){0}
    , decltype(_impl_.z_){0}
    , decltype(_impl_.yaw_){0}
    , decltype(_impl_.move_state_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

hyps_pos_info::~hyps_pos_info() {
  // @@protoc_insertion_point(destructor:Protocol.hyps_pos_info)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void hyps_pos_info::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void hyps_pos_info::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void hyps_pos_info::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.hyps_pos_info)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&_impl_.object_id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.move_state_) -
      reinterpret_cast<char*>(&_impl_.object_id_)) + sizeof(_impl_.move_state_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* hyps_pos_info::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint64 object_id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.object_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // float x = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 21)) {
          _impl_.x_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // float y = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 29)) {
          _impl_.y_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // float z = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 37)) {
          _impl_.z_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // float yaw = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 45)) {
          _impl_.yaw_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // .Protocol.hype_move_state move_state = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 48)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_move_state(static_cast<::Protocol::hype_move_state>(val));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* hyps_pos_info::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.hyps_pos_info)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint64 object_id = 1;
  if (this->_internal_object_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt64ToArray(1, this->_internal_object_id(), target);
  }

  // float x = 2;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_x = this->_internal_x();
  uint32_t raw_x;
  memcpy(&raw_x, &tmp_x, sizeof(tmp_x));
  if (raw_x != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(2, this->_internal_x(), target);
  }

  // float y = 3;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_y = this->_internal_y();
  uint32_t raw_y;
  memcpy(&raw_y, &tmp_y, sizeof(tmp_y));
  if (raw_y != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(3, this->_internal_y(), target);
  }

  // float z = 4;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_z = this->_internal_z();
  uint32_t raw_z;
  memcpy(&raw_z, &tmp_z, sizeof(tmp_z));
  if (raw_z != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(4, this->_internal_z(), target);
  }

  // float yaw = 5;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_yaw = this->_internal_yaw();
  uint32_t raw_yaw;
  memcpy(&raw_yaw, &tmp_yaw, sizeof(tmp_yaw));
  if (raw_yaw != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(5, this->_internal_yaw(), target);
  }

  // .Protocol.hype_move_state move_state = 6;
  if (this->_internal_move_state() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
      6, this->_internal_move_state(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.hyps_pos_info)
  return target;
}

size_t hyps_pos_info::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.hyps_pos_info)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // uint64 object_id = 1;
  if (this->_internal_object_id() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_object_id());
  }

  // float x = 2;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_x = this->_internal_x();
  uint32_t raw_x;
  memcpy(&raw_x, &tmp_x, sizeof(tmp_x));
  if (raw_x != 0) {
    total_size += 1 + 4;
  }

  // float y = 3;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_y = this->_internal_y();
  uint32_t raw_y;
  memcpy(&raw_y, &tmp_y, sizeof(tmp_y));
  if (raw_y != 0) {
    total_size += 1 + 4;
  }

  // float z = 4;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_z = this->_internal_z();
  uint32_t raw_z;
  memcpy(&raw_z, &tmp_z, sizeof(tmp_z));
  if (raw_z != 0) {
    total_size += 1 + 4;
  }

  // float yaw = 5;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_yaw = this->_internal_yaw();
  uint32_t raw_yaw;
  memcpy(&raw_yaw, &tmp_yaw, sizeof(tmp_yaw));
  if (raw_yaw != 0) {
    total_size += 1 + 4;
  }

  // .Protocol.hype_move_state move_state = 6;
  if (this->_internal_move_state() != 0) {
    total_size += 1 +
      ::_pbi::WireFormatLite::EnumSize(this->_internal_move_state());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData hyps_pos_info::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    hyps_pos_info::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*hyps_pos_info::GetClassData() const { return &_class_data_; }


void hyps_pos_info::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<hyps_pos_info*>(&to_msg);
  auto& from = static_cast<const hyps_pos_info&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Protocol.hyps_pos_info)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_object_id() != 0) {
    _this->_internal_set_object_id(from._internal_object_id());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_x = from._internal_x();
  uint32_t raw_x;
  memcpy(&raw_x, &tmp_x, sizeof(tmp_x));
  if (raw_x != 0) {
    _this->_internal_set_x(from._internal_x());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_y = from._internal_y();
  uint32_t raw_y;
  memcpy(&raw_y, &tmp_y, sizeof(tmp_y));
  if (raw_y != 0) {
    _this->_internal_set_y(from._internal_y());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_z = from._internal_z();
  uint32_t raw_z;
  memcpy(&raw_z, &tmp_z, sizeof(tmp_z));
  if (raw_z != 0) {
    _this->_internal_set_z(from._internal_z());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_yaw = from._internal_yaw();
  uint32_t raw_yaw;
  memcpy(&raw_yaw, &tmp_yaw, sizeof(tmp_yaw));
  if (raw_yaw != 0) {
    _this->_internal_set_yaw(from._internal_yaw());
  }
  if (from._internal_move_state() != 0) {
    _this->_internal_set_move_state(from._internal_move_state());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void hyps_pos_info::CopyFrom(const hyps_pos_info& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.hyps_pos_info)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool hyps_pos_info::IsInitialized() const {
  return true;
}

void hyps_pos_info::InternalSwap(hyps_pos_info* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(hyps_pos_info, _impl_.move_state_)
      + sizeof(hyps_pos_info::_impl_.move_state_)
      - PROTOBUF_FIELD_OFFSET(hyps_pos_info, _impl_.object_id_)>(
          reinterpret_cast<char*>(&_impl_.object_id_),
          reinterpret_cast<char*>(&other->_impl_.object_id_));
}

::PROTOBUF_NAMESPACE_ID::Metadata hyps_pos_info::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Struct_2eproto_getter, &descriptor_table_Struct_2eproto_once,
      file_level_metadata_Struct_2eproto[1]);
}

// ===================================================================

class hyps_object_info::_Internal {
 public:
  static const ::Protocol::hyps_pos_info& pos_info(const hyps_object_info* msg);
};

const ::Protocol::hyps_pos_info&
hyps_object_info::_Internal::pos_info(const hyps_object_info* msg) {
  return *msg->_impl_.pos_info_;
}
hyps_object_info::hyps_object_info(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Protocol.hyps_object_info)
}
hyps_object_info::hyps_object_info(const hyps_object_info& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  hyps_object_info* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.pos_info_){nullptr}
    , decltype(_impl_.object_id_){}
    , decltype(_impl_.object_type_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if (from._internal_has_pos_info()) {
    _this->_impl_.pos_info_ = new ::Protocol::hyps_pos_info(*from._impl_.pos_info_);
  }
  ::memcpy(&_impl_.object_id_, &from._impl_.object_id_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.object_type_) -
    reinterpret_cast<char*>(&_impl_.object_id_)) + sizeof(_impl_.object_type_));
  // @@protoc_insertion_point(copy_constructor:Protocol.hyps_object_info)
}

inline void hyps_object_info::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.pos_info_){nullptr}
    , decltype(_impl_.object_id_){uint64_t{0u}}
    , decltype(_impl_.object_type_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

hyps_object_info::~hyps_object_info() {
  // @@protoc_insertion_point(destructor:Protocol.hyps_object_info)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void hyps_object_info::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  if (this != internal_default_instance()) delete _impl_.pos_info_;
}

void hyps_object_info::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void hyps_object_info::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.hyps_object_info)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (GetArenaForAllocation() == nullptr && _impl_.pos_info_ != nullptr) {
    delete _impl_.pos_info_;
  }
  _impl_.pos_info_ = nullptr;
  ::memset(&_impl_.object_id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.object_type_) -
      reinterpret_cast<char*>(&_impl_.object_id_)) + sizeof(_impl_.object_type_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* hyps_object_info::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint64 object_id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.object_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // .Protocol.hype_object_type object_type = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_object_type(static_cast<::Protocol::hype_object_type>(val));
        } else
          goto handle_unusual;
        continue;
      // .Protocol.hyps_pos_info pos_info = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          ptr = ctx->ParseMessage(_internal_mutable_pos_info(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* hyps_object_info::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.hyps_object_info)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint64 object_id = 1;
  if (this->_internal_object_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt64ToArray(1, this->_internal_object_id(), target);
  }

  // .Protocol.hype_object_type object_type = 2;
  if (this->_internal_object_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
      2, this->_internal_object_type(), target);
  }

  // .Protocol.hyps_pos_info pos_info = 3;
  if (this->_internal_has_pos_info()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(3, _Internal::pos_info(this),
        _Internal::pos_info(this).GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.hyps_object_info)
  return target;
}

size_t hyps_object_info::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.hyps_object_info)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .Protocol.hyps_pos_info pos_info = 3;
  if (this->_internal_has_pos_info()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *_impl_.pos_info_);
  }

  // uint64 object_id = 1;
  if (this->_internal_object_id() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_object_id());
  }

  // .Protocol.hype_object_type object_type = 2;
  if (this->_internal_object_type() != 0) {
    total_size += 1 +
      ::_pbi::WireFormatLite::EnumSize(this->_internal_object_type());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData hyps_object_info::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    hyps_object_info::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*hyps_object_info::GetClassData() const { return &_class_data_; }


void hyps_object_info::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<hyps_object_info*>(&to_msg);
  auto& from = static_cast<const hyps_object_info&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Protocol.hyps_object_info)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_has_pos_info()) {
    _this->_internal_mutable_pos_info()->::Protocol::hyps_pos_info::MergeFrom(
        from._internal_pos_info());
  }
  if (from._internal_object_id() != 0) {
    _this->_internal_set_object_id(from._internal_object_id());
  }
  if (from._internal_object_type() != 0) {
    _this->_internal_set_object_type(from._internal_object_type());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void hyps_object_info::CopyFrom(const hyps_object_info& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.hyps_object_info)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool hyps_object_info::IsInitialized() const {
  return true;
}

void hyps_object_info::InternalSwap(hyps_object_info* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(hyps_object_info, _impl_.object_type_)
      + sizeof(hyps_object_info::_impl_.object_type_)
      - PROTOBUF_FIELD_OFFSET(hyps_object_info, _impl_.pos_info_)>(
          reinterpret_cast<char*>(&_impl_.pos_info_),
          reinterpret_cast<char*>(&other->_impl_.pos_info_));
}

::PROTOBUF_NAMESPACE_ID::Metadata hyps_object_info::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Struct_2eproto_getter, &descriptor_table_Struct_2eproto_once,
      file_level_metadata_Struct_2eproto[2]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Protocol
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Protocol::hyps_user_info*
Arena::CreateMaybeMessage< ::Protocol::hyps_user_info >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::hyps_user_info >(arena);
}
template<> PROTOBUF_NOINLINE ::Protocol::hyps_pos_info*
Arena::CreateMaybeMessage< ::Protocol::hyps_pos_info >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::hyps_pos_info >(arena);
}
template<> PROTOBUF_NOINLINE ::Protocol::hyps_object_info*
Arena::CreateMaybeMessage< ::Protocol::hyps_object_info >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::hyps_object_info >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
