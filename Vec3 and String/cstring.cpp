#include "cstring.h"

String::String(const String & str)
{
	size = str.size;
	mem_size = size + 1;

	string = new char[mem_size];

	for (int i = 0; i < mem_size; i++)
		string[i] = str.string[i];
}

String::String(const char* str)
{
	while (*str++)
		size++;

	mem_size = size + 1;
	string = new char[mem_size];
	str = str - mem_size;

	for (int i = 0; i < mem_size; i++)
		string[i] = str[i];
}

String::~String()
{
	delete[] string;
}

String String::operator+(const String & str) const
{
	short new_size = size + str.size + 1;

	char* new_string = new char[new_size + 1];

	for (int i = 0; i < size; i++)
		new_string[i] = string[i];
	for (int i = size; i < new_size; i++)
		new_string[i] = str.string[i - size];

	String ret = String(new_string);

	return ret;
}

bool String::operator==(const char * str) const
{
	short other_str_size = 0;
	while (*str++)
		other_str_size++;

	if (size != other_str_size)
		return false;

	str = str - (other_str_size + 1);
	for (int i = 0; i < size; i++)
		if (string[i] != str[i])
			return false;

	return true;
}

bool String::operator==(const String & str) const
{
	if (size != str.size)
		return false;

	for (int i = 0; i < size; i++)
		if (string[i] != str.string[i])
			return false;

	return true;
}

String String::operator=(const String & str)
{
	size = str.size;
	mem_size = str.mem_size;
	delete[] string;
	string = new char[mem_size];

	for (int i = 0; i < mem_size; i++)
		string[i] = str.string[i];

	return *this;
}

short String::length() const
{
	return size;
}

void String::clear()
{
	size = 0;
}

std::ostream & operator<<(std::ostream & out, String & str)
{
	if (str.size == 0)
		return out;

	out << str.string;
	return out;
}
