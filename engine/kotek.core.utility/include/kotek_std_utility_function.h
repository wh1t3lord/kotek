#pragma once

#include <kotek.core.containers.vector\include\kotek_core_containers_vector.h>
#include <kotek.core.containers.string\include\kotek_core_containers_string.h>
#include <kotek.core.defines_dependent.message\include\kotek_core_defines_dependent_message.h>
#include "kotek_std_utility_variant.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

// Primary template (not defined)
template <typename T>
struct function_traits;

// Specialization for regular functions
template <typename Ret, typename... Args>
struct function_traits<Ret(Args...)>
{
	using args_tuple = std::tuple<Args...>;
	using ret_tuple = std::tuple<Ret>;
	using ret_t = Ret;
	using func_t = std::function<Ret(Args...)>;
	using func_tuple = std::tuple<func_t>;
};

// Specialization for function pointers
template <typename Ret, typename... Args>
struct function_traits<Ret (*)(Args...)>
{
	using args_tuple = std::tuple<Args...>;
	using ret_tuple = std::tuple<Ret>;
	using ret_t = Ret;
	using func_t = std::function<Ret(Args...)>;
	using func_tuple = std::tuple<func_t>;
};

// Specialization for member function pointers
template <typename ClassType, typename Ret, typename... Args>
struct function_traits<Ret (ClassType::*)(Args...)>
{
	using args_tuple = std::tuple<Args...>;
	using ret_tuple = std::tuple<Ret>;
	using ret_t = Ret;
	using func_t = std::function<Ret(Args...)>;
	using func_tuple = std::tuple<func_t>;
};

// Specialization for const member function pointers
template <typename ClassType, typename Ret, typename... Args>
struct function_traits<Ret (ClassType::*)(Args...) const>
{
	using args_tuple = std::tuple<Args...>;
	using ret_tuple = std::tuple<Ret>;
	using ret_t = Ret;
	using func_t = std::function<Ret(Args...)>;
	using func_tuple = std::tuple<func_t>;
};

// Specialization for functors and lambdas
template <typename Func>
struct function_traits : public function_traits<decltype(&Func::operator())>
{
};

// Noexcept variants
template <typename Ret, typename... Args>
struct function_traits<Ret(Args...) noexcept> : function_traits<Ret(Args...)>
{
};

template <typename Ret, typename... Args>
struct function_traits<Ret (*)(Args...) noexcept>
	: function_traits<Ret(Args...)>
{
};

template <typename ClassType, typename Ret, typename... Args>
struct function_traits<Ret (ClassType::*)(Args...) noexcept>
	: function_traits<Ret (ClassType::*)(Args...)>
{
};

template <typename ClassType, typename Ret, typename... Args>
struct function_traits<Ret (ClassType::*)(Args...) const noexcept>
	: function_traits<Ret (ClassType::*)(Args...) const>
{
};

// Helper type traits - improved version
template <typename T>
struct is_function_traits : std::false_type
{
};

// Specialization for all function trait variations
template <typename Ret, typename... Args>
struct is_function_traits<function_traits<Ret(Args...)>> : std::true_type
{
};

template <typename Ret, typename... Args>
struct is_function_traits<function_traits<Ret (*)(Args...)>> : std::true_type
{
};

template <typename Class, typename Ret, typename... Args>
struct is_function_traits<function_traits<Ret (Class::*)(Args...)>>
	: std::true_type
{
};

template <typename Class, typename Ret, typename... Args>
struct is_function_traits<function_traits<Ret (Class::*)(Args...) const>>
	: std::true_type
{
};

// Add specialization for types that inherit from function_traits
template <typename T>
struct is_derived_function_traits
{
private:
	template <typename U>
	static std::true_type test(const function_traits<U>*);
	static std::false_type test(...);

public:
	static constexpr bool value = decltype(test(std::declval<T*>()))::value;
};

// Combined check
template <typename T>
inline constexpr bool is_function_traits_v =
	is_function_traits<T>::value || is_derived_function_traits<T>::value;

// -----------------------------------------------------------------
// Helpers to detect call operators
// -----------------------------------------------------------------

// 1. Detect non-templated operator()
template <typename T, typename = void>
struct has_call_operator : std::false_type
{
};

template <typename T>
struct has_call_operator<T, std::void_t<decltype(&T::operator())>>
	: std::true_type
{
};

// 2. Detect templated operator() by trying to call it with an int.
template <typename T, typename = void>
struct has_templated_call_operator : std::false_type
{
};

template <typename T>
struct has_templated_call_operator<T,
	std::void_t<decltype(std::declval<T>()(std::declval<int>()))>>
	: std::true_type
{
};

// 3. Helpers to force overload resolution for ref-qualified call operators.
template <typename T>
auto call_lvalue_impl(T& t) -> decltype(t.operator()())
{
	return t.operator()();
}

