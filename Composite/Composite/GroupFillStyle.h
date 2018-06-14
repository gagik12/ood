#pragma once
#include "IStyle.h"

typedef std::function<void(std::function<void(IStyle&)>)> FillStyleEnumerator;

class CGroupFillStyle : public IStyle
{
public:
	CGroupFillStyle(FillStyleEnumerator & enumerator);
	optional<bool> IsEnabled()const override;
	void Enable(bool enable) override;

	optional<RGBColor> GetColor()const override;
	void SetColor(RGBColor color) override;
private:
	FillStyleEnumerator & m_enumerator;
};

