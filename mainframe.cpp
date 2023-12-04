
#include "mainframe.h"

MyFrame::MyFrame():wxMDIParentFrame(nullptr, wxID_ANY, "Image Editor")
{
    SetClientSize(1080, 960);
    wxInitAllImageHandlers();

    wxIcon icon("../../app.ico");
    SetIcon(icon);

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
    CImageCustomDialog* tmp{ new CImageCustomDialog(this) };
    tmp->Show();
    tmp->Maximize();
    mdi_panel_child_frames.push_back(tmp);
}

void MyFrame::onHelpFile(wxCommandEvent& event)
{
    wxAboutDialogInfo aboutInfo;
    aboutInfo.SetName(wxTheApp->GetAppName());
    aboutInfo.SetVersion("1.0", "1.0.1");
    aboutInfo.SetDescription("Image Editor Tool");
    aboutInfo.SetWebSite("http://zlogdan.wordpress.com");
    aboutInfo.SetLicence("GNU GENERAL PUBLIC LICENSE GPLv3");
    wxArrayString Dev;
    wxString _me_ = "Daniel Vasconcelos Gomes";
    Dev.Add(_me_);
    aboutInfo.SetDevelopers(Dev);
    wxAboutBox(aboutInfo);
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close();
}

void MyFrame::OnClose(wxCommandEvent& event)
{
    //if (mdi_panel_child != nullptr)
    //{
    //    mdi_panel_child->Close();
    //    mdi_panel_child = nullptr;
    //}
}

void MyFrame::OnSave(wxCommandEvent& event)
{

}
