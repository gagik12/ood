#include "stdafx.h"
#include "../GumballMachine/GumBallMachineWithState.h"

using namespace with_state;

void CheckGumballMachineInfo(CGumballMachine const& machine, int ballsCount, const std::string& state)
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

BOOST_FIXTURE_TEST_SUITE(gumball_machine_with_state, SOutputStreamFixture)
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

	BOOST_AUTO_TEST_SUITE(machine_can_change_states)
		BOOST_AUTO_TEST_CASE(changes_state_if_insert_quarter)
		{
			CGumballMachine machine(2, outputStream);
			machine.InsertQuarter();
			BOOST_CHECK(outputStream.is_equal("You inserted a quarter\n"));
			CheckGumballMachineInfo(machine, 2, "waiting for turn of crank");
		}

		BOOST_AUTO_TEST_CASE(changes_state_if_get_last_gum)
		{
			CGumballMachine machine(1, outputStream);
			machine.InsertQuarter();
			CheckGumballMachineInfo(machine, 1, "waiting for turn of crank");
			machine.TurnCrank();
			CheckGumballMachineInfo(machine, 0, "sold out");
			BOOST_CHECK(outputStream.is_equal(R"(You inserted a quarter
You turned...
A gumball comes rolling out the slot...
Oops, out of gumballs
)"));
		}

		BOOST_AUTO_TEST_CASE(we_get_gum_if_insert_quarter_and_turn_crank)
		{
			CGumballMachine machine(2, outputStream);
			machine.InsertQuarter();
			CheckGumballMachineInfo(machine, 2, "waiting for turn of crank");
			machine.TurnCrank();
			BOOST_CHECK(outputStream.is_equal("You inserted a quarter\nYou turned...\nA gumball comes rolling out the slot...\n"));
			CheckGumballMachineInfo(machine, 1, "waiting for quarter");
		}

		BOOST_AUTO_TEST_CASE(can_insert_and_eject_quarter)
		{
			CGumballMachine machine(2, outputStream);
			machine.InsertQuarter();
			CheckGumballMachineInfo(machine, 2, "waiting for turn of crank");
			machine.EjectQuarter();
			CheckGumballMachineInfo(machine, 2, "waiting for quarter");
			BOOST_CHECK(outputStream.is_equal("You inserted a quarter\nQuarter returned\n"));
		}

	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()