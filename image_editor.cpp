#include "childframes.h"
#include "wxwimage_algos.h"
#include <wx/colordlg.h>


void CImageCustomDialog::setControlslayout()
{
    // set base sizer
    this->SetSize(CHILD_DEFAULT_W, CHILD_DEFAULT_H);
    basePanel->SetSize(CHILD_DEFAULT_W, CHILD_DEFAULT_H);
    basePanel->SetSizer(baseSizer);

    // add buttons to the horizontal box
    vbox1->Add(button5);
    vbox1->Add(button2);
    vbox1->Add(button3);
    vbox1->Add(button6);
    vbox1->Add(button4);
    vbox1->Add(button8);
    vbox1->Add(button9);
    vbox1->Add(button10);
    vbox1->Add(button11);
    vbox1->Add(button12);
    vbox1->Add(button13);
    vbox1->Add(button14);
    vbox1->Add(button17);

    vbox2->Add( image_canvas, 
                wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL);// wxALIGN_CENTER_HORIZONTAL

    // set horizontal base sizer at panel1 and panel2
    panel1->SetSizer(vbox1);
    panel2->SetSizer(vbox2);

    // add panel1 to the base sizer at the base panel
    baseSizer->Add(panel1);
    baseSizer->Add(panel2);

    Center();
}


