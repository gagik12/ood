#include "stdafx.h"
#include "GroupShape.h"


CGroupShape::CGroupShape()
{
}

RectD CGroupShape::GetFrame()
{
	if (m_shapes.empty())
	{
		throw std::runtime_error("Coollection empty");
	}

	auto fisrtFrame = m_shapes.front()->GetFrame();
	double minX = fisrtFrame.left;
	double minY = fisrtFrame.top;
	double maxX = fisrtFrame.left + fisrtFrame.width;
	double maxY = fisrtFrame.top + fisrtFrame.height;

	for (size_t i = 1; i < GetShapesCount(); ++i)
	{
		auto frame = m_shapes[i]->GetFrame();
		if (minX > frame.left)
		{
			minX = frame.left;
		}

		if (minY > frame.top)
		{
			minY = frame.top;
		}

		if (maxX < frame.left + frame.width)
		{
			maxX = frame.left + frame.width;
		}

		if (maxY < frame.top + frame.height)
		{
			maxY = frame.top + frame.height;
		}
	}
	return RectD{ minX, minY, maxX - minX, maxY - minY };
}

void CGroupShape::SetFrame(const RectD & rect)
{

}

std::shared_ptr<IOutlineStyle> CGroupShape::GetOutlineStyle()const
{
	if (m_shapes.empty())
	{
		throw std::runtime_error("Coollection empty");
	}

	bool stylesEqual = std::all_of(m_shapes.begin(), m_shapes.end(), [&](auto & shape) {
		return (shape->GetFillStyle() == m_shapes.front()->GetFillStyle());
	});
	return stylesEqual ? m_shapes.front()->GetOutlineStyle() : nullptr;
}

std::shared_ptr<IStyle> CGroupShape::GetFillStyle()const
{
	bool stylesEqual = std::all_of(m_shapes.begin(), m_shapes.end(), [&](auto & shape) {
		return (shape->GetFillStyle() == m_shapes.front()->GetFillStyle());
	});
	return stylesEqual ? m_shapes.front()->GetFillStyle() : nullptr;
}

std::shared_ptr<IGroupShape> CGroupShape::GetGroup()
{
	return shared_from_this();
}

std::shared_ptr<const IGroupShape> CGroupShape::GetGroup() const
{
	return shared_from_this();
}

size_t CGroupShape::GetShapesCount()const
{
	return m_shapes.size();
}

void CGroupShape::InsertShape(const std::shared_ptr<IShape> & shape, size_t position)
{
	if (position >= GetShapesCount())
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
	if (index >= GetShapesCount())
	{
		throw std::out_of_range("Index out of range");
	}
	return m_shapes[index];
}

void CGroupShape::RemoveShapeAtIndex(size_t index)
{
	if (index >= GetShapesCount())
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