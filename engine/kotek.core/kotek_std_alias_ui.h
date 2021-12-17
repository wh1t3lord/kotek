#pragma once

#include "kotek_std_preprocessors.h"

#ifdef KOTEK_USE_SDK
	#define WXUSINGDLL

	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include <wx/aui/aui.h>
#endif