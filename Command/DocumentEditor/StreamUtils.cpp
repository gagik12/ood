#include "stdafx.h"
#include "StreamUtils.h"
#include "Paragraph.h"
#include "StreamParsingError.h"
#include "StringUtils.h"

namespace ErrorMessages
{
	std::string INVALID_ARGUMENTS_COUNT_IN_INSERT_PARAGRAPH_COMMAND = "Invalid arguments count \n Usage: insertParagraph <position> | end <text>";
	std::string INVALID_ARGUMENTS_COUNT_IN_SAVE_COMMAND = "Invalid arguments count \n Usage: save <path>";
	std::string INVALID_INDEX = "Invalid index";
	std::string INVALID_PATH = "Invalid index";
}

ParagraphInfo CStreamUtils::GetParagraphInfo(std::istream & in, size_t itemsCount)
{
	static const std::string END = "end";
	ParagraphInfo paragraphInfo;
	std::string indexStr;
	if (!(in >> indexStr) || !(std::getline(in, paragraphInfo.second)))
	{
		throw CStreamParsingError(ErrorMessages::INVALID_ARGUMENTS_COUNT_IN_INSERT_PARAGRAPH_COMMAND);
	}
	
	if (indexStr != END)
	{
		try
		{
			paragraphInfo.first = boost::lexical_cast<size_t>(indexStr);
		}
		catch (boost::bad_lexical_cast const&)
		{
			throw CStreamParsingError(ErrorMessages::INVALID_INDEX);
		}
	}
	if (paragraphInfo.first.is_initialized() && (itemsCount < paragraphInfo.first.get()))
	{
		throw CStreamParsingError(ErrorMessages::INVALID_INDEX);
	}
	CStringUtils::LeftTrim(paragraphInfo.second);
	return paragraphInfo;
}

size_t CStreamUtils::GetIndex(std::istream & in, size_t itemsCount)
{
	size_t index;
	if (!(in >> index) || (index >= itemsCount))
	{
		throw CStreamParsingError(ErrorMessages::INVALID_INDEX);
	}
	return index;
}

std::string CStreamUtils::GetPath(std::istream & in)
{
	std::string path;
	if (!(in >> path))
	{
		throw CStreamParsingError(ErrorMessages::INVALID_ARGUMENTS_COUNT_IN_SAVE_COMMAND);
	}
	return path;
}

std::string CStreamUtils::GetText(std::istream & in)
{
	std::string title;
	std::getline(in, title);
	CStringUtils::LeftTrim(title);
	return title;
}