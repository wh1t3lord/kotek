#include "../include/kotek_core_utility.h"
#include <kotek.core.defines.static.tests/include/kotek_core_defines_static_tests.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>
#include <kotek.core.defines_dependent.message\include\kotek_core_defines_dependent_message.h>
#include <gtest/gtest.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG

// 1. Regular function
bool myFunc(int x)
{
	return x > 0;
}

// 4. Noexcept function
bool noexceptFunc() noexcept
{
	return true;
}

TEST(Utility, function_traits)
{
	using myFunc_traits = kun_kotek kun_ktk function_traits<decltype(myFunc)>;
	static_assert(std::is_same_v<myFunc_traits::ret_tuple, std::tuple<bool>>);
	static_assert(std::is_same_v<myFunc_traits::args_tuple, std::tuple<int>>);
	static_assert(std::is_same_v<myFunc_traits::func_tuple,
		std::tuple<std::function<bool(int)>>>);
	static_assert(kun_kotek kun_ktk is_function_traits_v<
		kun_kotek kun_ktk function_traits<decltype(myFunc)>>);

	// 2. Lambda
	auto lambda = [](int x, float y) -> bool { return x > y; };
	using lambda_traits = kun_kotek kun_ktk function_traits<decltype(lambda)>;
	static_assert(std::is_same_v<lambda_traits::ret_tuple, std::tuple<bool>>);
	static_assert(
		std::is_same_v<lambda_traits::args_tuple, std::tuple<int, float>>);
	static_assert(std::is_same_v<lambda_traits::func_tuple,
		std::tuple<std::function<bool(int, float)>>>);
	static_assert(kun_kotek kun_ktk is_function_traits_v<lambda_traits>);

	// 3. Member function
	struct Test
	{
		bool memberFunc2(double, int, float, const char*, int*, float*)
		{
			return false;
		}
		int memberFunc(double d) const { return static_cast<int>(d); }
	};
	using member_traits_const =
		kun_kotek kun_ktk function_traits<decltype(&Test::memberFunc)>;
	static_assert(
		std::is_same_v<member_traits_const::ret_tuple, std::tuple<int>>);
	static_assert(
		std::is_same_v<member_traits_const::args_tuple, std::tuple<double>>);
	static_assert(std::is_same_v<member_traits_const::func_tuple,
		std::tuple<std::function<int(double)>>>);
	static_assert(kun_kotek kun_ktk is_function_traits_v<member_traits_const>);

	using member_traits =
		kun_kotek kun_ktk function_traits<decltype(&Test::memberFunc2)>;
	static_assert(std::is_same_v<member_traits::ret_tuple, std::tuple<bool>>);
	static_assert(std::is_same_v<member_traits::args_tuple,
		std::tuple<double, int, float, const char*, int*, float*>>);
	static_assert(std::is_same_v<member_traits::func_tuple,
		std::tuple<std::function<bool(
			double, int, float, const char*, int*, float*)>>>);
	static_assert(kun_kotek kun_ktk is_function_traits_v<member_traits>);

	using noexcept_traits =
		kun_kotek kun_ktk function_traits<decltype(noexceptFunc)>;
	static_assert(std::is_same_v<noexcept_traits::ret_tuple, std::tuple<bool>>);
	static_assert(std::tuple_size_v<noexcept_traits::args_tuple> == 0);
	static_assert(std::is_same_v<noexcept_traits::func_tuple,
		std::tuple<std::function<bool()>>>);
	static_assert(kun_kotek kun_ktk is_function_traits_v<noexcept_traits>);
}

TEST(Utility, vfunction_lambda)
{
	auto p_lambda = []() -> bool { return false; };

	using myVar = std::variant<std::monostate>;

	auto func = kun_kotek kun_ktk make_vfunction<myVar>(p_lambda);

	EXPECT_FALSE(func(
		ktk_vector<myVar, KOTEK_DEF_CONSOLE_FUNCTION_MAX_ARGUMENT_COUNT>()));
}

bool testFunc()
{
	return false;
}

TEST(Utility, vfunction_function)
{
	using myVar = std::variant<std::monostate>;

	auto func = kun_kotek kun_ktk make_vfunction<myVar>(testFunc);

	EXPECT_FALSE(func(
		ktk_vector<myVar, KOTEK_DEF_CONSOLE_FUNCTION_MAX_ARGUMENT_COUNT>()));
}

TEST(Utility, vfunction_functor)
{
	struct _ktk_utility_test_functor_
	{
		bool operator()() { return false; }
	};

	using myVar = std::variant<std::monostate>;

	_ktk_utility_test_functor_ instance;

	auto func = kun_kotek kun_ktk make_vfunction<myVar>(instance);

	EXPECT_FALSE(func(
		ktk_vector<myVar, KOTEK_DEF_CONSOLE_FUNCTION_MAX_ARGUMENT_COUNT>()));
}

TEST(Utility, vfunction_ptr_lambda)
{
	auto p_lambda = []() -> bool { return false; };
	using myVar = std::variant<std::monostate>;

	kun_kotek kun_ktk ivfunction<myVar, bool>* p_interface =
		kun_kotek kun_ktk make_vfunction_ptr<myVar>(p_lambda);

	EXPECT_FALSE((*p_interface)(
		ktk_vector<myVar, KOTEK_DEF_CONSOLE_FUNCTION_MAX_ARGUMENT_COUNT>()));

	delete p_interface;
}

// 6. Noexcept functions
bool noexcept_func() noexcept
{
	return true;
}

// 1. Regular functions
bool regular_func()
{
	return false;
}
bool regular_func_args(int, float)
{
	return true;
}

TEST(Utility, is_callable_checks)
{
	static_assert(kun_kotek kun_ktk is_callable_v<decltype(regular_func)>);
	static_assert(kun_kotek kun_ktk is_callable_v<decltype(regular_func_args)>);

	// 2. Function pointers
	bool (*func_ptr)() = regular_func;
	bool (*func_ptr_args)(int, float) = regular_func_args;
	static_assert(kun_kotek kun_ktk is_callable_v<decltype(func_ptr)>);
	static_assert(kun_kotek kun_ktk is_callable_v<decltype(func_ptr_args)>);

	// 3. Lambdas - various forms
	auto lambda_simple = []() { return true; };
	static_assert(kun_kotek kun_ktk is_callable_v<decltype(lambda_simple)>);

	auto lambda_args = [](int x, float y) { return x > y; };
	static_assert(kun_kotek kun_ktk is_callable_v<decltype(lambda_args)>);

	int capture = 42;
	auto lambda_capture = [capture]() { return capture > 0; };
	static_assert(kun_kotek kun_ktk is_callable_v<decltype(lambda_capture)>);

	auto lambda_mutable = [x = 0]() mutable { return ++x > 0; };
	static_assert(kun_kotek kun_ktk is_callable_v<decltype(lambda_mutable)>);

	// 4. Function objects (functors)
	struct Functor
	{
		bool operator()() { return true; }
	};
	static_assert(kun_kotek kun_ktk is_callable_v<Functor>);

	struct FunctorWithArgs
	{
		bool operator()(int x, float y) { return x > y; }
	};
	static_assert(kun_kotek kun_ktk is_callable_v<FunctorWithArgs>);

	struct ConstFunctor
	{
		bool operator()() const { return true; }
	};
	static_assert(kun_kotek kun_ktk is_callable_v<ConstFunctor>);

	// 5. Member functions
	struct TestClass
	{
		bool member_func() { return true; }
		bool const_member_func() const { return true; }
		static bool static_func() { return true; }
	};
	static_assert(
		kun_kotek kun_ktk is_callable_v<decltype(&TestClass::member_func)>);
	static_assert(kun_kotek kun_ktk
			is_callable_v<decltype(&TestClass::const_member_func)>);
	static_assert(
		kun_kotek kun_ktk is_callable_v<decltype(&TestClass::static_func)>);

	static_assert(kun_kotek kun_ktk is_callable_v<decltype(noexcept_func)>);

	auto lambda_noexcept = []() noexcept { return true; };
	static_assert(kun_kotek kun_ktk is_callable_v<decltype(lambda_noexcept)>);

	// 7. std::function
	std::function<bool()> std_func = regular_func;
	static_assert(kun_kotek kun_ktk is_callable_v<decltype(std_func)>);

	// 8. Negative tests (non-callable types)
	static_assert(!kun_kotek kun_ktk is_callable_v<int>);
	static_assert(!kun_kotek kun_ktk is_callable_v<float>);
	static_assert(!kun_kotek kun_ktk is_callable_v<void>);
	static_assert(!kun_kotek kun_ktk is_callable_v<std::string>);

	struct NonCallable
	{
		int x;
	};
	static_assert(!kun_kotek kun_ktk is_callable_v<NonCallable>);

	// 9. Reference qualifiers
	struct RefQualifiers
	{
		bool operator()() & { return true; }
		bool operator()() && { return true; }
	};
	static_assert(kun_kotek kun_ktk is_callable_v<RefQualifiers>);

	// 10. Variadic functions
	auto variadic_lambda = [](auto... args) { return sizeof...(args) > 0; };
	static_assert(kun_kotek kun_ktk is_callable_v<decltype(variadic_lambda)>);

	// 11. Complex return types
	auto complex_lambda = []() -> std::pair<int, bool> { return {42, true}; };
	static_assert(kun_kotek kun_ktk is_callable_v<decltype(complex_lambda)>);
}

