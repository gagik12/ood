#pragma once
#include <iostream>
#include <boost/format.hpp>

namespace with_state_multi
{
	struct IState
	{
		virtual void InsertQuarter() = 0;
		virtual void EjectQuarter() = 0;
		virtual void TurnCrank() = 0;
		virtual void Dispense() = 0;
		virtual void Refill(unsigned count) = 0;
		virtual std::string ToString()const = 0;
		virtual ~IState() = default;
	};

	struct IGumballMachine
	{
		virtual void ReleaseBall() = 0;
		virtual unsigned GetBallCount()const = 0;

		virtual void AddQuarter() = 0;
		virtual void ReleaseQuarter() = 0;
		virtual bool ContainsQuarters()const = 0;
		virtual void EjectAllQuarters() = 0;

		virtual void SetSoldOutState() = 0;
		virtual void SetNoQuarterState() = 0;
		virtual void SetSoldState() = 0;
		virtual void SetHasQuarterState() = 0;

		virtual void Refill(unsigned count) = 0;
		virtual void AddBall(unsigned count) = 0;

		virtual ~IGumballMachine() = default;
	};

	class CSoldState : public IState
	{
	public:
		CSoldState(IGumballMachine & gumballMachine, std::ostream & stream)
			: m_gumballMachine(gumballMachine)
			, m_stream(stream)
		{}
		void InsertQuarter() override
		{
			m_stream << "Please wait, we're already giving you a gumball\n";
		}
		void EjectQuarter() override
		{
			m_stream << "Sorry you already turned the crank\n";
		}
		void TurnCrank() override
		{
			m_stream << "Turning twice doesn't get you another gumball\n";
		}
		void Dispense() override
		{
			m_gumballMachine.ReleaseBall();
			m_gumballMachine.ReleaseQuarter();

			if (m_gumballMachine.GetBallCount() == 0)
			{
				m_stream << "Oops, out of gumballs\n";
				m_gumballMachine.SetSoldOutState();
			}
			else
			{
				if (m_gumballMachine.ContainsQuarters())
				{
					m_gumballMachine.SetHasQuarterState();
				}
				else
				{
					m_gumballMachine.SetNoQuarterState();
				}
			}
		}

		void Refill(unsigned count) override
		{
			m_stream << "This operation is not available\n";
		}

		std::string ToString() const override
		{
			return "delivering a gumball";
		}
	private:
		IGumballMachine & m_gumballMachine;
		std::ostream & m_stream;
	};

	class CSoldOutState : public IState
	{
	public:
		CSoldOutState(IGumballMachine & gumballMachine, std::ostream & stream)
			: m_gumballMachine(gumballMachine)
			, m_stream(stream)
		{}

		void InsertQuarter() override
		{
			m_stream << "You can't insert a quarter, the machine is sold out\n";
		}
		void EjectQuarter() override
		{
			if (m_gumballMachine.ContainsQuarters())
			{
				m_gumballMachine.EjectAllQuarters();
				
				if (m_gumballMachine.GetBallCount() != 0)
				{
					m_gumballMachine.SetNoQuarterState();
				}
			}
			else
			{
				m_stream << "You can't eject, you haven't inserted a quarter yet\n";
			}
		}
		void TurnCrank() override
		{
			m_stream << "You turned but there's no gumballs\n";
		}
		void Dispense() override
		{
			m_stream << "No gumball dispensed\n";
		}
		void Refill(unsigned count) override
		{
			m_gumballMachine.AddBall(count);
			if (m_gumballMachine.ContainsQuarters())
			{
				m_gumballMachine.SetHasQuarterState();
			}
			else
			{
				m_gumballMachine.SetNoQuarterState();
			}
		}
		std::string ToString() const override
		{
			return "sold out";
		}
	private:
		IGumballMachine & m_gumballMachine;
		std::ostream & m_stream;
	};

	class CHasQuarterState : public IState
	{
	public:
		CHasQuarterState(IGumballMachine & gumballMachine, std::ostream & stream)
			: m_gumballMachine(gumballMachine)
			, m_stream(stream)
		{}

