#pragma once
#include "RGBColor.h"
template <typename T>
struct Rect
{
	T left;
	T top;
	T width;
	T height;
};

typedef Rect<double> RectD;

const int MAX_RGB_COLOR_VALUE = 255;