// Regular function tests
void func() {}

// Additional test for specific categories if needed
TEST(Utility, callable_categories)
{
	// Lambda specific tests
	auto lambda = []() {};
	static_assert(kun_kotek kun_ktk is_lambda_impl<decltype(lambda)>::value);

	static_assert(kun_kotek kun_ktk is_regular_function<decltype(func)>::value);

	// Member function tests
	struct Test
	{
		void mem_func() {}
		void const_mem_func() const {}
	};
	static_assert(kun_kotek kun_ktk
			is_member_function_ptr<decltype(&Test::mem_func)>::value);
	static_assert(kun_kotek kun_ktk
			is_member_function_ptr<decltype(&Test::const_mem_func)>::value);

	// Function object tests
	struct Functor
	{
		void operator()() {}
	};
	static_assert(kun_kotek kun_ktk has_call_operator<Functor>::value);
	// because it has operator() and lambda has that operator too!
	static_assert(kun_kotek kun_ktk is_lambda_impl<Functor>::value);
}

// Functor (not a lambda)
struct Functor
{
	void operator()() {}
};

// Functor with template operator()
struct TemplatedFunctor
{
	template <typename T>
	void operator()(T)
	{
	}
};

// Regular function
void RegularFunction() {}

// Function pointer type
using FnPtr = void (*)();

// Class with member function
struct MemberFunctionClass
{
	void memberFunction() {}
};

// Callable object with ref-qualified operator()
struct RefQualifiedFunctor
{
	void operator()() & {}  // L-value
	void operator()() && {} // R-value
};

TEST(CallableTraitsTest, LambdaDetection)
{
	auto lambda1 = []() {};
	EXPECT_TRUE(kun_kotek kun_ktk is_lambda_impl<decltype(lambda1)>::value);

	auto lambda2 = [](int x) { return x; };
	EXPECT_TRUE(kun_kotek kun_ktk is_lambda_impl<decltype(lambda2)>::value)
		<< "lambda2 (with int parameter) should be detected as a lambda.";

	// Generic lambda: now should be detected because our templated call
	// operator test uses a single int argument.
	auto lambda3 = [](auto x) { return x; };
	EXPECT_TRUE(kun_kotek kun_ktk is_lambda_impl<decltype(lambda3)>::value)
		<< "lambda3 (generic lambda) should be detected as a lambda.";
}

TEST(CallableTraitsTest, FunctorDetection)
{
	// A simple functor with non‑templated operator() should not be considered a
	// lambda.
	EXPECT_TRUE(kun_kotek kun_ktk is_lambda_impl<Functor>::value)
		<< "Functor should be detected as a lambda.";

	// Note: TemplatedFunctor will be detected as a lambda because it has a
	// templated operator() that accepts an int. In standard C++ there is no way
	// to reliably tell apart a generic lambda from a templated functor.
	EXPECT_TRUE(kun_kotek kun_ktk is_lambda_impl<TemplatedFunctor>::value)
		<< "TemplatedFunctor is detected as a lambda due to its templated call "
		   "operator.";

	EXPECT_FALSE(kun_kotek kun_ktk is_lambda_impl<RefQualifiedFunctor>::value)
		<< "RefQualifiedFunctor should not be detected as a lambda.";
}

TEST(CallableTraitsTest, RegularFunctionDetection)
{
	EXPECT_FALSE(kun_kotek kun_ktk is_lambda_impl<FnPtr>::value)
		<< "Function pointers should not be detected as lambdas.";
	EXPECT_TRUE((std::is_function_v<decltype(RegularFunction)>))
		<< "RegularFunction should be a regular function.";
}

TEST(CallableTraitsTest, MemberFunctionPointerDetection)
{
	EXPECT_FALSE(kun_kotek kun_ktk is_lambda_impl<
		decltype(&MemberFunctionClass::memberFunction)>::value)
		<< "Member function pointers should not be detected as lambdas.";
}

TEST(CallableTraitsTest, CallableDetection)
{
	auto lambda = []() {};
	EXPECT_TRUE(kun_kotek kun_ktk is_callable_v<decltype(RegularFunction)>);
	EXPECT_TRUE(kun_kotek kun_ktk is_callable_v<decltype(lambda)>)
		<< "Lambda should be callable.";
	EXPECT_TRUE(kun_kotek kun_ktk is_callable_v<Functor>)
		<< "Functor should be callable.";
	EXPECT_TRUE(kun_kotek kun_ktk is_callable_v<TemplatedFunctor>)
		<< "TemplatedFunctor should be callable.";
	EXPECT_TRUE(kun_kotek kun_ktk is_callable_v<FnPtr>)
		<< "Function pointer should be callable.";
	EXPECT_TRUE(kun_kotek kun_ktk
			is_callable_v<decltype(&MemberFunctionClass::memberFunction)>)
		<< "Member function pointer should be callable.";
	EXPECT_FALSE(kun_kotek kun_ktk is_callable_v<int>)
		<< "int is not callable.";
}

