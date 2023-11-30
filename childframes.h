//--------------------------------------------------------------------------------------------------
// Declaration of class interfaces for dialogs used in the application
// author: Daniel Vasconcelos Gomes 2023
// if an external code has been used I indicate the sources
//--------------------------------------------------------------------------------------------------
#ifndef _CHILD_FRAME_DEFS_
#define _CHILD_FRAME_DEFS_



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

using CPointCst = std::pair<int, int>;
using CDataValue = std::vector<CPointCst>;
using RGB_CST = unsigned char[3];


class CInputDialogBase : public wxFrame
{
public:

    CInputDialogBase(wxFrame* parent, wxString name);

protected:

    //--------------------------------------------------------------
    // Helpers
    //--------------------------------------------------------------

    // https://truelogic.org/wordpress/2021/12/17/5b-1-wxwidgets-wxboxsizer/
    virtual void setControlslayout() = 0;

};



class CDataCapture : public CDataValue
{
public:
    void insertPoint(int x, int y)
    {
        CPointCst p{ x,y };
        this->push_back(p);
    }

    void clear_me()
    {
        this->clear();
    }

    bool isPointInThePicture(int x, int y)
    {
        CPointCst p(x, y);
        if (std::find(this->begin(), this->end(), p) != this->end())
        {
            return true;
        }
        return false;
    }
};


class CImageCustomDialog : public CInputDialogBase
{
public:

    CImageCustomDialog(wxFrame* parent);

    void loadImage();
    void SaveImage();
    void reloadImage(int factor1 = 710, int factor2 = 710);

    wxImage getImage() { return image; };
    
    CDataCapture getCDataCapture() { return c; };

private:

    int w = 0;
    int h = 0;

    wxPanel* basePanel = new wxPanel(this, -1);
    wxPanel* panel1{ new wxPanel(basePanel) };
    wxPanel* panel2{ new wxPanel(basePanel, -1) };

    wxBoxSizer* baseSizer{ new wxBoxSizer(wxHORIZONTAL) };
    wxBoxSizer* vbox1{ new wxBoxSizer(wxVERTICAL) };
    wxBoxSizer* vbox2{ new wxBoxSizer(wxVERTICAL) };

    wxButton* button5{ new wxButton(panel1, wxID_ANY, "Load") };
    wxButton* button2{ new wxButton(panel1, wxID_ANY, "Cancel") };
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


    wxImage image;
    wxStaticBitmap* picture = new wxStaticBitmap(   panel2, wxID_ANY, wxNullBitmap, { -1,-1 }, {700,700}, wxBORDER_SUNKEN);

    std::vector<int> resize_factor;

    bool pog_mirror = false;

    void setControlslayout() override;

    CDataCapture c;

    bool capture = false;

    RGB_CST myrgb;

};

#endif