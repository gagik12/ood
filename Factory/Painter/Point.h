#pragma once
class CPoint
{
public:
	CPoint();
	CPoint(float x, float y);
	float GetX() const;
	float GetY() const;

	friend std::istream & operator>>(std::istream & stream, CPoint & point);
	friend std::ostream & operator<<(std::ostream& stream, CPoint const& point);
private:
	float m_x;
	float m_y;
};

