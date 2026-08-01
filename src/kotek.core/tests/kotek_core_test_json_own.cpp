#include "../include/kotek_core.h"

#if defined(KOTEK_USE_TESTS) && defined(KOTEK_DEBUG)
	#include <gtest/gtest.h>

	#include <cmath>
	#include <cstdio>
	#include <cstdint>
	#include <cstring>
	#include <limits>
	#include <string>
	#include <vector>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#if defined(KOTEK_USE_TESTS) && defined(KOTEK_DEBUG)
	#if defined(KOTEK_USE_JSON_LIBRARY_KOTEK_OWN)

// Functional proofs for kotek's own json backend (task K4,
// KOTEK_JSON_LIBRARY=KOTEK_OWN): DOM round trips, streaming
// reader/writer equivalence with the DOM, malformed-input robustness
// (every failure is an error_code, never a crash/exception), number
// edge cases and graceful resource exhaustion. The suite compiles to
// nothing under the boost backend — the boost parity of the shared
// call-site surface is covered by kotek_core_test_json.cpp.

namespace
{
	namespace kjson = kun_ktk json;

	void append_to_std_string(void* p_user, kjson::string_view chunk)
	{
		static_cast<std::string*>(p_user)
			->append(chunk.data(), chunk.size());
	}

	kjson::value parse_or_fail(
		kjson::string_view text, const char* p_what)
	{
		kjson::error_code code;
		kjson::value result = kjson::parse(text, code);

		EXPECT_TRUE(!code) << p_what << " failed with: "
		                   << code.message();

		return result;
	}

	std::string serialize_to_std(const kjson::value& data)
	{
		const kjson::string text = kjson::serialize(data);
		return std::string(text.data(), text.size());
	}

	std::string serialize_to_std(const kjson::object& data)
	{
		const kjson::string text = kjson::serialize(data);
		return std::string(text.data(), text.size());
	}

	/// records the whole event stream as text tokens; two feeds of
	/// the same document must produce identical logs regardless of
	/// chunking
	class recording_handler : public kjson::stream_handler
	{
	public:
		recording_handler(std::vector<std::string>& log) :
			m_log(log)
		{
		}

		bool on_object_begin(void) override
		{
			this->m_log.push_back("ob");
			return true;
		}

		bool on_object_end(void) override
		{
			this->m_log.push_back("oe");
			return true;
		}

		bool on_array_begin(void) override
		{
			this->m_log.push_back("ab");
			return true;
		}

		bool on_array_end(void) override
		{
			this->m_log.push_back("ae");
			return true;
		}

		bool on_key(kjson::string_view key) override
		{
			this->m_log.push_back(
				std::string("k:") +
				std::string(key.data(), key.size()));
			return true;
		}

		bool on_string(kjson::string_view data) override
		{
			this->m_log.push_back(
				std::string("s:") +
				std::string(data.data(), data.size()));
			return true;
		}

		bool on_null(void) override
		{
			this->m_log.push_back("n");
			return true;
		}

		bool on_bool(bool data) override
		{
			this->m_log.push_back(data ? "b:1" : "b:0");
			return true;
		}

		bool on_int64(std::int64_t data) override
		{
			char text[32];
			snprintf(text, sizeof(text), "i:%lld", data);
			this->m_log.push_back(text);
			return true;
		}

		bool on_uint64(std::uint64_t data) override
		{
			char text[32];
			snprintf(text, sizeof(text), "u:%llu", data);
			this->m_log.push_back(text);
			return true;
		}

		bool on_double(double data) override
		{
			char text[40];
			snprintf(text, sizeof(text), "d:%.17g", data);
			this->m_log.push_back(text);
			return true;
		}

	private:
		std::vector<std::string>& m_log;
	};

	/// re-emits every event through a stream_writer — the output must
	/// be byte-identical to the serializer's canonical text
	class reemit_handler : public kjson::stream_handler
	{
	public:
		reemit_handler(kjson::stream_writer& writer) :
			m_writer(writer)
		{
		}

		bool on_object_begin(void) override
		{
			return this->m_writer.on_object_begin();
		}

		bool on_object_end(void) override
		{
			return this->m_writer.on_object_end();
		}

