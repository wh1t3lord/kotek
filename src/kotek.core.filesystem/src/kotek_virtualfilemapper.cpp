#include "../include/kotek_virtualfilemapper.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkFileSystem_VFM::ktkFileSystem_VFM(void) 
{
}

ktkFileSystem_VFM::~ktkFileSystem_VFM(void) {}

void ktkFileSystem_VFM::Initialize()
{}

void ktkFileSystem_VFM::Shutdown() {}

void ktkFileSystem_VFM::MapFile(
	ktkFileHandleType file_id, kun_ktk fstream& file)
{

}

void ktkFileSystem_VFM::UnMapFile(
	ktkFileHandleType file_id, kun_ktk fstream& file)
{
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK