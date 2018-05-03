#pragma once
#include "IParagraph.h"
#include "IImage.h"
#include "DocumentItem.h"

class IDocument
{
public:
	// ��������� �������� ������ � ��������� ������� (������� ����������� ��������)
	// ���� �������� position �� ������, ������� ���������� � ����� ���������
	virtual void InsertParagraph(IParagraphPtr const& paragraph, boost::optional<size_t> position = boost::none) = 0;

	//// ��������� ����������� � ��������� ������� (������� ����������� ��������)
	//// �������� path ������ ���� � ������������ �����������
	//// ��� ������� ����������� ������ ������������ � ���������� images 
	//// ��� ������������� ��������������� ������
	//virtual std::shared_ptr<IImage> InsertImage(const std::string& path, int width, int height,
	//	boost::optional<size_t> position = boost::none) = 0;

	virtual size_t GetItemsCount()const = 0;

	virtual CDocumentItem GetItem(size_t index) = 0;

	//// ������� ������� �� ���������
	virtual void DeleteItem(size_t index) = 0;

	// ���������� ��������� ���������
	virtual std::string GetTitle()const = 0;
	// �������� ��������� ���������
	virtual void SetTitle(const std::string & title) = 0;

	// �������� � ����������� �������� Undo
	virtual bool CanUndo()const = 0;
	// �������� ������� ��������������
	virtual void Undo() = 0;

	// �������� � ����������� �������� Redo
	virtual bool CanRedo()const = 0;
	// ��������� ���������� ������� ��������������
	virtual void Redo() = 0;

	//// ��������� �������� � ������� html. ����������� ����������� � ���������� images.
	//// ���� � ������������ ����������� ������������ ���� � ������������ HTML �����
	virtual void Save(const boost::filesystem::path& path)const = 0;

	virtual void ReplaceText(size_t index, std::string const& newText) = 0;

	virtual ~IDocument() = default;
};