		bool on_array_begin(void) override
		{
			return this->m_writer.on_array_begin();
		}

		bool on_array_end(void) override
		{
			return this->m_writer.on_array_end();
		}

		bool on_key(kjson::string_view key) override
		{
			return this->m_writer.on_key(key);
		}

		bool on_string(kjson::string_view data) override
		{
			return this->m_writer.on_string(data);
		}

		bool on_null(void) override
		{
			return this->m_writer.on_null();
		}

		bool on_bool(bool data) override
		{
			return this->m_writer.on_bool(data);
		}

		bool on_int64(std::int64_t data) override
		{
			return this->m_writer.on_int64(data);
		}

		bool on_uint64(std::uint64_t data) override
		{
			return this->m_writer.on_uint64(data);
		}

		bool on_double(double data) override
		{
			return this->m_writer.on_double(data);
		}

	private:
		kjson::stream_writer& m_writer;
	};

	/// the large deterministic document shared by the streaming
	/// equivalence tests (mixed kinds, escapes, nesting)
	std::string generate_big_document(int key_count)
	{
		std::string text;

		char scratch[512];
		kjson::stream_writer writer(
			scratch, sizeof(scratch), &append_to_std_string, &text);

		bool status = writer.on_object_begin();

		for (int i = 0; i < key_count && status; ++i)
		{
			char key[32];
			snprintf(key, sizeof(key), "key_%d", i);

			status = writer.on_key(key);

			switch (i % 7)
			{
			case 0:
				status = writer.on_int64(-i);
				break;
			case 1:
				status = writer.on_uint64(
					static_cast<std::uint64_t>(i) * 7);
				break;
			case 2:
				status = writer.on_double(i * 0.5);
				break;
			case 3:
				status = writer.on_string(
					"text with \"quotes\" and \\slashes\\");
				break;
			case 4:
				status = writer.on_bool((i % 2) == 0);
				break;
			case 5:
				status = writer.on_null();
				break;
			default:
				status = writer.on_array_begin() &&
					writer.on_int64(i) &&
					writer.on_string("x") &&
					writer.on_double(-0.25) &&
					writer.on_array_end();
				break;
			}
		}

		status = status && writer.on_object_end();

		EXPECT_TRUE(status);
		EXPECT_TRUE(writer.finish());

		return text;
	}
} // namespace

TEST(JsonOwn, test_dom_roundtrip)
{
	kjson::object root;

	root["null_field"] = kjson::value();
	root["bool_field"] = true;
	root["int_field"] = -42;
	root["uint_field"] = 42u;
	root["double_field"] = 0.125;
	root["string_field"] = "hello";

	kjson::object nested;
	nested["a"] = 1;
	nested["b"] = "two";
	root["object_field"] = nested;

	kjson::array items;
	items.push_back(1);
	items.push_back(2.5);
	items.push_back("three");
	items.push_back(false);
	root["array_field"] = items;

	kjson::value root_value(root);

	const std::string text = serialize_to_std(root_value);

	EXPECT_EQ(
		text,
		"{\"null_field\":null,\"bool_field\":true,\"int_"
		"field\":-42,\"uint_field\":42,\"double_field\":0."
		"125,\"string_field\":\"hello\",\"object_field\":{"
		"\"a\":1,\"b\":\"two\"},\"array_field\":[1,2.5,"
		"\"three\",false]}");

	kjson::value parsed = parse_or_fail(text, "dom roundtrip parse");

	EXPECT_TRUE(parsed == root_value);

	// a second round trip must reproduce the text byte-identically
	EXPECT_EQ(serialize_to_std(parsed), text);
}

TEST(JsonOwn, test_nesting_escapes_unicode)
{
	// deep nesting (32 levels, half the reader's cap): 32 opening
	// brackets build 31 single-element levels around one innermost
	// empty array
	std::string deep;
	for (int i = 0; i < 32; ++i)
		deep += '[';
	for (int i = 0; i < 32; ++i)
		deep += ']';

	kjson::value nested = parse_or_fail(deep, "deep nesting parse");

	const kjson::value* p_cursor = &nested;
	for (int i = 0; i < 31; ++i)
	{
		ASSERT_TRUE(p_cursor->is_array());
		ASSERT_EQ(p_cursor->as_array().size(), 1u);
		p_cursor = &p_cursor->as_array()[0];
	}
	EXPECT_TRUE(p_cursor->is_array());
	EXPECT_TRUE(p_cursor->as_array().empty());

	// every escape form, \uXXXX and a surrogate pair
	const char* p_escapes_doc =
		"{\"s\":\"a\\nb\\t\\\"q\\\"\\\\\\u0041\\u20ac\\ud83d\\ude00\"}";

	kjson::value escapes =
		parse_or_fail(p_escapes_doc, "escapes parse");

	const std::string expected =
		std::string("a\nb\t\"q\"\\A") +
		std::string("\xE2\x82\xAC") +
		std::string("\xF0\x9F\x98\x80");

	const kjson::string& parsed_string =
		escapes.as_object().at("s").as_string();

	EXPECT_EQ(
		std::string(parsed_string.data(), parsed_string.size()),
		expected);

	// raw utf-8 passes through untouched
	const char* p_utf8_doc = "{\"s\":\"h\xC3\xA9llo\xE2\x98\x83\"}";
	kjson::value utf8 = parse_or_fail(p_utf8_doc, "utf-8 parse");

	EXPECT_EQ(serialize_to_std(utf8), std::string(p_utf8_doc));

	// round trip stability for the escaped document
	kjson::value escapes_again =
		parse_or_fail(serialize_to_std(escapes), "escapes reparse");

	EXPECT_TRUE(escapes_again == escapes);
}

TEST(JsonOwn, test_malformed_inputs_graceful)
{
	struct malformed_case
	{
		const char* p_text;
		kjson::error expected;
	};

	const malformed_case cases[] = {
		{"{\"key\": \"val", kjson::error::unexpected_end_of_input},
		{"{\"key\": tru", kjson::error::unexpected_end_of_input},
		{"{\"key\": 12", kjson::error::unexpected_end_of_input},
		{"[1,2", kjson::error::unexpected_end_of_input},
		{"", kjson::error::unexpected_end_of_input},
		{"   ", kjson::error::unexpected_end_of_input},
		{"nul", kjson::error::unexpected_end_of_input},
		{"nulL", kjson::error::invalid_literal},
		{"{\"key\": @}", kjson::error::expected_value},
		{"{\"key\" 1}", kjson::error::expected_colon},
		{"[1 2]", kjson::error::expected_comma_or_end},
		{"{\"a\":1} extra", kjson::error::trailing_content},
		{"{\"a\":\"b\x01\"}", kjson::error::unexpected_character},
		{"{\"a\":\"b\\x\"}", kjson::error::invalid_escape},
		{"{\"a\":\"\\u12zz\"}", kjson::error::invalid_unicode_escape},
		{"{\"a\":\"\\udc00\"}", kjson::error::invalid_unicode_escape},
		{"{\"a\":\"\\ud800x\"}",
			kjson::error::invalid_unicode_escape},
		{"{\"a\":01}", kjson::error::invalid_number},
		{"{\"a\":1.}", kjson::error::invalid_number},
		{"{\"a\":-}", kjson::error::invalid_number},
		{"{\"a\":1e}", kjson::error::invalid_number},
		{"[1,2,]", kjson::error::expected_value},
		{"{\"a\":1,}", kjson::error::expected_key},
		{"{\"a\":truex}", kjson::error::expected_comma_or_end},
		{"]", kjson::error::expected_value},
		{"}", kjson::error::expected_value},
	};

	for (const malformed_case& test_case : cases)
	{
		kjson::error_code code;
		kjson::value result = kjson::parse(test_case.p_text, code);

		EXPECT_TRUE(static_cast<bool>(code))
			<< "expected an error for: " << test_case.p_text;
		EXPECT_EQ(code.value(), test_case.expected)
			<< "wrong error for: " << test_case.p_text;
		EXPECT_TRUE(result.is_null());
	}

	// depth overflow: one more level than the reader's cap
	{
		std::string too_deep;
		for (int i = 0; i <= KOTEK_DEF_OWN_JSON_STREAM_MAX_DEPTH; ++i)
			too_deep += '[';

		kjson::error_code code;
		kjson::parse(too_deep, code);

		EXPECT_TRUE(static_cast<bool>(code));
		EXPECT_EQ(code.value(), kjson::error::depth_exceeded);
	}

	// a string token that does not fit the assembly buffer (the
	// escape forces assembly — without one a single-chunk string is
	// delivered zero-copy and the buffer never engages)
	{
		std::string huge = "{\"s\":\"";
		huge.append(
			KOTEK_DEF_OWN_JSON_STREAM_TOKEN_BUFFER_SIZE + 64, 'a');
		huge += "\\n\"}";

		kjson::error_code code;
		kjson::parse(huge, code);

		EXPECT_TRUE(static_cast<bool>(code));
		EXPECT_EQ(code.value(), kjson::error::token_too_long);
	}

	// a number token that does not fit its buffer
	{
		std::string huge = "[";
		huge.append(
			KOTEK_DEF_OWN_JSON_STREAM_NUMBER_BUFFER_SIZE + 16, '7');
		huge += "]";

		kjson::error_code code;
		kjson::parse(huge, code);

		EXPECT_TRUE(static_cast<bool>(code));
		EXPECT_EQ(code.value(), kjson::error::token_too_long);
	}

	// trailing comma accepted only with the option enabled
	{
		kjson::parse_options options;
		options.allow_trailing_commas = true;

		kjson::error_code code;
		kjson::value result = kjson::parse(
			"{\"a\": [1, 2,], \"b\": 3,}", code, {}, options);

		EXPECT_TRUE(!code) << code.message();
		EXPECT_TRUE(result.is_object());
	}

	// comments accepted only with the option enabled
	{
		const char* p_doc = "/* header */ {\"a\": 1} // tail";

		kjson::error_code code;
		kjson::parse(p_doc, code);
		EXPECT_TRUE(static_cast<bool>(code));

		kjson::parse_options options;
		options.allow_comments = true;

		kjson::value result = kjson::parse(p_doc, code, {}, options);
		EXPECT_TRUE(!code) << code.message();
		EXPECT_TRUE(result.is_object());
	}
}

