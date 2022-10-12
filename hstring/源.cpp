#include"hstring.h"
#include<string>
using namespace m_hstring;
using namespace std;
int main()
{
	string s1;
	string s2;
	s1 + s2;
	hstring h1 = "hello";
	hstring h2 = "fm";
	std::cout << h2;
	h2 = (h1 + h2);
	std::cout << h2;
	return 0;
}