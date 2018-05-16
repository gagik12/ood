#include "stdafx.h"
#include "../DocumentEditor/Image.h"
#include "../DocumentEditor/History.h"

struct SHistoryFixture
{
	CHistory history;
};

BOOST_FIXTURE_TEST_SUITE(Image, SHistoryFixture)
	BOOST_AUTO_TEST_CASE(can_create_image)
	{
		auto image = std::make_unique<CImage>("img/image.png", std::make_pair(100, 200), history);
		BOOST_CHECK(image != nullptr);
	}

	BOOST_AUTO_TEST_CASE(can_get_size)
	{
		const auto size = std::make_pair(100, 200);
		auto image = std::make_unique<CImage>("img/image.png", size, history);

		BOOST_CHECK(image->GetWidth() == size.first);
		BOOST_CHECK(image->GetHeight() == size.second);
	}

	BOOST_AUTO_TEST_CASE(can_resize)
	{
		auto image = std::make_unique<CImage>("img/image.png", std::make_pair(100, 200), history);
		image->Resize(200, 100);

		BOOST_CHECK(image->GetWidth() == 200);
		BOOST_CHECK(image->GetHeight() == 100);
	}
BOOST_AUTO_TEST_SUITE_END()