TEST(JsonOwn, test_number_edge_cases)
{
	struct integer_case
	{
		const char* p_text;
		bool is_signed;
		std::int64_t as_signed;
		std::uint64_t as_unsigned;
	};

	const integer_case integers[] = {
		{"0", true, 0, 0},
		{"1", true, 1, 1},
		{"-1", true, -1, 0},
		{"9223372036854775807", true, INT64_MAX, 0},
		{"-9223372036854775808", true, INT64_MIN, 0},
		{"9223372036854775808",
			false,
			0,
			9223372036854775808ull},
		{"18446744073709551615", false, 0, UINT64_MAX},
	};

	for (const integer_case& test_case : integers)
	{
		kjson::error_code code;
		kjson::value result = kjson::parse(test_case.p_text, code);

		ASSERT_TRUE(!code) << test_case.p_text;

		if (test_case.is_signed)
		{
			EXPECT_TRUE(result.is_int64()) << test_case.p_text;
			EXPECT_EQ(result.as_int64(), test_case.as_signed);
		}
		else
		{
			EXPECT_TRUE(result.is_uint64()) << test_case.p_text;
			EXPECT_EQ(result.as_uint64(), test_case.as_unsigned);
		}

		// integer text round trips exactly
		EXPECT_EQ(serialize_to_std(result), test_case.p_text);
	}

	// beyond uint64 the reader degrades to double
	{
		kjson::error_code code;
		kjson::value result =
			kjson::parse("18446744073709551616", code);

		ASSERT_TRUE(!code);
		EXPECT_TRUE(result.is_double());
		EXPECT_DOUBLE_EQ(result.as_double(), 1.8446744073709552e19);
	}

	// a negative integer zero loses its sign (same as boost: it
	// parses as the integer 0); the double form -0.0 keeps it
	{
		kjson::error_code code;
		kjson::value result = kjson::parse("-0", code);

		ASSERT_TRUE(!code);
		EXPECT_TRUE(result.is_int64());
		EXPECT_EQ(result.as_int64(), 0);
		EXPECT_EQ(serialize_to_std(result), "0");
	}

	// doubles: parse kind + value, then exact round-trip text
	struct double_case
	{
		const char* p_text;
		double data;
		const char* p_canonical;
	};

	const double_case doubles[] = {
		{"0.1", 0.1, "0.1"},
		{"1.0", 1.0, "1.0"},
		{"-2.5", -2.5, "-2.5"},
		{"1e2", 100.0, "100.0"},
		{"1.5e-7", 1.5e-7, "1.5e-07"},
		{"3.141592653589793", 3.141592653589793, "3.141592653589793"},
		{"1e-3", 0.001, "0.001"},
	};

	for (const double_case& test_case : doubles)
	{
		kjson::error_code code;
		kjson::value result = kjson::parse(test_case.p_text, code);

		ASSERT_TRUE(!code) << test_case.p_text;
		EXPECT_TRUE(result.is_double()) << test_case.p_text;
		EXPECT_DOUBLE_EQ(result.as_double(), test_case.data);
		EXPECT_EQ(serialize_to_std(result), test_case.p_canonical)
			<< test_case.p_text;
	}

	// kind stability: an integer-valued double keeps its kind
	// through a round trip (the engine reads component floats back
	// with as_double())
	{
		kjson::error_code code;
		kjson::value result = kjson::parse(
			serialize_to_std(kjson::value(42.0)), code);

		ASSERT_TRUE(!code);
		EXPECT_TRUE(result.is_double());
		EXPECT_DOUBLE_EQ(result.as_double(), 42.0);
	}

	// negative zero keeps its sign and kind
	{
		kjson::error_code code;
		kjson::value result = kjson::parse(
			serialize_to_std(kjson::value(-0.0)), code);

		ASSERT_TRUE(!code);
		EXPECT_TRUE(result.is_double());
		EXPECT_TRUE(std::signbit(result.as_double()));
	}

	// nan/inf degrade to null instead of crashing the writer
	{
		EXPECT_EQ(
			serialize_to_std(
				kjson::value(std::numeric_limits<double>::quiet_NaN())),
			"null");
		EXPECT_EQ(
			serialize_to_std(kjson::value(
				std::numeric_limits<double>::infinity())),
			"null");
	}
}

