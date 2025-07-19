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

TEST(Utility, thread_naming) 
{
	std::thread kek([] {
		kun_ktk set_thread_name("kek");	
	});

	kek.join();
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
	constexpr auto vector_info = kun_kotek kun_ktk
	get_variant_container_value_type_info<VectorContainer>();
	constexpr auto array_info = kun_kotek kun_ktk
	get_variant_container_value_type_info<ArrayContainer>();

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
		kun_kotek kun_ktk get_variant_container_types(array_container);
	KOTEK_MESSAGE_S(
		"Array types: {}", 1024, std::string_view(array_types.data()));

	// Runtime tests
	using RuntimeVariant = std::variant<int, float, double, std::string>;
	std::vector<RuntimeVariant> vector_container{RuntimeVariant{42},
		RuntimeVariant{3.14f}, RuntimeVariant{std::string{"test"}}};

	auto vector_types =
		kun_kotek kun_ktk get_variant_container_types(vector_container);
	KOTEK_MESSAGE_S(
		"Vector types: {}", 1024, std::string_view(vector_types.data()));

	// Test different order in vector
	vector_container = {RuntimeVariant{std::string{"first"}},
		RuntimeVariant{1.0}, RuntimeVariant{123}};

	vector_types =
		kun_kotek kun_ktk get_variant_container_types(vector_container);
	KOTEK_MESSAGE_S("Vector types (reordered): {}", 1024,
		std::string_view(vector_types.data()));

	// Test empty vector
	std::vector<RuntimeVariant> empty_vector;
	vector_types = kun_kotek kun_ktk get_variant_container_types(empty_vector);
	KOTEK_MESSAGE_S(
		"Empty vector types: {}", 1024, std::string_view(vector_types.data()));

	// Test complex types in vector
	using ComplexVariant =
		std::variant<std::vector<int>, std::tuple<int, float>>;
	std::vector<ComplexVariant> complex_vector{
		ComplexVariant{std::vector<int>{1, 2, 3}},
		ComplexVariant{std::tuple<int, float>{42, 3.14f}}};

	vector_types =
		kun_kotek kun_ktk get_variant_container_types(complex_vector);
	KOTEK_MESSAGE_S("Complex vector types: {}", 1024,
		std::string_view(vector_types.data()));
}

TEST(Utility, fill_vector_variant_test)
{
	std::vector<std::string_view> input{"42", "3.14", "2.718", "hello"};

	auto result = kun_kotek kun_ktk
		fill_vector_variant<std::variant<int, float, double, std::string>,
			std::vector<std::variant<int, float, double, std::string>>,
			std::vector<std::string_view>, int, float, double, std::string>(
			input);

	EXPECT_EQ(result.size(), 4);
	EXPECT_TRUE(std::holds_alternative<int>(result[0]));
	EXPECT_TRUE(std::holds_alternative<float>(result[1]));
	EXPECT_TRUE(std::holds_alternative<double>(result[2]));
	EXPECT_TRUE(std::holds_alternative<std::string>(result[3]));

	EXPECT_EQ(std::get<int>(result[0]), 42);
	EXPECT_FLOAT_EQ(std::get<float>(result[1]), 3.14f);
	EXPECT_DOUBLE_EQ(std::get<double>(result[2]), 2.718);
	EXPECT_EQ(std::get<std::string>(result[3]), "hello");

	// Test invalid input
	std::vector<std::string_view> invalid_input{
		"not_a_number", "not_b_number", "not_c_number"};

	(kun_kotek kun_ktk fill_vector_variant<std::variant<int, float, double>,
		std::vector<std::variant<int, float, double>>,
		std::vector<std::string_view>, int, float, double>(invalid_input));
}

