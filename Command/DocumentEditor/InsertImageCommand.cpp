#include "stdafx.h"
#include "InsertImageCommand.h"


CInsertImageCommand::CInsertImageCommand()
{
}

void CInsertImageCommand::DoExecute()
{
	//m_documentItems.emplace(m_documentItems.begin() + m_index, CDocumentItem(nullptr, m_paragraph));
}

void CInsertImageCommand::DoUnexecute()
{
	//m_documentItems.erase(m_documentItems.begin() + m_index);
}