// Test cases
TEST(Utility, is_tuple_check)
{
	// Basic tuples
	static_assert(kun_kotek kun_ktk is_tuple_v<std::tuple<>>);
	static_assert(kun_kotek kun_ktk is_tuple_v<std::tuple<int>>);
	static_assert(kun_kotek kun_ktk is_tuple_v<std::tuple<int, float>>);
	static_assert(
		kun_kotek kun_ktk is_tuple_v<std::tuple<int, float, std::string>>);

	// Const/volatile qualified tuples
	static_assert(kun_kotek kun_ktk is_tuple_v<const std::tuple<int>>);
	static_assert(kun_kotek kun_ktk is_tuple_v<volatile std::tuple<int>>);
	static_assert(kun_kotek kun_ktk is_tuple_v<const volatile std::tuple<int>>);

	// Nested tuples
	static_assert(kun_kotek kun_ktk is_tuple_v<std::tuple<std::tuple<int>>>);
	static_assert(
		kun_kotek kun_ktk is_tuple_v<std::tuple<int, std::tuple<float>>>);

	// Negative tests
	static_assert(!kun_kotek kun_ktk is_tuple_v<int>);
	static_assert(!kun_kotek kun_ktk is_tuple_v<void>);
	static_assert(!kun_kotek kun_ktk is_tuple_v<std::string>);
	static_assert(!kun_kotek kun_ktk is_tuple_v<std::pair<int, int>>);
	static_assert(!kun_kotek kun_ktk is_tuple_v<std::array<int, 5>>);

	struct NotATuple
	{
	};
	static_assert(!kun_kotek kun_ktk is_tuple_v<NotATuple>);
}

TEST(Utility, is_in_variant_check)
{
	// Basic type checks
	using BasicVariant = std::variant<int, float, double>;
	static_assert(kun_kotek kun_ktk is_in_variant_v<int, BasicVariant>);
	static_assert(kun_kotek kun_ktk is_in_variant_v<float, BasicVariant>);
	static_assert(kun_kotek kun_ktk is_in_variant_v<double, BasicVariant>);
	static_assert(!kun_kotek kun_ktk is_in_variant_v<char, BasicVariant>);
	static_assert(
		!kun_kotek kun_ktk is_in_variant_v<std::string, BasicVariant>);

	// Check with cv-qualified types
	static_assert(!kun_kotek kun_ktk is_in_variant_v<const int, BasicVariant>);
	static_assert(
		!kun_kotek kun_ktk is_in_variant_v<volatile float, BasicVariant>);
	static_assert(!kun_kotek kun_ktk
					  is_in_variant_v<const volatile double, BasicVariant>);

	// Complex types
	using ComplexVariant =
		std::variant<std::string, std::vector<int>, std::tuple<int, float>>;
	static_assert(
		kun_kotek kun_ktk is_in_variant_v<std::string, ComplexVariant>);
	static_assert(
		kun_kotek kun_ktk is_in_variant_v<std::vector<int>, ComplexVariant>);
	static_assert(kun_kotek kun_ktk
			is_in_variant_v<std::tuple<int, float>, ComplexVariant>);
	static_assert(
		!kun_kotek kun_ktk is_in_variant_v<std::vector<float>, ComplexVariant>);
	static_assert(!kun_kotek kun_ktk
					  is_in_variant_v<std::tuple<float, int>, ComplexVariant>);

	// Reference types
	using RefVariant = std::variant<int&, const float&, std::string&>;
	static_assert(kun_kotek kun_ktk is_in_variant_v<int&, RefVariant>);
	static_assert(kun_kotek kun_ktk is_in_variant_v<const float&, RefVariant>);
	static_assert(kun_kotek kun_ktk is_in_variant_v<std::string&, RefVariant>);
	static_assert(!kun_kotek kun_ktk is_in_variant_v<double&, RefVariant>);

	// Empty variant
	using EmptyVariant = std::variant<>;
	static_assert(!kun_kotek kun_ktk is_in_variant_v<int, EmptyVariant>);
	static_assert(!kun_kotek kun_ktk is_in_variant_v<void, EmptyVariant>);

	// Monostate
	using MonostateVariant = std::variant<std::monostate, int>;
	static_assert(
		kun_kotek kun_ktk is_in_variant_v<std::monostate, MonostateVariant>);
	static_assert(kun_kotek kun_ktk is_in_variant_v<int, MonostateVariant>);
	static_assert(!kun_kotek kun_ktk is_in_variant_v<float, MonostateVariant>);

	// Custom types
	struct CustomType
	{
	};
	using CustomVariant = std::variant<CustomType, int>;
	static_assert(kun_kotek kun_ktk is_in_variant_v<CustomType, CustomVariant>);
	static_assert(!kun_kotek kun_ktk is_in_variant_v<float, CustomVariant>);
}

