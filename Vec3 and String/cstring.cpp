#include "cstring.h"
#include <iostream>

/*String::String(): strlen(1)
{
	cstr = new char[strlen];
	cstr[strlen - 1] = '\0';
}*/

String::String(const char* str)
{
	strlen = 1;
	while (*str++)
		strlen++;

	cstr = new char[strlen];
	str = str - strlen;

	for (int i = 0; i < strlen; i++)
		cstr[i] = str[i];
}


