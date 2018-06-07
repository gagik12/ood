#include "stdafx.h"
#include "../GumballMachine/GumBallMachineWithState.h"

using namespace with_state;

typedef std::shared_ptr<CGumballMachine> GumballMachinePtr;

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

BOOST_AUTO_TEST_SUITE(gumball_machine_with_state)
	BOOST_AUTO_TEST_SUITE(init_machine)
		BOOST_AUTO_TEST_CASE(waiting_for_quarter_if_has_gum)
		{
			CGumballMachine machine(2);
			CheckGumballMachineInfo(machine, 2, "waiting for quarter");
		}

		BOOST_AUTO_TEST_CASE(sold_out_if_has_no_gum)
		{
			CGumballMachine machine(0);
			CheckGumballMachineInfo(machine, 0, "sold out");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(machine_has_no_quarter)
		BOOST_AUTO_TEST_CASE(change_state_if_insert_quarter)
		{
			CGumballMachine machine(2);
			machine.InsertQuarter();
			CheckGumballMachineInfo(machine, 2, "waiting for turn of crank");
		}

		BOOST_AUTO_TEST_CASE(we_get_gum_if_insert_quarter_and_turn_crank)
		{
			CGumballMachine machine(2);
			machine.InsertQuarter();
			machine.TurnCrank();
			CheckGumballMachineInfo(machine, 1, "waiting for quarter");
		}

		BOOST_AUTO_TEST_CASE(can_insert_and_eject_quarter)
		{
			CGumballMachine machine(2);
			machine.InsertQuarter();
			CheckGumballMachineInfo(machine, 2, "waiting for turn of crank");
			machine.EjectQuarter();
			CheckGumballMachineInfo(machine, 2, "waiting for quarter");
		}
	BOOST_AUTO_TEST_SUITE_END()

	/*struct SGumballMachineFixture
	{
		SGumballMachineFixture()
			: machine(std::make_shared<CGumballMachine>(2))
		{
			machine->InsertQuarter();
		}
		GumballMachinePtr machine;
	};

	BOOST_FIXTURE_TEST_SUITE(machine_has_quarter, SGumballMachineFixture)

	BOOST_AUTO_TEST_SUITE_END()*/
BOOST_AUTO_TEST_SUITE_END()