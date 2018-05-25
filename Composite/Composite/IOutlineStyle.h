#pragma once
#include "IStyle.h"

class IOutlineStyle : public IStyle
{
public:
	virtual float GetOutlineThikness() const = 0;
	virtual void SetOutlineThikness(float thikness) = 0;
};