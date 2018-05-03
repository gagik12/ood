#include "stdafx.h"
#include "DocumentItem.h"

CDocumentItem::CDocumentItem(IImagePtr const& image, IParagraphPtr const& paragraph)
	: m_image(image)
	, m_paragraph(paragraph)
{
}

IImagePtr CDocumentItem::GetImage()
{
	return m_image;
}

IParagraphPtr CDocumentItem::GetParagraph()
{
	return m_paragraph;
}
