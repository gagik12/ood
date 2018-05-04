#pragma once
#include "IParagraph.h"

typedef std::pair<int, int> Size;
typedef std::pair<boost::optional<size_t>, std::string> ParagraphInfo;
typedef std::pair<boost::optional<size_t>, Size> ResizeImageOptions;

struct ImageInfo
{
	Size size;
	boost::optional<size_t> position;
	std::string path;
};

class CStreamUtils
{
public:
	static ParagraphInfo GetParagraphInfo(std::istream & in, size_t itemsCount);
	static ImageInfo GetImageInfo(std::istream & in, size_t itemsCount);
	static ResizeImageOptions GetResizeImageOptions(std::istream & in, size_t itemsCount);
	static size_t GetIndex(std::istream & in, size_t itemsCount);
	static std::string GetPath(std::istream & in);
	static std::string GetText(std::istream & in);
};

