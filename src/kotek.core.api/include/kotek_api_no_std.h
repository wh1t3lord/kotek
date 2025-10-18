#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkIWindowSplash
{
public:
	virtual ~ktkIWindowSplash(void) {}

	virtual int Get_Width(void) const noexcept = 0;
	virtual int Get_Height(void) const noexcept = 0;

	virtual void Show(void) noexcept = 0;
	virtual void Hide(void) noexcept = 0;

	virtual void Create(int width, int height, unsigned char* p_raw_image_data,
		float* p_max_progress) noexcept = 0;

	virtual void Set_Text(
		const char* p_string, int* p_color_rgb_array = nullptr) noexcept = 0;

	virtual void Set_Progress(float progress) noexcept = 0;
	virtual void Set_Progress(void) noexcept = 0;

	virtual bool Is_Initialized(void) const noexcept = 0;

	/// @brief implements message loop for your window, supposed to be called in
	/// separated thread because of purpose of window (splash - preview before
	/// loading the main window)
	virtual void Update() noexcept = 0;
};

class ktkILogger
{
public:
	virtual ~ktkILogger(void) {}
	virtual void Initialize(void) = 0;
	virtual void Shutdown(void) = 0;
	virtual void* Get(const char* p_logger_name) = 0;
	virtual void Flush_All(void) = 0;
};

struct ktkResourceBinaryFileHeader
{
	/// @brief \~english user defined version, you can interpret that data as
	/// you wish but it is supposed to be version
	unsigned char version;
	/// @brief \~english user defined subversion, you can interpret that data as
	/// you wish but it is supposed to be subversion of version
	unsigned char subversion;
	/// @brief \~english user defined subsubversion, you can interpret that data
	/// as you wish but it is supposed to be subversion of subversion
	unsigned char subsubversion;
	
	/// @brief \~english defines resource type as number and can be interpreted
	/// by engines as they defined
	unsigned short resource_type;

	/// @brief \~english for different resources we might write data differently
	/// but in order to efficiently accessing data we need to mark offsets to
	/// each beginning of reading sections in file
	/// definition of table depends on user implementation and implementation
	/// for resource_type
	size_t offset_to_offset_table;

	/// @brief \~english this offset table will contain as first number the
	/// amount of serialized fields and then each entry of that table will be
	/// represented like this: OFFSET,SIZE_OF_STRING so OFFSET will be size_t
	/// type and SIZE_OF_STRING will be unsigned char size by SIZE_OF_STRING you
	/// will understand what length of string was serialized by moving cursor of
	/// FILE using OFFSET
	size_t offset_to_string_metadata_offset_table;

	/// @brief \~english defines where the beginning of manually allocated
	/// string field (p_string_field_manually_allocated) is located in binary
	/// file
	size_t offset_to_manually_allocated_string_field;

	/// @brief ~\english in case if user is not satisfied with current
	/// string_fields and needed more information to write to file you can use
	/// offset_to_manually_allocated_string_field and then after delimiter ,
	/// (comma) read the size of serialized manually allocated string_field that
	/// implementation had
	unsigned char* p_string_field_manually_allocated = 0;

	/// @brief \~english char array for length of 8 you can write the data
	/// whatever you wish but it is supposed that these metadata can contain
	/// useful information like authorship, information related to vendor how
	/// that asset was imported, hashes and many other stuff
	char string_field_small[8];

	/// @brief \~english char array for length of 16 you can write the data
	/// whatever you wish but it is supposed that these metadata can contain
	/// useful information like authorship, information related to vendor how
	/// that asset was imported, hashes and many other stuff
	char string_field_medium[16];

	/// @brief \~english char array for length of 32 you can write the data
	/// whatever you wish but it is supposed that these metadata can contain
	/// useful information like authorship, information related to vendor how
	/// that asset was imported, hashes and many other stuff
	char string_field_big[32];
};

/// @brief \~english uses everywhere across framework + engine,
/// we keep as the lightweight representation of class that will
/// be used in inheritence but without it like in Zircon engine
/// implementation hard to define destroying resources that
/// would be allocated by allocator instead of predefined
/// (preallocated) data that uses as cache by engine, if cpp can
/// provide a such functionality then it is better to not use
/// virtual tables since it grows memory size of class instances
class ktkIResource
{
public:
	virtual ~ktkIResource() {}
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK