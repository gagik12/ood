#include "stdafx.h"
#include "Shape.h"
#include "FillStyle.h"
#include "OutlineStyle.h"

CShape::CShape()
	: m_fillStyle(std::make_shared<CFillStyle>(true, RGBColor{255, 0, 0}))
	, m_outlineStyle(std::make_shared<COutlineStyle>(true, RGBColor{255, 255, 22}, 2.f))
{
}

std::shared_ptr<IOutlineStyle> CShape::GetOutlineStyle()
{
	return m_outlineStyle;
}

std::shared_ptr<const IOutlineStyle> CShape::GetOutlineStyle() const
{
	return m_outlineStyle;
}

std::shared_ptr<IStyle> CShape::GetFillStyle()
{
	return m_fillStyle;
}

std::shared_ptr<const IStyle> CShape::GetFillStyle() const
{
	return m_fillStyle;
}

std::shared_ptr<IGroupShape> CShape::GetGroup()
{
	return nullptr;
}

std::shared_ptr<const IGroupShape> CShape::GetGroup() const
{
	return nullptr;
}

void CShape::Draw(ICanvas & canvas) const
{
	canvas.SetOutlineThickness(m_outlineStyle->IsEnabled() ? m_outlineStyle->GetOutlineThikness().get() : 0);
	canvas.SetLineColor(m_outlineStyle->IsEnabled() ? m_outlineStyle->GetColor().get() : RGBColor{ 0, 0, 0 });
	canvas.SetFillColor(m_fillStyle->IsEnabled() ? m_fillStyle->GetColor().get() : RGBColor{0, 0, 0});

	DrawBehavior(canvas);
}