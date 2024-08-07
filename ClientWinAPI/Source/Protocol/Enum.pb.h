// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Enum.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021008 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Enum_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Enum_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Enum_2eproto;
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE
namespace Protocol {

enum hype_user : int {
  user_none = 0,
  user_master = 1,
  user_normal = 2,
  hype_user_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  hype_user_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool hype_user_IsValid(int value);
constexpr hype_user hype_user_MIN = user_none;
constexpr hype_user hype_user_MAX = user_normal;
constexpr int hype_user_ARRAYSIZE = hype_user_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* hype_user_descriptor();
template<typename T>
inline const std::string& hype_user_Name(T enum_t_value) {
  static_assert(::std::is_same<T, hype_user>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function hype_user_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    hype_user_descriptor(), enum_t_value);
}
inline bool hype_user_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, hype_user* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<hype_user>(
    hype_user_descriptor(), name, value);
}
enum hype_move_state : int {
  move_state_none = 0,
  move_state_idle = 1,
  move_state_run = 2,
  hype_move_state_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  hype_move_state_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool hype_move_state_IsValid(int value);
constexpr hype_move_state hype_move_state_MIN = move_state_none;
constexpr hype_move_state hype_move_state_MAX = move_state_run;
constexpr int hype_move_state_ARRAYSIZE = hype_move_state_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* hype_move_state_descriptor();
template<typename T>
inline const std::string& hype_move_state_Name(T enum_t_value) {
  static_assert(::std::is_same<T, hype_move_state>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function hype_move_state_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    hype_move_state_descriptor(), enum_t_value);
}
inline bool hype_move_state_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, hype_move_state* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<hype_move_state>(
    hype_move_state_descriptor(), name, value);
}
enum hype_object_type : int {
  none = 0,
  creature = 1,
  projectile = 2,
  env = 3,
  hype_object_type_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  hype_object_type_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool hype_object_type_IsValid(int value);
constexpr hype_object_type hype_object_type_MIN = none;
constexpr hype_object_type hype_object_type_MAX = env;
constexpr int hype_object_type_ARRAYSIZE = hype_object_type_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* hype_object_type_descriptor();
template<typename T>
inline const std::string& hype_object_type_Name(T enum_t_value) {
  static_assert(::std::is_same<T, hype_object_type>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function hype_object_type_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    hype_object_type_descriptor(), enum_t_value);
}
inline bool hype_object_type_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, hype_object_type* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<hype_object_type>(
    hype_object_type_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Protocol

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::Protocol::hype_user> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::hype_user>() {
  return ::Protocol::hype_user_descriptor();
}
template <> struct is_proto_enum< ::Protocol::hype_move_state> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::hype_move_state>() {
  return ::Protocol::hype_move_state_descriptor();
}
template <> struct is_proto_enum< ::Protocol::hype_object_type> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::hype_object_type>() {
  return ::Protocol::hype_object_type_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto
