#include "../include/kotek_filesystem_native.h"
#include "../include/kotek_virtualfilemapper.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_FILESYSTEM_TYPE_NATIVE
ktkFileSystem_Native::ktkFileSystem_Native(void)
	#ifdef KOTEK_USE_FILESYSTEM_FEATURE_VFM
	: m_p_vfm{}
	#endif
{
}

ktkFileSystem_Native::~ktkFileSystem_Native(void) {}
#endif

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK