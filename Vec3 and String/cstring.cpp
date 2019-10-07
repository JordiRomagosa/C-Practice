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

char * String::operator+(String & str)
{
	short size = strlen + str.strlen - 1;
	char* string = new char[size];

	for (int i = 0; i < strlen - 1; i++)
		string[i] = cstr[i];
	for (int i = strlen - 1; i < size; i++)
		string[i] = str.cstr[i - (strlen - 1)];

	return string;
}

bool String::operator==(const char * str)
{
	bool same = true;

	for (int i = 0; i < strlen; i++) {
		if (*cstr++ != *str++) {
			same = false;
			cstr = cstr - (i + 1);
			break;
		}
		
	}

	if (same)
		cstr = cstr - strlen;
	
	return same;
}

short String::length()
{
	return strlen - 1;
}

void String::clear()
{
	strlen = 1;
	cstr = new char[strlen];
	cstr[0] = '\0';
}



