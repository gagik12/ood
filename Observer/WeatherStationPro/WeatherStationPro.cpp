#include "stdafx.h"
#include "WeatherData.h"

int main()
{
	CWeatherData wd;

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, 2);

	wd.SetMeasurements(3, 0.7, 760, 10, 180);
	wd.SetMeasurements(4, 0.8, 761, 10, 360);

	return 0;
}