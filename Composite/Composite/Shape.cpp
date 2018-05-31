#include "stdafx.h"
#include "Shape.h"
#include "FillStyle.h"
#include "OutlineStyle.h"

CShape::CShape()
	: m_fillStyle(std::make_shared<CFillStyle>(true, 255))
	, m_outlineStyle(std::make_shared<COutlineStyle>(true, 255, 10.f))
{
}

void CShape::SetOutlineStyle(std::shared_ptr<IOutlineStyle> const& outlineStyle)
{
	m_outlineStyle = outlineStyle;
}

std::shared_ptr<IOutlineStyle> CShape::GetOutlineStyle()const
{
	return m_outlineStyle;
}

void CShape::SetFillStyle(std::shared_ptr<IStyle> const& fillStyle)
{
	m_fillStyle = fillStyle;
}

std::shared_ptr<IStyle> CShape::GetFillStyle()const
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

void CShape::Draw(ICanvas & canvas)
{
	if (m_outlineStyle->IsEnabled())
	{
		canvas.SetOutlineThickness(m_outlineStyle->GetOutlineThikness().get());
		canvas.SetLineColor(m_outlineStyle->GetColor().get());
	}

	if (m_fillStyle->IsEnabled())
	{
		canvas.BeginFill(m_fillStyle->GetColor().get());
	}

	DrawBehavior(canvas);

	if (m_fillStyle->IsEnabled())
	{
		canvas.EndFill();
	}
}