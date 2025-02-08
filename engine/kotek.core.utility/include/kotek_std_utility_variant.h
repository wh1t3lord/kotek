#pragma once

#include <kotek.core.containers.variant\include\kotek_core_containers_variant.h>

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
constexpr std::array<char, 512> get_variant_container_type_info()
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
constexpr std::array<char, 512> print_variant_container_types(
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

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK