#pragma once
class CFloat
{
public:
	CFloat();
	float GetValue();

	friend std::istream & operator >> (std::istream & stream, CFloat & fl);
	friend std::ostream & operator<<(std::ostream& stream, CFloat const& fl);
private:
	float m_value = 0;
};

