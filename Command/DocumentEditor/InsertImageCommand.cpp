#include "stdafx.h"
#include "InsertImageCommand.h"
#include "FileUtils.h"
#include "StringUtils.h"

CInsertImageCommand::CInsertImageCommand(IImagePtr const& image, size_t index, std::vector<CDocumentItem> & documentItems)
	: m_image(image)
	, m_index(index)
	, m_documentItems(documentItems)
{
}
CInsertImageCommand::~CInsertImageCommand()
{
	boost::filesystem::remove(m_image->GetPath());
}

void CInsertImageCommand::DoExecute()
{
	//C:\Users\vadim\Desktop\img.png
	if (m_imageName.empty())
	{
		auto originalImagePath = m_image->GetPath();
		m_imageName = CStringUtils::GetRandomString(originalImagePath.filename().size());
		std::string imagePath = FOLDER_WITH_IMAGES + m_imageName + originalImagePath.extension().string();
		CFileUtils::CopyImageInFolder(m_image->GetPath(), m_imageName);
		m_image->SetPath(imagePath);
	}
	else
	{
		std::string imagePath = FOLDER_WITH_IMAGES + m_imageName + m_image->GetPath().extension().string();
		boost::filesystem::rename(m_image->GetPath(), imagePath);
		m_image->SetPath(imagePath);
	}
	m_documentItems.emplace(m_documentItems.begin() + m_index, CDocumentItem(m_image, nullptr));
}

void CInsertImageCommand::DoUnexecute()
{
	m_documentItems.erase(m_documentItems.begin() + m_index);
	auto imagePath = FOLDER_WITH_IMAGES + m_imageName + DELETION_MARKER + m_image->GetPath().extension().string();
	boost::filesystem::rename(m_image->GetPath(), imagePath);
	m_image->SetPath(imagePath);
}
