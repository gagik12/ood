#include "stdafx.h"
#include "../DocumentEditor/History.h"
#include "../DocumentEditor/InsertImageCommand.h"
#include "../DocumentEditor/InsertParagraphCommand.h"
#include "../DocumentEditor/ResizeImageCommand.h"

BOOST_AUTO_TEST_SUITE(History)
	BOOST_AUTO_TEST_CASE(can_add_and_execute_insert_paragraph_command)
	{
		CHistory history;
		std::vector<CDocumentItem> items;

		history.AddAndExecuteCommand(std::make_unique<CInsertParagraphCommand>(items, "paragraph", 0, history));
		BOOST_CHECK_EQUAL(items.size(), 1);
		BOOST_CHECK_EQUAL(items.at(0).GetParagraph()->GetText(), "paragraph");
	}

	BOOST_AUTO_TEST_CASE(can_add_and_execute_insert_image_command)
	{
		CHistory history;
		std::vector<CDocumentItem> items;

		history.AddAndExecuteCommand(std::make_unique<CInsertImageCommand>("resource/img.png", std::make_pair(100, 200), items));
		BOOST_CHECK_EQUAL(items.size(), 1);
		auto image = items.at(0).GetImage();
		BOOST_CHECK_EQUAL(image->GetPath(), "resource/img.png");
		BOOST_CHECK_EQUAL(image->GetHeight(), 200);
		BOOST_CHECK_EQUAL(image->GetWidth(), 100);
	}

	BOOST_AUTO_TEST_CASE(can_add_and_execute_resize_image_command)
	{
		CHistory history;
		std::vector<CDocumentItem> items;

		history.AddAndExecuteCommand(std::make_unique<CInsertImageCommand>("resource/img.png", std::make_pair(100, 200), items));
		BOOST_CHECK_EQUAL(items.size(), 1);
		auto image = items.at(0).GetImage();
		BOOST_CHECK_EQUAL(image->GetPath(), "resource/img.png");
		BOOST_CHECK_EQUAL(image->GetHeight(), 200);
		BOOST_CHECK_EQUAL(image->GetWidth(), 100);

		image->Resize(20, 10);
		BOOST_CHECK_EQUAL(image->GetPath(), "resource/img.png");
		BOOST_CHECK_EQUAL(image->GetHeight(), 10);
		BOOST_CHECK_EQUAL(image->GetWidth(), 20);
	}
BOOST_AUTO_TEST_SUITE_END()