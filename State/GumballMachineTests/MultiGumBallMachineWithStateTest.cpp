#include "stdafx.h"
#include "../GumballMachine/MultiGumBallMachineWithState.h"

using namespace with_state_multi;

void CheckGumballMachineInfo(CMultiGumballMachine const& machine, int ballsCount, const std::string& state)
{
	boost::format format = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
)");

	BOOST_CHECK_EQUAL(machine.ToString(), (format % ballsCount % ((ballsCount == 1) ? "" : "s") % state).str());
};

struct SOutputStreamFixture
{
	boost::test_tools::output_test_stream outputStream;
};

BOOST_FIXTURE_TEST_SUITE(multi_gumball_machine_with_state, SOutputStreamFixture)
	BOOST_AUTO_TEST_SUITE(init_machine)
		BOOST_AUTO_TEST_CASE(waiting_for_quarter_if_has_gum)
		{
			CMultiGumballMachine machine(2, outputStream);
			BOOST_CHECK(outputStream.is_equal(""));
			CheckGumballMachineInfo(machine, 2, "waiting for quarter");
		}

		BOOST_AUTO_TEST_CASE(sold_out_if_has_no_gum)
		{
			CMultiGumballMachine machine(0, outputStream);
			BOOST_CHECK(outputStream.is_equal(""));
			CheckGumballMachineInfo(machine, 0, "sold out");
		}
	BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_CASE(we_can_insert_5_quarters)
	{
		CMultiGumballMachine machine(6, outputStream);
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
		CMultiGumballMachine machine(6, outputStream);
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
You need to pay first
)"));
		CheckGumballMachineInfo(machine, 6, "waiting for quarter");
	}

	BOOST_AUTO_TEST_CASE(return_all_quarters_in_solid_state)
	{
		CMultiGumballMachine machine(1, outputStream);
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.InsertQuarter();
		machine.TurnCrank();
		machine.EjectQuarter();
		BOOST_CHECK(outputStream.is_equal(R"(You inserted a quarter
You inserted a quarter
You inserted a quarter
You turned...
A gumball comes rolling out the slot...
Oops, out of gumballs
Returned 2 quarters
)"));
		CheckGumballMachineInfo(machine, 0, "sold out");
	}
	BOOST_AUTO_TEST_SUITE(refill_machine)
		BOOST_AUTO_TEST_CASE(can_refill_from_solid_out_state)
		{
			CMultiGumballMachine machine(0, outputStream);
			machine.Refill(4);
			CheckGumballMachineInfo(machine, 4, "waiting for quarter");
			BOOST_CHECK(outputStream.is_equal("Added: 4\n"));
		}

		BOOST_AUTO_TEST_CASE(can_refill_from_has_quarter_state)
		{
			CMultiGumballMachine machine(2, outputStream);
			machine.InsertQuarter();
			machine.Refill(4);
			CheckGumballMachineInfo(machine, 6, "waiting for turn of crank");
			BOOST_CHECK(outputStream.is_equal("You inserted a quarter\nAdded: 4\n"));
		}

		BOOST_AUTO_TEST_CASE(can_refill_from_no_quarter_state)
		{
			CMultiGumballMachine machine(2, outputStream);
			machine.Refill(4);
			CheckGumballMachineInfo(machine, 6, "waiting for quarter");
			BOOST_CHECK(outputStream.is_equal("Added: 4\n"));
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()