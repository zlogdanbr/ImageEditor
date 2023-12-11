#include "image_util.h"

namespace image_util
{
    // http://cool-emerald.blogspot.com/2017/11/opencv-with-wxwidgets.html
    wxImage wx_from_mat(Mat& img)
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
    Mat mat_from_wx(wxImage& wx)
    {
        Mat im2(Size(wx.GetWidth(), wx.GetHeight()), CV_8UC3, wx.GetData());
        cvtColor(im2, im2, COLOR_RGB2BGR);
        return im2;
    }

    void putpixel(int i, int j, wxImage img, RGB& rgb)
    {
        img.SetRGB(i, j, rgb[0], rgb[1], rgb[2]);
    }

    void drawcircle(int x0, int y0, int radius, wxImage img, RGB& r)
    {
        int x = radius;
        int y = 0;
        int err = 0;

        while (x >= y)
        {
            putpixel(x0 + x, y0 + y, img, r);
            putpixel(x0 + y, y0 + x, img, r);
            putpixel(x0 - y, y0 + x, img, r);
            putpixel(x0 - x, y0 + y, img, r);
            putpixel(x0 - x, y0 - y, img, r);
            putpixel(x0 - y, y0 - x, img, r);
            putpixel(x0 + y, y0 - x, img, r);
            putpixel(x0 + x, y0 - y, img, r);

            if (err <= 0)
            {
                y += 1;
                err += 2 * y + 1;
            }

            if (err > 0)
            {
                x -= 1;
                err -= 2 * x + 1;
            }
        }
    }

};