TEST(Utility, is_variant_check)
{
	// Basic variants
	static_assert(kun_kotek kun_ktk is_variant_v<std::variant<int>>);
	static_assert(kun_kotek kun_ktk is_variant_v<std::variant<int, float>>);
	static_assert(
		kun_kotek kun_ktk is_variant_v<std::variant<int, float, double>>);
	static_assert(kun_kotek kun_ktk is_variant_v<std::variant<std::string>>);

	// Empty variant
	static_assert(kun_kotek kun_ktk is_variant_v<std::variant<>>);

	// Variant with monostate
	static_assert(kun_kotek kun_ktk is_variant_v<std::variant<std::monostate>>);
	static_assert(
		kun_kotek kun_ktk is_variant_v<std::variant<std::monostate, int>>);

	// CV-qualified variants
	static_assert(kun_kotek kun_ktk is_variant_v<const std::variant<int>>);
	static_assert(kun_kotek kun_ktk is_variant_v<volatile std::variant<int>>);
	static_assert(
		kun_kotek kun_ktk is_variant_v<const volatile std::variant<int>>);

	// Complex types in variants
	static_assert(
		kun_kotek kun_ktk is_variant_v<std::variant<std::vector<int>>>);
	static_assert(
		kun_kotek kun_ktk is_variant_v<std::variant<std::tuple<int, float>>>);
	static_assert(
		kun_kotek kun_ktk is_variant_v<std::variant<std::array<int, 5>>>);
	static_assert(kun_kotek kun_ktk
			is_variant_v<std::variant<std::map<int, std::string>>>);

	// Reference types in variants
	static_assert(kun_kotek kun_ktk is_variant_v<std::variant<int&>>);
	static_assert(kun_kotek kun_ktk is_variant_v<std::variant<const int&>>);
	static_assert(kun_kotek kun_ktk is_variant_v<std::variant<int&&>>);

	// Nested variants
	static_assert(
		kun_kotek kun_ktk is_variant_v<std::variant<std::variant<int>>>);
	static_assert(
		kun_kotek kun_ktk is_variant_v<std::variant<int, std::variant<float>>>);

	// Custom types
	struct CustomType
	{
	};
	static_assert(kun_kotek kun_ktk is_variant_v<std::variant<CustomType>>);
	static_assert(
		kun_kotek kun_ktk is_variant_v<std::variant<CustomType, int>>);

	// Negative tests - not variants
	static_assert(!kun_kotek kun_ktk is_variant_v<int>);
	static_assert(!kun_kotek kun_ktk is_variant_v<void>);
	static_assert(!kun_kotek kun_ktk is_variant_v<std::string>);
	static_assert(!kun_kotek kun_ktk is_variant_v<std::vector<int>>);
	static_assert(!kun_kotek kun_ktk is_variant_v<std::tuple<int>>);
	static_assert(!kun_kotek kun_ktk is_variant_v<std::array<int, 5>>);
	static_assert(!kun_kotek kun_ktk is_variant_v<CustomType>);
	static_assert(!kun_kotek kun_ktk is_variant_v<int*>);
	static_assert(!kun_kotek kun_ktk is_variant_v<int&>);
	static_assert(!kun_kotek kun_ktk is_variant_v<const int>);
	static_assert(!kun_kotek kun_ktk is_variant_v<std::function<void()>>);

	// Pointer to variant is not a variant
	static_assert(!kun_kotek kun_ktk is_variant_v<std::variant<int>*>);
	static_assert(!kun_kotek kun_ktk is_variant_v<const std::variant<int>*>);

	// Reference to variant is not a variant
	static_assert(!kun_kotek kun_ktk is_variant_v<std::variant<int>&>);
	static_assert(!kun_kotek kun_ktk is_variant_v<const std::variant<int>&>);
	static_assert(!kun_kotek kun_ktk is_variant_v<std::variant<int>&&>);
}

