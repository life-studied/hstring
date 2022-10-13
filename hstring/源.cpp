#include"hstring.h"
#include<string>
using namespace m_hstring;
using namespace std;
int main()
{
	
	hstring h1 = "hello";
	hstring h2 = "fm";
	std::cout << "h1:" << h1 << "h2:" << h2 << endl;
	swap(h1, h2);
	std::cout << "h1:" << h1 << "h2:" << h2 << endl;
	h2.find(h1);
	return 0;
}