#include "stdafx.h"
#include "HtmlExporter.h"
#include "StringUtils.h"
#include "FileUtils.h"

namespace Templates
{
	const std::string TITLE = R"(<title>%1%</title>
)";
	const std::string IMAGE = R"(<img src="%1%" width="%2%" height="%3%">
)";
	const std::string PARAGRAPH = R"(<p>%1%</p>
)";
	const std::string MAIN = R"(
<!DOCTYPE html>
<html>
	<head>
		%1%
	</head>
	<body>
		%2%
	</body>
</html>)";
}

CHtmlExporter::CHtmlExporter(std::string const& title, std::vector<CDocumentItem> const& documentItems)
	: m_title(title)
	, m_documentItems(documentItems)
{
}

std::string CHtmlExporter::ConvertTitleInDOMElement()
{
	CStringUtils::EncodeSpecialCharacters(m_title);
	return (boost::format(Templates::TITLE) % m_title).str();
}

std::string CHtmlExporter::ConvertImageInDOMElement(IImagePtr const& image) const
{
	std::string path = image->GetPath().string();
	CStringUtils::EncodeSpecialCharacters(path);
	return (boost::format(Templates::IMAGE) % path % image->GetWidth() % image->GetHeight()).str();
}

std::string CHtmlExporter::ConvertParagraphInDOMElement(IParagraphPtr const& paragraph) const
{
	std::string text = paragraph->GetText();
	CStringUtils::EncodeSpecialCharacters(text);
	return (boost::format(Templates::PARAGRAPH) % text).str();
}

std::string CHtmlExporter::ConvertDocumentInDOMElements() const
{
	std::string documentElements;
	for (auto item : m_documentItems)
	{
		std::string itemElements;
		auto paragraph = item.GetParagraph();
		auto image = item.GetImage();
		if (paragraph != nullptr)
		{
			itemElements = ConvertParagraphInDOMElement(paragraph);
		}
		if (image != nullptr)
		{
			itemElements += ConvertImageInDOMElement(image);
		}
		documentElements += itemElements;
	}
	return documentElements;
}

void CHtmlExporter::Export(boost::filesystem::path const& path)
{
	std::string titleElement = ConvertTitleInDOMElement();
	std::string documentElements = ConvertDocumentInDOMElements();
	std::string htmlCode = (boost::format(Templates::MAIN) % titleElement % documentElements).str();
	SaveHtmlCodeInFile(htmlCode, path);
	CFileUtils::CopyFolderWithImage(FOLDER_WITH_IMAGES, path.branch_path());
}

void CHtmlExporter::SaveHtmlCodeInFile(std::string const& pageCode, boost::filesystem::path const& path) const
{
	boost::filesystem::path directory = path.branch_path();
	if (!boost::filesystem::exists(directory))
	{
		boost::filesystem::create_directory(directory);
	}
	std::ofstream stream(path.string());

	stream << pageCode << std::endl;
}

