#include "stdafx.h"
#include "../DocumentEditor/Paragraph.h"
#include "../DocumentEditor/History.h"

struct SHistoryFixture
{
	CHistory history;
};

BOOST_FIXTURE_TEST_SUITE(Paragraph, SHistoryFixture)
	BOOST_AUTO_TEST_CASE(can_create_paragraph)
	{
		auto paragraph = std::make_unique<CParagraph>("Hello, world!", history);
		BOOST_CHECK(paragraph != nullptr);
	}

	BOOST_AUTO_TEST_CASE(can_get_text)
	{
		const std::string TEXT = "Hello, world!";
		auto paragraph = std::make_unique<CParagraph>(TEXT, history);

		BOOST_CHECK(paragraph->GetText() == TEXT);
	}

	BOOST_AUTO_TEST_CASE(can_set_text)
	{
		const std::string TEXT = "Hello, world!";
		auto paragraph = std::make_unique<CParagraph>("text", history);
		paragraph->SetText(TEXT);

		BOOST_CHECK(paragraph->GetText() == TEXT);
	}
BOOST_AUTO_TEST_SUITE_END()