#include "stdafx.h"
#include "ResizeImageCommand.h"
#include "IImage.h"

CResizeImageCommand::CResizeImageCommand(std::pair<int, int> & targetSize, std::pair<int, int> const& newSize)
	: m_targetSize(targetSize)
	, m_newSize(newSize)
{
}

void CResizeImageCommand::DoExecute()
{
	m_newSize.swap(m_targetSize);
}

void CResizeImageCommand::DoUnexecute()
{
	m_newSize.swap(m_targetSize);
}
