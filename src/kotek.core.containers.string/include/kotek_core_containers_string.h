#pragma once

#include "kotek_std_alias_string.h"
#include "kotek_std_alias_static_string.h"
#include "kotek_std_alias_hybrid_string.h"

#if defined(KOTEK_USE_LIBRARY_TYPE_EMB) && \
	defined(KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS)

	#define ktk_cstring kun_kotek kun_ktk static_cstring
	#define KTK_CSTRING kun_kotek kun_ktk static_cstring
	#define ktkCString kun_kotek kun_ktk static_cstring

	#define ktk_cstring_view kun_kotek kun_ktk static_cstring_view
	#define KTK_CSTRING_VIEW kun_kotek kun_ktk static_cstring_view
	#define ktkCStringView kun_kotek kun_ktk static_cstring_view

	#define ktk_wstring kun_kotek kun_ktk static_wstring
	#define KTK_WSTRING kun_kotek kun_ktk static_wstring
	#define ktkWString kun_kotek kun_ktk static_wstring

	#define ktk_wstring_view kun_kotek kun_ktk static_wstring_view
	#define KTK_WSTRING_VIEW kun_kotek kun_ktk static_wstring_view
	#define ktkWStringView kun_kotek kun_ktk static_wstring_view

	#define ktk_u8string kun_kotek kun_ktk static_u8string
	#define KTK_U8STRING kun_kotek kun_ktk static_u8string
	#define ktkU8String kun_kotek kun_ktk static_u8string

	#define ktk_u8string_view kun_kotek kun_ktk static_u8string_view
	#define KTK_U8STRING_VIEW kun_kotek kun_ktk static_u8string_view
	#define ktkU8StringView kun_kotek kun_ktk static_u8string_view

	#define ktk_u16string kun_kotek kun_ktk static_u16string
	#define KTK_U16STRING kun_kotek kun_ktk static_u16string
	#define ktkU16String kun_kotek kun_ktk static_u16string

	#define ktk_u16string_view kun_kotek kun_ktk static_u16string_view
	#define KTK_U16STRING_VIEW kun_kotek kun_ktk static_u16string_view
	#define ktkU16StringView kun_kotek kun_ktk static_u16string_view

	#define ktk_u32string kun_kotek kun_ktk static_u32string
	#define KTK_U32STRING kun_kotek kun_ktk static_u32string
	#define ktkU32String kun_kotek kun_ktk static_u32string

	#define ktk_u32string_view kun_kotek kun_ktk static_u32string_view
	#define KTK_U32STRING_VIEW kun_kotek kun_ktk static_u32string_view
	#define ktkU32StringView kun_kotek kun_ktk static_u32string_view

	#define ktk_ustring kun_kotek kun_ktk static_ustring
	#define KTK_USTRING kun_kotek kun_ktk static_ustring
	#define ktkUString kun_kotek kun_ktk static_ustring

	#define ktk_ustring_view kun_kotek kun_ktk static_ustring_view
	#define KTK_USTRING_VIEW kun_kotek kun_ktk static_ustring_view
	#define ktkUStringView kun_kotek kun_ktk static_ustring_view

#else

	#define ktk_string kun_kotek kun_ktk cstring
	#define KTK_STRING kun_kotek kun_ktk cstring
	#define ktkString kun_kotek kun_ktk cstring

	#define ktk_string_view kun_kotek kun_ktk cstring_view
	#define KTK_STRING_VIEW kun_kotek kun_ktk cstring_view
	#define ktkStringView kun_kotek kun_ktk cstring_view

	#define ktk_wstring kun_kotek kun_ktk wstring
	#define KTK_WSTRING kun_kotek kun_ktk wstring
	#define ktkWString kun_kotek kun_ktk wstring

	#define ktk_wstring_view kun_kotek kun_ktk wstring_view
	#define KTK_WSTRING_VIEW kun_kotek kun_ktk wstring_view
	#define ktkWStringView kun_kotek kun_ktk wstring_view

	#define ktk_u8string kun_kotek kun_ktk u8string
	#define KTK_U8STRING kun_kotek kun_ktk u8string
	#define ktkU8String kun_kotek kun_ktk u8string

	#define ktk_u8string_view kun_kotek kun_ktk u8string_view
	#define KTK_U8STRING_VIEW kun_kotek kun_ktk u8string_view
	#define ktkU8StringView kun_kotek kun_ktk u8string_view

	#define ktk_u16string kun_kotek kun_ktk u16string
	#define KTK_U16STRING kun_kotek kun_ktk u16string
	#define ktkU16String kun_kotek kun_ktk u16string

	#define ktk_u16string_view kun_kotek kun_ktk u16string_view
	#define KTK_U16STRING_VIEW kun_kotek kun_ktk u16string_view
	#define ktkU16StringView kun_kotek kun_ktk u16string_view

	#define ktk_u32string kun_kotek kun_ktk u32string
	#define KTK_U32STRING kun_kotek kun_ktk u32string
	#define ktkU32String kun_kotek kun_ktk u32string

	#define ktk_u32string_view kun_kotek kun_ktk u32string_view
	#define KTK_U32STRING_VIEW kun_kotek kun_ktk u32string_view
	#define ktkU32String kun_kotek kun_ktk u32string_view

	#define ktk_ustring kun_kotek kun_ktk ustring
	#define KTK_USTRING kun_kotek kun_ktk ustring
	#define ktkUString kun_kotek kun_ktk ustring

	#define ktk_ustring_view kun_kotek kun_ktk ustring_view
	#define KTK_USTRING_VIEW kun_kotek kun_ktk ustring_view
	#define ktkUStringView kun_kotek kun_ktk ustring_view

