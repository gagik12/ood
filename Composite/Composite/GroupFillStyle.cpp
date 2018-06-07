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

optional<RGBAColor> CGroupFillStyle::GetColor()const
{
	optional<RGBAColor> color;

	auto callback = [&](IStyle& style) {
		if (!color.is_initialized())
		{
			color = style.IsEnabled();
		}
		else if (color != style.GetColor())
		{
			color = boost::none;
		}
	};

	m_enumerator(callback);

	return color;
}

void CGroupFillStyle::SetColor(RGBAColor color)
{
	m_enumerator([&](IStyle& style) {
		style.SetColor(color);
	});
}