TEST(JsonOwn, test_static_resource_exhaustion_graceful)
{
	// a parse that cannot fit its DOM into the fixed buffer must
	// report resource_exhausted, not crash
	{
		unsigned char memory[96];
		kjson::static_resource resource(memory);
		kjson::storage_ptr sp(&resource);

		kjson::error_code code;
		kjson::parse(
			"{\"alpha\": \"some longer string value\", \"beta\": "
			"[1,2,3,4]}",
			code,
			sp);

		EXPECT_TRUE(resource.failed());
		EXPECT_TRUE(static_cast<bool>(code));
		EXPECT_EQ(code.value(), kjson::error::resource_exhausted);
	}

	// direct DOM building on a too-small resource: operations
	// degrade, the failed flag reports it, serialize stays safe
	{
		unsigned char memory[64];
		kjson::static_resource resource(memory);
		kjson::object object(&resource);

		for (int i = 0; i < 20; ++i)
		{
			char key[8];
			snprintf(key, sizeof(key), "%d", i);
			object[key] = i;
		}

		EXPECT_TRUE(resource.failed());

		const kjson::string text = kjson::serialize(object);
		(void)text;
	}

	// ktkJson's embedded layout degrades the same way: writes that
	// do not fit leave an empty/partial json whose Serialize simply
	// reports its status
	{
		ktkJson<64, false> tiny;

		for (int i = 0; i < 16; ++i)
		{
			char key[8];
			snprintf(key, sizeof(key), "k%d", i);
			tiny.Write(key, i);
		}

		kun_ktk cstring out;
		const bool status = tiny.Serialize(out);
		EXPECT_FALSE(status);
	}

	// a monotonic resource may grow past its initial buffer and the
	// parse then succeeds untouched
	{
		unsigned char memory[64];
		kjson::monotonic_resource resource(memory);
		kjson::storage_ptr sp(&resource);

		kjson::error_code code;
		kjson::value result = kjson::parse(
			"{\"alpha\": \"a fairly long string value here\", "
			"\"beta\": [1, 2, 3, 4, 5], \"gamma\": {\"x\": 1.5, "
			"\"y\": true}}",
			code,
			sp);

		EXPECT_TRUE(!code) << code.message();
		EXPECT_FALSE(resource.failed());

		ASSERT_TRUE(result.is_object());
		const kjson::object& object = result.as_object();
		ASSERT_EQ(object.size(), 3u);
		EXPECT_TRUE(
			object.at("alpha").as_string() ==
			"a fairly long string value here");
		EXPECT_EQ(object.at("beta").as_array().size(), 5u);
		EXPECT_TRUE(
			object.at("gamma").as_object().at("y").as_bool());
	}
}

