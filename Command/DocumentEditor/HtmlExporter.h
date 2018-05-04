#pragma once
#include "IDocument.h"

class CHtmlExporter
{
public:
	CHtmlExporter(std::string const& title, std::vector<CDocumentItem> const& documentItems);
	void Export(boost::filesystem::path const& path);
private:
	std::string m_title;
	std::vector<CDocumentItem> const& m_documentItems;

	std::string ConvertTitleInDOMElement();
	std::string ConvertImageInDOMElement(IImagePtr const& image) const;
	std::string ConvertParagraphInDOMElement(IParagraphPtr const& paragraph) const;
	std::string ConvertDocumentInDOMElements() const;

	void SaveHtmlCodeInFile(std::string const& pageCode, boost::filesystem::path const& path) const;
};
