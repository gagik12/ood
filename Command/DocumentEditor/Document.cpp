#include "stdafx.h"
#include "Document.h"
#include "ChangeStringCommand.h"
#include "InsertParagraphCommand.h"
#include "DeleteItemCommand.h"
#include "Paragraph.h"
#include "HtmlExporter.h"
#include "InsertImageCommand.h"
#include "FileUtils.h"
#include "ResizeImageCommand.h"
#include "Image.h"

using namespace std;

CDocument::~CDocument()
{
	CFileUtils::ClearFolder(FOLDER_WITH_IMAGES);
}

void CDocument::SetTitle(const std::string & title)
{
	m_history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(m_title, title));
}

void CDocument::InsertParagraph(std::string const& text, boost::optional<size_t> position)
{
	size_t index = position.is_initialized() ? position.get() : m_documentItems.size();
	IParagraphPtr paragraph = std::make_shared<CParagraph>(text, m_history);
	m_history.AddAndExecuteCommand(make_unique<CInsertParagraphCommand>(paragraph, index, m_documentItems));
}

void CDocument::InsertImage(std::string const& path, std::pair<int, int> const& size, boost::optional<size_t> position)
{
	size_t index = position.is_initialized() ? position.get() : m_documentItems.size();
	IImagePtr image = std::make_shared<CImage>(path, size, m_history);
	m_history.AddAndExecuteCommand(make_unique<CInsertImageCommand>(image, index, m_documentItems));
}

void CDocument::DeleteItem(size_t index)
{
	m_history.AddAndExecuteCommand(make_unique<CDeleteItemCommand>(index, m_documentItems));
}

std::string CDocument::GetTitle() const
{
	return m_title;
}

size_t CDocument::GetItemsCount() const
{
	return m_documentItems.size();
}

CDocumentItem CDocument::GetItem(size_t index)
{
	return m_documentItems.at(index);
}
bool CDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void CDocument::Undo()
{
	m_history.Undo();
}

bool CDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void CDocument::Redo()
{
	m_history.Redo();
}

void CDocument::Save(const boost::filesystem::path& path) const
{	
	CHtmlExporter htmlExporter(m_title, m_documentItems);
	htmlExporter.Export(path);
}