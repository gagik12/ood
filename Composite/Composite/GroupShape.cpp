#include "stdafx.h"
#include "GroupShape.h"

CGroupShape::CGroupShape()
{
	/*auto groupFillStyleEnumerator = [this](std::function<void(std::shared_ptr<IStyle>&)> fun) {
		for (auto && shape : m_shapes)
		{
			//fun(shape->GetFillStyle());
		}
	};
	groupFillStyleEnumerator([&](std::shared_ptr<IStyle>& style) {
	});*/
	FillStyleEnumerator fillStyleEnumerator = [this](std::function<void(std::shared_ptr<IStyle>&)> fun) {
		for (auto && shape : m_shapes)
		{
			fun(shape->GetFillStyle());
		}
	};
	m_groupFillStyle = std::make_shared<CGroupFillStyle>(fillStyleEnumerator);

	OutlineStyleEnumerator outlineStyleEnumerator = [this](std::function<void(std::shared_ptr<IOutlineStyle>&)> fun) {
		for (auto && shape : m_shapes)
		{
			fun(shape->GetOutlineStyle());
		}
	};
	m_groupOutlineStyle = std::make_shared<CGroupOutlineStyle>(outlineStyleEnumerator);

}

RectD CGroupShape::GetFrame()
{
	if (m_shapes.empty())
	{
		throw std::runtime_error("Coollection empty");
	}

	auto firstFrame = m_shapes.front()->GetFrame();
	double minX = firstFrame.left;
	double minY = firstFrame.top;
	double maxX = firstFrame.left + firstFrame.width;
	double maxY = firstFrame.top + firstFrame.height;

	for (size_t i = 1; i < GetShapesCount(); ++i)
	{
		auto frame = m_shapes[i]->GetFrame();
		minX = std::min(minX, frame.left);
		minY = std::min(minX, frame.top);

		maxX = std::min(maxX, frame.left + frame.width);
		maxY = std::min(maxY, frame.top + frame.height);
	}
	return RectD{ minX, minY, maxX - minX, maxY - minY };
}

void CGroupShape::SetFrame(const RectD & rect)
{
	auto currentFrame = GetFrame();
	double frameScaleX = rect.width / currentFrame.width;
	double frameScaleY = rect.height / currentFrame.height;
	for (auto & shape : m_shapes)
	{
		auto shapeFrame = shape->GetFrame();
		double shapeOffsetX = shapeFrame.left - rect.left;
		double shapeOffsetY = shapeFrame.height - rect.height;
		shape->SetFrame({
			rect.left + shapeOffsetX * frameScaleX,
			rect.top + shapeOffsetY * frameScaleY,
			rect.width * frameScaleX,
			rect.height * frameScaleY
		});
	}
}


std::shared_ptr<IOutlineStyle> CGroupShape::GetOutlineStyle()const
{
	return m_groupOutlineStyle;
}

std::shared_ptr<IStyle> CGroupShape::GetFillStyle()const
{
	return m_groupFillStyle;
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