TEST(Utility, are_args_in_variant_check)
{
	using MyVariant = std::variant<int, float, double, std::string>;

	// Single argument tests
	static_assert(
		kun_kotek kun_ktk are_args_in_variant<std::tuple<int>, MyVariant>());
	static_assert(
		kun_kotek kun_ktk are_args_in_variant<std::tuple<float>, MyVariant>());
	static_assert(kun_kotek kun_ktk
			are_args_in_variant<std::tuple<std::string>, MyVariant>());
	static_assert(
		!kun_kotek kun_ktk are_args_in_variant<std::tuple<char>, MyVariant>());

	// Multiple arguments tests
	static_assert(kun_kotek kun_ktk
			are_args_in_variant<std::tuple<int, float>, MyVariant>());
	static_assert(kun_kotek kun_ktk
			are_args_in_variant<std::tuple<double, std::string>, MyVariant>());
	static_assert(kun_kotek kun_ktk
			are_args_in_variant<std::tuple<int, float, double>, MyVariant>());
	static_assert(!kun_kotek kun_ktk
					  are_args_in_variant<std::tuple<int, char>, MyVariant>());

	// Empty tuple test
	static_assert(
		kun_kotek kun_ktk are_args_in_variant<std::tuple<>, MyVariant>());

	// CV-qualified types
	static_assert(!kun_kotek kun_ktk
					  are_args_in_variant<std::tuple<const int>, MyVariant>());
	static_assert(
		!kun_kotek kun_ktk
			are_args_in_variant<std::tuple<volatile float>, MyVariant>());
	static_assert(!kun_kotek kun_ktk are_args_in_variant<
				  std::tuple<const volatile double>, MyVariant>());

	// Complex variant
	using ComplexVariant =
		std::variant<std::vector<int>, std::tuple<int, float>>;
	static_assert(
		kun_kotek kun_ktk are_args_in_variant<std::tuple<std::vector<int>>,
			ComplexVariant>());
	static_assert(kun_kotek kun_ktk are_args_in_variant<
		std::tuple<std::tuple<int, float>>, ComplexVariant>());
	static_assert(
		!kun_kotek kun_ktk are_args_in_variant<std::tuple<std::vector<float>>,
			ComplexVariant>());
}

TEST(Utility, is_in_variant_check2)
{
	using MyVariant = std::variant<int, float, double, std::string>;

	// Basic type checks
	static_assert(kun_kotek kun_ktk is_in_variant_v<int, MyVariant>);
	static_assert(kun_kotek kun_ktk is_in_variant_v<float, MyVariant>);
	static_assert(kun_kotek kun_ktk is_in_variant_v<double, MyVariant>);
	static_assert(kun_kotek kun_ktk is_in_variant_v<std::string, MyVariant>);
	static_assert(!kun_kotek kun_ktk is_in_variant_v<char, MyVariant>);
	static_assert(!kun_kotek kun_ktk is_in_variant_v<unsigned int, MyVariant>);

	// CV-qualified types
	static_assert(!kun_kotek kun_ktk is_in_variant_v<const int, MyVariant>);
	static_assert(
		!kun_kotek kun_ktk is_in_variant_v<volatile float, MyVariant>);
	static_assert(
		!kun_kotek kun_ktk is_in_variant_v<const volatile double, MyVariant>);

	// Complex variant
	using ComplexVariant =
		std::variant<std::vector<int>, std::tuple<int, float>>;
	static_assert(
		kun_kotek kun_ktk is_in_variant_v<std::vector<int>, ComplexVariant>);
	static_assert(kun_kotek kun_ktk
			is_in_variant_v<std::tuple<int, float>, ComplexVariant>);
	static_assert(
		!kun_kotek kun_ktk is_in_variant_v<std::vector<float>, ComplexVariant>);
	static_assert(!kun_kotek kun_ktk
					  is_in_variant_v<std::tuple<float, int>, ComplexVariant>);

	// Reference types
	static_assert(!kun_kotek kun_ktk is_in_variant_v<int&, MyVariant>);
	static_assert(!kun_kotek kun_ktk is_in_variant_v<const float&, MyVariant>);
	static_assert(!kun_kotek kun_ktk is_in_variant_v<double&&, MyVariant>);

	// Pointer types
	static_assert(!kun_kotek kun_ktk is_in_variant_v<int*, MyVariant>);
	static_assert(!kun_kotek kun_ktk is_in_variant_v<const float*, MyVariant>);
	static_assert(!kun_kotek kun_ktk is_in_variant_v<void*, MyVariant>);

	// Empty variant
	using EmptyVariant = std::variant<>;
	static_assert(!kun_kotek kun_ktk is_in_variant_v<int, EmptyVariant>);
	static_assert(!kun_kotek kun_ktk is_in_variant_v<void, EmptyVariant>);

	// Variant with std::monostate
	using MonostateVariant = std::variant<std::monostate, int>;
	static_assert(
		kun_kotek kun_ktk is_in_variant_v<std::monostate, MonostateVariant>);
	static_assert(kun_kotek kun_ktk is_in_variant_v<int, MonostateVariant>);
	static_assert(!kun_kotek kun_ktk is_in_variant_v<float, MonostateVariant>);

	// Custom types
	struct CustomType
	{
	};
	using CustomVariant = std::variant<CustomType, int>;
	static_assert(kun_kotek kun_ktk is_in_variant_v<CustomType, CustomVariant>);
	static_assert(!kun_kotek kun_ktk is_in_variant_v<float, CustomVariant>);
}

