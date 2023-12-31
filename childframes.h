//--------------------------------------------------------------------------------------------------
// Declaration of class interfaces for dialogs used in the application
// author: Daniel Vasconcelos Gomes 2023
// if an external code has been used I indicate the sources
//--------------------------------------------------------------------------------------------------
#ifndef _CHILD_FRAME_DEFS_
#define _CHILD_FRAME_DEFS_

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
#include <wx/aboutdlg.h>
#include <memory>
#include <map>
#include <iostream>
#include <sstream>
#include <string>
#include <functional>
#include <queue>
#include <stack>
#include <deque>
#include "image_sizers.h"

constexpr int CHILD_DEFAULT_W = 710;
constexpr int CHILD_DEFAULT_H = 710;

class CImageCustomDialog : public wxMDIChildFrame
{
public:

    CImageCustomDialog(wxMDIParentFrame* parent);

    void loadImage();
    void SaveImage();
    void reloadImage();
    wxImage getImage() { return image; };

private:
    
    wxPanel* basePanel = new wxPanel(this, -1);
    wxPanel* panel1{ new wxPanel(basePanel) };
    wxPanel* panel2{ new wxPanel(basePanel, -1) };

    wxBoxSizer* baseSizer{ new wxBoxSizer(wxHORIZONTAL) };
    wxBoxSizer* vbox1{ new wxBoxSizer(wxVERTICAL) };
    wxBoxSizer* vbox2{ new wxBoxSizer(wxVERTICAL) };

    wxButton* button5{ new wxButton(panel1, wxID_ANY, "Open") };
    wxButton* button2{ new wxButton(panel1, wxID_ANY, "Close") };
    wxButton* button3{ new wxButton(panel1, wxID_ANY, "Rescale-") };
    wxButton* button6{ new wxButton(panel1, wxID_ANY, "Rescale+") };
    wxButton* button4{ new wxButton(panel1, wxID_ANY, "Save") };        
    wxButton* button8{ new wxButton(panel1, wxID_ANY, "Rotate+") };
    wxButton* button9{ new wxButton(panel1, wxID_ANY, "Rotate-") };
    wxButton* button10{ new wxButton(panel1, wxID_ANY, "BlurH") };
    wxButton* button11{ new wxButton(panel1, wxID_ANY, "BlurV") };
    wxButton* button12{ new wxButton(panel1, wxID_ANY, "Blur") };
    wxButton* button13{ new wxButton(panel1, wxID_ANY, "Gray") };
    wxButton* button14{ new wxButton(panel1, wxID_ANY, "Color") };
    wxButton* button17{ new wxButton(panel1, wxID_ANY, "Undo") };
    wxButton* button15{ new wxButton(panel1, wxID_ANY, "Select") };
    wxButton* button16{ new wxButton(panel1, wxID_ANY, "Edit") };

    wxImage image;
    wxImage backup;
    wxStaticBitmap* image_canvas = new wxStaticBitmap(   
                                                    panel2, 
                                                    wxID_ANY, 
                                                    wxNullBitmap, 
                                                    { -1,-1 }, 
                                                    { CHILD_DEFAULT_W,CHILD_DEFAULT_H},
                                                    wxBORDER_SUNKEN
                                                    );

    void setControlslayout();

    bool changed = false;

    CSizeKeepers CImage{ basePanel, panel1, panel2, image_canvas};

    void doscaleLess(wxNumberEntryDialog& dialog);
    void doscalePlus(wxNumberEntryDialog& dialog);
    void dorotateLeft();
    void dorotateRight();
    void doblurH(wxNumberEntryDialog& dialog);
    void doblurv(wxNumberEntryDialog& dialog);
    void doblur(wxNumberEntryDialog& dialog);
    void ConverImageToGray();

};

#endif