template <typename T>
auto call_rvalue_impl(T&& t) -> decltype(std::forward<T>(t).operator()())
{
	return std::forward<T>(t).operator()();
}

// Detect ref-qualified operator() by using the helper functions.
template <typename T, typename = void>
struct has_ref_qualified_call : std::false_type
{
};

template <typename T>
struct has_ref_qualified_call<T,
	std::void_t<decltype(call_lvalue_impl(std::declval<T&>())),
		decltype(call_rvalue_impl(std::declval<T&&>()))>> : std::true_type
{
};

// -----------------------------------------------------------------
// is_lambda_impl: a trait that (heuristically) detects lambda types.
// (Note: This will also be true for many functors.)
template <typename T>
struct is_lambda_impl
{
private:
	template <typename L>
	static constexpr bool is_lambda_type()
	{
		using U = std::remove_cv_t<std::remove_reference_t<L>>;
		if constexpr (!std::is_class_v<U>)
			return false;
		// Accept if either a non-templated or templated call operator is
		// present.
		if constexpr (!(has_call_operator<U>::value ||
						  has_templated_call_operator<U>::value))
			return false;
		return true;
	}

public:
	static constexpr bool value = is_lambda_type<T>();
};

template <typename T>
inline constexpr bool is_lambda_v = is_lambda_impl<T>::value;

// -----------------------------------------------------------------
// Additional traits for callable detection
// -----------------------------------------------------------------
template <typename T>
struct is_regular_function : std::false_type
{
};

template <typename Ret, typename... Args>
struct is_regular_function<Ret(Args...)> : std::true_type
{
};

template <typename Ret, typename... Args>
struct is_regular_function<Ret (*)(Args...)> : std::true_type
{
};

template <typename T>
struct is_member_function_ptr : std::false_type
{
};

template <typename Class, typename Ret, typename... Args>
struct is_member_function_ptr<Ret (Class::*)(Args...)> : std::true_type
{
};

template <typename Class, typename Ret, typename... Args>
struct is_member_function_ptr<Ret (Class::*)(Args...) const> : std::true_type
{
};

template <typename T>
struct is_callable_impl
{
	using clean_type = std::remove_cv_t<std::remove_reference_t<T>>;
	static constexpr bool value =
		std::is_function_v<std::remove_pointer_t<clean_type>> ||
		is_regular_function<clean_type>::value ||
		is_member_function_ptr<clean_type>::value ||
		is_lambda_impl<clean_type>::value ||
		has_call_operator<clean_type>::value ||
		has_ref_qualified_call<clean_type>::value ||
		has_templated_call_operator<clean_type>::value;
};

template <typename T>
inline constexpr bool is_callable_v = is_callable_impl<T>::value;

template <typename VariantType, typename ContainerType, typename ReturnType,
	typename... Args, std::size_t... I>
bool _call_function_impl(const std::function<ReturnType(Args...)>& f,
	const ContainerType& args, std::index_sequence<I...>)
{
	// If an element in args does not hold the expected type,
	// std::get<T>(...) will throw std::bad_variant_access.
	return f(std::get<Args>(args[I])...);
}

template <typename VariantType, typename ContainerType, typename ReturnType,
	typename... Args>
bool call(
	const std::function<ReturnType(Args...)>& f, const ContainerType& args)
{
	if (args.size() != sizeof...(Args))
	{
		KOTEK_MESSAGE_WARNING_S("passed wrong amount of "
								"arguments, expected: [{}] | passed: [{}]",
			512, sizeof...(Args), args.size());
		return false;
	}

	return _call_function_impl<VariantType, ContainerType, ReturnType, Args...>(
		f, args, std::index_sequence_for<Args...>{});
}

template <typename Variant, typename Func>
constexpr bool are_callable_args_in_variant(Func)
{
	return are_args_in_variant<typename function_traits<Func>::args_tuple,
		Variant>();
}

template <typename VariantType, typename ReturnType>
class ivfunction
{
public:
	virtual ~ivfunction() {}

	static_assert(std::is_unsigned_v<KOTEK_DEF_CONSOLE_TYPE_FOR_ARGUMENT_COUNT>,
		"your specified type must be arithmetic e.g. numeric and unsigned "
		"otherwise there's no point for signed type or even types that doesn't "
		"represent a number in any other possible ways...");

	virtual KOTEK_DEF_CONSOLE_TYPE_FOR_ARGUMENT_COUNT
	Get_ArgumentCount() const = 0;

	virtual ktk_vector<VariantType,
		KOTEK_DEF_CONSOLE_FUNCTION_MAX_ARGUMENT_COUNT>
	Parse(const ktk_vector<std::string_view,
		KOTEK_DEF_CONSOLE_FUNCTION_MAX_ARGUMENT_COUNT>& args) const = 0;

