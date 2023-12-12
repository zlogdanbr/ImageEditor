#include "image_draweropencv.h"
#include "image_util.h"

CDrawerOpenCV::CDrawerOpenCV(wxImage& img)
{
    _img = image_util::mat_from_wx(img);
}

// https://docs.opencv.org/4.x/d5/d98/tutorial_mat_operations.html
void CDrawerOpenCV::showImage(const std::string& title)
{
    /*
            The function creates a window and allows users to select a ROI using the mouse.
            Controls: use space or enter to finish selection, use key c to cancel selection
            (function will return the zero cv::Rect)
    */

    Mat clone = _img.clone();
    Rect rect = selectROI(title, clone,false);
    Mat roi = Mat(clone, rect);

    waitKey(0);
    

    cv::Size s = roi.size();
    if (s.width == 0 || s.height == 0)
    {
        destroyWindow(title);
        return;
    }

    destroyWindow(title);

    wxFileDialog saveFileDialog(nullptr,
        wxEmptyString,
        wxEmptyString,
        "MyFile.jpg", "Text Files (*.jpg)|*.jpg|All Files (*.*)|*.*",
        wxFD_SAVE);

    if (saveFileDialog.ShowModal() == wxID_OK)
    {
        wxString path = saveFileDialog.GetPath();
        wxImage tmp = image_util::wx_from_mat(roi);
        tmp.SaveFile(path, wxBITMAP_TYPE_JPEG);
    }

}