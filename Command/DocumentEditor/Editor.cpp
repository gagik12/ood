#include "stdafx.h"
#include "Editor.h"
#include "StreamUtils.h"
#include "Paragraph.h"
#include "Image.h"
#include "IImage.h"
#include "FileUtils.h"

using namespace std;
using namespace std::placeholders;

CEditor::CEditor()
	:m_document(make_unique<CDocument>())
{
	m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
	m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
	AddMenuItem("setTitle", "Changes title. Args: <new title>", &CEditor::SetTitle);
	m_menu.AddItem("list", "Show document", bind(&CEditor::List, this, _1));
	AddMenuItem("undo", "Undo command", &CEditor::Undo);
	AddMenuItem("redo", "Redo undone command", &CEditor::Redo);
	AddMenuItem("insertParagraph", "Add paragraph. Args: <position>|end <text>", &CEditor::InsertParagraph);
	AddMenuItem("deleteItem", "Delete document item. Args: <position>", &CEditor::DeleteItem);
	AddMenuItem("save", "Save document. Args: <path>", &CEditor::Save);
	AddMenuItem("replaceText", "Replace text paragraph. Args: <position> <text>", &CEditor::ReplaceText);
	AddMenuItem("insertImage", "Add image. Args: <position>|end <width> <height> <path>", &CEditor::InsertImage);
	AddMenuItem("resizeImage", "Resize image. Args: <position> <width> <height>", &CEditor::ResizeImage);
}

void CEditor::Start()
{
	m_menu.Run();
}

void CEditor::AddMenuItem(const string & shortcut, const string & description, MenuHandler handler)
{
	m_menu.AddItem(shortcut, description, bind(handler, this, _1));
}

void CEditor::InsertParagraph(istream & in)
{
	ParagraphInfo paragraphInfo = CStreamUtils::GetParagraphInfo(in, m_document->GetItemsCount());
	auto position = paragraphInfo.first;
	m_document->InsertParagraph(paragraphInfo.second, position);
}

void CEditor::InsertImage(std::istream & in)
{
	//std::string const& path, int width, int height
	ImageInfo imageInfo = CStreamUtils::GetImageInfo(in, m_document->GetItemsCount());
	auto position = imageInfo.position;
	std::string path = imageInfo.path;

	m_document->InsertImage(path, imageInfo.size, position);
}

void CEditor::DeleteItem(istream & in)
{
	size_t index = CStreamUtils::GetIndex(in, m_document->GetItemsCount());
	m_document->DeleteItem(index);
}

void CEditor::SetTitle(istream & in)
{
	string title = CStreamUtils::GetText(in);
	m_document->SetTitle(title);
}

void CEditor::ReplaceText(std::istream & in)
{
	size_t index = CStreamUtils::GetIndex(in, m_document->GetItemsCount());
	string text = CStreamUtils::GetText(in);
	auto & documentItem = m_document->GetItem(index);
	auto & paragraph = documentItem.GetParagraph();
	if (paragraph == nullptr)
	{
		throw std::length_error("In this position there is no paragraph");
	}
	paragraph->SetText(text);
	//m_document->ReplaceText(index, text);
}

void CEditor::ResizeImage(std::istream & in)
{
	auto resizeOptions = CStreamUtils::GetResizeImageOptions(in, m_document->GetItemsCount());
	auto & documentItem = m_document->GetItem(resizeOptions.first.get());
	auto & image = documentItem.GetImage();
	if (image == nullptr)
	{
		throw std::length_error("In this position there is no image");
	}
	auto size = resizeOptions.second;
	image->Resize(size.first, size.second);
	//m_document->ResizeImage(size.second, size.first.get());
}

void CEditor::Save(istream & in)
{
	std::string path = CStreamUtils::GetPath(in);
	m_document->Save(path);
}

void CEditor::List(istream &)
{
	cout << "-------------" << endl;
	cout << "Title: " << m_document->GetTitle() << endl;
	for (size_t index = 0; index < m_document->GetItemsCount(); ++index)
	{
		auto item = m_document->GetItem(index);
		auto paragraph = item.GetParagraph();
		auto image = item.GetImage();
		if (paragraph != nullptr)
		{
			std::cout << index << ". Paragraph: " << paragraph->GetText() << std::endl;
		}
		if (image != nullptr)
		{
			std::cout << index << ". Image: " << image->GetWidth() << " " << image->GetHeight() << " " << image->GetPath().string() << std::endl;
		}
	}
	cout << "-------------" << endl;
}

void CEditor::Undo(istream &)
{
	if (m_document->CanUndo())
	{
		m_document->Undo();
	}
	else
	{
		cout << "Can't undo" << endl;
	}
}

void CEditor::Redo(istream &)
{
	if (m_document->CanRedo())
	{
		m_document->Redo();
	}
	else
	{
		cout << "Can't redo" << endl;
	}
}