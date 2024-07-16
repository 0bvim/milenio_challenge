#include <gtest/gtest.h>
#include "libcsv.hpp"
#include "utils.hpp"

// Test case for `parseCsvHeader`
TEST(CsvTest, ParseCsvHeader)
{
	std::string headerLine = "Name,Age,Location";
	std::vector<std::string> headers = parseCsvHeader(headerLine);

	ASSERT_EQ(headers.size(), 3);
	EXPECT_EQ(headers[0], "Name");
	EXPECT_EQ(headers[1], "Age");
	EXPECT_EQ(headers[2], "Location");
}

// Test case for `mapWorkColumns`
TEST(CsvTest, MapWorkColumns)
{
	std::vector<std::string> headers = {"Name", "Age", "Location"};
	std::string workColumns = "Age,Location";
	std::vector<int> selectedCols = mapWorkColumns(headers, workColumns);

	ASSERT_EQ(selectedCols.size(), 2);
	EXPECT_EQ(selectedCols[0], 1); // Age
	EXPECT_EQ(selectedCols[1], 2); // Location
}

// Test case for `applyFilters`
TEST(CsvTest, ApplyFilters)
{
	std::vector<std::string> headers = {"Name", "Age"};
	std::vector<std::string> rowData = {"Alice", "30"};
	std::vector<std::string> rowFilters = {"Age>=30"};

	bool result = applyFilters(headers, rowData, rowFilters);
	EXPECT_TRUE(result);
}

// Test case for `printVector` (this requires redirecting stdout for verification)
TEST(CsvTest, PrintVector)
{
	std::vector<int> indices = {0, 1};
	std::vector<std::string> data = {"Name", "Age"};

	// Redirect stdout to capture the output
	std::ostringstream oss;
	std::streambuf *orig_buf = std::cout.rdbuf(oss.rdbuf());

	printVector(indices, data);

	std::cout.rdbuf(orig_buf); // Restore stdout
	std::string output = oss.str();
	EXPECT_EQ(output, "Name,Age\n");
}
