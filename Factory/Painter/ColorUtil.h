#pragma once

#include "RGBColor.h"

enum class Color
{
	RED,
	GREEN,
	YELLOW,
	BLACK,
	BLUE,
	PINK
};

typedef std::map<std::string, Color> ColorMap;
typedef std::map<std::string, RGBColor> RGBColorMap;

static const int MAX_RGB_COLOR_VALUE = 255;

const ColorMap COLOR_MAP = {
	{ "red", Color::RED },
	{ "green", Color::GREEN },
	{ "blue", Color::BLUE },
	{ "yellow", Color::YELLOW },
	{ "black", Color::BLACK },
	{ "pink", Color::PINK }
};

const RGBColorMap RGB_COLOR_MAP = {
	{ "red", RGBColor({ uint8_t(255), uint8_t(0), uint8_t(0) }) },
	{ "green",  RGBColor({ uint8_t(0), uint8_t(255), uint8_t(0) }) },
	{ "blue",  RGBColor({ uint8_t(0), uint8_t(0), uint8_t(255) }) },
	{ "yellow",  RGBColor({ uint8_t(255), uint8_t(255), uint8_t(0) }) },
	{ "black",  RGBColor({ uint8_t(0),uint8_t(0), uint8_t(0) }) },
	{ "pink",  RGBColor({ uint8_t(255), uint8_t(192), uint8_t(203) }) }
};

class CColorUtil
{
public:
	static Color ToColor(std::string const& str);
	static std::string ToString(Color color);
	static RGBColor ToRGBColor(std::string const& str);
};

