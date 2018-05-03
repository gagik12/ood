#pragma once
#include "IParagraph.h"
#include "IImage.h"
#include "DocumentItem.h"

class IDocument
{
public:
	// Вставляет параграф текста в указанную позицию (сдвигая последующие элементы)
	// Если параметр position не указан, вставка происходит в конец документа
	virtual void InsertParagraph(IParagraphPtr const& paragraph, boost::optional<size_t> position = boost::none) = 0;

	//// Вставляет изображение в указанную позицию (сдвигая последующие элементы)
	//// Параметр path задает путь к вставляемому изображению
	//// При вставке изображение должно копироваться в подкаталог images 
	//// под автоматически сгенерированным именем
	//virtual std::shared_ptr<IImage> InsertImage(const std::string& path, int width, int height,
	//	boost::optional<size_t> position = boost::none) = 0;

	virtual size_t GetItemsCount()const = 0;

	virtual CDocumentItem GetItem(size_t index) = 0;

	//// Удаляет элемент из документа
	virtual void DeleteItem(size_t index) = 0;

	// Возвращает заголовок документа
	virtual std::string GetTitle()const = 0;
	// Изменяет заголовок документа
	virtual void SetTitle(const std::string & title) = 0;

	// Сообщает о доступности операции Undo
	virtual bool CanUndo()const = 0;
	// Отменяет команду редактирования
	virtual void Undo() = 0;

	// Сообщает о доступности операции Redo
	virtual bool CanRedo()const = 0;
	// Выполняет отмененную команду редактирования
	virtual void Redo() = 0;

	//// Сохраняет документ в формате html. Изображения сохраняются в подкаталог images.
	//// Пути к изображениям указываются относительно пути к сохраняемому HTML файлу
	virtual void Save(const boost::filesystem::path& path)const = 0;

	virtual void ReplaceText(size_t index, std::string const& newText) = 0;

	virtual ~IDocument() = default;
};
