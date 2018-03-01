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
private:
	std::string m_description;
};

enum CoffeePortion
{
	STANDART,
	DOUBLE,
};

const std::map<CoffeePortion, std::string> COFFEE_PORTION_DESCRIPTION = {
	{ CoffeePortion::STANDART, "Standart " },
	{ CoffeePortion::DOUBLE, "Double " },
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description) 
	{}

	double GetCost() const override 
	{
		return 60; 
	}
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino(CoffeePortion coffeePortion = CoffeePortion::STANDART)
		: CCoffee(COFFEE_PORTION_DESCRIPTION.at(coffeePortion) + "Capuccino")
		, m_capuccinoPortion(coffeePortion)
	{}

	double GetCost() const override 
	{
		return (m_capuccinoPortion == CoffeePortion::STANDART) ? 80 : 120;
	}
private:
	CoffeePortion m_capuccinoPortion;
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(CoffeePortion coffeePortion = CoffeePortion::STANDART)
		: CCoffee(COFFEE_PORTION_DESCRIPTION.at(coffeePortion) + "Latte")
		, m_lattePortion(coffeePortion)
	{}

	double GetCost() const override 
	{
		return (m_lattePortion == CoffeePortion::STANDART) ? 90 : 130;
	}
private:
	CoffeePortion m_lattePortion;
};

enum TeaGrade
{
	GREEN,
	BLACK,
	JASMINE,
	WHITE
};

const std::map<TeaGrade, std::string> TEA_GRADE_DESCRIPTION = {
	{ TeaGrade::GREEN, "Green " },
	{ TeaGrade::BLACK, "Black " },
	{ TeaGrade::JASMINE, "Jasmine " },
	{ TeaGrade::WHITE, "White " },
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(TeaGrade teaGrade = TeaGrade::BLACK)
		: CBeverage(TEA_GRADE_DESCRIPTION.at(teaGrade) + "Tea")
		, m_teaGrade(teaGrade)
	{}

	double GetCost() const override 
	{
		return 30; 
	}
private:
	TeaGrade m_teaGrade;
};

enum MilkshakePortion
{
	SMALL,
	MIDDLE,
	BIG
};

const std::map<MilkshakePortion, std::string> MILKSHAKE_PORTION_DESCRIPTION = {
	{ MilkshakePortion::SMALL, "Small " },
	{ MilkshakePortion::MIDDLE, "Middle " },
	{ MilkshakePortion::BIG, "Big " },
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakePortion milkshakePortion = MilkshakePortion::SMALL)
		: CBeverage(MILKSHAKE_PORTION_DESCRIPTION.at(milkshakePortion) + "Milkshake")
		, m_milkshakePortion(milkshakePortion)
	{}

	double GetCost() const override 
	{ 
		static const std::vector<int> COSTS = { 50, 60, 80 };
		return COSTS[m_milkshakePortion];
	}
private:
	MilkshakePortion m_milkshakePortion;
};
