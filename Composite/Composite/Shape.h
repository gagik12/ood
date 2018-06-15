#pragma once
#include "IShape.h"
#include "IOutlineStyle.h"

class CShape : public IShape
{
public:
	CShape();

	std::shared_ptr<IOutlineStyle> GetOutlineStyle() override;
	std::shared_ptr<const IOutlineStyle> GetOutlineStyle() const override;

	std::shared_ptr<IStyle> GetFillStyle() override;
	std::shared_ptr<const IStyle> GetFillStyle()const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	void Draw(ICanvas & canvas) const override;
protected:
	virtual void DrawBehavior(ICanvas & canvas)const = 0;
private:
	std::shared_ptr<IStyle> m_fillStyle;
	std::shared_ptr<IOutlineStyle> m_outlineStyle;
};

