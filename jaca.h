#pragma once

#include <wx/numdlg.h>
#include <wx/wx.h>
#include <wx/progdlg.h>
#include <wx/dc.h>
#include <wx/wx.h>
#include <wx/statbmp.h>
#include <wx/panel.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/artprov.h>
#include<opencv2/highgui/highgui.hpp>
#include <wx/aboutdlg.h>


class CSizeKeepers
{

public:
	CSizeKeepers(wxPanel* main, wxPanel* left, wxPanel* right, wxStaticBitmap* image_canvas):
		main{ main }, left{ left }, right{ right }, image_canvas{ image_canvas }
	{
	}


	void setSizeOfPanel(wxSize s, wxPanel* panel);
	wxSize getSizeOfPanel(wxPanel* panel);

	void keepRatio( wxImage& image);


private:

	wxPanel* main = nullptr;
	wxPanel* left = nullptr;
	wxPanel* right = nullptr;
	wxStaticBitmap* image_canvas = nullptr;


};
