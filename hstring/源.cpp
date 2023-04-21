#include"hstring.h"
#include<string>
using namespace m_hstring;
using namespace std;
int main()
{
	
	hstring hstr = "fhdskljagfhaslkfdjvbnapoisrefhasd;lnvcsfd;jghk12432uy4132947895y3wqieuh980723qy54rhure3w";
	cout << hstr << endl;
	const char* ptr = "12432";
	cout<<hstr.find(ptr);
	//
	return 0;
}