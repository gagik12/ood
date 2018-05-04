#pragma once
#include "IDocument.h"
#include "History.h"
#include "DocumentItem.h"

typedef std::vector<CDocumentItem> DocumentItems;

class CDocument : public IDocument
{
public:
	~CDocument();
	void SetTitle(const std::string & title) override;
	void InsertParagraph(IParagraphPtr const& paragraph, boost::optional<size_t> position = boost::none) override;
	void InsertImage(IImagePtr const& image, boost::optional<size_t> position = boost::none) override;
	void DeleteItem(size_t index) override;
	void Save(const boost::filesystem::path& path) const override;
	void ReplaceText(size_t index, std::string const& newText) override;
	void ResizeImage(std::pair<int, int> const& newSize, size_t index) override;

	std::string GetTitle() const override;
	size_t GetItemsCount() const override;
	CDocumentItem GetItem(size_t index) override;
	
	bool CanUndo() const override;	
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;

private:
	std::string m_title;
	DocumentItems m_documentItems;
	CHistory m_history;
};