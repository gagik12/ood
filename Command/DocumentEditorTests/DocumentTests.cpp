#include "stdafx.h"
#include "../DocumentEditor/Document.h"

BOOST_AUTO_TEST_SUITE(Document)
	BOOST_AUTO_TEST_SUITE(Image)
		BOOST_AUTO_TEST_CASE(can_insert_image)
		{
			CDocument document;
			document.InsertImage("resource/img.png", std::make_pair(100, 200));
			document.InsertImage("resource/img2.png", std::make_pair(100, 200), 1);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 2);

			auto image = document.GetItem(0).GetImage();
			auto image2 = document.GetItem(1).GetImage();
			BOOST_CHECK(image != nullptr);
			BOOST_CHECK(image2 != nullptr);
		}

		BOOST_AUTO_TEST_CASE(can_undo_and_redo_image_item)
		{
			CDocument document;
			document.InsertImage("resource/img.png", std::make_pair(100, 200));
			BOOST_CHECK(document.CanUndo());
			BOOST_CHECK(!document.CanRedo());

			document.Undo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
			BOOST_CHECK(!document.CanUndo());
			BOOST_CHECK(document.CanRedo());

			document.Redo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
			BOOST_CHECK(document.CanUndo());
			BOOST_CHECK(!document.CanRedo());
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Paragraph)
		BOOST_AUTO_TEST_CASE(can_insert_paragraph)
		{
			CDocument document;
			document.InsertParagraph("paragraph1", 0);
			document.InsertParagraph("paragraph2");
			BOOST_CHECK(document.GetItemsCount() == 2);
			BOOST_CHECK(document.GetItem(0).GetParagraph()->GetText() == "paragraph1");
			BOOST_CHECK(document.GetItem(1).GetParagraph()->GetText() == "paragraph2");
		}

		BOOST_AUTO_TEST_CASE(can_undo_and_redo_paragraph_item)
		{
			CDocument document;
			document.InsertParagraph("text");

			BOOST_CHECK(document.CanUndo());
			BOOST_CHECK(!document.CanRedo());

			document.Undo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
			BOOST_CHECK(!document.CanUndo());
			BOOST_CHECK(document.CanRedo());

			document.Redo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
			BOOST_CHECK(document.CanUndo());
			BOOST_CHECK(!document.CanRedo());
			BOOST_CHECK_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "text");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(can_change_title)
	{
		CDocument document;
		document.SetTitle("Title");
		BOOST_CHECK_EQUAL(document.GetTitle(), "Title");
	}

	BOOST_AUTO_TEST_CASE(can_remove_item)
	{
		CDocument document;
		document.InsertParagraph("Paragraph1");
		document.InsertParagraph("Paragraph2");
		document.InsertParagraph("Paragraph3");
		document.InsertParagraph("Paragraph4");
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 4);
		BOOST_CHECK_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "Paragraph1");
		BOOST_CHECK_EQUAL(document.GetItem(1).GetParagraph()->GetText(), "Paragraph2");
		BOOST_CHECK_EQUAL(document.GetItem(2).GetParagraph()->GetText(), "Paragraph3");
		BOOST_CHECK_EQUAL(document.GetItem(3).GetParagraph()->GetText(), "Paragraph4");
		document.DeleteItem(0);
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 3);
		BOOST_CHECK_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "Paragraph2");
		BOOST_CHECK_EQUAL(document.GetItem(1).GetParagraph()->GetText(), "Paragraph3");
		BOOST_CHECK_EQUAL(document.GetItem(2).GetParagraph()->GetText(), "Paragraph4");
	}
BOOST_AUTO_TEST_SUITE_END()