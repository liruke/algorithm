#include"string.h"



namespace lyrics
{
	void teststring1()
	{
		string s("hello");
		cout << s.c_str() << endl;
		s += " hello";
		cout << s << endl;
	}
}


int main()
{
	lyrics::teststring1();
	return 0;
}


