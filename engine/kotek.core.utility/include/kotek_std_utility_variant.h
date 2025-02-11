#pragma once

#include <kotek.core.containers.variant\include\kotek_core_containers_variant.h>
#include <kotek.core.defines_dependent.assert\include\kotek_core_defines_dependent_assert.h>
#include <kotek.core.containers.filesystem.path\include\kotek_core_containers_filesystem_path.h>
#include <kotek.core.api\include\kotek_api_resource_manager.h>
#include <kotek.core.containers.shared_ptr\include\kotek_core_containers_shared_ptr.h>

// #include
// <kotek.core.containers.string\include\kotek_core_containers_string.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

template <typename T, typename Variant>
struct is_in_variant;

template <typename T, typename... Ts>
struct is_in_variant<T, std::variant<Ts...>>
	: std::disjunction<std::is_same<T, Ts>...>
{
};

template <typename T, typename Variant>
inline constexpr bool is_in_variant_v = is_in_variant<T, Variant>::value;

template <typename T>
struct is_variant : std::false_type
{
};

template <typename... Args>
struct is_variant<std::variant<Args...>> : std::true_type
{
};

template <typename T>
inline constexpr bool is_variant_v = is_variant<std::remove_cv_t<T>>::value;

template <typename T>
struct is_tuple : std::false_type
{
};

template <typename... Args>
struct is_tuple<std::tuple<Args...>> : std::true_type
{
};

template <typename T>
inline constexpr bool is_tuple_v = is_tuple<std::remove_cv_t<T>>::value;

template <typename Tuple, typename Variant, std::size_t... I>
constexpr bool are_args_in_variant_impl(std::index_sequence<I...>)
{
	// Fold-expression: for each index I, check that the I-th tuple type is in
	// the variant.
	return (
		is_in_variant<std::tuple_element_t<I, Tuple>, Variant>::value && ...);
}

// Non-recursive, compile-time function to check that every type in Tuple exists
// in Variant.
template <typename Tuple, typename Variant>
constexpr bool are_args_in_variant()
{
	return are_args_in_variant_impl<Tuple, Variant>(
		std::make_index_sequence<std::tuple_size_v<Tuple>>{});
}

// -------------------------------------------------------------------
// Custom helper: variant_holds_alternative
//
// This function checks if a given variant holds a value of type T.
// We implement it with a lambda inside std::visit so that we avoid
// the static_assert issue with std::holds_alternative if T is not unique.
// It is marked constexpr so it can be used in compile-time contexts.
template <typename TypeFromTuple, typename VariantType>
constexpr bool variant_holds_alternative(const VariantType& v)
{
	bool result = false;
	std::visit(
		[&result](auto&& arg) constexpr
		{
			if constexpr (std::is_same_v<std::decay_t<decltype(arg)>,
							  TypeFromTuple>)
				result = true;
		},
		v);
	return result;
}

// -------------------------------------------------------------------
// Check Types Implementation (Generic over container type)
//
// This helper function works for any tuple type ArgTuple and any container
// that supports .size() and operator[]. It uses an index sequence to check,
// at compile time, that for every index I the container element at position I
// holds a value of type std::tuple_element_t<I, ArgTuple>.
// It is marked constexpr so that it can be evaluated at compile time.
template <typename ArgTuple, typename Container, std::size_t... I>
constexpr bool check_args_impl(const Container& args, std::index_sequence<I...>)
{
	if (args.size() != sizeof...(I))
		return false;
	// Fold expression over all indices.
	return (... &&
		variant_holds_alternative<std::tuple_element_t<I, ArgTuple>,
			decltype(args[I])>(args[I]));
}

// The main checking function. It deduces the expected number and types from
// ArgTuple and then calls checkArgsImpl with an appropriate index sequence.
// (The container here may be a constexpr container such as std::array.)
template <typename ArgTuple, typename Container>
constexpr bool check_args(const Container& args)
{
	return check_args_impl<ArgTuple>(
		args, std::make_index_sequence<std::tuple_size_v<ArgTuple>>{});
}

