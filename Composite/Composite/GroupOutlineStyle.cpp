#include "stdafx.h"
#include "GroupOutlineStyle.h"


CGroupOutlineStyle::CGroupOutlineStyle(OutlineStyleEnumerator & enumerator)
	: m_enumerator(enumerator)
{
}

optional<bool> CGroupOutlineStyle::IsEnabled()const
{
	optional<bool> isEnabled;

	auto callback = [&](IOutlineStyle& style) {
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

void CGroupOutlineStyle::Enable(bool enable)
{
	m_enumerator([&](IOutlineStyle& style) {
		style.Enable(enable);
	});
}

optional<RGBAColor> CGroupOutlineStyle::GetColor()const
{
	optional<RGBAColor> color;

	auto callback = [&](IOutlineStyle& style) {
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

void CGroupOutlineStyle::SetColor(RGBAColor color)
{
	m_enumerator([&](IOutlineStyle& style) {
		style.SetColor(color);
	});
}

optional<float> CGroupOutlineStyle::GetOutlineThikness() const
{
	optional<float> outlineThikness;

	auto callback = [&](IOutlineStyle& style) {
		if (!outlineThikness.is_initialized())
		{
			outlineThikness = style.IsEnabled();
		}
		else if (outlineThikness != style.GetOutlineThikness())
		{
			outlineThikness = boost::none;
		}
	};

	m_enumerator(callback);

	return outlineThikness;
}

void CGroupOutlineStyle::SetOutlineThikness(float thikness)
{
	m_enumerator([&](IOutlineStyle& style) {
		style.SetOutlineThikness(thikness);
	});
}