#include "stdafx.h"
#include "Canvas.h"


CCanvas::CCanvas(std::ostream & ostream)
	: m_ostream(ostream)
{
}


void CCanvas::SetLineColor(RGBAColor color)
{
	m_ostream << "Color ( " << color << " )" << std::endl;
}

void CCanvas::BeginFill(RGBAColor color)
{
	m_ostream << "BeginFill" << std::endl;
	m_ostream << "FillColor ( " << color << " )" << std::endl;
}

void CCanvas::EndFill() 
{
	m_ostream << "EndFill" << std::endl;
}

void CCanvas::MoveTo(double x, double y)
{
	m_ostream << "MoveTo ( " << x << ", " << y << " )" << std::endl;
}

void CCanvas::LineTo(double x, double y)
{
	m_ostream  << "LineTo ( " << x << ", " << y << " )" << std::endl;
}

void CCanvas::DrawEllipse(double left, double top, double width, double height)
{
	m_ostream << "Draw ellipse center [" << left << ", " << top << "], Width: " << width << " height: " << height << std::endl;
}

void CCanvas::SetOutlineThickness(double thickness)
{
	m_ostream << "Outline Thickness ( " << thickness << " )" << std::endl;
}