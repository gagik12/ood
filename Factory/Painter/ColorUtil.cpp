#include "stdafx.h"
#include "ColorUtil.h"
#include "RGBColor.h"

Color CColorUtil::ToColor(std::string const& str)
{
	auto it = COLOR_MAP.find(str);

	if (it == COLOR_MAP.end())
	{
		throw std::invalid_argument("Color not found");
	}

	return it->second;
}

std::string CColorUtil::ToString(Color color)
{
	switch (color)
	{
	case Color::GREEN:
		return "green";
	case Color::RED:
		return "red";
	case Color::BLUE:
		return "blue";
	case Color::YELLOW:
		return "yellow";
	case Color::PINK:
		return "pink";
	case Color::BLACK:
		return "black";
	default:
		return "black";
	}
}

RGBColor CColorUtil::ToRGBColor(std::string const& str)
{
	auto it = RGB_COLOR_MAP.find(str);

	if (it == RGB_COLOR_MAP.end())
	{
		throw std::invalid_argument("Color not found");
	}

	return it->second;
}
