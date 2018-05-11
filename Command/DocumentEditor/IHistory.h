#pragma once
#include "ICommand_fwd.h"

class IHistory
{
public:
	virtual void AddAndExecuteCommand(ICommandPtr && command) = 0;
};