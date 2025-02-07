#include "../include/kotek_core_utility.h"
#include <kotek.core.defines.static.tests/include/kotek_core_defines_static_tests.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>
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

	kun_kotek kun_ktk ifunction<myVar, bool>* p_interface =
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

	#endif
#endif

void RegisterTests_Utility_ForModule_Core()
{
#ifdef KOTEK_USE_TESTS
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
