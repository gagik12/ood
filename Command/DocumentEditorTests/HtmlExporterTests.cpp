#include "stdafx.h"
#include "../DocumentEditor/HtmlExporter.h"
#include "../DocumentEditor/FileUtils.h"

BOOST_AUTO_TEST_SUITE(HtmlExporter)
	BOOST_AUTO_TEST_CASE(can_export_document_in_html)
	{
		std::vector<CDocumentItem> items;
		CHtmlExporter htmlExporter("title", items);
		htmlExporter.Export("tmp/file.html");

		BOOST_CHECK(boost::filesystem::exists("tmp/file.html"));
		CFileUtils::ClearFolder("tmp");
	}
BOOST_AUTO_TEST_SUITE_END()