TEST(Utility, are_callable_args_in_variant_check)
{
	using MyVariant = std::variant<int, float, double, std::string>;

	// Regular functions
	auto func1 = [](int) {};
	static_assert(
		kun_kotek kun_ktk are_callable_args_in_variant<MyVariant>(func1));

	auto func2 = [](int, float) {};
	static_assert(
		kun_kotek kun_ktk are_callable_args_in_variant<MyVariant>(func2));

	auto func3 = [](char) {}; // char is not in variant
	static_assert(
		!kun_kotek kun_ktk are_callable_args_in_variant<MyVariant>(func3));

	// No arguments
	auto func_no_args = []() {};
	static_assert(kun_kotek kun_ktk are_callable_args_in_variant<MyVariant>(
		func_no_args));

	// Function objects
	struct Functor1
	{
		void operator()(int, float) {}
	};
	static_assert(
		kun_kotek kun_ktk are_callable_args_in_variant<MyVariant>(Functor1{}));

	struct Functor2
	{
		void operator()(char) {} // char is not in variant
	};
	static_assert(
		!kun_kotek kun_ktk are_callable_args_in_variant<MyVariant>(Functor2{}));

	// Complex variant
	using ComplexVariant =
		std::variant<std::vector<int>, std::tuple<int, float>>;
	auto complex_func1 = [](std::vector<int>) {};
	auto complex_func2 = [](std::tuple<int, float>) {};
	auto complex_func3 = [](std::vector<float>) {}; // not in variant

	static_assert(
		kun_kotek kun_ktk are_callable_args_in_variant<ComplexVariant>(
			complex_func1));
	static_assert(
		kun_kotek kun_ktk are_callable_args_in_variant<ComplexVariant>(
			complex_func2));
	static_assert(
		!kun_kotek kun_ktk are_callable_args_in_variant<ComplexVariant>(
			complex_func3));

	// Reference and pointer types
	auto ref_func1 = [](int&) {};
	auto ref_func2 = [](const float&) {};
	auto ptr_func = [](int*) {};
	static_assert(
		!kun_kotek kun_ktk are_callable_args_in_variant<MyVariant>(ref_func1));
	static_assert(
		!kun_kotek kun_ktk are_callable_args_in_variant<MyVariant>(ref_func2));
	static_assert(
		!kun_kotek kun_ktk are_callable_args_in_variant<MyVariant>(ptr_func));

	// Multiple arguments with different combinations
	auto multi_func1 = [](int, float, double) {};
	auto multi_func2 = [](std::string, int, float) {};
	auto multi_func3 = [](int, char, float) {}; // char is not in variant

	static_assert(
		kun_kotek kun_ktk are_callable_args_in_variant<MyVariant>(multi_func1));
	static_assert(
		kun_kotek kun_ktk are_callable_args_in_variant<MyVariant>(multi_func2));
	static_assert(!kun_kotek kun_ktk are_callable_args_in_variant<MyVariant>(
		multi_func3));
}

TEST(Utility, check_args_test)
{
	using RuntimeVariant = std::variant<int, float, double, std::string>;
	using CompileTimeVariant =
		std::variant<int, float, double, std::string_view>;

	// Compile-time tests with std::array
	{
		// Valid arguments
		constexpr std::array<CompileTimeVariant, 3> valid_args = {
			CompileTimeVariant{42}, CompileTimeVariant{3.14f},
			CompileTimeVariant{std::string_view{"test"}}};

		static_assert(kun_kotek kun_ktk
				check_args<std::tuple<int, float, std::string_view>>(
					valid_args));

		// Invalid arguments (wrong order)
		constexpr std::array invalid_args{CompileTimeVariant{3.14f},
			CompileTimeVariant{42},
			CompileTimeVariant{std::string_view{"test"}}};

		static_assert(!kun_kotek kun_ktk
						  check_args<std::tuple<int, float, std::string_view>>(
							  invalid_args));

		// Empty tuple with empty array
		constexpr std::array<CompileTimeVariant, 0> empty_args{};
		static_assert(kun_kotek kun_ktk check_args<std::tuple<>>(empty_args));
	}

	// Runtime tests with std::vector
	{
		// Valid arguments
		std::vector<RuntimeVariant> valid_args{RuntimeVariant{42},
			RuntimeVariant{3.14f}, RuntimeVariant{std::string{"test"}}};

		EXPECT_TRUE(
			(kun_kotek kun_ktk check_args<std::tuple<int, float, std::string>>(
				valid_args)));

		// Invalid arguments (wrong type)
		std::vector<RuntimeVariant> invalid_args{RuntimeVariant{42},
			RuntimeVariant{3.14}, // double instead of float
			RuntimeVariant{std::string{"test"}}};

		EXPECT_FALSE(
			(kun_kotek kun_ktk check_args<std::tuple<int, float, std::string>>(
				invalid_args)));

		// Invalid arguments (wrong size)
		std::vector<RuntimeVariant> wrong_size_args{
			RuntimeVariant{42}, RuntimeVariant{3.14f}};

		EXPECT_FALSE(
			(kun_kotek kun_ktk check_args<std::tuple<int, float, std::string>>(
				wrong_size_args)));

		// Empty tuple with empty vector
		std::vector<RuntimeVariant> empty_args;
		EXPECT_TRUE((kun_kotek kun_ktk check_args<std::tuple<>>(empty_args)));
	}

	// Complex types
	{
		using ComplexRuntimeVariant =
			std::variant<std::vector<int>, std::tuple<int, float>>;
		std::vector<ComplexRuntimeVariant> complex_args{
			ComplexRuntimeVariant{std::vector<int>{1, 2, 3}},
			ComplexRuntimeVariant{std::tuple<int, float>{42, 3.14f}}};

		EXPECT_TRUE((kun_kotek kun_ktk check_args<
			std::tuple<std::vector<int>, std::tuple<int, float>>>(
			complex_args)));
	}
}

