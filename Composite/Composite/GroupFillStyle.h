#pragma once
#include "IStyle.h"

typedef std::function<void(std::function<void(std::shared_ptr<IStyle>&)>)> FillStyleEnumerator;

class CGroupFillStyle : public IStyle
{
public:
	CGroupFillStyle(FillStyleEnumerator & enumerator);
	optional<bool> IsEnabled()const;
	void Enable(bool enable);

	optional<RGBAColor> GetColor()const;
	void SetColor(RGBAColor color);
private:
	FillStyleEnumerator & m_enumerator;
};

