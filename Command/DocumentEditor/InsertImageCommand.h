#pragma once
#include "AbstractCommand.h"

class CInsertImageCommand : public CAbstractCommand
{
public:
	CInsertImageCommand();
protected:
	void DoExecute() override;
	void DoUnexecute() override;
};

