#include "stdafx.h"
#include "MainFrame.h"
#include <shlobj.h>
#include <sstream>

CMainFrame::CMainFrame() : m_hBrushDark(NULL), m_hBrushDarkControl(NULL)
{
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
    if (ATL::CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
        return TRUE;

    return FALSE;
}

BOOL CMainFrame::OnIdle()
{
    return FALSE;
}

void CMainFrame::SetDarkTheme()
{
    // Create dark brushes
    m_hBrushDark = CreateSolidBrush(RGB(30, 30, 30));
    m_hBrushDarkControl = CreateSolidBrush(RGB(45, 45, 45));
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    SetDarkTheme();
    
    // Create Import Label
    m_importLabel.Create(m_hWnd, NULL, L"Import Images", WS_CHILD | WS_VISIBLE | SS_LEFT, 0, IDC_IMPORT_LIST);
    
    // Create Import List Box
    m_importList.Create(m_hWnd, NULL, NULL, 
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_NOTIFY, 
        0, IDC_IMPORT_LIST);
    
    // Create Export Label
    m_exportLabel.Create(m_hWnd, NULL, L"Export Images", WS_CHILD | WS_VISIBLE | SS_LEFT, 0, IDC_EXPORT_LIST);
    
    // Create Export List Box
    m_exportList.Create(m_hWnd, NULL, NULL, 
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_NOTIFY, 
        0, IDC_EXPORT_LIST);
    
    // Create Settings Label
    m_settingsLabel.Create(m_hWnd, NULL, L"Settings", WS_CHILD | WS_VISIBLE | SS_LEFT, 0, 1010);
    
    // Create Import Button
    m_importButton.Create(m_hWnd, NULL, L"Import Images", 
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
        0, IDC_IMPORT_BUTTON);
    
    // Create Process Button
    m_processButton.Create(m_hWnd, NULL, L"Process Images", 
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
        0, IDC_PROCESS_BUTTON);
    
    // Create Position ComboBox
    m_positionCombo.Create(m_hWnd, NULL, NULL, 
        WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 
        0, IDC_POSITION_COMBO);
    m_positionCombo.AddString(L"Bottom");
    m_positionCombo.AddString(L"Top");
    m_positionCombo.SetCurSel(0);
    
    // Create EXIF checkboxes
    m_apertureCheck.Create(m_hWnd, NULL, L"Show Aperture", 
        WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 
        0, IDC_EXIF_APERTURE);
    m_apertureCheck.SetCheck(BST_CHECKED);
    
    m_isoCheck.Create(m_hWnd, NULL, L"Show ISO", 
        WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 
        0, IDC_EXIF_ISO);
    m_isoCheck.SetCheck(BST_CHECKED);
    
    m_shutterCheck.Create(m_hWnd, NULL, L"Show Shutter Speed", 
        WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 
        0, IDC_EXIF_SHUTTER);
    m_shutterCheck.SetCheck(BST_CHECKED);
    
    UpdateLayout();
    
    return 0;
}

LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    if (m_hBrushDark)
    {
        DeleteObject(m_hBrushDark);
        m_hBrushDark = NULL;
    }
    if (m_hBrushDarkControl)
    {
        DeleteObject(m_hBrushDarkControl);
        m_hBrushDarkControl = NULL;
    }
    
    bHandled = FALSE;
    PostQuitMessage(0);
    return 0;
}

LRESULT CMainFrame::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    UpdateLayout();
    return 0;
}

void CMainFrame::UpdateLayout()
{
    RECT rc;
    GetClientRect(&rc);
    
    int width = rc.right - rc.left;
    int height = rc.bottom - rc.top;
    
    int margin = 10;
    int labelHeight = 20;
    int buttonHeight = 30;
    int controlWidth = (width - margin * 3) / 2;
    
    // Import section (left side)
    int yPos = margin;
    m_importLabel.MoveWindow(margin, yPos, controlWidth, labelHeight);
    yPos += labelHeight + 5;
    
    int listHeight = height - yPos - buttonHeight - margin * 3 - labelHeight - 30;
    m_importList.MoveWindow(margin, yPos, controlWidth, listHeight);
    yPos += listHeight + margin;
    
    m_importButton.MoveWindow(margin, yPos, controlWidth, buttonHeight);
    
    // Export section (right side)
    yPos = margin;
    m_exportLabel.MoveWindow(margin * 2 + controlWidth, yPos, controlWidth, labelHeight);
    yPos += labelHeight + 5;
    
    m_exportList.MoveWindow(margin * 2 + controlWidth, yPos, controlWidth, listHeight);
    yPos += listHeight + margin;
    
    // Settings section (bottom)
    yPos = height - buttonHeight * 3 - margin * 3;
    m_settingsLabel.MoveWindow(margin, yPos, controlWidth, labelHeight);
    yPos += labelHeight + 5;
    
    m_apertureCheck.MoveWindow(margin, yPos, 150, 25);
    m_isoCheck.MoveWindow(margin + 160, yPos, 150, 25);
    m_shutterCheck.MoveWindow(margin + 320, yPos, 200, 25);
    yPos += 30;
    
    m_positionCombo.MoveWindow(margin, yPos, 200, 25);
    yPos += 35;
    
    m_processButton.MoveWindow(margin, yPos, controlWidth, buttonHeight);
}

LRESULT CMainFrame::OnCtlColorStatic(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    HDC hdc = (HDC)wParam;
    SetTextColor(hdc, RGB(220, 220, 220));
    SetBkColor(hdc, RGB(30, 30, 30));
    return (LRESULT)m_hBrushDark;
}

LRESULT CMainFrame::OnCtlColorBtn(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    HDC hdc = (HDC)wParam;
    SetTextColor(hdc, RGB(220, 220, 220));
    SetBkColor(hdc, RGB(30, 30, 30));
    return (LRESULT)m_hBrushDark;
}

LRESULT CMainFrame::OnCtlColorListBox(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    HDC hdc = (HDC)wParam;
    SetTextColor(hdc, RGB(220, 220, 220));
    SetBkColor(hdc, RGB(45, 45, 45));
    return (LRESULT)m_hBrushDarkControl;
}

LRESULT CMainFrame::OnImportImages(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    WTL::CFileDialog dlg(TRUE, L"jpg", NULL, 
        OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, 
        L"Image Files (*.jpg;*.jpeg;*.png;*.bmp)\0*.jpg;*.jpeg;*.png;*.bmp\0All Files (*.*)\0*.*\0", 
        m_hWnd);
    
    // Allocate buffer for multiple files
    const int BUFFER_SIZE = 32768;
    WCHAR* buffer = new WCHAR[BUFFER_SIZE];
    ZeroMemory(buffer, BUFFER_SIZE * sizeof(WCHAR));
    dlg.m_ofn.lpstrFile = buffer;
    dlg.m_ofn.nMaxFile = BUFFER_SIZE;
    
    if (dlg.DoModal() == IDOK)
    {
        m_importedFiles.clear();
        m_importList.ResetContent();
        
        WCHAR* p = buffer;
        std::wstring directory = p;
        p += wcslen(p) + 1;
        
        if (*p == 0)
        {
            // Single file selected
            m_importedFiles.push_back(directory);
            
            // Get filename only for display
            size_t pos = directory.find_last_of(L"\\");
            std::wstring filename = (pos != std::wstring::npos) ? directory.substr(pos + 1) : directory;
            m_importList.AddString(filename.c_str());
        }
        else
        {
            // Multiple files selected
            while (*p)
            {
                std::wstring filename = p;
                std::wstring fullPath = directory + L"\\" + filename;
                m_importedFiles.push_back(fullPath);
                m_importList.AddString(filename.c_str());
                p += wcslen(p) + 1;
            }
        }
    }
    
    delete[] buffer;
    return 0;
}

LRESULT CMainFrame::OnProcessImages(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    if (m_importedFiles.empty())
    {
        MessageBox(L"Please import images first!", L"Error", MB_OK | MB_ICONERROR);
        return 0;
    }
    
    // Select output folder
    BROWSEINFO bi = { 0 };
    bi.hwndOwner = m_hWnd;
    bi.lpszTitle = L"Select Output Folder";
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
    if (pidl == NULL)
        return 0;
    
    WCHAR outputFolder[MAX_PATH];
    if (!SHGetPathFromIDList(pidl, outputFolder))
    {
        CoTaskMemFree(pidl);
        return 0;
    }
    CoTaskMemFree(pidl);
    
    // Get configuration
    WatermarkConfig config;
    config.showAperture = (m_apertureCheck.GetCheck() == BST_CHECKED);
    config.showISO = (m_isoCheck.GetCheck() == BST_CHECKED);
    config.showShutterSpeed = (m_shutterCheck.GetCheck() == BST_CHECKED);
    config.position = (m_positionCombo.GetCurSel() == 0) ? WatermarkPosition::Bottom : WatermarkPosition::Top;
    
    // Process images
    m_exportList.ResetContent();
    
    for (size_t i = 0; i < m_importedFiles.size(); i++)
    {
        std::wstring inputPath = m_importedFiles[i];
        
        // Get filename
        size_t pos = inputPath.find_last_of(L"\\");
        std::wstring filename = (pos != std::wstring::npos) ? inputPath.substr(pos + 1) : inputPath;
        
        // Create output path
        std::wstring outputPath = outputFolder;
        outputPath += L"\\";
        outputPath += filename;
        
        // Process image
        if (m_imageProcessor.ProcessImage(inputPath, outputPath, config))
        {
            m_exportList.AddString(filename.c_str());
        }
        else
        {
            std::wstring error = L"Failed: " + filename;
            m_exportList.AddString(error.c_str());
        }
    }
    
    MessageBox(L"Image processing completed!", L"Success", MB_OK | MB_ICONINFORMATION);
    return 0;
}

LRESULT CMainFrame::OnExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    DestroyWindow();
    return 0;
}
