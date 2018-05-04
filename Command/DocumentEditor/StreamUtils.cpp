#include "stdafx.h"
#include "StreamUtils.h"
#include "Paragraph.h"
#include "StreamParsingError.h"
#include "StringUtils.h"
#include "FileUtils.h"

static const std::string END = "end";

namespace ErrorMessages
{
	std::string INVALID_ARGUMENTS_COUNT_IN_INSERT_PARAGRAPH_COMMAND = "Invalid arguments count \n Usage: insertParagraph <position> | end <text>";
	std::string INVALID_ARGUMENTS_COUNT_IN_SAVE_COMMAND = "Invalid arguments count \n Usage: save <path>";
	std::string INVALID_ARGUMENTS_COUNT_IN_RESIZE_IMAGE_COMMAND = "Invalid arguments count \n Usage: resizeImage <position> <width> <height>";
	std::string INVALID_ARGUMENTS_COUNT_IN_INSERT_IMAGE_COMMAND = "Invalid arguments count \n Usage: insertImage <position>|end <width> <height> <path>";
	std::string INVALID_INDEX = "Invalid index";
	std::string INVALID_IMAGE_SIZE = "Invalid image size. Size range [1 .. 10000]";
}

namespace
{
	bool IsAllowableSize(std::pair<int, int> const& size)
	{
		static const std::pair<int, int> SIZE_RANGE = std::make_pair(1, 10000);
		return (size.first >= SIZE_RANGE.first) && (size.second >= SIZE_RANGE.first)
			&& (size.first <= SIZE_RANGE.second) && (size.second <= SIZE_RANGE.second);
	};
}

ParagraphInfo CStreamUtils::GetParagraphInfo(std::istream & in, size_t itemsCount)
{
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

ImageInfo CStreamUtils::GetImageInfo(std::istream & in, size_t itemsCount)
{
	ImageInfo imageInfo;
	std::string positionStr;
	std::string widthStr;
	std::string heightStr;
	if (!(in >> positionStr) || !(in >> widthStr) || !(in >> heightStr) || !(std::getline(in, imageInfo.path)))
	{
		throw CStreamParsingError(ErrorMessages::INVALID_ARGUMENTS_COUNT_IN_INSERT_IMAGE_COMMAND);
	}
	try
	{
		if (positionStr != END)
		{
			imageInfo.position = boost::lexical_cast<size_t>(positionStr);
		}
		imageInfo.size.first = boost::lexical_cast<int>(widthStr);
		imageInfo.size.second = boost::lexical_cast<int>(heightStr);
	}
	catch (boost::bad_lexical_cast const& ex)
	{
		throw CStreamParsingError(ex.what());
	}

	if (!IsAllowableSize(imageInfo.size))
	{
		throw std::out_of_range(ErrorMessages::INVALID_IMAGE_SIZE);
	}

	if (imageInfo.position.is_initialized() && (itemsCount < imageInfo.position.get()))
	{
		throw CStreamParsingError(ErrorMessages::INVALID_INDEX);
	}
	CStringUtils::LeftTrim(imageInfo.path);
	return imageInfo;
}

ResizeImageOptions CStreamUtils::GetResizeImageOptions(std::istream & in, size_t itemsCount)
{
	ResizeImageOptions resizeImageOptions;
	std::string positionStr;
	std::string widthStr;
	std::string heightStr;
	if (!(in >> positionStr) || !(in >> widthStr) || !(in >> heightStr))
	{
		throw CStreamParsingError(ErrorMessages::INVALID_ARGUMENTS_COUNT_IN_RESIZE_IMAGE_COMMAND);
	}
	try
	{
		auto & size = resizeImageOptions.second;
		resizeImageOptions.first = boost::lexical_cast<size_t>(positionStr);
		size.first = boost::lexical_cast<int>(widthStr);
		size.second = boost::lexical_cast<int>(heightStr);
	}
	catch (boost::bad_lexical_cast const& ex)
	{
		throw CStreamParsingError(ex.what());
	}

	if (!IsAllowableSize(resizeImageOptions.second))
	{
		throw std::out_of_range(ErrorMessages::INVALID_IMAGE_SIZE);
	}

	if (resizeImageOptions.first.is_initialized() && (itemsCount < resizeImageOptions.first.get()))
	{
		throw CStreamParsingError(ErrorMessages::INVALID_INDEX);
	}
	return resizeImageOptions;
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