#include "ovo.h"

MyDrawingFrame::MyDrawingFrame(wxFrame* parent, const wxImage& _image, wxColor* _color):
    wxFrame{ 
                parent, 
                wxID_ANY, 
                "Edit Image", 
                wxDefaultPosition, 
                wxSize( _image.GetWidth(),  _image.GetHeight())
            }
{
    color = _color;
    clone_image = _image.Copy();
    wxBitmap bitMap{ wxBitmap(clone_image) };
    image_canvas->SetSize(_image.GetWidth(), _image.GetHeight());
    image_canvas->SetBitmap(bitMap);

    image_canvas->Bind(wxEVT_MOTION, [&](wxMouseEvent& event)
        {
            if (event.Dragging())
            {
                wxClientDC dc(image_canvas);
                wxPen pen(*color, 2); // red pen of width 1
                dc.SetPen(pen);
                dc.DrawPoint(event.GetPosition());
                dc.SetPen(wxNullPen);
            }
        });

    image_canvas->Bind(wxEVT_RIGHT_DOWN, [&](wxMouseEvent& event)
        {
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
