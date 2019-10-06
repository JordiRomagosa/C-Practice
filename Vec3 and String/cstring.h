class String
{

private:
	short strlen;
	
public:
	char* cstr;
	
	String(const char* str);

	char* operator +(String& str);
	//bool operator ==(const char* str);
	short length();
	//void clear();
};

