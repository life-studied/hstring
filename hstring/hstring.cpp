#include"hstring.h"
using namespace m_hstring;
Memory_Pool* hstring::only_pool = new Memory_Pool;
int Memory_Pool::Element::num = 0;

