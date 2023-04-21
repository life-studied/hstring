#include"hstring.h"
using namespace m_hstring;
Memory_Pool* hstring::only_pool = Memory_Pool::getInstance();
int Memory_Pool::Element::num = 0;