#endif

#ifdef KOTEK_USE_LIBRARY_TYPE_EMB
static_assert(
	std::is_same_v<kun_kotek kun_ktk static_cstring<1>, ktk_cstring<1>>,
	"If library type was defined as EMB (aka static) it means that all "
	"containers that "
	"kotek framework provides to use ARE with static_ prefix it means that "
	"this cstring "
	"container is expected as static_cstring implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk static_u8string<1>, ktk_u8string<1>>,
	"If library type was defined as EMB (aka static) it means that all "
	"containers that "
	"kotek framework provides to use ARE with static_ prefix it means that "
	"this u8string "
	"container is expected as static_u8string implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk static_u16string<1>, ktk_u16string<1>>,
	"If library type was defined as EMB (aka static) it means that all "
	"containers that "
	"kotek framework provides to use ARE with static_ prefix it means that "
	"this u16string "
	"container is expected as static_u16string implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk static_u32string<1>, ktk_u32string<1>>,
	"If library type was defined as EMB (aka static) it means that all "
	"containers that "
	"kotek framework provides to use ARE with static_ prefix it means that "
	"this u32string "
	"container is expected as static_u32string implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk static_wstring<1>, ktk_wstring<1>>,
	"If library type was defined as EMB (aka static) it means that all "
	"containers that "
	"kotek framework provides to use ARE with static_ prefix it means that "
	"this wstring "
	"container is expected as static_wstring implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk static_cstring_view, ktk_cstring_view>,
	"If library type was defined as EMB (aka static) it means that all "
	"containers that "
	"kotek framework provides to use ARE with static_ prefix it means that "
	"this cstring_view "
	"container is expected as static_cstring_view implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk static_u8string_view, ktk_u8string_view>,
	"If library type was defined as EMB (aka static) it means that all "
	"containers that "
	"kotek framework provides to use ARE with static_ prefix it means that "
	"this u8string_view "
	"container is expected as static_u8string_view implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk static_u16string_view, ktk_u16string_view>,
	"If library type was defined as EMB (aka static) it means that all "
	"containers that "
	"kotek framework provides to use ARE with static_ prefix it means that "
	"this u16string_view "
	"container is expected as static_u16string_view implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk static_u32string_view, ktk_u32string_view>,
	"If library type was defined as EMB (aka static) it means that all "
	"containers that "
	"kotek framework provides to use ARE with static_ prefix it means that "
	"this u32string_view "
	"container is expected as static_u32string_view implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk static_wstring_view, ktk_wstring_view>,
	"If library type was defined as EMB (aka static) it means that all "
	"containers that "
	"kotek framework provides to use ARE with static_ prefix it means that "
	"this wstring_view "
	"container is expected as static_wstring_view implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_DYN)
static_assert(std::is_same_v<kun_kotek kun_ktk cstring<1>, ktk_cstring<1>>,
	"If library type was defined as DYN (aka dynamic) it means that all "
	"containers that "
	"kotek framework provides to use ARE WITHOUT static_ prefix and hybrid_ "
	"prefix it means that "
	"this cstring "
	"container is expected as cstring implementation");

static_assert(std::is_same_v<kun_kotek kun_ktk u8string<1>, ktk_u8string<1>>,
	"If library type was defined as DYN (aka dynamic) it means that all "
	"containers that "
	"kotek framework provides to use ARE WITHOUT static_ prefix and hybrid_ "
	"prefix it means that "
	"this u8string "
	"container is expected as u8string implementation");

static_assert(std::is_same_v<kun_kotek kun_ktk u16string<1>, ktk_u16string<1>>,
	"If library type was defined as DYN (aka dynamic) it means that all "
	"containers that "
	"kotek framework provides to use ARE WITHOUT static_ prefix and hybrid_ "
	"prefix it means that "
	"this u16string "
	"container is expected as u16string implementation");

static_assert(std::is_same_v<kun_kotek kun_ktk u32string<1>, ktk_u32string<1>>,
	"If library type was defined as DYN (aka dynamic) it means that all "
	"containers that "
	"kotek framework provides to use ARE WITHOUT static_ prefix and hybrid_ "
	"prefix it means that "
	"this u32string "
	"container is expected as u32string implementation");

static_assert(std::is_same_v<kun_kotek kun_ktk wstring<1>, ktk_wstring<1>>,
	"If library type was defined as DYN (aka dynamic) it means that all "
	"containers that "
	"kotek framework provides to use ARE WITHOUT static_ prefix and hybrid_ "
	"prefix it means that "
	"this wstring "
	"container is expected as wstring implementation");

static_assert(std::is_same_v<kun_kotek kun_ktk cstring_view, ktk_cstring_view>,
	"If library type was defined as DYN (aka dynamic) it means that all "
	"containers that "
	"kotek framework provides to use ARE WITHOUT static_ prefix and hybrid_ "
	"prefix it means that "
	"this cstring_view "
	"container is expected as cstring_view implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk u8string_view, ktk_u8string_view>,
	"If library type was defined as DYN (aka dynamic) it means that all "
	"containers that "
	"kotek framework provides to use ARE WITHOUT static_ prefix and hybrid_ "
	"prefix it means that "
	"this u8string_view "
	"container is expected as u8string_view implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk u16string_view, ktk_u16string_view>,
	"If library type was defined as DYN (aka dynamic) it means that all "
	"containers that "
	"kotek framework provides to use ARE WITHOUT static_ prefix and hybrid_ "
	"prefix it means that "
	"this u16string_view "
	"container is expected as u16string_view implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk u32string_view, ktk_u32string_view>,
	"If library type was defined as DYN (aka dynamic) it means that all "
	"containers that "
	"kotek framework provides to use ARE WITHOUT static_ prefix and hybrid_ "
	"prefix it means that "
	"this u32string_view "
	"container is expected as u32string_view implementation");

static_assert(std::is_same_v<kun_kotek kun_ktk wstring_view, ktk_wstring_view>,
	"If library type was defined as DYN (aka dynamic) it means that all "
	"containers that "
	"kotek framework provides to use ARE WITHOUT static_ prefix and hybrid_ "
	"prefix it means that "
	"this wstring_view "
	"container is expected as wstring_view implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_HYB)
static_assert(
	std::is_same_v<kun_kotek kun_ktk hybrid_cstring<1>, ktk_cstring<1>>,
	"If library type was defined as HYB (aka hybrid) it means that all "
	"containers that "
	"kotek framework provides to use ARE with hybrid_ prefix it means that "
	"this cstring "
	"container is expected as hybrid_cstring implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk hybrid_u8string<1>, ktk_u8string<1>>,
	"If library type was defined as HYB (aka hybrid) it means that all "
	"containers that "
	"kotek framework provides to use ARE with hybrid_ prefix it means that "
	"this u8string "
	"container is expected as hybrid_u8string implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk hybrid_u16string<1>, ktk_u16string<1>>,
	"If library type was defined as HYB (aka hybrid) it means that all "
	"containers that "
	"kotek framework provides to use ARE with hybrid_ prefix it means that "
	"this u16string "
	"container is expected as hybrid_u16string implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk hybrid_u32string<1>, ktk_u32string<1>>,
	"If library type was defined as HYB (aka hybrid) it means that all "
	"containers that "
	"kotek framework provides to use ARE with hybrid_ prefix it means that "
	"this u32string "
	"container is expected as hybrid_u32string implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk hybrid_wstring<1>, ktk_wstring<1>>,
	"If library type was defined as HYB (aka hybrid) it means that all "
	"containers that "
	"kotek framework provides to use ARE with hybrid_ prefix it means that "
	"this wstring "
	"container is expected as hybrid_wstring implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk hybrid_cstring_view, ktk_cstring_view>,
	"If library type was defined as HYB (aka hybrid) it means that all "
	"containers that "
	"kotek framework provides to use ARE with hybrid_ prefix it means that "
	"this cstring_view "
	"container is expected as hybrid_cstring_view implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk hybrid_u8string_view, ktk_u8string_view>,
	"If library type was defined as HYB (aka hybrid) it means that all "
	"containers that "
	"kotek framework provides to use ARE with hybrid_ prefix it means that "
	"this u8string_view "
	"container is expected as hybrid_u8string_view implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk hybrid_u16string_view, ktk_u16string_view>,
	"If library type was defined as HYB (aka hybrid) it means that all "
	"containers that "
	"kotek framework provides to use ARE with hybrid_ prefix it means that "
	"this u16string_view "
	"container is expected as hybrid_u16string_view implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk hybrid_u32string_view, ktk_u32string_view>,
	"If library type was defined as HYB (aka hybrid) it means that all "
	"containers that "
	"kotek framework provides to use ARE with hybrid_ prefix it means that "
	"this u32string_view "
	"container is expected as hybrid_u32string_view implementation");

static_assert(
	std::is_same_v<kun_kotek kun_ktk hybrid_wstring_view, ktk_wstring_view>,
	"If library type was defined as HYB (aka hybrid) it means that all "
	"containers that "
	"kotek framework provides to use ARE with hybrid_ prefix it means that "
	"this wstring_view "
	"container is expected as hybrid_wstring_view implementation");
#else
	#error unknown configuration, kotek supports three configurations: DYN (dynamic), EMB (static), HYB (hybrid)
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Containers_String(ktkMainManager* p_manager);
bool SerializeModule_Core_Containers_String(ktkMainManager* p_manager);
bool DeserializeModule_Core_Containers_String(ktkMainManager* p_manager);
bool ShutdownModule_Core_Containers_String(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK