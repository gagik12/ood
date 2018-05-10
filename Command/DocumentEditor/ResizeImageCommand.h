#pragma once
#include "AbstractCommand.h"
#include "IImage.h"
#include "DocumentItem.h"

class CResizeImageCommand : public CAbstractCommand
{
public:
	CResizeImageCommand(std::pair<int, int> & targetSize, std::pair<int, int> const& newSize);
protected:
	void DoExecute() override;
	void DoUnexecute() override;
private:
	std::pair<int, int> & m_targetSize;
	std::pair<int, int> m_newSize;
};