CImageCustomDialog::CImageCustomDialog(wxMDIParentFrame* parent) :wxMDIChildFrame(parent, wxID_ANY, "Image Editor")
{

    memset(myrgb, 0x00, 3);

    setControlslayout();

    this->Bind(wxEVT_MAXIMIZE, [&](wxMaximizeEvent& event)
        {

        });

    image_canvas->Bind(wxEVT_LEFT_DOWN, [&](wxMouseEvent& event)
        {
        });

    button2->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            // cancel
            Close();
        });


    button3->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            if (image.IsOk())
            {
                wxNumberEntryDialog dialog(this, "Scale Factor", "Choose Scale Factor", "Scale Factor", 2, 2, 10);

                if (dialog.ShowModal() == wxID_OK)
                {
                    backup = image.Copy();
                    auto scale = static_cast<int>(dialog.GetValue());
                    Dimensions d;
                    wxImage image2 = scaleLessImage(image, scale, d);
                    image = image2.Copy();
                    image2.Clear();
                    reloadImage();
                    changed = true;
                    return;
                }
                changed = false;
            }

        });

    button6->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            if (image.IsOk())
            {
                wxNumberEntryDialog dialog(this, "Scale Factor", "Choose Scale Factor", "Scale Factor", 2, 2, 10);

                if (dialog.ShowModal() == wxID_OK)
                {
                    backup = image.Copy();
                    auto scale = static_cast<int>(dialog.GetValue());                    
                    Dimensions d;
                    wxImage image2 = scalePlusImage(image, scale, d);
                    image = image2.Copy();
                    image2.Clear();
                    reloadImage();
                    changed = true;
                    return;
                }
                changed = false;
            }
        });

    button4->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            if (image.IsOk())
            {
                SaveImage();
            }

        });

    button5->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            loadImage();
            backup = image.Copy();
        });

    button8->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            if (image.IsOk())
            {
                backup = image.Copy();
                wxImage image2 = image.Rotate90(true);
                image = image2.Copy();
                image2.Clear();
                image2.Destroy();
                reloadImage();
                changed = true;
                return;
            }
            changed = false;
        });

    button9->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            if (image.IsOk())
            {
                backup = image.Copy();
                wxImage image2 = rotate_right(image);
                image = image2.Copy();
                image2.Clear();
                image2.Destroy();
                reloadImage();
                changed = true;
                return;
            }
            changed = false;
        });

    button10->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            int alpha = 30;
            if (image.IsOk())
            {
                wxNumberEntryDialog dialog(this, "Scale Factor", "Choose Scale Factor", "Scale Factor", 2, 1, 100);

                if (dialog.ShowModal() == wxID_OK)
                {
                    backup = image.Copy();
                    auto scale = static_cast<int>(dialog.GetValue());
                    wxImage image2 = BlurH(image, scale);
                    image = image2.Copy();
                    image2.Clear();
                    reloadImage();
                    changed = true;
                    return;
                }
            }
            changed = false;
        });

    button11->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            if (image.IsOk())
            {
                wxNumberEntryDialog dialog(this, "Scale Factor", "Choose Scale Factor", "Scale Factor", 2, 1, 100);
                if (dialog.ShowModal() == wxID_OK)
                {
                    backup = image.Copy();
                    auto scale = static_cast<int>(dialog.GetValue());
                    wxImage image2 = BlurV(image, scale);
                    image = image2.Copy();
                    image2.Clear();
                    reloadImage();
                    changed = true;
                    return;
                }
            }
            changed = false;
        });

    button12->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            if (image.IsOk())
            {
                wxNumberEntryDialog dialog(this, "Scale Factor", "Choose Scale Factor", "Scale Factor", 2, 1, 100);
                if (dialog.ShowModal() == wxID_OK)
                {
                    backup = image.Copy();
                    auto scale = static_cast<int>(dialog.GetValue());
                    wxImage image2 = Blur(image, scale);
                    image = image2.Copy();
                    image2.Clear();
                    reloadImage();
                    changed = true;
                    return;
                }
            }
            changed = false;
        });

    button13->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            if (image.IsOk())
            {
                backup = image.Copy();
                wxImage image2 = ConvertToGrayScale(image);
                image = image2.Copy();
                image2.Clear();
                image2.Destroy();
                reloadImage();
                changed = true;                
                return;
            }

            changed = false;
        });

    button14->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            if (image.IsOk())
            {
                wxColourDialog colourDialog(this);

                if (colourDialog.ShowModal() == wxID_OK)
                {
                    wxColour color = colourDialog.GetColourData().GetColour();
                    myrgb[0] = color.GetRed();
                    myrgb[1] = color.GetGreen();
                    myrgb[2] = color.GetBlue();
                }
            }
        });

    image_canvas->Bind(wxEVT_RIGHT_DOWN, [&](wxMouseEvent& event)
        {
            if (image.IsOk())
            {   
                wxColourDialog colourDialog(this);

                if (colourDialog.ShowModal() == wxID_OK) 
                {
                    wxColour color = colourDialog.GetColourData().GetColour();    
                    myrgb[0] = color.GetRed();
                    myrgb[1] = color.GetGreen();
                    myrgb[2] = color.GetBlue();

                }
            }
        });

    button17->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            if (image.IsOk())
            {
                if (changed == false)
                {
                    image.Clear();
                    image.Destroy();
                    if (backup.IsOk())
                    {
                        image = backup.Copy();
                        reloadImage();
                    }
                }
                else
                {
                    image = backup.Copy();
                    reloadImage();
                    changed = false;
                    backup.Clear();
                    backup.Destroy();
                    backup = image.Copy();
                }
            }
        });
}


void CImageCustomDialog::loadImage()
{
    wxInitAllImageHandlers();

    wxFileDialog openFileDialog(this,
        wxEmptyString,
        wxEmptyString,
        wxEmptyString,
        "jpg and tif files(*.jpg; *.tif) | *.jpg; *.tif",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_OK)
    {
        wxString path = openFileDialog.GetPath();
        wxImage tmp(path);
        image = tmp;
        image_canvas->SetSize(CHILD_DEFAULT_W, CHILD_DEFAULT_H);
        reloadImage();
    }
}

void CImageCustomDialog::reloadImage()
{
    if (image.IsOk() == true)
    {
        int w = image.GetWidth();
        int h = image.GetHeight();
        wxBitmap bitMap{ wxBitmap(image) };
        image_canvas->SetBitmap(bitMap);
        image_canvas->SetSize(w, h);
    }
}

void CImageCustomDialog::SaveImage()
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
        tmp = image.Copy();
        tmp.SaveFile(path, wxBITMAP_TYPE_JPEG);
    }
}
