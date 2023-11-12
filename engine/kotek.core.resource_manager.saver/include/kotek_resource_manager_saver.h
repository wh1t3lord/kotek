#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkResourceSaverManager : public ktkIResourceSaverManager
{
private:
	class ktkWritingFile
	{
	public:
		ktkWritingFile();
		~ktkWritingFile();


	private:
		ktk::cofstream m_file;
		eResourceWritingPolicy m_policy;
		eResourceWritingMode m_mode;
	};

public:
	ktkResourceSaverManager(void);
	~ktkResourceSaverManager(void);

	void Initialize(
		ktkIFileSystem* p_filesystem, ktkMainManager* p_main_manager) override;
	void Shutdown(void) override;

	void Set_Saver(eResourceLoadingType resource_type,
		ktkIResourceSaver* p_saver) override;

	ktkIResourceSaver* Get_Saver(
		eResourceLoadingType resource_type) const noexcept override;

	bool Save(
		const ktk::filesystem::path& path, ktk::any data) noexcept override;

	bool Open(const ktk::filesystem::path& path,
		eResourceWritingType resource_type, eResourceWritingPolicy policy,
		eResourceWritingMode mode, ktk::uint32_t id) noexcept override;
	void Write(
		ktk::uint32_t resource_id, const char* p_string) noexcept override;
	void Write(ktk::uint32_t resource_id, const char* p_string,
		ktk::size_t size) noexcept override;
	void Write(ktk::uint32_t resource_id,
		const unsigned char* p_raw_memory) noexcept override;
	void Write(ktk::uint32_t resource_id, const unsigned char* p_raw_memory,
		ktk::size_t size) noexcept override;
	void Write(ktk::uint32_t resource_id, ktk::int32_t value) noexcept override;
	void Write(ktk::uint32_t resource_id, ktk::float_t value) noexcept override;
	void Write(
		ktk::uint32_t resource_id, ktk::double_t value) noexcept override;
	void Write(ktk::uint32_t resource_id, const ktk::int32_t* p_arr,
		ktk::size_t size) noexcept override;
	void Write(ktk::uint32_t resource_id, const ktk::uint32_t* p_arr,
		ktk::size_t size) noexcept override;
	void Write(ktk::uint32_t resource_id, const ktk::float_t* p_arr,
		ktk::size_t size) noexcept override;
	void Write(ktk::uint32_t resource_id, const ktk::double_t* p_arr,
		ktk::size_t size) noexcept override;
	void Write(ktk::uint32_t resource_id, const ktk::int8_t* p_arr,
		ktk::size_t size) noexcept override;
	void Write(ktk::uint32_t resource_id, const ktk::uint8_t* p_arr,
		ktk::size_t size) noexcept override;
	void Write(ktk::uint32_t resource_id, const ktk::int16_t* p_arr,
		ktk::size_t size) noexcept override;
	void Write(ktk::uint32_t resource_id, const ktk::uint16_t* p_arr,
		ktk::size_t size) noexcept override;
	bool Close(ktk::uint32_t id) noexcept override;

protected:
	eResourceLoadingType DetectResourceTypeByFileFormat(
		const ktk::filesystem::path& path) noexcept override;

private:
	bool CreateWriter(
		const ktk::filesystem::path& path, ktk::uint32_t id) noexcept;

private:
	ktk::unordered_map<eResourceLoadingType, ktkIResourceSaver*> m_savers;

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	ktk::static_unordered_map<ktk::uint32_t, ktk::cofstream, 10> m_writers;
#else
	ktk::unordered_map<ktk::uint32_t, ktk::cofstream> m_writers;
#endif
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK