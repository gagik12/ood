#include "stdafx.h"
#include "GroupShape.h"


CGroupShape::CGroupShape()
{
}

RectD CGroupShape::GetFrame()
{
	if (m_shapes.size() == 0)
	{

	}

	for (auto const& shape : m_shapes)
	{
	}
	return RectD();
}

void CGroupShape::SetFrame(const RectD & rect)
{

}

IOutlineStyle & CGroupShape::GetOutlineStyle()
{
	return *m_outlineStyle;
}

const IOutlineStyle & CGroupShape::GetOutlineStyle()const
{
	return *m_outlineStyle;
}

IStyle & CGroupShape::GetFillStyle()
{
	return *m_fillStyle;
}

const IStyle & CGroupShape::GetFillStyle()const
{
	return *m_fillStyle;
}

std::shared_ptr<IGroupShape> CGroupShape::GetGroup()
{
	return std::make_shared<CGroupShape>();
}

std::shared_ptr<const IGroupShape> CGroupShape::GetGroup() const
{
	return std::make_shared<CGroupShape>();
}

size_t CGroupShape::GetShapesCount()const
{
	return 0;
}

void CGroupShape::InsertShape(const std::shared_ptr<IShape> & shape, size_t position)
{
	if (position >= m_shapes.size())
	{
		m_shapes.push_back(shape);
	}
	else
	{
		m_shapes.insert(m_shapes.begin() + position, shape);
	}
}

std::shared_ptr<IShape> CGroupShape::GetShapeAtIndex(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index out of range");
	}
	return m_shapes[index];
}

void CGroupShape::RemoveShapeAtIndex(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index out of range");
	}

	m_shapes.erase(m_shapes.begin() + index);
}

void CGroupShape::Draw(ICanvas & canvas)
{
	for (auto const& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

void CGroupShape::SetOutlineStyle(std::shared_ptr<IOutlineStyle> const& outlineStyle)
{
	for (auto & shape : m_shapes)
	{
		shape->SetOutlineStyle(outlineStyle);
	}
}

void CGroupShape::SetFillStyle(std::shared_ptr<IStyle> const& fillStyle)
{
	for (auto & shape : m_shapes)
	{
		shape->SetFillStyle(fillStyle);
	}
}