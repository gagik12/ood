#include "stdafx.h"
#include "Document.h"
#include "ChangeStringCommand.h"
#include "InsertParagraphCommand.h"
#include "DeleteItemCommand.h"
#include "Paragraph.h"
#include "HtmlExporter.h"
#include "ReplaceTextCommand.h"
#include "InsertImageCommand.h"
#include "FileUtils.h"
#include "ResizeImageCommand.h"

using namespace std;

CDocument::~CDocument()
{
	CFileUtils::ClearFolder(FOLDER_WITH_IMAGES);
}

void CDocument::SetTitle(const std::string & title)
{
	m_history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(m_title, title));
}

void CDocument::InsertParagraph(IParagraphPtr const& paragraph, boost::optional<size_t> position)
{
	size_t index = position.is_initialized() ? position.get() : m_documentItems.size();
	m_history.AddAndExecuteCommand(make_unique<CInsertParagraphCommand>(paragraph, index, m_documentItems));
}

void CDocument::InsertImage(IImagePtr const& image, boost::optional<size_t> position)
{
	size_t index = position.is_initialized() ? position.get() : m_documentItems.size();
	m_history.AddAndExecuteCommand(make_unique<CInsertImageCommand>(image, index, m_documentItems));
}

void CDocument::DeleteItem(size_t index)
{
	m_history.AddAndExecuteCommand(make_unique<CDeleteItemCommand>(index, m_documentItems));
}

void CDocument::ReplaceText(size_t index, std::string const& newText)
{
	m_history.AddAndExecuteCommand(make_unique<CReplaceTextCommand>(newText, index, m_documentItems));
}

void CDocument::ResizeImage(std::pair<int, int> const& newSize, size_t index)
{
	m_history.AddAndExecuteCommand(make_unique<CResizeImageCommand>(newSize, index, m_documentItems));
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