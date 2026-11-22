#pragma once

/// \file kotek_json_key_codec.h
/// \~english one key-encoding contract for every JSON-backed configuration:
/// Debug keeps the full human-readable key; Release emits a short base32 key
/// (4 chars by default, 3 or 4 selectable in CMake). Reads always try the
/// encoded key first and the full key second, so old and new files interoperate.
/// This is a stable FNV-1a encoding, not a truncation (which would collide
/// e.g. render_passes_editor with render_passes_game). Arbitrary asset keys
/// (gltf fields, localization text ids) deliberately do NOT pass through it.

#include <kotek.core.containers.json/include/kotek_std_alias_json.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>

#ifndef KOTEK_DEF_JSON_KEY_SHORT_LENGTH
	#define KOTEK_DEF_JSON_KEY_SHORT_LENGTH 4
#endif
static_assert(KOTEK_DEF_JSON_KEY_SHORT_LENGTH == 3 ||
		KOTEK_DEF_JSON_KEY_SHORT_LENGTH == 4,
	"short json keys support 3 or 4 characters (CMake: KOTEK_JSON_KEY_SHORT_LENGTH)");

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

/// \~english constexpr FNV-1a-1 over the FULL key. Public for compile-time
/// regression pins; the encoded form is derived from these exact bytes.
constexpr kun_ktk uint32_t json_key_hash(const char* p_key) noexcept
{
	kun_ktk uint32_t hash = 2166136261u;
	if (p_key == nullptr)
		return 0u;
	for (const unsigned char* p = reinterpret_cast<const unsigned char*>(p_key);
		 *p != 0; ++p)
	{
		hash ^= static_cast<kun_ktk uint32_t>(*p);
		hash *= 16777619u;
	}
	return hash;
}

/// \~english one base32 output character, constexpr so key encoders can be
/// verified at compile time. Lowercase+digits keeps every key JSON-safe.
constexpr char json_key_char(kun_ktk uint32_t hash,
	kun_ktk uint8_t character_index) noexcept
{
	constexpr char alphabet[] = "abcdefghijklmnopqrstuvwxyz234567";
	return alphabet[(hash >> (character_index * 5u)) & 31u];
}

/// \~english always emit the short form (independent of PCH/configuration).
/// Useful for tests, tooling and callers that explicitly opt a document in.
inline ktk_cstring<KOTEK_DEF_RESOURCE_TEXT_KEY_FIELD_NAME_LENGTH>
json_key_encode_short(const char* p_key) noexcept
{
	ktk_cstring<KOTEK_DEF_RESOURCE_TEXT_KEY_FIELD_NAME_LENGTH> result;
	if (p_key == nullptr)
		return result;
	const kun_ktk uint32_t hash = json_key_hash(p_key);
	char encoded[KOTEK_DEF_JSON_KEY_SHORT_LENGTH + 1]{};
	for (kun_ktk uint8_t index = 0; index < KOTEK_DEF_JSON_KEY_SHORT_LENGTH;
		 ++index)
	{
		encoded[index] = json_key_char(hash, index);
	}
	result.assign(encoded, KOTEK_DEF_JSON_KEY_SHORT_LENGTH);
	return result;
}

/// \~english the key to WRITE. The return type is the existing fixed-capacity
/// string, so no dynamic container appears in either configuration.
inline ktk_cstring<KOTEK_DEF_RESOURCE_TEXT_KEY_FIELD_NAME_LENGTH>
json_key_encode(const char* p_key) noexcept
{
	ktk_cstring<KOTEK_DEF_RESOURCE_TEXT_KEY_FIELD_NAME_LENGTH> result;
	if (p_key == nullptr)
		return result;

#if defined(KOTEK_USE_JSON_SHORT_KEYS)
	result = json_key_encode_short(p_key);
#else
	result.assign(p_key);
#endif
	return result;
}

/// \~english the key to READ: encoded first (new files), full key second
/// (legacy files). Works for Boost.JSON and the own backend's object type.
template <typename JsonObject>
auto json_key_find(const JsonObject& object, const char* p_key)
	-> decltype(object.end())
{
	const auto encoded = json_key_encode(p_key);
	auto it = object.find(encoded.c_str());
	if (it != object.end())
		return it;
	return object.find(p_key);
}

/// \~english explicit short-form lookup with the same legacy fallback.
template <typename JsonObject>
auto json_key_find_short(const JsonObject& object, const char* p_key)
	-> decltype(object.end())
{
	const auto encoded = json_key_encode_short(p_key);
	auto it = object.find(encoded.c_str());
	if (it != object.end())
		return it;
	return object.find(p_key);
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
