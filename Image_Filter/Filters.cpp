#include "stdafx.h"
#include "Filters.h"

void Filters::Filter::setImage(cimg_library::CImg<unsigned char> source)
{
	image = source;
}

cimg_library::CImg<unsigned char> Filters::Filter::getImage()
{
	return image;
}

Filters::Filter::Filter()
{
	image = cimg_library::CImg<unsigned char>();
}

Filters::Filter::Filter(cimg_library::CImg<unsigned char> source)
{
	image = cimg_library::CImg<unsigned char>(source);
}

cimg_library::CImg<unsigned char> Filters::GaussianFilter::applyFilter()
{
	cimg_library::CImg<unsigned char> resultingImage(image._width, image._height, image._depth, image._spectrum);
	int x, y, z, i, j, value;
	for (x = 1; x < image._width - 1; x++)
	{
		for (y = 1; y < image._height - 1; y++)
			for (z = 0; z < image._spectrum; z++)
			{
				value = 0;
				for (i = -1; i < 2; i++)
					for (j = -1; j < 2; j++)
						value += image(x + i, y + j, z) * filter[i + 1][j + 1];
				resultingImage(x, y, z) = value / 16;
			}
	}
	return resultingImage;
}

cimg_library::CImg<unsigned char> Filters::SharpenFilter::applyFilter()
{
	cimg_library::CImg<unsigned char> resultingImage(image._width, image._height, image._depth, image._spectrum);
	int x, y, z, value;
	for (x = 1; x < image._width - 1; x++)
		for (y = 1; y < image._height - 1; y++)
			for (z = 0; z < image._spectrum; z++)
			{
				value = image(x, y, z) * filter[1][1] + image(x - 1, y, z) * filter[1][0] + image(x, y - 1, z) * filter[0][1] + image(x + 1, y, z) * filter[1][2] + image(x, y + 1, z) * filter[2][1];
				if (value > 255)
					value = 255;
				if (value < 0)
					value = 0;
				resultingImage(x, y, z) = value;
			}
	return resultingImage;
}

cimg_library::CImg<unsigned char> Filters::EdgeDetectionFilter::applyFilter()
{
	cimg_library::CImg<unsigned char> resultingImage(image._width, image._height, image._depth, image._spectrum);
	int x, y, z, i, j, value, max;
	for (x = 1; x < image._width - 1; x++)
	{
		for (y = 1; y < image._height - 1; y++)
		{
			max = 0;
			for (z = 0; z < image._spectrum; z++)
			{
				value = 0;
				for (i = -1; i < 2; i++)
					for (j = -1; j < 2; j++)
						value += image(x + i, y + j, z) * filter[i + 1][j + 1];
				if (value < 0)
					value = -value;
				if (value > 255)
					value = 255;
				max = value > max ? value : max;
			}
			resultingImage(x, y, 0) = max;
			resultingImage(x, y, 1) = max;
			resultingImage(x, y, 2) = max;
		}
	}
	return resultingImage;
}