TEST(Utility, hash_constexpr) 
{
	using namespace std::string_view_literals;

	// Test basic hash computation
	constexpr std::string_view transform = "transform"sv;
	constexpr std::string_view renderable = "renderable"sv;
	constexpr std::string_view camera = "camera"sv;
	constexpr std::string_view light = "light"sv;
	constexpr std::string_view physics = "physics"sv;
	constexpr std::string_view audio = "audio"sv;

	// Use the existing fnv1a_32 function from the codebase
	constexpr kun_kotek kun_ktk size_t hash_transform = kun_kotek kun_ktk fnv1a_32(transform);
	constexpr kun_kotek kun_ktk size_t hash_renderable =
		kun_kotek kun_ktk fnv1a_32(renderable);
	constexpr kun_kotek kun_ktk size_t hash_camera =
		kun_kotek kun_ktk fnv1a_32(camera);
	constexpr kun_kotek kun_ktk size_t hash_light =
		kun_kotek kun_ktk fnv1a_32(light);
	constexpr kun_kotek kun_ktk size_t hash_physics =
		kun_kotek kun_ktk fnv1a_32(physics);
	constexpr kun_kotek kun_ktk size_t hash_audio =
		kun_kotek kun_ktk fnv1a_32(audio);

	// Test same string produces same hash
	constexpr std::string_view transform_2 = "transform"sv;
	constexpr kun_kotek kun_ktk size_t hash_transform_2 =
		kun_kotek kun_ktk fnv1a_32(transform_2);
	static_assert(hash_transform == hash_transform_2,
		"Same string must produce same hash");

	// Test different strings produce different hashes
	static_assert(hash_transform != hash_renderable,
		"Hash collision between transform and renderable");
	static_assert(hash_transform != hash_camera,
		"Hash collision between transform and camera");
	static_assert(hash_transform != hash_light,
		"Hash collision between transform and light");
	static_assert(hash_transform != hash_physics,
		"Hash collision between transform and physics");
	static_assert(hash_transform != hash_audio,
		"Hash collision between transform and audio");

	static_assert(hash_renderable != hash_camera,
		"Hash collision between renderable and camera");
	static_assert(hash_renderable != hash_light,
		"Hash collision between renderable and light");
	static_assert(hash_renderable != hash_physics,
		"Hash collision between renderable and physics");
	static_assert(hash_renderable != hash_audio,
		"Hash collision between renderable and audio");

	static_assert(
		hash_camera != hash_light, "Hash collision between camera and light");
	static_assert(hash_camera != hash_physics,
		"Hash collision between camera and physics");
	static_assert(
		hash_camera != hash_audio, "Hash collision between camera and audio");

	static_assert(
		hash_light != hash_physics, "Hash collision between light and physics");
	static_assert(
		hash_light != hash_audio, "Hash collision between light and audio");

	static_assert(
		hash_physics != hash_audio, "Hash collision between physics and audio");

	// Display hash values for verification
	KOTEK_MESSAGE("Hash values:");
	KOTEK_MESSAGE("transform: {}", hash_transform);
	KOTEK_MESSAGE("renderable: {}", hash_renderable);
	KOTEK_MESSAGE("camera: {}", hash_camera);
	KOTEK_MESSAGE("light: {}", hash_light);
	KOTEK_MESSAGE("physics: {}", hash_physics);
	KOTEK_MESSAGE("audio: {}", hash_audio);
}

