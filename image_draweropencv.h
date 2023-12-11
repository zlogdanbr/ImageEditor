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
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "filesys.h"


using namespace cv;


class CDrawerOpenCV
{
public:
	CDrawerOpenCV(wxImage& img);
	void showImage(const std::string& title);

private:
	Mat _img;

	wxImage wx_from_mat(Mat& img) const;
	Mat mat_from_wx(wxImage& wx) const;
};