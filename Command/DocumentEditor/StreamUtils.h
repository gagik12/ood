#pragma once
#include "IParagraph.h"

typedef std::pair<boost::optional<size_t>, std::string> ParagraphInfo;

class CStreamUtils
{
public:
	static ParagraphInfo GetParagraphInfo(std::istream & in, size_t itemsCount);
	static size_t GetIndex(std::istream & in, size_t itemsCount);
	static std::string GetPath(std::istream & in);
	static std::string GetText(std::istream & in);
};