TEST(Utility, DrillingCompilerHashTest) 
{
	using namespace std::string_view_literals;

	// ==================== COMPONENT NAMES ====================
	constexpr std::array<std::string_view, 50> component_names = {
		// Common game components
		"transform"sv, "renderable"sv, "camera"sv, "light"sv, "physics"sv,
		"audio"sv, "animation"sv, "input"sv, "health"sv, "damage"sv,
		"collision"sv, "trigger"sv, "navigation"sv, "pathfinding"sv,
		"inventory"sv, "character"sv, "enemy"sv, "player"sv, "projectile"sv,
		"particle"sv, "script"sv, "network"sv, "ui"sv, "text"sv, "sprite"sv,
		"model"sv, "rigidbody"sv, "joint"sv, "constraint"sv, "material"sv,
		"mesh"sv, "texture"sv, "shader"sv, "terrain"sv, "vegetation"sv,
		"water"sv, "skybox"sv, "atmosphere"sv, "vehicle"sv, "weapon"sv,
		"armor"sv, "consumable"sv, "quest"sv, "dialogue"sv, "interaction"sv,
		"ai"sv, "behavior"sv, "state"sv, "timer"sv, "lifecycle"sv};

	// ==================== CONFIG SECTION NAMES ====================
	constexpr std::array<std::string_view, 40> config_sections = {
		// Engine configuration sections
		"engine"sv, "rendering"sv, "graphics"sv, "audio"sv, "input"sv,
		"network"sv, "physics"sv, "resources"sv, "memory"sv, "threading"sv,
		"scripting"sv, "debug"sv, "optimization"sv, "logging"sv, "paths"sv,
		"platform"sv, "window"sv, "display"sv, "performance"sv, "quality"sv,
		"shadows"sv, "lighting"sv, "postprocessing"sv, "textures"sv, "models"sv,
		"animations"sv, "particles"sv, "sounds"sv, "music"sv, "controls"sv,
		"keybindings"sv, "gamepad"sv, "mouse"sv, "keyboard"sv, "touch"sv,
		"gameplay"sv, "saving"sv, "loading"sv, "preferences"sv};

	// ==================== EVENT NAMES ====================
	constexpr std::array<std::string_view, 30> event_names = {
		// Common engine events
		"on_start"sv, "on_update"sv, "on_fixed_update"sv, "on_late_update"sv,
		"on_render"sv, "on_collision_enter"sv, "on_collision_exit"sv,
		"on_trigger_enter"sv, "on_trigger_exit"sv, "on_destroy"sv,
		"on_enable"sv, "on_disable"sv, "on_pause"sv, "on_resume"sv,
		"on_key_down"sv, "on_key_up"sv, "on_mouse_down"sv, "on_mouse_up"sv,
		"on_mouse_move"sv, "on_touch_begin"sv, "on_touch_end"sv, "on_gesture"sv,
		"on_focus_gain"sv, "on_focus_lost"sv, "on_level_load"sv,
		"on_level_unload"sv, "on_save"sv, "on_load"sv, "on_quit"sv,
		"on_error"sv};

	// ==================== RESOURCE PATHS ====================
	constexpr std::array<std::string_view, 25> resource_paths = {
		// Common resource paths
		"textures/diffuse"sv, "textures/normal"sv, "textures/specular"sv,
		"textures/emission"sv, "models/characters"sv, "models/environment"sv,
		"models/weapons"sv, "models/vehicles"sv, "audio/sfx"sv, "audio/music"sv,
		"audio/voices"sv, "audio/ambient"sv, "shaders/vertex"sv,
		"shaders/fragment"sv, "shaders/compute"sv, "shaders/geometry"sv,
		"data/levels"sv, "data/quests"sv, "data/items"sv, "data/npcs"sv,
		"scripts/game"sv, "scripts/ui"sv, "scripts/ai"sv, "scripts/cutscenes"sv,
		"scripts/events"sv};

	// ==================== SYSTEM NAMES ====================
	constexpr std::array<std::string_view, 20> system_names = {// Engine systems
		"render_system"sv, "physics_system"sv, "audio_system"sv,
		"input_system"sv, "animation_system"sv, "collision_system"sv,
		"particle_system"sv, "ai_system"sv, "script_system"sv,
		"networking_system"sv, "ui_system"sv, "resource_system"sv,
		"event_system"sv, "scene_system"sv, "camera_system"sv,
		"lighting_system"sv, "navigation_system"sv, "inventory_system"sv,
		"dialogue_system"sv, "quest_system"sv};

	// ==================== SPECIAL CASES ====================
	// Different character cases to test case sensitivity
	constexpr std::array<std::string_view, 10> case_variants = {"Transform"sv,
		"TRANSFORM"sv, "transform"sv, "Renderable"sv, "RENDERABLE"sv,
		"renderable"sv, "PhysicsSystem"sv, "PHYSICS_SYSTEM"sv,
		"physics_system"sv, "physicsSystem"sv};

	// Empty and very short strings
	constexpr std::array<std::string_view, 5> edge_cases = {
		""sv, "a"sv, "ab"sv, "abc"sv, "1234"sv};

	// Very long strings to test hash distribution
	constexpr std::array<std::string_view, 5> long_strings = {
		"very_long_component_name_that_exceeds_normal_length_for_testing_hash_distribution"sv,
		"another_extremely_long_string_for_testing_hash_function_with_many_characters_included"sv,
		"configuration_section_with_a_detailed_and_specific_purpose_that_is_verbose_in_nature"sv,
		"resource_path_with_multiple_directories_and_subdirectories_to_test_forward_slash_handling"sv,
		"event_handler_callback_registration_for_complex_interaction_management_in_the_engine_core"sv};

	// Similar strings that differ slightly
	constexpr std::array<std::string_view, 10> similar_strings = {
		"transform_component"sv, "transform_system"sv, "transform_data"sv,
		"physics_component"sv, "physics_system"sv, "physics_data"sv,
		"resource_load"sv, "resource_unload"sv, "resource_reload"sv,
		"resource_manager"sv};

	// Strings with special characters
	constexpr std::array<std::string_view, 10> special_chars = {
		"component/transform"sv, "component/renderable"sv, "config.rendering"sv,
		"config.physics"sv, "event:on_collision"sv, "event:on_trigger"sv,
		"resource-texture"sv, "resource-model"sv, "system.update()"sv,
		"system.render()"sv};

	// Combined array of all test strings
	constexpr std::array<std::string_view,
		component_names.size() + config_sections.size() + event_names.size() +
			resource_paths.size() + system_names.size() + case_variants.size() +
			edge_cases.size() + long_strings.size() + similar_strings.size() +
			special_chars.size()>
		all_strings = []()
	{
		std::array<std::string_view,
			component_names.size() + config_sections.size() +
				event_names.size() + resource_paths.size() +
				system_names.size() + case_variants.size() + edge_cases.size() +
				long_strings.size() + similar_strings.size() +
				special_chars.size()>
			result = {};

		size_t index = 0;

		// Copy all arrays into the combined array
		for (auto& str : component_names)
			result[index++] = str;
		for (auto& str : config_sections)
			result[index++] = str;
		for (auto& str : event_names)
			result[index++] = str;
		for (auto& str : resource_paths)
			result[index++] = str;
		for (auto& str : system_names)
			result[index++] = str;
		for (auto& str : case_variants)
			result[index++] = str;
		for (auto& str : edge_cases)
			result[index++] = str;
		for (auto& str : long_strings)
			result[index++] = str;
		for (auto& str : similar_strings)
			result[index++] = str;
		for (auto& str : special_chars)
			result[index++] = str;

		return result;
	}();

	// ==================== HASH CALCULATIONS ====================
	// Calculate all hashes at compile time
	constexpr auto all_hashes = []()
	{
		std::array<kun_kotek kun_ktk size_t, all_strings.size()> hashes = {};
		for (size_t i = 0; i < all_strings.size(); ++i)
		{
			hashes[i] = kun_kotek kun_ktk fnv1a_32(all_strings[i]);
		}
		return hashes;
	}();

	// ==================== COLLISION DETECTION ====================
	// Check for any collisions at compile time
	constexpr bool has_collision = []()
	{
		for (size_t i = 0; i < all_hashes.size(); ++i)
		{
			for (size_t j = i + 1; j < all_hashes.size(); ++j)
			{
				if (all_hashes[i] == all_hashes[j] &&
					all_strings[i] != all_strings[j])
				{
					return true; // Collision detected
				}
			}
		}
		return false; // No collisions
	}();

	static_assert(!has_collision, "Hash collision detected in fnv1a_32!");

	// ==================== RUNTIME VERIFICATION ====================
	// Also verify at runtime and print detailed information
	KOTEK_MESSAGE(
		"Verifying {} strings for hash collisions", all_strings.size());

	// Count unique hashes using a sorted array approach
	std::array<kun_kotek kun_ktk size_t, all_strings.size()> hash_values;
	for (size_t i = 0; i < all_strings.size(); ++i)
	{
		hash_values[i] = kun_kotek kun_ktk fnv1a_32(all_strings[i]);
	}

	// Sort the hashes to make duplicates adjacent
	std::sort(hash_values.begin(), hash_values.end());

	// Count unique hashes by comparing adjacent elements
	kun_kotek kun_ktk size_t unique_hash_count =
		1; // Start with 1 for the first hash
	for (size_t i = 1; i < hash_values.size(); ++i)
	{
		if (hash_values[i] != hash_values[i - 1])
		{
			unique_hash_count++;
		}
	}

	KOTEK_MESSAGE("Found {} unique hashes from {} strings", unique_hash_count,
		all_strings.size());

	// Count unique strings (also using an array)
	std::array<std::string_view, all_strings.size()> unique_strings_arr;
	kun_kotek kun_ktk size_t unique_strings_count = 0;

	for (auto& str : all_strings)
	{
		bool found = false;
		for (size_t i = 0; i < unique_strings_count; ++i)
		{
			if (str == unique_strings_arr[i])
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			unique_strings_arr[unique_strings_count++] = str;
		}
	}

	KOTEK_MESSAGE("Expected {} unique hashes (based on unique strings)",
		unique_strings_count);

	EXPECT_EQ(unique_hash_count, unique_strings_count)
		<< "Number of unique hashes should match number of unique strings";

	// Detailed check for any runtime collisions
	bool runtime_collision_found = false;
	for (size_t i = 0; i < all_strings.size(); ++i)
	{
		for (size_t j = i + 1; j < all_strings.size(); ++j)
		{
			if (all_strings[i] != all_strings[j])
			{ // Different strings
				auto hash_i = kun_kotek kun_ktk fnv1a_32(all_strings[i]);
				auto hash_j = kun_kotek kun_ktk fnv1a_32(all_strings[j]);

				if (hash_i == hash_j)
				{
					runtime_collision_found = true;
					KOTEK_MESSAGE_WARNING("Hash collision detected: '{}' and "
					                      "'{}' both hash to {}",
						all_strings[i], all_strings[j], hash_i);
				}
			}
		}
	}

	EXPECT_FALSE(runtime_collision_found)
		<< "No collisions should be found at runtime";

	// ==================== HASH DISTRIBUTION ANALYSIS ====================
	// Analyze hash distribution (bit patterns)
	constexpr size_t NUM_BITS = sizeof(kun_kotek kun_ktk size_t) * 8;
	std::array<int, NUM_BITS> bit_counts = {};

	for (auto hash : all_hashes)
	{
		for (size_t bit = 0; bit < NUM_BITS; ++bit)
		{
			if ((hash & (1ULL << bit)) != 0)
			{
				bit_counts[bit]++;
			}
		}
	}

	// Calculate bit distribution stats
	double avg_bits = 0;
	int min_bits = all_hashes.size();
	int max_bits = 0;
	double bit_variance = 0;

	for (size_t bit = 0; bit < NUM_BITS; ++bit)
	{
		avg_bits += bit_counts[bit];
		min_bits = std::min(min_bits, bit_counts[bit]);
		max_bits = std::max(max_bits, bit_counts[bit]);
	}
	avg_bits /= NUM_BITS;

	for (size_t bit = 0; bit < NUM_BITS; ++bit)
	{
		bit_variance +=
			(bit_counts[bit] - avg_bits) * (bit_counts[bit] - avg_bits);
	}
	bit_variance /= NUM_BITS;

	double bit_stddev = std::sqrt(bit_variance);

	KOTEK_MESSAGE("Hash bit distribution stats:");
	KOTEK_MESSAGE("  Average bits set: {:.2f}", avg_bits);
	KOTEK_MESSAGE("  Min bits set: {}", min_bits);
	KOTEK_MESSAGE("  Max bits set: {}", max_bits);
	KOTEK_MESSAGE("  Bit standard deviation: {:.2f}", bit_stddev);

	// Expect reasonable bit distribution
	double expected_avg = all_hashes.size() / 2.0;
	double tolerance = expected_avg * 0.3; // Allow 30% deviation
	EXPECT_NEAR(avg_bits, expected_avg, tolerance)
		<< "Bit distribution should be roughly balanced";

	// ==================== INDIVIDUAL HASH VERIFICATION ====================
	// Verify specific important strings hash consistently
	KOTEK_MESSAGE("Verifying important string hashes:");
	for (auto& component :
		{"transform"sv, "physics"sv, "renderable"sv, "camera"sv, "light"sv})
	{
		kun_kotek kun_ktk size_t hash = kun_kotek kun_ktk fnv1a_32(component);
		KOTEK_MESSAGE("  '{}' hash: {:#x}", component, hash);
	}

	// Test passes if all assertions pass!
	KOTEK_MESSAGE(
		"fnv1a_32 hash function passed all collision tests for {} strings!",
		all_strings.size());
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
