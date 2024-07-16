#include "libcsv.hpp"

int main()
{
	const char csv[] = "header1,header2,header3,header4\n1,2,3,4\n5,6,7,8\n9,10,11,12";
	processCsv(csv, "header1,header3,header4", "header1>1\nheader3<10");

	processCsv(csv, "", "");

	const char csv2[] = "header1,header2,header3\n1,2,3\n4,5,6\n7,8,9";
	processCsv(csv2, "header1,header3", "header1>1\nheader3<8");

	return 0;
}
