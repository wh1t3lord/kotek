#include "../include/kotek_filesystem_zlib.h"
#include "../include/kotek_virtualfilemapper.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkFileSystem_Zlib::ktkFileSystem_Zlib()
#ifdef KOTEK_USE_FILESYSTEM_FEATURE_VFM
	: m_p_vfm{}
#endif
{
}

ktkFileSystem_Zlib::~ktkFileSystem_Zlib() {}

void ktkFileSystem_Zlib::Shutdown(void) {}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK