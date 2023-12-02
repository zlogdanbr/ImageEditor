#ifndef _MAIN_FRAME_MY_APP_DVG_
#define _MAIN_FRAME_MY_APP_DVG_


#include <functional>
#include <wx/numdlg.h>
#include <wx/wx.h>
#include <wx/progdlg.h>
#include <wx/dc.h>
#include <wx/wx.h>
#include <wx/statbmp.h>
#include <wx/panel.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/artprov.h>
#include<opencv2/highgui/highgui.hpp>
#include <memory>
#include <map>
#include <iostream>
#include <sstream>
#include <string>
#include <functional>
#include <queue>
#include <stack>
#include <deque>
#include <chrono>
#include "childframes.h"


class MyFrame : public wxMDIParentFrame
{
public:

    MyFrame();

    ~MyFrame()
    {
        for (auto& mdichild : mdi_panel_child_frames)
        {
            if (mdichild != nullptr)
            {
                //delete mdichild;
                mdichild = nullptr;
            }
        }

        mdi_panel_child_frames.clear();

    }

    CImageCustomDialog* getChildFrame() { return mdi_panel_child; };

private:

    wxMenuBar* mainMenu = new wxMenuBar();

    //--------------------------------------------------------------
    // components---------------------------------------------------
    //--------------------------------------------------------------

    wxPanel* main_panel = nullptr;
    CImageCustomDialog* mdi_panel_child = nullptr;
    std::vector<  CImageCustomDialog* > mdi_panel_child_frames;

    //---------------------------------------------------------------
    // event handlers------------------------------------------------
    //---------------------------------------------------------------
    void OnOpen(wxCommandEvent& event);
    void OnClose(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void onHelpFile(wxCommandEvent& event);

    void BindAllEvents()
    {
        Bind(wxEVT_MENU, &MyFrame::OnOpen, this, wxID_OPEN);
        Bind(wxEVT_MENU, &MyFrame::OnClose, this, wxID_CLOSE);
        Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
        Bind(wxEVT_MENU, &MyFrame::OnSave, this, wxID_SAVE);     
        Bind(wxEVT_MENU, &MyFrame::onHelpFile, this, wxID_ABOUT);
    }

};
#endif
