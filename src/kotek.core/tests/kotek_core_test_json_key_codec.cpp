// The explicit short-form API avoids any PCH/include-order dependency and
// lets the default Debug boot prove compact encoding + full-key fallback.
#include "../include/kotek_core.h"
#include <kotek.core.containers.json/include/kotek_json_key_codec.h>
#include <gtest/gtest.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#if defined(KOTEK_USE_TESTS) && defined(KOTEK_DEBUG)

TEST(JsonKeyCodec, CompactEncodingIsStableAndBounded)
{
	const auto first = json_key_encode_short("render_passes_editor");
	const auto second = json_key_encode_short("render_passes_editor");
	const auto other = json_key_encode_short("render_passes_game");

	EXPECT_EQ(first.size(), KOTEK_DEF_JSON_KEY_SHORT_LENGTH);
	EXPECT_STREQ(first.c_str(), second.c_str());
	EXPECT_STRNE(first.c_str(), other.c_str());
	EXPECT_STRNE(first.c_str(), "render_passes_editor");
	static_assert(json_key_char(0u, 0u) == 'a',
		"the base32 alphabet is a compile-time contract");
}

TEST(JsonKeyCodec, WriteReadAndLegacyFallback)
{
	const auto encoded = json_key_encode_short("render_passes_editor");
	kun_ktk json::object document;
	document[encoded.c_str()] = 42;

	auto it = json_key_find_short(document, "render_passes_editor");
	ASSERT_NE(it, document.end());
	EXPECT_EQ(it->value().as_int64(), 42);
	EXPECT_EQ(document.find("render_passes_editor"), document.end());

	// An old full-key document still resolves through the same fallback.
	kun_ktk json::object legacy;
	legacy["render_passes_editor"] = 7;
	EXPECT_NE(json_key_find_short(legacy, "render_passes_editor"), legacy.end());
}

TEST(JsonKeyCodec, CurrentConfigKeysHaveNoCollisions)
{
	constexpr const char* keys[] = {
		"render_passes_editor", "render_passes_game", "render_passes",
		"add_required_components_automatically", "sphere_bounding_box_quality",
		"show_pass_manager_on_start", "graphics_development",
		"sdk_camera_rotation_quaternion", "sdk_camera_input_bootstrap",
		"localization_editor_language", "localization_game_language",
		"render_geometry_path", "language", "entries", "InitializeCallback",
		"ShutdownCallback", "UpdateCallback", "InitializeCallback_Render",
		"UserLibraryName"};

	ktk_cstring<KOTEK_DEF_RESOURCE_TEXT_KEY_FIELD_NAME_LENGTH>
		encoded[sizeof(keys) / sizeof(keys[0])]{};
	constexpr size_t count = sizeof(keys) / sizeof(keys[0]);

	for (size_t first = 0; first < count; ++first)
	{
		encoded[first] = json_key_encode_short(keys[first]);
		EXPECT_EQ(encoded[first].size(), KOTEK_DEF_JSON_KEY_SHORT_LENGTH)
			<< keys[first];
		for (size_t previous = 0; previous < first; ++previous)
		{
			EXPECT_STRNE(encoded[first].c_str(), encoded[previous].c_str())
				<< keys[first] << " collides with " << keys[previous];
		}
	}
}

#endif

void RegisterTests_JsonKeyCodec_ForModule_Core(void)
{
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
