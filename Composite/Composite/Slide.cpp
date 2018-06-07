#include "stdafx.h"
#include "Slide.h"


CSlide::CSlide(double width, double height)
	: m_width(width)
	, m_height(height)
{

}

double CSlide::GetWidth()const
{
	return m_width;
}

double CSlide::GetHeight()const
{
	return m_height;
}

void CSlide::AddShape(std::shared_ptr<IShape> const& shape)
{
	m_shapes.push_back(shape);
}

void CSlide::Draw(ICanvas& canvas)
{
	for (auto const& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}