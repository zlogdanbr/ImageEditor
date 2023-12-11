#include "image_draweropencv.h"


CDrawerOpenCV::CDrawerOpenCV(wxImage& img)
{
    _img = mat_from_wx(img);
}


// http://cool-emerald.blogspot.com/2017/11/opencv-with-wxwidgets.html
wxImage CDrawerOpenCV::wx_from_mat(Mat& img) const
{
    Mat im2;
    if (img.channels() == 1) { cvtColor(img, im2, COLOR_GRAY2RGB); }
    else if (img.channels() == 4) { cvtColor(img, im2, COLOR_BGRA2RGB); }
    else { cvtColor(img, im2, COLOR_BGR2RGB); }
    long imsize = im2.rows * im2.cols * im2.channels();
    wxImage wx(im2.cols, im2.rows, (unsigned char*)malloc(imsize), false);
    unsigned char* s = im2.data;
    unsigned char* d = wx.GetData();
    for (long i = 0; i < imsize; i++) { d[i] = s[i]; }
    return wx;
}

// http://cool-emerald.blogspot.com/2017/11/opencv-with-wxwidgets.html
Mat CDrawerOpenCV::mat_from_wx(wxImage& wx) const
{
    Mat im2(Size(wx.GetWidth(), wx.GetHeight()), CV_8UC3, wx.GetData());
    cvtColor(im2, im2, COLOR_RGB2BGR);
    return im2;
}

// https://docs.opencv.org/4.x/d5/d98/tutorial_mat_operations.html
void CDrawerOpenCV::showImage(const std::string& title)
{
    /*
            The function creates a window and allows users to select a ROI using the mouse.
            Controls: use space or enter to finish selection, use key c to cancel selection
            (function will return the zero cv::Rect)

    */

    Rect rect = selectROI("Image", _img,false);
    Mat roi = Mat(_img, rect);

    cv::Size s = roi.size();
    if (s.width == 0 || s.height == 0)
    {
        return;
    }

    wxFileDialog saveFileDialog(nullptr,
        wxEmptyString,
        wxEmptyString,
        "MyFile.jpg", "Text Files (*.jpg)|*.jpg|All Files (*.*)|*.*",
        wxFD_SAVE);

    if (saveFileDialog.ShowModal() == wxID_OK)
    {
        wxString path = saveFileDialog.GetPath();
        wxImage tmp = wx_from_mat(roi);
        tmp.SaveFile(path, wxBITMAP_TYPE_JPEG);
    }

}