#include "stdafx.h"
#include "../GumballMachine/NaiveGumBallMachine.h"

using namespace naive;

void CheckGumballMachineInfo(CGumballMachine const& machine, int ballsCount, const std::string& state)
{
	boost::format format = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Machine is %3%
)");

	BOOST_CHECK_EQUAL(machine.ToString(), (format % ballsCount % ((ballsCount == 1) ? "" : "s") % state).str());
};

struct SOutputStreamFixture
{
	boost::test_tools::output_test_stream outputStream;
};

BOOST_FIXTURE_TEST_SUITE(naive_gum_ball_machine, SOutputStreamFixture)
	BOOST_AUTO_TEST_SUITE(init_machine)
		BOOST_AUTO_TEST_CASE(waiting_for_quarter_if_has_gum)
		{
			CGumballMachine machine(2, outputStream);
			BOOST_CHECK(outputStream.is_equal(""));
			CheckGumballMachineInfo(machine, 2, "waiting for quarter");
		}

		BOOST_AUTO_TEST_CASE(sold_out_if_has_no_gum)
		{
			CGumballMachine machine(0, outputStream);
			BOOST_CHECK(outputStream.is_equal(""));
			CheckGumballMachineInfo(machine, 0, "sold out");
		}
	BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_CASE(we_can_insert_5_quarters)
	{
		CGumballMachine machine(6, outputStream);
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		BOOST_CHECK(outputStream.is_equal(R"(You inserted a quarter
You inserted a quarter
You inserted a quarter
You inserted a quarter
You inserted a quarter
You can't insert another quarter
)"));
		CheckGumballMachineInfo(machine, 6, "waiting for turn of crank");
	}

	BOOST_AUTO_TEST_CASE(we_can_return_all_quarters)
	{
		CGumballMachine machine(6, outputStream);
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.EjectQuarter();
		BOOST_CHECK(outputStream.is_equal(R"(You inserted a quarter
You inserted a quarter
You inserted a quarter
You inserted a quarter
Returned 4 quarters
)"));
		outputStream.clear();
		CheckGumballMachineInfo(machine, 6, "waiting for quarter");

		machine.TurnCrank();
		BOOST_CHECK(outputStream.is_equal(R"(You turned but there's no quarter
)"));
		CheckGumballMachineInfo(machine, 6, "waiting for quarter");
	}

	BOOST_AUTO_TEST_CASE(return_all_quarters_in_solid_state)
	{
		CGumballMachine machine(1, outputStream);
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.TurnCrank();
		machine.EjectQuarter();
		BOOST_CHECK(outputStream.is_equal(R"(You inserted a quarter
You inserted a quarter
You inserted a quarter
You turned...
A gumball comes rolling out the slot
Oops, out of gumballs
Returned 2 quarters
)"));
		CheckGumballMachineInfo(machine, 0, "sold out");
	}
BOOST_AUTO_TEST_SUITE_END()