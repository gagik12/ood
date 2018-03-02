#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>

// Интерфейс "напиток"
class IBeverage
{
public:
	virtual std::string GetDescription() const = 0;
	virtual void SetDescription(std::string const& description) = 0;
	virtual double GetCost()const = 0;
	virtual ~IBeverage() = default;
};

typedef std::unique_ptr<IBeverage> IBeveragePtr;