TEST(Utility, type_info_of_type)
{
	using MyTuple = std::tuple<int, float, std::string_view>;
	using MyVariant = std::variant<int, double, std::string_view>;
	using VectorContainer = std::vector<MyVariant>;
	using ArrayContainer = std::array<MyVariant, 3>;

	constexpr auto tuple_info =
		kun_kotek kun_ktk get_tuple_type_info<MyTuple>();
	constexpr auto vector_info =
		kun_kotek kun_ktk get_variant_container_type_info<VectorContainer>();
	constexpr auto array_info =
		kun_kotek kun_ktk get_variant_container_type_info<ArrayContainer>();

	KOTEK_MESSAGE_S(
		"tuple type info: {}", 1024, std::string_view(tuple_info.data()));
	KOTEK_MESSAGE_S(
		"vector type info: {}", 1024, std::string_view(vector_info.data()));
	KOTEK_MESSAGE_S(
		"array type info: {}", 1024, std::string_view(array_info.data()));
}

TEST(Utility, type_info_test)
{
	// Compile-time tests
	using CompileTimeVariant =
		std::variant<int, float, double, std::string_view>;
	constexpr std::array<CompileTimeVariant, 3> array_container{
		CompileTimeVariant{42}, CompileTimeVariant{3.14f},
		CompileTimeVariant{std::string_view{"test"}}};

	constexpr auto array_types =
		kun_kotek kun_ktk print_variant_container_types(array_container);
	KOTEK_MESSAGE_S(
		"Array types: {}", 1024, std::string_view(array_types.data()));

	// Runtime tests
	using RuntimeVariant = std::variant<int, float, double, std::string>;
	std::vector<RuntimeVariant> vector_container{RuntimeVariant{42},
		RuntimeVariant{3.14f}, RuntimeVariant{std::string{"test"}}};

	auto vector_types =
		kun_kotek kun_ktk print_variant_container_types(vector_container);
	KOTEK_MESSAGE_S(
		"Vector types: {}", 1024, std::string_view(vector_types.data()));

	// Test different order in vector
	vector_container = {RuntimeVariant{std::string{"first"}},
		RuntimeVariant{1.0}, RuntimeVariant{123}};

	vector_types =
		kun_kotek kun_ktk print_variant_container_types(vector_container);
	KOTEK_MESSAGE_S("Vector types (reordered): {}", 1024,
		std::string_view(vector_types.data()));

	// Test empty vector
	std::vector<RuntimeVariant> empty_vector;
	vector_types =
		kun_kotek kun_ktk print_variant_container_types(empty_vector);
	KOTEK_MESSAGE_S(
		"Empty vector types: {}", 1024, std::string_view(vector_types.data()));

	// Test complex types in vector
	using ComplexVariant =
		std::variant<std::vector<int>, std::tuple<int, float>>;
	std::vector<ComplexVariant> complex_vector{
		ComplexVariant{std::vector<int>{1, 2, 3}},
		ComplexVariant{std::tuple<int, float>{42, 3.14f}}};

	vector_types =
		kun_kotek kun_ktk print_variant_container_types(complex_vector);
	KOTEK_MESSAGE_S("Complex vector types: {}", 1024,
		std::string_view(vector_types.data()));
}

	#endif
#endif

void RegisterTests_Utility_ForModule_Core()
{
#ifdef KOTEK_USE_TESTS
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
