#pragma once
#include "IGroupShape.h"
#include "IOutlineStyle.h"
#include "GroupFillStyle.h"
#include "GroupOutlineStyle.h"

class CGroupShape : public IGroupShape, std::enable_shared_from_this<CGroupShape>
{
public:
	CGroupShape();

	RectD GetFrame() override;
	void SetFrame(const RectD & rect) override;

	std::shared_ptr<IOutlineStyle> GetOutlineStyle() override;
	std::shared_ptr<const IOutlineStyle> GetOutlineStyle() const override;

	std::shared_ptr<IStyle> GetFillStyle() override;
	std::shared_ptr<const IStyle> GetFillStyle()const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	size_t GetShapesCount()const override;
	void InsertShape(const std::shared_ptr<IShape> & shape, size_t position = std::numeric_limits<size_t>::max()) override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override;
	void RemoveShapeAtIndex(size_t index) override;
	void Draw(ICanvas & canvas) override;
private:
	std::vector<std::shared_ptr<IShape>> m_shapes;

	std::shared_ptr<IStyle> m_groupFillStyle;
	std::shared_ptr<IOutlineStyle> m_groupOutlineStyle;
};

