#include "stdafx.h"
#include "FillStyle.h"


CFillStyle::CFillStyle(bool enabled, RGBColor color)
	: m_enabled(enabled)
	, m_color(color)
{
}

optional<bool> CFillStyle::IsEnabled()const
{
	return m_enabled;
}

void CFillStyle::Enable(bool enable)
{
	m_enabled = enable;
}

optional<RGBColor> CFillStyle::GetColor()const
{
	return m_color;
}

void CFillStyle::SetColor(RGBColor color)
{
	m_color = color;
}