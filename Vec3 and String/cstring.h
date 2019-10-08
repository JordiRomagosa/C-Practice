#include <iostream>
class String
{

private:
	char * string = nullptr;
	short size = 0;
	short mem_size  = 0;
	
public:
	String() {};
	String(const String & str);
	String(const char * str);
	virtual ~String();

	char * operator +(const String & str) const;
	bool operator ==(const char * str) const;
	bool operator ==(const String & str) const;
	String & operator =(const String & str);
	friend std::ostream & operator <<(std::ostream & out, String & str);

	short length() const;
	void clear();
};

