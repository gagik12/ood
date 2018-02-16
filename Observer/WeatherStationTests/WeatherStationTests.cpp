#include "stdafx.h"
#include "../WeatherStation/Observer.h"
#include "../WeatherStation/WeatherData.h"

using namespace std;

namespace TestObserverPriority
{
	class CTestDisplay : public IObserver<SWeatherInfo>
	{
	public:
		CTestDisplay(boost::test_tools::output_test_stream & stream)
			: m_stream(stream)
		{}
	private:
		void Update(SWeatherInfo const& data) override
		{
			m_stream << "CTestDisplay\n";
		}
		boost::test_tools::output_test_stream & m_stream;
	};

	class CTestStatsDisplay : public IObserver<SWeatherInfo>
	{
	public:
		CTestStatsDisplay(boost::test_tools::output_test_stream & stream)
			: m_stream(stream)
		{}
	private:
		void Update(SWeatherInfo const& data) override
		{
			m_stream << "CTestStatsDisplay\n";
		}
		boost::test_tools::output_test_stream & m_stream;
	};
}

BOOST_AUTO_TEST_SUITE(task_3)
	BOOST_AUTO_TEST_CASE(can_set_the_priority)
	{
		boost::test_tools::output_test_stream stream;
		
		CWeatherData wd;

		TestObserverPriority::CTestDisplay testDisplay(stream);
		TestObserverPriority::CTestStatsDisplay testStatsDisplay(stream);

		wd.RegisterObserver(testDisplay, 100);
		wd.RegisterObserver(testStatsDisplay, 10);
		wd.SetMeasurements(3, 0.7, 760);
		BOOST_CHECK(stream.is_equal("CTestDisplay\nCTestStatsDisplay\n"));

		stream.clear();
		wd.RemoveObserver(testDisplay);
		wd.RemoveObserver(testStatsDisplay);

		wd.RegisterObserver(testDisplay, 10);
		wd.RegisterObserver(testStatsDisplay, 100);
		wd.SetMeasurements(3, 0.7, 760);
		BOOST_CHECK(stream.is_equal("CTestStatsDisplay\nCTestDisplay\n"));
	}
BOOST_AUTO_TEST_SUITE_END()

namespace TestSafeNotificationObservers
{
	class CTestDisplay : public IObserver<SWeatherInfo>
	{
	public:
		CTestDisplay(boost::test_tools::output_test_stream & stream, CObservable<SWeatherInfo> & Observable)
			: m_stream(stream)
			, m_Observable(Observable)
		{}
	private:
		void Update(SWeatherInfo const& data) override
		{
			//отписаться от уведомлений
			m_Observable.RemoveObserver(*this);
			m_stream << "Removed CTestDisplay\n";
		}

		boost::test_tools::output_test_stream & m_stream;
		CObservable<SWeatherInfo> & m_Observable;
	};

	class CTestStatsDisplay : public IObserver<SWeatherInfo>
	{
	public:
		CTestStatsDisplay(boost::test_tools::output_test_stream & stream, CObservable<SWeatherInfo> & Observable)
			: m_stream(stream)
			, m_Observable(Observable)
		{}
	private:
		void Update(SWeatherInfo const& data) override
		{
			//отписаться от уведомлений
			m_Observable.RemoveObserver(*this);
			m_stream << "Removed CTestStatsDisplay\n";
		}
		boost::test_tools::output_test_stream & m_stream;
		CObservable<SWeatherInfo> & m_Observable;
	};
}

BOOST_AUTO_TEST_SUITE(task_2)
	BOOST_AUTO_TEST_CASE(safe_notification_observers)
	{
		boost::test_tools::output_test_stream stream;

		CWeatherData wd;

		TestSafeNotificationObservers::CTestDisplay testDisplay(stream, wd);
		TestSafeNotificationObservers::CTestStatsDisplay testStatsDisplay(stream, wd);

		wd.RegisterObserver(testDisplay, 2);
		wd.RegisterObserver(testStatsDisplay, 1);
		wd.SetMeasurements(3, 0.7, 760);
		BOOST_CHECK(stream.is_equal("Removed CTestDisplay\nRemoved CTestStatsDisplay\n"));

		stream.clear();
		wd.SetMeasurements(3, 0.7, 760);
		//так как наблюдатели сами отписались от издателя то stream == ""
		BOOST_CHECK(stream.is_equal(""));

	}
BOOST_AUTO_TEST_SUITE_END()