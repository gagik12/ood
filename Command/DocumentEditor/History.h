#pragma once

#include "ICommand_fwd.h"
#include "IHistory.h"

class CHistory : public IHistory
{
public:
	CHistory();
	~CHistory();

	bool CanUndo()const;	
	void Undo();
	bool CanRedo()const;
	void Redo();
	void AddAndExecuteCommand(ICommandPtr && command) override;
private:
	std::deque<ICommandPtr> m_commands;
	size_t m_nextCommandIndex = 0;
};

