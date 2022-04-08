#pragma once

#include "kotek_std_preprocessors.h"

#ifdef KOTEK_USE_SDK
	#define WXUSINGDLL
	#define wxUSE_LISTCTRL 1

	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include <wx/listctrl.h>
	#include <wx/aui/aui.h>
#endif