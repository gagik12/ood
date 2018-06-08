#pragma once

#include <iostream>
#include <boost/format.hpp>

namespace naive
{
class CGumballMachine
{
public:
	enum class State
	{
		SoldOut,		// Жвачка закончилась
		NoQuarter,		// Нет монетки
		HasQuarter,		// Есть монетка
		Sold,			// Монетка выдана
	};

	CGumballMachine(unsigned count, std::ostream & stream)
		: m_count(count)
		, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
		, m_stream(stream)
	{
	}

	void InsertQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			m_stream << "You can't insert a quarter, the machine is sold out\n";
			break;
		case State::NoQuarter:
			AddQuarter();
			m_state = State::HasQuarter;
			break;
		case State::HasQuarter:
			AddQuarter();
			break;
		case State::Sold:
			m_stream << "Please wait, we're already giving you a gumball\n";
			break;
		}
	}

	void EjectQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::HasQuarter:
			EjectAllQuarters();
			m_state = State::NoQuarter;
			break;
		case State::NoQuarter:
			m_stream << "You haven't inserted a quarter\n";
			break;
		case State::Sold:
			m_stream << "Sorry you already turned the crank\n";
			break;
		case State::SoldOut:
			if (m_quarters != 0)
			{
				EjectAllQuarters();

				if (m_count != 0)
				{
					m_state = State::NoQuarter;
				}
			}
			else
			{
				m_stream << "You can't eject, you haven't inserted a quarter yet\n";
			}
			break;
		}
	}

	void TurnCrank()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			m_stream << "You turned but there's no gumballs\n";
			break;
		case State::NoQuarter:
			m_stream << "You turned but there's no quarter\n";
			break;
		case State::HasQuarter:
			m_stream << "You turned...\n";
			m_state = State::Sold;
			ReleaseQuarter();
			Dispense();
			break;
		case State::Sold:
			m_stream << "Turning twice doesn't get you another gumball\n";
			break;
		}
	}

	void Refill(unsigned numBalls)
	{
		m_count = numBalls;
		m_state = numBalls > 0 ? State::NoQuarter : State::SoldOut;
	}

	std::string ToString()const
	{
		std::string state =
			(m_state == State::SoldOut)    ? "sold out" :
			(m_state == State::NoQuarter)  ? "waiting for quarter" :
			(m_state == State::HasQuarter) ? "waiting for turn of crank"
			                               : "delivering a gumball";
		auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Machine is %3%
)");
		return (fmt % m_count % (m_count != 1 ? "s" : "") % state).str();
	}

private:
	void Dispense()
	{
		using namespace std;
		switch (m_state)
		{
		case State::Sold:
			m_stream << "A gumball comes rolling out the slot\n";
			--m_count;
			if (m_count == 0)
			{
				m_stream << "Oops, out of gumballs\n";
				m_state = State::SoldOut;
			}
			else
			{
				m_state = (m_quarters > 0) ? State::HasQuarter : State::NoQuarter;
			}
			break;
		case State::NoQuarter:
			m_stream << "You need to pay first\n";
			break;
		case State::SoldOut:
		case State::HasQuarter:
			m_stream << "No gumball dispensed\n";
			break;
		}
	}

	void AddQuarter()
	{
		if (m_quarters < MAX_COUNT_QUARTERS)
		{
			m_quarters++;
			m_stream << "You inserted a quarter\n";
		}
		else
		{
			m_stream << "You can't insert another quarter\n";
		}
	}

	void ReleaseQuarter()
	{
		if (m_quarters != 0)
		{
			--m_quarters;
		}
	}

	void EjectAllQuarters()
	{
		m_stream << "Returned " << m_quarters << " quarters\n";
		m_quarters = 0;
	}

	unsigned m_count;	// Количество шариков
	unsigned m_quarters = 0;
	const unsigned MAX_COUNT_QUARTERS = 5;
	State m_state = State::SoldOut;
	std::ostream & m_stream;
};
}