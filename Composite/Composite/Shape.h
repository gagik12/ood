#pragma once
#include "IShape.h"
#include "IOutlineStyle.h"

class CShape : public IShape
{
public:
	CShape();

	void SetOutlineStyle(std::shared_ptr<IOutlineStyle> const& outlineStyle) override;
	IOutlineStyle & GetOutlineStyle() override;
	const IOutlineStyle & GetOutlineStyle()const override;

	void SetFillStyle(std::shared_ptr<IStyle> const& fillStyle) override;
	IStyle & GetFillStyle() override;
	const IStyle & GetFillStyle()const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	void Draw(ICanvas & canvas) override;
protected:
	virtual void DrawBehavior(ICanvas & canvas)const = 0;
private:
	std::shared_ptr<IStyle> m_fillStyle;
	std::shared_ptr<IOutlineStyle> m_outlineStyle;
};

