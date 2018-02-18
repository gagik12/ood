#pragma once
#include "Observer.h"

using namespace std;

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
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

class CWeatherStatistic
{
public:
	CWeatherStatistic(std::string weatherStatisticName)
		: m_weatherStatisticName(weatherStatisticName)
	{
	}

	void Update(double value)
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

	void Print() const
	{
		std::cout << "Max " << m_weatherStatisticName << " " << m_maxValue << std::endl;
		std::cout << "Min " << m_weatherStatisticName << " " << m_minValue << std::endl;
		std::cout << "Average " << m_weatherStatisticName << " " << (m_accValue / m_countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	}
private:
	std::string m_weatherStatisticName;
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0;
	unsigned m_countAcc = 0;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay()
		: m_temperatureStatistic(CWeatherStatistic("Temperature"))
		, m_humidityStatistic(CWeatherStatistic("Humidity"))
		, m_pressureStatistic(CWeatherStatistic("Pressure"))
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
		m_temperatureStatistic.Update(data.temperature);
		m_humidityStatistic.Update(data.humidity);
		m_pressureStatistic.Update(data.pressure);
	}

	void PrintWeatherStatistics() const
	{
		m_temperatureStatistic.Print();
		m_humidityStatistic.Print();
		m_pressureStatistic.Print();
	}

	CWeatherStatistic m_temperatureStatistic;
	CWeatherStatistic m_humidityStatistic;
	CWeatherStatistic m_pressureStatistic;
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

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};