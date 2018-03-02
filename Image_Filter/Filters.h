#pragma once
#include "Cimg.h"

namespace Filters {

	class Filter
	{
	public:
		virtual cimg_library::CImg<unsigned char> applyFilter() = 0;
		void setImage(cimg_library::CImg<unsigned char> source);
		cimg_library::CImg<unsigned char> getImage();
		Filter();
		Filter(cimg_library::CImg<unsigned char> source);
	protected:
		cimg_library::CImg<unsigned char> image;
	};


	class GaussianFilter : public Filter
	{
	public:
		GaussianFilter() : Filter() {};
		GaussianFilter(cimg_library::CImg<unsigned char> source) : Filter(source) {};
		cimg_library::CImg<unsigned char> applyFilter();
	private:
		int filter[3][3] = { { 1,2,1 },{ 2,4,2 },{ 1,2,1 } };
	};

	class SharpenFilter : public Filter
	{
	public:
		SharpenFilter() : Filter() {};
		SharpenFilter(cimg_library::CImg<unsigned char> source) : Filter(source) {};
		cimg_library::CImg<unsigned char> applyFilter();
	private:
		int filter[3][3] = { { 0,-1,0 },{ -1,5,-1 },{ 0,-1,0 } };
	};

	class EdgeDetectionFilter : public Filter
	{
	public:
		EdgeDetectionFilter() : Filter() {};
		EdgeDetectionFilter(cimg_library::CImg<unsigned char> source) : Filter(source) {};
		cimg_library::CImg<unsigned char> applyFilter();
	private:
		int filter[3][3] = { { -1,-1,-1 },{ -1,8,-1 },{ -1,-1,-1 } };
	};	

}