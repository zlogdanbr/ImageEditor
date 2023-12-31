#pragma once

#include "wx/wx.h"
#include <stack>

using RGB = unsigned char[3];

class MyDrawingFrame : public wxFrame
{
public:
    MyDrawingFrame(wxFrame* parent, const wxImage& _image, RGB myrgb );

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

    RGB rgb;
    wxImage clone_image;
    std::vector<wxPoint> pts;
    std::vector<wxPoint> circles;
    std::vector<int> radiuses;

    struct myrect
    {
        wxPoint p1;
        wxPoint p2;
        wxPoint p3;
        wxPoint p4;
    };

    wxPoint sPos;

    myrect RectTangle;

    void DrawFinally();

    std::stack<wxPoint> line;
    void putpixel(int i, int j, RGB& r);
    void drawcircle(int x0, int y0, int radius, wxImage img, RGB& r);
    void saveRectangle();
    void saveArea();

    void drawLineHorizontal(wxKeyEvent& event, int direction);
    void drawLineVertical(wxKeyEvent& event, int direction);
};