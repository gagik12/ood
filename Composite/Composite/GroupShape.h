#pragma once
#include "IGroupShape.h"
#include "IOutlineStyle.h"

class CGroupShape : public IGroupShape
{
public:
	CGroupShape();

	RectD GetFrame() override;
	void SetFrame(const RectD & rect) override;

	IOutlineStyle & GetOutlineStyle() override;
	const IOutlineStyle & GetOutlineStyle()const override;

	IStyle & GetFillStyle() override;
	const IStyle & GetFillStyle()const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	size_t GetShapesCount()const override;
	void InsertShape(const std::shared_ptr<IShape> & shape, size_t position = std::numeric_limits<size_t>::max()) override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override;
	void RemoveShapeAtIndex(size_t index) override;
	void Draw(ICanvas & canvas) override;
	void SetOutlineStyle(std::shared_ptr<IOutlineStyle> const& outlineStyle) override;
	void SetFillStyle(std::shared_ptr<IStyle> const& fillStyle) override;
private:
	std::shared_ptr<IStyle> m_fillStyle;
	std::shared_ptr<IOutlineStyle> m_outlineStyle;
	std::vector<std::shared_ptr<IShape>> m_shapes;
};

