#ifndef COLORS_IN
#define COLORS_IN

#include <string>
#include <ostream>
#include "windows.h"

using std::string;
using std::ostream;

// Color table
enum COLOR { black, blue, green, cyan, red, magenta, brown, normal, darkgray, lightblue, lightgreen, lightcyan, lightred, lightmagenta, yellow, white };

// Color overload for cout, used when iomanip functions are combined
ostream & operator<< (ostream &stm, const COLOR &c)
{
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out_handle, c);
	return stm;
}

#endif
