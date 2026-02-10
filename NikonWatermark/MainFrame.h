#pragma once
#include "stdafx.h"
#include "resource.h"
#include "ImageProcessor.h"
#include <vector>

class CMainFrame : public ATL::CFrameWindowImpl<CMainFrame>,
                   public WTL::CUpdateUI<CMainFrame>,
                   public WTL::CMessageFilter,
                   public WTL::CIdleHandler
{
public:
    DECLARE_FRAME_WND_CLASS(L"NikonWatermark", IDR_MAINFRAME)

    CMainFrame();

    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual BOOL OnIdle();

    BEGIN_UPDATE_UI_MAP(CMainFrame)
    END_UPDATE_UI_MAP()

    BEGIN_MSG_MAP(CMainFrame)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        MESSAGE_HANDLER(WM_CTLCOLORSTATIC, OnCtlColorStatic)
        MESSAGE_HANDLER(WM_CTLCOLORBTN, OnCtlColorBtn)
        MESSAGE_HANDLER(WM_CTLCOLORLISTBOX, OnCtlColorListBox)
        COMMAND_ID_HANDLER(IDC_IMPORT_BUTTON, OnImportImages)
        COMMAND_ID_HANDLER(IDC_PROCESS_BUTTON, OnProcessImages)
        COMMAND_ID_HANDLER(IDCANCEL, OnExit)
        CHAIN_MSG_MAP(ATL::CFrameWindowImpl<CMainFrame>)
    END_MSG_MAP()

    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnCtlColorStatic(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnCtlColorBtn(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnCtlColorListBox(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnImportImages(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
    LRESULT OnProcessImages(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

private:
    void SetDarkTheme();
    void UpdateLayout();
    
    WTL::CListBox m_importList;
    WTL::CListBox m_exportList;
    WTL::CButton m_importButton;
    WTL::CButton m_processButton;
    WTL::CComboBox m_positionCombo;
    WTL::CButton m_apertureCheck;
    WTL::CButton m_isoCheck;
    WTL::CButton m_shutterCheck;
    WTL::CStatic m_importLabel;
    WTL::CStatic m_exportLabel;
    WTL::CStatic m_settingsLabel;
    
    HBRUSH m_hBrushDark;
    HBRUSH m_hBrushDarkControl;
    
    std::vector<std::wstring> m_importedFiles;
    ImageProcessor m_imageProcessor;
};
