#include"hstring.h"
#include<string>
using namespace m_hstring;
using namespace std;
int main()
{
	hstring hstr1 = "jj";
	hstring hstr2 = "sd";
	hstr1 += hstr2;
	cout << hstr1;

	return 0;
}