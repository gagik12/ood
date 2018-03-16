#pragma once
#include "Observer.h"

using namespace std;


struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double windSpeed = 0;
	double windDirection = 0;
};

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class IStatisticsCalculator
{
public:
	virtual void Update(double value) = 0;
	virtual void Print()const = 0;
	virtual ~IStatisticsCalculator() = default;
};

class CStatisticsCalculator : public IStatisticsCalculator
{
public:
	CStatisticsCalculator(std::string const& statisticName)
		: m_statisticName(statisticName)
	{
	}

	void Update(double value)override
	{
		if (m_minValue > value)
		{
			m_minValue = value;
		}
		if (m_maxValue < value)
		{
			m_maxValue = value;
		}
		m_accValue += value;
		++m_countAcc;
	}

	void Print()const override
	{
		std::cout << "Max " << m_statisticName << " " << m_maxValue << std::endl;
		std::cout << "Min " << m_statisticName << " " << m_minValue << std::endl;
		std::cout << "Average " << m_statisticName << " " << (m_accValue / m_countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	}
private:
	std::string m_statisticName;
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0;
	unsigned m_countAcc = 0;
};

class CWindStatisticsCalculator : public IStatisticsCalculator
{
public:
	CWindStatisticsCalculator(std::string const& statisticName)
		: m_statisticName(statisticName)
	{
	}

	void Update(double value)override
	{
		if (m_minValue > value)
		{
			m_minValue = value;
		}
		if (m_maxValue < value)
		{
			m_maxValue = value;
		}

		double radians = ConvertDegreesToRadians(value);
		m_x += cos(radians);
		m_y += sin(radians);
		double degrees = ConvertRadiansToDegrees(atan2(m_y, m_x));
		m_average = (degrees >= 0.0) ? degrees : 360 + degrees;
	}

	void Print()const override
	{
		std::cout << "Max " << m_statisticName << " " << m_maxValue << std::endl;
		std::cout << "Min " << m_statisticName << " " << m_minValue << std::endl;
		std::cout << "Average " << m_statisticName << " " << m_average << std::endl;
		std::cout << "----------------" << std::endl;
	}
private:
	std::string m_statisticName;
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_x = 0;
	double m_y = 0;
	double m_average = 0;

	static double ConvertDegreesToRadians(double degrees)
	{
		return degrees * M_PI / 180.0;
	}

	static double ConvertRadiansToDegrees(double radians)
	{
		return radians * 180.0 / M_PI;
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay()
		: m_temperatureStatistics(CStatisticsCalculator("Temperature"))
		, m_humidityStatistics(CStatisticsCalculator("Humidity"))
		, m_pressureStatistics(CStatisticsCalculator("Pressure"))
		, m_windSpeedStatistics(CStatisticsCalculator("Wind Speed"))
		, m_windStatistics(CWindStatisticsCalculator("Wind Direction"))
	{
	}

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		UpdateWeatherStatistics(data);
		PrintWeatherStatistics();
	}

	void UpdateWeatherStatistics(SWeatherInfo const& data)
	{
		//m_temperatureStatistics.Update(data.temperature);
		//m_humidityStatistics.Update(data.humidity);
		//m_pressureStatistics.Update(data.pressure);
		m_windSpeedStatistics.Update(data.windSpeed);
		m_windStatistics.Update(data.windDirection);
	}

	void PrintWeatherStatistics() const
	{
		//m_temperatureStatistics.Print();
		//m_humidityStatistics.Print();
		//m_pressureStatistics.Print();
		m_windSpeedStatistics.Print();
		m_windStatistics.Print();
	}

	CStatisticsCalculator m_temperatureStatistics;
	CStatisticsCalculator m_humidityStatistics;
	CStatisticsCalculator m_pressureStatistics;
	CStatisticsCalculator m_windSpeedStatistics;
	CWindStatisticsCalculator m_windStatistics;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	double GetWindSpeed()const
	{
		return m_windSpeed;
	}

	double GetWindDirection()const
	{
		return m_windDirection;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windSpeed = windSpeed;
		m_windDirection = windDirection;
		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.windSpeed = GetWindSpeed();
		info.windDirection = GetWindDirection();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windSpeed = 0;
	double m_windDirection = 0;
};