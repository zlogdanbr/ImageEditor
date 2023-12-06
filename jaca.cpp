#include "jaca.h"


void CSizeKeepers::setSizeOfPanel(wxSize s, wxPanel* panel)
{
	panel->SetSize(s);
}

wxSize CSizeKeepers::getSizeOfPanel(wxPanel* panel)
{
	return panel->GetSize();
}

void CSizeKeepers::keepRatio(wxImage& image)
{
	auto smain = getSizeOfPanel(main);// can increase or decrease on maximize
	auto sright = getSizeOfPanel(right);// can increase or decrease on maximize
	auto sleft = getSizeOfPanel(left);// fixed
	auto scanvas = image_canvas->GetSize();// can increase with the image size
	auto simage = image.GetSize();// should set all the other sizes

	int smainH = smain.GetHeight();
	int smainW = smain.GetWidth();
	int imageH = image.GetHeight();
	int imageW = image.GetWidth();
	int srightH = sright.GetHeight();
	int srightW = sright.GetWidth();
	int sleftH = sleft.GetHeight();
	int sleftW = sleft.GetWidth();
	int scanvasH = scanvas.GetHeight();
	int scanvasW = scanvas.GetWidth();

	if (imageH >= smainH || imageW >= smainW )
	{
		srightH = smainH - 10;
		srightW = smainW - sleftW;
		scanvasH = srightH - 10;
		scanvasW = srightW - 10;
		imageH = scanvasH - 5;
		imageW = scanvasW - 5;
	}
	else
	{
		scanvasH = srightH;
		scanvasW = srightW;
		imageH = scanvasH - 5;
		imageW = scanvasW - 5;
	}

	sright.SetHeight(srightH);
	sright.SetWidth(srightW);

	scanvas.SetHeight(scanvasH);
	scanvas.SetWidth(scanvasW);

	simage.SetHeight(imageH);
	simage.SetWidth(imageW);

	right->SetSize(sright);
	image_canvas->SetSize(scanvas);
	image.Size(simage, { -1, -1 });

	wxBitmap bitMap{ wxBitmap(image) };
	image_canvas->SetBitmap(bitMap);
}