TEST(JsonOwn, test_stream_reader_matches_dom_parse)
{
	constexpr int key_count = 2000;
	const std::string text = generate_big_document(key_count);

	kjson::error_code code;
	kjson::value dom = kjson::parse(text, code);

	ASSERT_TRUE(!code) << code.message();
	ASSERT_TRUE(dom.is_object());
	ASSERT_EQ(dom.as_object().size(),
		static_cast<size_t>(key_count));

	// the same document fed in odd-sized chunks must build the
	// identical DOM
	const size_t chunk_sizes[] = {1, 7, 63, 1023};

	for (size_t chunk_size : chunk_sizes)
	{
		kjson::detail::dom_builder builder;
		kjson::stream_reader reader(builder);

		bool status = true;

		for (size_t position = 0;
		     position < text.size() && status;
		     position += chunk_size)
		{
			const size_t piece =
				(text.size() - position) < chunk_size
				? (text.size() - position)
				: chunk_size;

			status = reader.feed(kjson::string_view(
				text.data() + position, piece));
		}

		status = status && reader.finish();

		ASSERT_TRUE(status)
			<< "chunk size " << chunk_size << " failed with: "
			<< reader.get_error().message();

		kjson::value chunked = builder.release_root();

		EXPECT_TRUE(chunked == dom)
			<< "chunked parse diverged at chunk size "
			<< chunk_size;
	}

	// the raw event stream itself must be chunk-invariant
	std::vector<std::string> events_whole;
	std::vector<std::string> events_chunked;

	{
		recording_handler handler(events_whole);
		kjson::stream_reader reader(handler);
		ASSERT_TRUE(reader.feed(text));
		ASSERT_TRUE(reader.finish());
	}

	{
		recording_handler handler(events_chunked);
		kjson::stream_reader reader(handler);

		bool status = true;
		for (size_t position = 0;
		     position < text.size() && status;
		     position += 977)
		{
			const size_t piece =
				(text.size() - position) < 977
				? (text.size() - position)
				: 977;

			status = reader.feed(kjson::string_view(
				text.data() + position, piece));
		}

		ASSERT_TRUE(status);
		ASSERT_TRUE(reader.finish());
	}

	EXPECT_TRUE(events_whole == events_chunked);
	EXPECT_TRUE(events_whole.empty() == false);
}

TEST(JsonOwn, test_stream_writer_matches_serialize)
{
	const std::string text = generate_big_document(512);

	// re-emitting the event stream must reproduce the serializer's
	// canonical text byte-identically
	std::string reemitted;
	char scratch[256];
	kjson::stream_writer writer(
		scratch, sizeof(scratch), &append_to_std_string, &reemitted);

	reemit_handler handler(writer);
	kjson::stream_reader reader(handler);

	ASSERT_TRUE(reader.feed(text));
	ASSERT_TRUE(reader.finish());
	ASSERT_TRUE(writer.finish());

	EXPECT_EQ(reemitted, text);

	// and the canonical text is what the DOM serializer produces
	kjson::error_code code;
	kjson::value dom = kjson::parse(text, code);
	ASSERT_TRUE(!code);

	EXPECT_EQ(serialize_to_std(dom), text);
}

