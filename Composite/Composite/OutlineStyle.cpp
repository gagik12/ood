#include "stdafx.h"
#include "OutlineStyle.h"


COutlineStyle::COutlineStyle(bool enabled, RGBAColor color, float thickness)
	: m_enabled(enabled)
	, m_color(color)
	, m_thickness(thickness)
{
}

optional<bool> COutlineStyle::IsEnabled()const
{
	return m_enabled;
}

void COutlineStyle::Enable(bool enable)
{
	m_enabled = enable;
}

optional<RGBAColor> COutlineStyle::GetColor()const
{
	return m_color;
}

void COutlineStyle::SetColor(RGBAColor color)
{
	m_color = color;
}

optional<float> COutlineStyle::GetOutlineThikness() const
{
	return m_thickness;
}

void COutlineStyle::SetOutlineThikness(float thikness)
{
	m_thickness = thikness;
}