		void InsertQuarter() override
		{
			m_gumballMachine.AddQuarter();
		}
		void EjectQuarter() override
		{
			m_gumballMachine.EjectAllQuarters();
			if (m_gumballMachine.GetBallCount() == 0)
			{
				m_gumballMachine.SetSoldOutState();
			}
			else
			{
				m_gumballMachine.SetNoQuarterState();
			}
		}
		void TurnCrank() override
		{
			m_stream << "You turned...\n";
			m_gumballMachine.SetSoldState();
		}
		void Dispense() override
		{
			m_stream << "No gumball dispensed\n";
		}
		void Refill(unsigned count) override
		{
			m_gumballMachine.AddBall(count);
		}
		std::string ToString() const override
		{
			return "waiting for turn of crank";
		}
	private:
		IGumballMachine & m_gumballMachine;
		std::ostream & m_stream;
	};

	class CNoQuarterState : public IState
	{
	public:
		CNoQuarterState(IGumballMachine & gumballMachine, std::ostream & stream)
			: m_gumballMachine(gumballMachine)
			, m_stream(stream)
		{}

		void InsertQuarter() override
		{
			m_gumballMachine.SetHasQuarterState();
			m_gumballMachine.AddQuarter();
		}
		void EjectQuarter() override
		{
			m_stream << "You haven't inserted a quarter\n";
		}
		void TurnCrank() override
		{
			m_stream << "You turned but there's no quarter\n";
		}
		void Dispense() override
		{
			m_stream << "You need to pay first\n";
		}
		void Refill(unsigned count) override
		{
			m_gumballMachine.AddBall(count);
		}
		std::string ToString() const override
		{
			return "waiting for quarter";
		}
	private:
		IGumballMachine & m_gumballMachine;
		std::ostream & m_stream;
	};

	class CMultiGumballMachine : private IGumballMachine
	{
	public:
		CMultiGumballMachine(unsigned numBalls, std::ostream & stream)
			: m_soldState(*this, stream)
			, m_soldOutState(*this, stream)
			, m_noQuarterState(*this, stream)
			, m_hasQuarterState(*this, stream)
			, m_state(&m_soldOutState)
			, m_count(numBalls)
			, m_stream(stream)
		{
			if (m_count > 0)
			{
				m_state = &m_noQuarterState;
			}
		}
		void EjectQuarter()
		{
			m_state->EjectQuarter();
		}
		void InsertQuarter()
		{
			m_state->InsertQuarter();
		}
		void Refill(unsigned count)
		{
			m_state->Refill(count);
		}

		void TurnCrank()
		{
			m_state->TurnCrank();
			m_state->Dispense();
		}
		std::string ToString()const
		{
			auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
)");
			return (fmt % m_count % (m_count != 1 ? "s" : "") % m_state->ToString()).str();
		}
	private:

		void AddQuarter() override
		{
			if (m_quarter < MAX_COUNT_QUARTERS)
			{
				m_quarter++;
				m_stream << "You inserted a quarter\n";
			}
			else
			{
				m_stream << "You can't insert another quarter\n";
			}
		}

		void AddBall(unsigned count) override
		{
			m_count += count;
			m_stream << "Added: " << count << std::endl;
		}

		void ReleaseQuarter() override
		{
			if (ContainsQuarters())
			{
				--m_quarter;
			}
		}

		bool ContainsQuarters()const override
		{
			return m_quarter != 0;
		}

		void EjectAllQuarters() override
		{
			m_stream << "Returned " << m_quarter << " quarters\n";
			m_quarter = 0;
		}

		unsigned GetBallCount() const override
		{
			return m_count;
		}

		void ReleaseBall() override
		{
			if (m_count != 0)
			{
				m_stream << "A gumball comes rolling out the slot...\n";
				--m_count;
			}
		}

		void SetSoldOutState() override
		{
			m_state = &m_soldOutState;
		}

		void SetNoQuarterState() override
		{
			m_state = &m_noQuarterState;
		}

		void SetSoldState() override
		{
			m_state = &m_soldState;
		}

		void SetHasQuarterState() override
		{
			m_state = &m_hasQuarterState;
		}
	private:
		unsigned m_count = 0;
		unsigned m_quarter = 0;
		CSoldState m_soldState;
		CSoldOutState m_soldOutState;
		CNoQuarterState m_noQuarterState;
		CHasQuarterState m_hasQuarterState;
		IState * m_state;

		std::ostream & m_stream;

		const unsigned MAX_COUNT_QUARTERS = 5;

	};

}
