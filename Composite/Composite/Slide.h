#pragma once
#include "ISlide.h"

class CSlide : public ISlide
{
public:
	CSlide(double width, double height);
	double GetWidth()const;
	double GetHeight()const;

	std::vector<std::shared_ptr<IShape>> & GetShapes();
	void AddShape(std::shared_ptr<IShape> const& shape);
	void Draw(ICanvas& canvas);

private:
	double m_width;
	double m_height;
	std::vector<std::shared_ptr<IShape>> m_shapes;
};

