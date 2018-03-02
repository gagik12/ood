#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}

	void SetDescription(std::string const& description) override final
	{
		m_description = description;
	}
private:
	std::string m_description;
};

enum class CoffeePortion
{
	STANDARTD,
	DOUBLE,
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(CoffeePortion coffeePortion = CoffeePortion::STANDARTD, const std::string& description = "Coffee")
		: CBeverage(GetCoffeePortionDescription() + " " + description)
		, m_coffeePortion(coffeePortion)
	{}

	CoffeePortion GetCoffeePortion() const
	{
		return m_coffeePortion;
	}

	double GetCost() const override
	{
		return 60;
	}
private:
	CoffeePortion m_coffeePortion;

	std::string GetCoffeePortionDescription()const
	{
		std::string result;
		switch (m_coffeePortion)
		{
		case CoffeePortion::STANDARTD:
			result = "Standartd";
			break;
		case CoffeePortion::DOUBLE:
			result = "Double";
			break;
		default:
			break;
		}
		return result;
	}
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino(CoffeePortion coffeePortion = CoffeePortion::STANDARTD)
		: CCoffee(coffeePortion, "Capuccino")
	{}

	double GetCost() const override 
	{
		return (GetCoffeePortion() == CoffeePortion::STANDARTD) ? 80 : 120;
	}
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(CoffeePortion coffeePortion = CoffeePortion::STANDARTD)
		: CCoffee(coffeePortion, "Latte")
	{}

	double GetCost() const override 
	{
		return (GetCoffeePortion() == CoffeePortion::STANDARTD) ? 90 : 130;
	}
};

enum class TeaGrade
{
	GREEN,
	BLACK,
	JASMINE,
	WHITE
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(TeaGrade teaGrade = TeaGrade::BLACK)
		: CBeverage("Tea")
	{
		SetDescription(GetTeaGradeDescription() + " " + GetDescription());
	}

	double GetCost() const override 
	{
		return 30; 
	}
private:
	TeaGrade m_teaGrade;

	std::string GetTeaGradeDescription()const
	{
		std::string result;
		switch (m_teaGrade)
		{
		case TeaGrade::GREEN:
			result = "Green";
			break;
		case TeaGrade::BLACK:
			result = "Black";
			break;
		case TeaGrade::JASMINE:
			result = "Jasmine";
			break;
		case TeaGrade::WHITE:
			result = "White";
			break;
		default:
			break;
		}
		return result;
	}
};

enum class MilkshakePortion
{
	SMALL,
	MIDDLE,
	BIG
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakePortion milkshakePortion = MilkshakePortion::SMALL)
		: CBeverage("Milkshake")
		, m_milkshakePortion(milkshakePortion)
	{
		SetDescription(GetMilkshakePortionDescription() + " " + GetDescription());
	}

	double GetCost() const override 
	{ 
		static const int COSTS[] = { 50, 60, 80 };
		return COSTS[static_cast<int>(m_milkshakePortion)];
	}
private:
	MilkshakePortion m_milkshakePortion;

	std::string GetMilkshakePortionDescription()const
	{
		std::string result;
		switch (m_milkshakePortion)
		{
		case MilkshakePortion::SMALL:
			result = "Small";
			break;
		case MilkshakePortion::MIDDLE:
			result = "Middle";
			break;
		case MilkshakePortion::BIG:
			result = "Big";
			break;
		default:
			break;
		}
		return result;
	}
};
