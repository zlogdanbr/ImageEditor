
#include "mainframe.h"

MyFrame::MyFrame():wxMDIParentFrame(nullptr, wxID_ANY, "Image Editor")
{
    SetClientSize(640, 480);
    wxInitAllImageHandlers();

    // ------------------------------------------------------------------------------  
    // menu   file
    // ------------------------------------------------------------------------------  
    auto menuFile = new wxMenu();

    auto menuItemFileOpen = menuFile->Append(wxID_OPEN);
    menuItemFileOpen->SetBitmap(wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_MENU));

    menuFile->Append(wxID_CLOSE, "Close\tCtrl+W");

    menuFile->AppendSeparator();

    auto menuItemFileSave = menuFile->Append(wxID_SAVE);
    menuItemFileSave->SetBitmap(wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_MENU));

    menuFile->AppendSeparator();

    auto menuItemFileQuit = menuFile->Append(wxID_EXIT);
    menuItemFileQuit->SetBitmap(wxArtProvider::GetBitmap(wxART_QUIT, wxART_MENU));

    // -----------------------------------------------------------------------------  
    // menu   help
    // -----------------------------------------------------------------------------
    auto menuHelp = new wxMenu();
    menuHelp->Append(wxID_ABOUT);

    // ----------------------------------------------------------------------------- 
    // Menu loaded
    // -----------------------------------------------------------------------------
    mainMenu->Append(menuFile, "&File");
    mainMenu->Append(menuHelp, "&Help");

    // -----------------------------------------------------------------------------  
    // Menu Events
    // -----------------------------------------------------------------------------
    BindAllEvents();
    SetMenuBar(mainMenu);

    Centre();

}


void MyFrame::OnOpen(wxCommandEvent & event)
{
    mdi_panel_child = new CImageCustomDialog(this);
    mdi_panel_child->Maximize();
    mdi_panel_child->Show();
}

void MyFrame::onHelpFile(wxCommandEvent& event)
{

}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close();
}

void MyFrame::OnClose(wxCommandEvent& event)
{
    if (mdi_panel_child != nullptr)
    {
        mdi_panel_child->Close();
        mdi_panel_child = nullptr;
    }
}

void MyFrame::OnSave(wxCommandEvent& event)
{

}