// Compile-time type_name<T>() using __PRETTY_FUNCTION__ and
// std::string_view. Adjust the prefix/suffix strings for your compiler.
template <typename T>
constexpr std::string_view type_name()
{
#if defined(__clang__)
	std::string_view p = __PRETTY_FUNCTION__;
	constexpr std::string_view prefix = "std::string_view type_name() [T = ";
	constexpr std::string_view suffix = "]";
#elif defined(__GNUC__)
	std::string_view p = __PRETTY_FUNCTION__;
	constexpr std::string_view prefix =
		"constexpr std::string_view type_name() [with T = ";
	constexpr std::string_view suffix = "]";
#elif defined(_MSC_VER)
	std::string_view p = __FUNCSIG__;
	constexpr std::string_view prefix = "type_name<";
	constexpr std::string_view suffix = ">(void)";
#else
	std::string_view p = "unknown";
	constexpr std::string_view prefix = "";
	constexpr std::string_view suffix = "";
#endif
	auto start = p.find(prefix);
	if (start == std::string_view::npos)
		return "unknown";
	start += prefix.size();
	auto end = p.find(suffix, start);
	return p.substr(start, end - start);
}

template <typename Tuple>
constexpr std::array<char, 512> get_tuple_type_info()
{
	std::array<char, 512> buffer = {};
	size_t pos = 0;

	[&]<std::size_t... I>(std::index_sequence<I...>)
	{
		((
			 [&]
			 {
				 constexpr std::string_view type = kun_kotek kun_ktk
				 type_name<std::tuple_element_t<I, Tuple>>();
				 for (char c : type)
				 {
					 buffer[pos++] = c;
				 }
			 }(),
			 [&]
			 {
				 if constexpr (I < sizeof...(I) - 1)
				 {
					 buffer[pos++] = ',';
					 buffer[pos++] = ' ';
				 }
			 }()),
			...);
	}(std::make_index_sequence<std::tuple_size_v<Tuple>>{});

	buffer[pos] = '\0';
	return buffer;
}

template <typename VariantContainer>
constexpr std::array<char, 512> get_variant_container_value_type_info()
{
	std::array<char, 512> buffer = {};
	size_t pos = 0;

	using VariantType = typename VariantContainer::value_type;
	[&]<std::size_t... I>(std::index_sequence<I...>)
	{
		((
			 [&]
			 {
				 constexpr std::string_view type = kun_kotek kun_ktk
				 type_name<std::variant_alternative_t<I, VariantType>>();
				 for (char c : type)
				 {
					 buffer[pos++] = c;
				 }
			 }(),
			 [&]
			 {
				 if constexpr (I < sizeof...(I) - 1)
				 {
					 buffer[pos++] = ',';
					 buffer[pos++] = ' ';
				 }
			 }()),
			...);
	}(std::make_index_sequence<std::variant_size_v<VariantType>>{});

	buffer[pos] = '\0';
	return buffer;
}

template <typename Container>
constexpr std::array<char, 512> get_variant_container_types(
	const Container& container)
{
	std::array<char, 512> buffer = {};
	size_t pos = 0;

	for (size_t i = 0; i < container.size(); ++i)
	{
		const auto& variant = container[i];
		std::visit(
			[&buffer, &pos](const auto& value)
			{
				constexpr std::string_view type = kun_kotek kun_ktk
				type_name<std::decay_t<decltype(value)>>();
				for (char c : type)
				{
					buffer[pos++] = c;
				}
			},
			variant);

		if (i < container.size() - 1)
		{
			buffer[pos++] = ',';
			buffer[pos++] = ' ';
		}
	}

	buffer[pos] = '\0';
	return buffer;
}

//---------------------------------------------------------------------------
// Helper: next_power_of_2
// Returns the next power of two greater than or equal to n.
inline std::size_t next_power_of_2(std::size_t n)
{
	if (n == 0)
		return 2;
	std::size_t power = 1;
	while (power < n)
		power *= 2;
	return power;
}

//---------------------------------------------------------------------------
// Helper: Detect if a type is a specialization of std::array<char, N>
template <typename T>
struct is_char_array : std::false_type
{
};

template <std::size_t N>
struct is_char_array<std::array<char, N>> : std::true_type
{
	static constexpr std::size_t size = N;
	static constexpr bool is_fs = false;
};

