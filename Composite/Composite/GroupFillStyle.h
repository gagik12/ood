#pragma once
#include "IStyle.h"

typedef std::function<void(std::function<void(IStyle&)>)> FillStyleEnumerator;

class CGroupFillStyle : public IStyle
{
public:
	CGroupFillStyle(FillStyleEnumerator & enumerator);
	optional<bool> IsEnabled()const;
	void Enable(bool enable);

	optional<RGBColor> GetColor()const;
	void SetColor(RGBColor color);
private:
	FillStyleEnumerator & m_enumerator;
};

