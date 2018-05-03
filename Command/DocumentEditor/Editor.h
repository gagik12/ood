#pragma once
#include "Document.h"
#include "Menu.h"
#include "IDocument.h"

class CEditor
{
public:
	CEditor();
	void Start();
private:
	// Указатель на метод класса CEditor, принимающий istream& и возвращающий void
	typedef void (CEditor::*MenuHandler)(std::istream & in);

	void AddMenuItem(const std::string & shortcut, const std::string & description, MenuHandler handler);

	void SetTitle(std::istream & in);
	void InsertParagraph(std::istream & in);
	void DeleteItem(std::istream & in);
	void Save(std::istream & in);
	void ReplaceText(std::istream & in);

	void List(std::istream &);

	void Undo(std::istream &);
	void Redo(std::istream &);

	CMenu m_menu;
	std::unique_ptr<IDocument> m_document;
};