#include "stdafx.h"
#include "WeatherData.h"

int main()
{
	CWeatherData inWd("in");
	CWeatherData outWd("out");

	CStatsDisplay statsDisplay;
	outWd.RegisterObserver(statsDisplay, 2);
	inWd.RegisterObserver(statsDisplay, 4);

	inWd.SetMeasurements(3, 0.7, 760);
	inWd.SetMeasurements(8, 0.2, 765);
	outWd.SetMeasurements(4, 0.8, 761);

	return 0;
}