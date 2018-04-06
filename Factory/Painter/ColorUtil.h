#pragma once

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

const ColorMap COLOR_MAP = {
	{ "red", Color::RED },
	{ "green", Color::GREEN },
	{ "blue", Color::BLUE },
	{ "yellow", Color::YELLOW },
	{ "black", Color::BLACK },
	{ "pink", Color::PINK }
};

class CColorUtil
{
public:
	static Color ToColor(std::string const& str);
	static std::string ToString(Color color);
};

