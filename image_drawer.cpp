#include "image_drawer.h"
#include <wx/progdlg.h>
#include <wx/numdlg.h>
#include <wx/aboutdlg.h>
#include <thread>
#include <mutex>

MyDrawingFrame::MyDrawingFrame(wxFrame* parent, const wxImage& _image, RGB myrgb):
    wxFrame{ 
                parent, 
                wxID_ANY, 
                "Edit Image", 
                wxDefaultPosition, 
                wxSize( _image.GetWidth(),  _image.GetHeight())
            }
{
    memset(rgb, 0x00, 3);
    rgb[0] = myrgb[0];
    rgb[1] = myrgb[1];
    rgb[2] = myrgb[2];
    clone_image = _image.Copy();
    wxBitmap bitMap{ wxBitmap(clone_image) };
    image_canvas->SetSize(_image.GetWidth(), _image.GetHeight());
    image_canvas->SetBitmap(bitMap);

    pts.clear();
    circles.clear();

    image_canvas->Bind(wxEVT_MOTION, [&](wxMouseEvent& event)
        {
            if (event.Dragging())
            {
                std::mutex mtex;
                wxClientDC dc(image_canvas);
                wxPen pen(*wxRED, 5, wxPENSTYLE_SOLID); // red pen of width 1
                dc.SetPen(pen);
                auto p = event.GetPosition();
                mtex.lock();
                pts.push_back(p);
                mtex.unlock();
                dc.DrawPoint(event.GetPosition());
                dc.SetPen(wxNullPen);
            }

        });

    image_canvas->Bind(wxEVT_LEFT_DCLICK, [&](wxMouseEvent& event)
        {

            wxNumberEntryDialog dialog(this, "Point Radius", "1-50", "Point Radius", 1, 1, 50);
                
            int radius = 5;

            if (dialog.ShowModal() == wxID_OK)
            {
                radius = dialog.GetValue();
            }

            std::mutex mtex;
            wxClientDC dc(image_canvas);
            wxPen pen(*wxRED, 5, wxPENSTYLE_SOLID); // red pen of width 1
            dc.SetPen(pen);
            auto p = event.GetPosition();
            dc.DrawPoint(event.GetPosition());
            wxCoord r(radius);
            mtex.lock();
            circles.push_back(p);
            mtex.unlock();
            mtex.lock();
            if (line.size() < 2)
            {
                line.push(p);
            }
            mtex.unlock();
            dc.DrawCircle(event.GetPosition(), r);           
            dc.SetPen(wxNullPen);
        });

    image_canvas->Bind(wxEVT_MOUSEWHEEL, [&](wxMouseEvent& event)
        {
            if (line.size() == 2)
            {
                std::mutex mtex;
                mtex.lock();
                wxPoint p1 = line.top();
                line.pop();
                wxPoint p2 = line.top();
                line.pop();
                mtex.unlock();
                
                wxClientDC dc(image_canvas);
                wxPen pen(*wxRED, 5, wxPENSTYLE_SOLID); // red pen of width 1
                dc.SetPen(pen);
                auto p = event.GetPosition();
                dc.DrawLine(p1, p2);
                dc.SetPen(wxNullPen);
            }
        });

    image_canvas->Bind(wxEVT_RIGHT_DOWN, [&](wxMouseEvent& event)
        {
            DrawFinally();
            wxFileDialog saveFileDialog(this,
            wxEmptyString,
            wxEmptyString,
            "MyFile.jpg", "Text Files (*.jpg)|*.jpg|All Files (*.*)|*.*",
            wxFD_SAVE);
            if (saveFileDialog.ShowModal() == wxID_OK)
            {
                wxString path = saveFileDialog.GetPath();
                wxImage tmp;
                tmp = clone_image.Copy();
                tmp.SaveFile(path, wxBITMAP_TYPE_JPEG);
                clone_image.Destroy();
                tmp.Destroy();
                Close();
            }
        });

}

void MyDrawingFrame::DrawFinally()
{
    for (int i = 0; i < clone_image.GetWidth(); i++)
    {
        for (int j = 0; j < clone_image.GetHeight(); j++)
        {
            wxPoint p(i, j);
            if (find(pts.begin(), pts.end(), p) != pts.end())
            {
                clone_image.SetRGB(i, j, rgb[0], rgb[1], rgb[2]);
                clone_image.SetRGB(i-1, j-1, rgb[0], rgb[1], rgb[2]);
                clone_image.SetRGB(i+1, j+1, rgb[0], rgb[1], rgb[2]);
            }
            if (find(circles.begin(), circles.end(), p) != circles.end())
            {
                clone_image.SetRGB(i, j,0xFF, 0xEE, 0x00);

                for (int k = 0; k < 5; k++)
                {
                    clone_image.SetRGB(i - k, j - k, 0xFF, 0xEE, 0x00);
                    clone_image.SetRGB(i - k, j + k, 0xFF, 0xEE, 0x00);
                    clone_image.SetRGB(i + k, j - k, 0xFF, 0xEE, 0x00);
                    clone_image.SetRGB(i + k, j + k, 0xFF, 0xEE, 0x00);
                }
            }
        }
    }
}