	virtual ReturnType operator()(const ktk_vector<VariantType,
		KOTEK_DEF_CONSOLE_FUNCTION_MAX_ARGUMENT_COUNT>& args) = 0;
};

template <typename VariantType, typename FunctionType>
class vfunction : public ivfunction<VariantType,
					  typename function_traits<FunctionType>::ret_t>
{
public:
	using args_t = typename function_traits<FunctionType>::args_tuple;
	using result_t = function_traits<FunctionType>::ret_t;
	using function_t = function_traits<FunctionType>::func_t;

	static_assert(is_variant_v<VariantType>,
		"you must pass a std::variant or some analogue but still it is "
		"preferred to use std's version. So in any other case report to "
		"developers!");
	static_assert(is_callable_v<FunctionType>,
		"you must pass a function not any other type");
	static_assert(are_args_in_variant<args_t, VariantType>(),
		"your variant must contain same types as in your callable function "
		"(object) instance");

public:
	vfunction(FunctionType& func) : m_callback{func} {}
	~vfunction() {}

	KOTEK_DEF_CONSOLE_TYPE_FOR_ARGUMENT_COUNT Get_ArgumentCount() const override
	{
		return static_cast<KOTEK_DEF_CONSOLE_TYPE_FOR_ARGUMENT_COUNT>(
			std::tuple_size_v<args_t>);
	}

	inline ktk_vector<VariantType,
		KOTEK_DEF_CONSOLE_FUNCTION_MAX_ARGUMENT_COUNT>
	Parse(const ktk_vector<std::string_view,
		KOTEK_DEF_CONSOLE_FUNCTION_MAX_ARGUMENT_COUNT>& args) const override
	{
		ktk_vector<VariantType, KOTEK_DEF_CONSOLE_FUNCTION_MAX_ARGUMENT_COUNT>
			result;

		result = std::apply(
			[result, args]<typename... Args>(Args... _args)
			{
				return fill_vector_variant<VariantType, decltype(result),
					decltype(args), Args...>(args);
			},
			args_t());

		return result;
	}

	inline result_t operator()(const ktk_vector<VariantType,
		KOTEK_DEF_CONSOLE_FUNCTION_MAX_ARGUMENT_COUNT>& args) override
	{
		static_assert(std::tuple_size_v<args_t> <=
				std::numeric_limits<unsigned char>::max(),
			"the number of arguments is limited to unsigned char type, please "
			"report to developers if you really needed more than 255 arguments "
			"in a function...");

		constexpr KOTEK_DEF_CONSOLE_TYPE_FOR_ARGUMENT_COUNT _kMaxArguments =
			static_cast<KOTEK_DEF_CONSOLE_TYPE_FOR_ARGUMENT_COUNT>(
				std::tuple_size_v<args_t>);

		result_t result_empty{};

		if (args.size() != _kMaxArguments)
		{
			bool is_less = args.size() < _kMaxArguments;

			if (is_less)
			{
				KOTEK_MESSAGE_WARNING("you passed less arguments than "
									  "expected: expected[{}] | passed[{}]",
					_kMaxArguments, args.size());
			}
			else
			{
				KOTEK_MESSAGE_WARNING("you passed more arguments than "
									  "expected: expected[{}] | passed[{}]",
					_kMaxArguments, args.size());
			}

			return result_empty;
		}

		bool validation = check_args<args_t>(args);

		// it means that variant has types that's needed to our function_t
		// signature like if function is int,float,double that means each
		// element of vector has in the order types as defined in function
		// args[0]=int; args[1]=float; args[2]=double
		// that means we can safely (at least in terms of evaluation) use these
		// arguments for calling
		if (validation)
		{
			return std::apply(
				[this, args]<typename... Args>(Args&&... _args) -> result_t
				{
					return call<VariantType, decltype(args), result_t, Args...>(
						m_callback, args);
				},
				args_t());
		}
#ifdef KOTEK_DEBUG
		else
		{
			KOTEK_MESSAGE_WARNING_S(
				"your variant vector contains wrong types in wrong order that "
				"are different to function signature: function sinagute[{}] | "
				"your arguments[{}]",
				2048, ktk_cstring_view(get_tuple_type_info<args_t>().data()),
				ktk_cstring_view(get_variant_container_types(args).data()));
		}
#endif

		return result_empty;
	}

private:
	function_t m_callback;
};

template <typename VariantType, typename F>
inline auto make_vfunction(F&& func)
{
	return kun_kotek kun_ktk vfunction<VariantType, std::remove_cvref_t<F>>(
		std::forward<F>(func));
}

template <typename VariantType, typename F>
inline auto make_vfunction_ptr(F&& func)
{
	return new kun_kotek kun_ktk vfunction<VariantType, std::remove_cvref_t<F>>(
		std::forward<F>(func));
}

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK