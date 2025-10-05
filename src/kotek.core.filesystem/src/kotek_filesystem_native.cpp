#include "../include/kotek_filesystem_native.h"
#include "../include/kotek_virtualfilemapper.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_FILESYSTEM_TYPE_NATIVE
ktkFileSystem_Native::ktkFileSystem_Native() :
	#ifdef KOTEK_DEBUG
	m_shutdown_was_called{},
	#endif

	m_default_stream_buffer_size{},
	#ifdef KOTEK_USE_FILESYSTEM_FEATURE_VFM
	, m_p_vfm{}
	#endif
{
}

ktkFileSystem_Native::~ktkFileSystem_Native(void) 
{
	#ifdef KOTEK_DEBUG
	KOTEK_ASSERT(
		this->m_shutdown_was_called,
		"you forgot to call shutdown for this manager"
	);
	#endif
}
#endif

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK