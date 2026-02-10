#pragma once

#define STRICT
#define WIN32_LEAN_AND_MEAN
#define _WTL_NO_CSTRING
#define _ATL_NO_AUTOMATIC_NAMESPACE

#include <atlbase.h>
#include <atlapp.h>

extern ATL::CAppModule _Module;

#include <atlwin.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlctrlw.h>
#include <atlmisc.h>

#include <windows.h>
#include <commctrl.h>
#include <gdiplus.h>
#include <string>
#include <vector>
#include <memory>

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;
