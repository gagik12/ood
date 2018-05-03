#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"

class CDeleteItemCommand : public CAbstractCommand
{
public:
	CDeleteItemCommand(size_t index, std::vector<CDocumentItem> & documentItems);
protected:
	void DoExecute() override;
	void DoUnexecute() override;
private:
	size_t m_index;
	std::vector<CDocumentItem> & m_documentItems;
	CDocumentItem m_documentItem;
};

