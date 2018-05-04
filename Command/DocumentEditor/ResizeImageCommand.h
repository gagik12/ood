#pragma once
#include "AbstractCommand.h"
#include "IImage.h"
#include "DocumentItem.h"

class CResizeImageCommand : public CAbstractCommand
{
public:
	CResizeImageCommand(std::pair<int, int> const& newSize, size_t index, std::vector<CDocumentItem> & documentItems);
protected:
	void DoExecute() override;
	void DoUnexecute() override;
private:
	std::pair<int, int> m_newSize;
	std::pair<int, int> m_oldSize;
	size_t m_index;
	std::vector<CDocumentItem> & m_documentItems;
};

