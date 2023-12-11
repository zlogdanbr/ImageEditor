#include "CImageEditorPlus.h"


static void onMouse(int event, int x, int y, int, void* userInput)
{

}

CImageEditorPlus::CImageEditorPlus(wxImage& image)
{
	op_cv_image = image_util::mat_from_wx(image);
}

void CImageEditorPlus::loadImage()
{
    int value = 1;
    namedWindow("edit", WINDOW_NORMAL);
    imshow("edit", op_cv_image);    
}