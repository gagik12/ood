#include "stdafx.h"
#include "FillStyle.h"


CFillStyle::CFillStyle(bool enabled, RGBAColor color)
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

optional<RGBAColor> CFillStyle::GetColor()const
{
	return m_color;
}

void CFillStyle::SetColor(RGBAColor color)
{
	m_color = color;
}