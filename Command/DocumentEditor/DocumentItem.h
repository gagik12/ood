#pragma once
#include "IImage.h"
#include "IParagraph.h"

class CDocumentItem
{
public:
	CDocumentItem(IImagePtr const& image, IParagraphPtr const& paragraph);
	// ���������� ��������� �� �����������, ���� nullptr, ���� ������� �� �������� ������������
	IImagePtr GetImage();
	// ���������� ��������� �� ��������, ���� nullptr, ���� ������� �� �������� ����������
	IParagraphPtr GetParagraph();
private:
	IImagePtr m_image;
	IParagraphPtr m_paragraph;
};
