#pragma once
#include "opencv2/objdetect.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>
#include "wx/wx.h"


using namespace cv;

namespace image_util
{
    using CPointCst = std::pair<int, int>;
    using CDataValue = std::vector<CPointCst>;
    using RGB = unsigned char[3];

    class CDataCapture : public CDataValue
    {
    public:
        void insertPoint(int x, int y)
        {
            CPointCst p{ x,y };
            this->push_back(p);
        }

        void clear_me()
        {
            this->clear();
        }

        bool isPointInThePicture(int x, int y)
        {
            CPointCst p(x, y);
            if (std::find(this->begin(), this->end(), p) != this->end())
            {
                return true;
            }
            return false;
        }
    };

    wxImage wx_from_mat(Mat& img);
    Mat mat_from_wx(wxImage& wx);

    void putpixel(int i, int j, wxImage img, RGB& rgb);

    //------------------------------------------------------------------------
    // Mid Point Algorithm for circles
    // https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
    // Adapted from 
    // https://www.thecrazyprogrammer.com/2016/12/bresenhams-midpoint-circle-algorithm-c-c.html
    //------------------------------------------------------------------------
    void drawcircle(int x0, int y0, int radius, wxImage img, RGB& r);

};