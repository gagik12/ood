#include "stdafx.h"
#include "Canvas.h"


CCanvas::CCanvas(std::ostream & outStream)
	: m_outStream(outStream)
{
}

void CCanvas::SetColor(Color color)
{
	m_color = color;
	m_outStream << "Color: " << CColorUtil::ToString(m_color) << std::endl;
}

void CCanvas::DrawLine(CPoint const& from, CPoint const& to)
{
	m_outStream << "Draw line: from [" << from << "] to [" << to << "]" << std::endl;
}

void CCanvas::DrawEllipse(CPoint const& center, float width, float height)
{
	std::cout << "Draw ellipse center [" << center << "], Width: " << width << " height: " << height << std::endl;
}