#include "stdafx.h"
#include "GroupFillStyle.h"


CGroupFillStyle::CGroupFillStyle(FillStyleEnumerator & enumerator)
	: m_enumerator(enumerator)
{
}

optional<bool> CGroupFillStyle::IsEnabled()const
{
	optional<bool> isEnabled;

	auto callback = [&](IStyle& style) {
		if (!isEnabled.is_initialized())
		{
			isEnabled = style.IsEnabled();
		}
		else if (isEnabled != style.IsEnabled())
		{
			isEnabled = boost::none;
		}
	};

	m_enumerator(callback);

	return isEnabled;
}

void CGroupFillStyle::Enable(bool enable)
{
	m_enumerator([&](IStyle& style) {
		style.Enable(enable);
	});
}

optional<RGBColor> CGroupFillStyle::GetColor()const
{
	optional<RGBColor> color = RGBColor{0, 0, 0};

	auto callback = [&](IStyle& style) {
		if (!color.is_initialized())
		{
			color = style.GetColor();
		}
	};

	m_enumerator(callback);

	return color;
}

void CGroupFillStyle::SetColor(RGBColor color)
{
	m_enumerator([&](IStyle& style) {
		style.SetColor(color);
	});
}