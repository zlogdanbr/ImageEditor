#include "childframes.h"
#include <wx/colordlg.h>
#include "image_acton.h"
#include "image_draweropencv.h"

CImageCustomDialog::CImageCustomDialog(wxMDIParentFrame* parent) :wxMDIChildFrame(parent, wxID_ANY, "Image Editor")
{
    setControlslayout();

    // captures ROI
    button15->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            if (image.IsOk())
            {
                CDrawerOpenCV cdrawer(image);
                std::string s = "Edit";
                cdrawer.showImage(s);
            }
        });

    // close current frame
    button2->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            Close();
        });

    // scale less 
    button3->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            if (image.IsOk())
            {
                wxNumberEntryDialog dialog(this, "Scale Factor", "Choose Scale Factor", "Scale Factor", 2, 2, 10);

                if (dialog.ShowModal() == wxID_OK)
                {
                    doscaleLess(dialog);
                    return;
                }
                changed = false;
            }

        });

    // scale plus
    button6->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            if (image.IsOk())
            {
                wxNumberEntryDialog dialog(this, "Scale Factor", "Choose Scale Factor", "Scale Factor", 2, 2, 10);

                if (dialog.ShowModal() == wxID_OK)
                {
                    doscalePlus(dialog);
                    return;
                }
                changed = false;
            }
        });

    // Save Image
    button4->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            if (image.IsOk())
            {
                SaveImage();
            }
        });

    // load image
    button5->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            loadImage();
            backup = image.Copy();
        });

    // rotate left
    button8->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            if (image.IsOk())
            {
                dorotateLeft();
                return;
            }
            changed = false;
        });

    // rotate right
    button9->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            if (image.IsOk())
            {
                dorotateRight();
                return;
            }
            changed = false;
        });

    // blur H
    button10->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            if (image.IsOk())
            {
                wxNumberEntryDialog dialog(this, "Scale Factor", "Choose Scale Factor", "Scale Factor", 2, 1, 100);

                if (dialog.ShowModal() == wxID_OK)
                {
                    doblurH(dialog);
                    return;
                }
            }
            changed = false;
        });

    // blur V
    button11->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            if (image.IsOk())
            {
                wxNumberEntryDialog dialog(this, "Scale Factor", "Choose Scale Factor", "Scale Factor", 2, 1, 100);
                if (dialog.ShowModal() == wxID_OK)
                {
                    doblurv(dialog);
                    return;
                }
            }
            changed = false;
        });

    // blur
    button12->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            if (image.IsOk())
            {
                wxNumberEntryDialog dialog(this, "Scale Factor", "Choose Scale Factor", "Scale Factor", 2, 1, 100);
                if (dialog.ShowModal() == wxID_OK)
                {
                    doblur(dialog);
                    return;
                }
            }
            changed = false;
        });

    // conver to gray
    button13->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event)
        {
            if (image.IsOk())
            {
                ConverImageToGray();
                return;
            }

            changed = false;
        });

    // restore last
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

void CImageCustomDialog::doscaleLess(wxNumberEntryDialog& dialog)
{
    backup = image.Copy();
    auto scale = static_cast<int>(dialog.GetValue());
    Dimensions d;
    wxImage image2 = scaleLessImage(image, scale, d);
    image = image2.Copy();
    image2.Clear();
    reloadImage();
    changed = true;
}

void CImageCustomDialog::doscalePlus(wxNumberEntryDialog& dialog)
{
    backup = image.Copy();
    auto scale = static_cast<int>(dialog.GetValue());
    Dimensions d;
    wxImage image2 = scalePlusImage(image, scale, d);
    image = image2.Copy();
    image2.Clear();
    reloadImage();
    changed = true;
}

void CImageCustomDialog::dorotateLeft()
{
    backup = image.Copy();
    // rotate_left
    wxImage image2 = rotate_left(image);
    image = image2.Copy();
    image2.Clear();
    image2.Destroy();
    reloadImage();
    changed = true;
}

void CImageCustomDialog::dorotateRight()
{
    backup = image.Copy();
    wxImage image2 = rotate_right(image);
    image = image2.Copy();
    image2.Clear();
    image2.Destroy();
    reloadImage();
    changed = true;
}

void CImageCustomDialog::doblurH(wxNumberEntryDialog& dialog)
{
    backup = image.Copy();
    auto scale = static_cast<int>(dialog.GetValue());
    wxImage image2 = BlurH(image, scale);
    image = image2.Copy();
    image2.Clear();
    reloadImage();
    changed = true;
}

void CImageCustomDialog::doblurv(wxNumberEntryDialog& dialog)
{
    backup = image.Copy();
    auto scale = static_cast<int>(dialog.GetValue());
    wxImage image2 = BlurV(image, scale);
    image = image2.Copy();
    image2.Clear();
    reloadImage();
    changed = true;
}

void CImageCustomDialog::doblur(wxNumberEntryDialog& dialog)
{
    backup = image.Copy();
    auto scale = static_cast<int>(dialog.GetValue());
    wxImage image2 = Blur(image, scale);
    image = image2.Copy();
    image2.Clear();
    reloadImage();
    changed = true;
}

void CImageCustomDialog::ConverImageToGray()
{
    backup = image.Copy();
    wxImage image2 = ConvertToGrayScale(image);
    image = image2.Copy();
    image2.Clear();
    image2.Destroy();
    reloadImage();
    changed = true;
}

void CImageCustomDialog::setControlslayout()
{
    // set base sizer
    this->SetSize(CHILD_DEFAULT_W, CHILD_DEFAULT_H);
    basePanel->SetSize(CHILD_DEFAULT_W, CHILD_DEFAULT_H);
    basePanel->SetSizer(baseSizer);

    // add buttons to the horizontal box
    vbox1->Add(button5);
    vbox1->Add(button4);
    vbox1->Add(button2);
    vbox1->Add(button3);
    vbox1->Add(button6);
    vbox1->Add(button8);
    vbox1->Add(button9);
    vbox1->Add(button10);
    vbox1->Add(button11);
    vbox1->Add(button12);
    vbox1->Add(button13);
    vbox1->Add(button17);
    vbox1->Add(button15);

    vbox2->Add(image_canvas,
        wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL);// wxALIGN_CENTER_HORIZONTAL

    // set horizontal base sizer at panel1 and panel2
    panel1->SetSizer(vbox1);
    panel2->SetSizer(vbox2);

    // add panel1 to the base sizer at the base panel
    baseSizer->Add(panel1);
    baseSizer->Add(panel2);

    Center();
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
        reloadImage();
    }
}

void CImageCustomDialog::reloadImage()
{
    if (image.IsOk() == true)
    {
        CImage.keepRatio(image);
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
