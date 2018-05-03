#pragma once
#include "IImage.h"
#include "IParagraph.h"

class CDocumentItem
{
public:
	CDocumentItem(IImagePtr const& image, IParagraphPtr const& paragraph);
	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	IImagePtr GetImage();
	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	IParagraphPtr GetParagraph();
private:
	IImagePtr m_image;
	IParagraphPtr m_paragraph;
};