TEST(JsonOwn, test_chunk_split_every_position)
{
	const char* p_document =
		"{\"name\":\"esc\\n\\u20ac\\ud83d\\ude00\",\"nums\":[0,-1,"
		"1.5,1e3,9223372036854775808],\"deep\":{\"a\":[{\"b\":null}]"
		"},\"flag\":false,\"empty\":\"\"}";

	const size_t length = strlen(p_document);

	kjson::value reference = parse_or_fail(p_document, "reference");

	for (size_t split = 0; split <= length; ++split)
	{
		kjson::detail::dom_builder builder;
		kjson::stream_reader reader(builder);

		bool status =
			reader.feed(kjson::string_view(p_document, split));

		status = status &&
			reader.feed(
				kjson::string_view(p_document + split, length - split));

		status = status && reader.finish();

		ASSERT_TRUE(status)
			<< "split at " << split << " failed with: "
			<< reader.get_error().message();

		EXPECT_TRUE(builder.release_root() == reference)
			<< "split at " << split;
	}
}

TEST(JsonOwn, test_parser_class_streaming)
{
	kjson::parse_options options;
	options.allow_comments = true;

	kjson::parser parser(kjson::storage_ptr(), options);

	kjson::error_code code;

	const char* p_part_1 = "/* header */ {\"a\": [1, 2,";
	const char* p_part_2 = " 3], \"b\": \"x\"} // tail";

	EXPECT_EQ(
		parser.write(p_part_1, strlen(p_part_1), code),
		strlen(p_part_1));
	EXPECT_TRUE(!code);

	EXPECT_EQ(
		parser.write(p_part_2, strlen(p_part_2), code),
		strlen(p_part_2));
	EXPECT_TRUE(!code);

	EXPECT_TRUE(parser.is_done());

	kjson::value result = parser.release();

	ASSERT_TRUE(result.is_object());
	EXPECT_EQ(result.as_object().at("a").as_array().size(), 3u);
	EXPECT_TRUE(result.as_object().at("b").as_string() == "x");
}

TEST(JsonOwn, test_value_conversions)
{
	{
		kjson::value data = kjson::value_from(-7);
		EXPECT_TRUE(data.is_int64());
		EXPECT_EQ(data.as_int64(), -7);
		EXPECT_EQ(kjson::value_to<int>(data), -7);
		// to_number is tolerant across numeric kinds
		EXPECT_FLOAT_EQ(kjson::value_to<float>(data), -7.0f);
	}

	{
		kjson::value data = kjson::value_from(7u);
		EXPECT_TRUE(data.is_uint64());
		EXPECT_EQ(data.as_uint64(), 7u);
	}

	{
		kjson::value data = kjson::value_from(0.5f);
		EXPECT_TRUE(data.is_double());
		EXPECT_DOUBLE_EQ(data.as_double(), 0.5);
		EXPECT_FLOAT_EQ(kjson::value_to<float>(data), 0.5f);
	}

	{
		kjson::value data = kjson::value_from(true);
		EXPECT_TRUE(data.is_bool());
		EXPECT_TRUE(data.as_bool());
		EXPECT_TRUE(kjson::value_to<bool>(data));
	}

	{
		kjson::value data = kjson::value_from("literal");
		EXPECT_TRUE(data.is_string());
		EXPECT_TRUE(data.as_string() == "literal");
	}

	{
		const std::string source = "std string value";
		kjson::value data = kjson::value_from(source);
		EXPECT_TRUE(data.is_string());
		EXPECT_TRUE(data.as_string() == source.c_str());

		const std::string back = kjson::value_to<std::string>(data);
		EXPECT_EQ(back, source);
	}

	{
		// integers serialize without a fraction part
		const kjson::string text =
			kjson::serialize(kjson::value(1));
		EXPECT_TRUE(text == "1");
	}

	{
		// object/array identity conversions used by the call sites
		kjson::object source;
		source["k"] = 5;
		kjson::value data = kjson::value_from(source);
		EXPECT_TRUE(data.is_object());

		kjson::object copy = kjson::value_to<kjson::object>(data);
		EXPECT_EQ(copy.size(), 1u);
		EXPECT_EQ(copy.at("k").as_int64(), 5);
	}
}

	#endif
#endif

void RegisterTests_JsonOwn_ForModule_Core(void)
{
#ifdef KOTEK_USE_TESTS
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
