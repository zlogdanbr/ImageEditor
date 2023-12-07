#pragma once

#include "wx/wx.h"


class MyDrawingFrame : public wxFrame
{
public:
    MyDrawingFrame(wxFrame* parent, const wxImage& _image, wxColor* _color);

private:

    wxPanel* m_board{ new wxPanel(this, wxID_ANY) };

    wxStaticBitmap* image_canvas = new wxStaticBitmap(
        m_board,
        wxID_ANY,
        wxNullBitmap,
        { -1,-1 },
        { 0,0 },
        wxBORDER_SUNKEN
    );

    wxColor* color = nullptr;
    wxImage clone_image;

};