#ifdef KOTEK_USE_LIBRARY_TYPE_EMB
template <std::size_t N>
struct is_char_array<static_cstring<N>> : std::true_type
{
	static constexpr std::size_t size = N;
	static constexpr bool is_fs = false;
};

template <std::size_t N>
struct is_char_array<kun_filesystem static_path<N>> : std::true_type
{
	static constexpr std::size_t size = N;
	static constexpr bool is_fs = true;
};
#endif

//---------------------------------------------------------------------------
// TAG DISPATCHING
// Define tag types to distinguish among conversion categories.
struct bool_tag
{
};
struct integral_tag
{
};
struct floating_tag
{
};
struct char_array_tag
{
};
struct string_tag
{
};
struct char_string_pointer_tag
{
};
struct custom_tag
{
}; // For user–defined types

// A helper to always yield false dependent on T.
template <typename T>
struct dependent_false : std::false_type
{
};

// Helper: select_tag – choose which conversion category applies to T.
template <typename T>
constexpr auto select_tag()
{
	if constexpr (std::is_same_v<T, bool>)
		return bool_tag{};
	else if constexpr (std::is_integral_v<T> && !std::is_same_v<T, bool>)
		return integral_tag{};
	else if constexpr (std::is_floating_point_v<T>)
		return floating_tag{};
	else if constexpr (is_char_array<T>::value)
		return char_array_tag{};
	else if constexpr (std::is_same_v<T, std::string>)
		return string_tag{};
	else if constexpr (std::is_same_v<T, const char*>)
		return char_string_pointer_tag{};
	else
		return custom_tag{};
}

//---------------------------------------------------------------------------
// Conversion implementations via tag dispatching.
// For built–in types we supply definitions.
// For custom types (tag custom_tag) the default implementation triggers a
// compile–time error.

// -- bool conversion:
template <typename T>
T convert_impl(std::string_view str, bool& status, bool_tag)
{
	// Accept "true" or "1" as true; "false" or "0" as false.
	if (str == "true" || str == "1" || str == "on")
		return static_cast<T>(true);
	else if (str == "false" || str == "0" || str == "off")
		return static_cast<T>(false);
	else
	{
		status = false;
		KOTEK_ASSERT(
			false, "Conversion to bool failed. Analyzed string: [{}]", str);
		return false;
	}
}

// -- Integral conversion (excluding bool):
template <typename T>
T convert_impl(std::string_view str, bool& status, integral_tag)
{
	T temp{};
	if constexpr (std::is_unsigned_v<T>)
	{
		unsigned long long val = 0;
		auto [ptr, ec] =
			std::from_chars(str.data(), str.data() + str.size(), val);
		if (ec == std::errc{} && ptr == str.data() + str.size() &&
			val <= std::numeric_limits<T>::max())
		{
			temp = static_cast<T>(val);
			return temp;
		}
	}
	else
	{
		long long val = 0;
		auto [ptr, ec] =
			std::from_chars(str.data(), str.data() + str.size(), val);
		if (ec == std::errc{} && ptr == str.data() + str.size() &&
			val >= std::numeric_limits<T>::lowest() &&
			val <= std::numeric_limits<T>::max())
		{
			temp = static_cast<T>(val);
			return temp;
		}
	}

	status = false;
	KOTEK_MESSAGE_WARNING(
		"failed to convert to integral, analyzed string: [{}]", str);

	return std::numeric_limits<short>::min();
}

// -- Floating–point conversion:
template <typename T>
T convert_impl(std::string_view str, bool& status, floating_tag)
{
	T temp{};
	char* end = nullptr;
	double val = std::strtod(str.data(), &end);
	if (end == str.data() + str.size())
	{
		if constexpr (std::is_same_v<T, float>)
		{
			if (val >= std::numeric_limits<float>::lowest() &&
				val <= std::numeric_limits<float>::max())
			{
				temp = static_cast<float>(val);
				return temp;
			}
		}
		else if constexpr (std::is_same_v<T, double>)
		{
			temp = static_cast<double>(val);
			return temp;
		}
	}

	status = false;
	KOTEK_MESSAGE_WARNING(
		"failed to convert to float or to double, analyzed string: [{}]", str);

	return std::numeric_limits<float>::min();
}

