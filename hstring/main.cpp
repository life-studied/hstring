#include"hstring.h"
#include<string>
using namespace m_hstring;
using namespace std;
int main()
{
	hstring hstr = "fhdskljagfhaslkfdjvbnapoisrefhasd;lnvcsfd;jghk12432uy4132947895y3wqieuh980723qy54rhure3w";
	cout << hstr << endl;
	const char* ptr = "f";

	size_t res{};
	if ((res = hstr.find(ptr)) != hstring::npos)
		cout <<"index is: " << res << endl;
	else
		cout << "could not find the index" << endl;
	return 0;
}