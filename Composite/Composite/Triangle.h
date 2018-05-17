#pragma once
#include "IShape.h"

class CTriangle : public IShape
{
public:
	CTriangle();
	RectD GetFrame() = 0;
	virtual void SetFrame(const RectD & rect) = 0;

	virtual IStyle & GetOutlineStyle() = 0;
	virtual const IStyle & GetOutlineStyle()const = 0;

	virtual IStyle & GetFillStyle() = 0;
	virtual const IStyle & GetFillStyle()const = 0;

	virtual std::shared_ptr<IGroupShape> GetGroup() = 0;
	virtual std::shared_ptr<const IGroupShape> GetGroup() const = 0;
};