// -- Fixed–size char array conversion:
template <typename T>
T convert_impl(std::string_view str, bool& status, char_array_tag)
{
	constexpr std::size_t candidate_size = is_char_array<T>::size;
	std::size_t required = next_power_of_2(str.size());
	if (required == candidate_size || (is_char_array<T>::is_fs))
	{
		T arr{};

		if constexpr (is_char_array<T>::is_fs)
		{
			arr = str;
		}
		else
		{
			std::copy(str.begin(), str.end(), arr.begin());
		}

		return arr;
	}

	status = false;
	T arr{};
	KOTEK_MESSAGE_WARNING(
		"Conversion to fixed–size char array failed. Analyzed string: [{}]",
		str);
	return arr;
}

// -- std::string conversion:
template <typename T>
T convert_impl(std::string_view str, bool& status, string_tag)
{
	return T(str);
}

template <typename T>
T convert_impl(std::string_view str, bool& status, char_string_pointer_tag)
{
	return T(str.data());
}

// -- Custom conversion: This must be specialized by the user for any custom
// type.
template <typename T>
T convert_impl(std::string_view, bool& status, custom_tag)
{
	static_assert(dependent_false<T>::value,
		"No conversion provided for custom type T. Please specialize "
		"convert_impl for your type.");
}

template <>
inline kun_kotek kun_core ktkLoadingRequest
convert_impl<kun_kotek kun_core ktkLoadingRequest>(
	std::string_view str, bool& status, custom_tag)
{
	kun_kotek kun_core ktkLoadingRequest result;

	KOTEK_ASSERT(false, "not implemented!");

	return result;
}

template <>
inline kun_kotek kun_ktk shared_ptr<kun_kotek kun_core ktkResourceHandle>
convert_impl<
	kun_kotek kun_ktk shared_ptr<kun_kotek kun_core ktkResourceHandle>>(
	std::string_view str, bool& status, custom_tag)
{
	int simple_resource;
	const char* _kTypeName = typeid(simple_resource).name();
	const char* _kFunctionName = __FUNCTION__;
	const char* _kFileName = __FILE__;

	KOTEK_ASSERT(false, "not implemented!");

	return std::make_shared<kun_kotek kun_core ktkResourceHandle>(
		&simple_resource, false
#ifdef KOTEK_DEBUG
		,
		_kTypeName, _kFunctionName, _kFileName
#endif
	);
}

// The generic conversion function that dispatches based on T.
template <typename T>
T convert_from_string(std::string_view str, bool& status)
{
	return convert_impl<T>(str, status, select_tag<T>());
}

template <typename Variant, typename ReturnContainer, typename InputContainer,
	typename... Ts>
ReturnContainer fill_vector_variant(const InputContainer& input)
{
	static_assert((is_in_variant_v<Ts, Variant> && ...),
		"All candidate types must be among the alternatives of the Variant "
		"type.");

	if (input.size() != sizeof...(Ts))
	{
		KOTEK_MESSAGE_WARNING(
			"the input argument size must be equal to types for casting like "
			"int,double,float = ['1', '3.2', '3.3f']. Expected: [{}] Passed: "
			"[{}]",
			sizeof...(Ts), input.size());
		return ReturnContainer{};
	}

	ReturnContainer result;

	// Helper lambda: for each candidate type, convert the corresponding input
	// string.
	auto push_conversion = [&]<typename T>(T, std::size_t element_index)
	{
		std::string_view str = input[element_index].data();

		// we suppose that our convert operation was successful
		bool status = true;

		auto candidate = convert_from_string<T>(str, status);

		if (status)
		{
			result.push_back(candidate);
		}
		else
		{
			// If conversion fails, try fallback to std::string if available.
			if constexpr (is_in_variant_v<std::string, Variant>)
				result.push_back(std::string(str));
			else
			{
				KOTEK_MESSAGE_WARNING("failed to convert string to type, "
									  "analyzed string: [{}] type: [{}]",
					str, type_name<T>());
			}
		}
	};

	std::size_t index = 0;
	// Expand the candidate pack (order is preserved).
	(push_conversion(Ts{}, index++), ...);
	return result;
}

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK