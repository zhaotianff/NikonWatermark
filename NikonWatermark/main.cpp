#include "stdafx.h"
#include "resource.h"
#include "MainFrame.h"

ATL::CAppModule _Module;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPWSTR /*lpCmdLine*/, int nCmdShow)
{
    // Initialize GDI+
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    
    // Initialize COM
    HRESULT hRes = ::CoInitialize(NULL);
    ATLASSERT(SUCCEEDED(hRes));
    
    // Initialize Common Controls
    INITCOMMONCONTROLSEX iccx;
    iccx.dwSize = sizeof(iccx);
    iccx.dwICC = ICC_WIN95_CLASSES;
    ::InitCommonControlsEx(&iccx);
    
    // Initialize WTL
    hRes = _Module.Init(NULL, hInstance);
    ATLASSERT(SUCCEEDED(hRes));
    
    int nRet = 0;
    
    // Create main window
    CMainFrame wndMain;
    
    RECT rcWindow = { 0, 0, 1000, 700 };
    
    if (wndMain.CreateEx(NULL, rcWindow) == NULL)
    {
        ATLTRACE(L"Main window creation failed!\n");
        return 0;
    }
    
    wndMain.ShowWindow(nCmdShow);
    wndMain.UpdateWindow();
    
    // Message loop
    WTL::CMessageLoop theLoop;
    _Module.AddMessageLoop(&theLoop);
    theLoop.AddMessageFilter(&wndMain);
    theLoop.AddIdleHandler(&wndMain);
    
    nRet = theLoop.Run();
    
    _Module.RemoveMessageLoop();
    
    // Cleanup
    _Module.Term();
    ::CoUninitialize();
    
    // Shutdown GDI+
    Gdiplus::GdiplusShutdown(gdiplusToken);
    
    return nRet;
}
