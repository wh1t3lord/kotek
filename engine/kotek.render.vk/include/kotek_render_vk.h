#pragma once

#include <kotek.core/include/kotek_std.h>

namespace Kotek
{
	namespace Render
	{
		bool InitializeModule_Render_VK(Core::ktkMainManager& main_manager);
		bool ShutdownModule_Render_VK(Core::ktkMainManager& main_manager);

#ifdef KOTEK_DEBUG

		/// <summary>
		/// �������� ����������� � ���, ��� ���� �������� �������� � ���������
		/// ����� (�����) � ������ �������, �� ������� (boost ����������) ��
		/// ������ ��������� ���������������� �����, ������� �� ������ �������
		/// �������� ������������� ����� � ��� ����� ���������� ������� ���� ��
		/// ���� ����� ������� ������� ������������� � ��������������� ����� ���
		/// ������ ����� �������, ����� �������� ����� ��� ���� ����� ���
		/// ����������� �����:
		///		- ������� ��� ����
		///		- �������� ����� ����� BOOST_AUTO_TEST_CASE
		///		- ������ ����� �� ��� �� ���������������� ����� ������� �����
		///�����-�� ������� �� ����� ����� � ���� ��� ���������������� ������
		///		- ����� ������� �� �������� ��������� �������� ����������� �
		///����������� ������ ����� ������� ������� ���������� ���, ��� �� �
		///���������� ������������� � ���������� ������
		///		- �������� ����� ������� � registerAllTests, �������� ������
		///������� ������ ���������� � ��������� � main_��������_������_dll.cpp,
		///����� ������� ��� ������ ��������� � �� ����� ������������ � �����-��
		///��������, � ������� ����� �� ������� ���� �� ���� main_***_dll.cpp
		/// </summary>

		void registerTests_ShaderManager_ForModule_Render_VK();
		void registerTests_Device_ForModule_Render_VK();
		void registerTests_CommandListRing_ForModule_Render_VK();
		void registerTests_Swapchain_ForModule_Render_VK();
		void registerTests_ShaderCacheManager_ForModule_Render_VK();
#endif
	} // namespace Render
} // namespace Kotek
