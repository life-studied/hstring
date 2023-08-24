#include <vector>
#include <cstring>
#include"hstring.h"
using namespace m_hstring;
Memory_Pool* hstring::only_pool = Memory_Pool::getInstance();
int Memory_Pool::Element::num = 0;
const size_t hstring::npos = SIZE_MAX;

hstring& m_hstring::hstring::operator=(const char* str)
{
    this->only_pool->deleteMemory(this->Number);
    this->Number = this->only_pool->getMemory(length(str), str);
    this->len = length(str);
    return *this;
}

hstring& m_hstring::hstring::operator=(hstring hstr)
{
    this->only_pool->deleteMemory(this->Number);
    this->Number = this->only_pool->getMemory(hstr.len, hstr.c_str());
    this->len = hstr.len;
    return *this;
}

char& m_hstring::hstring::operator[](int n)
{
    assert(len > n);
    char* temp = only_pool->search(Number);
    return temp[n];
}

hstring& m_hstring::hstring::operator+=(hstring& hstr2)
{
    *this = *this + hstr2;
    return *this;
}

const char* m_hstring::hstring::c_str() const
{
    return only_pool->search(Number);
}

size_t m_hstring::hstring::find(hstring hstr)
{ 
    size_t res{};
    if ((res=kmp(hstr.c_str(), hstr.len - 1, this->c_str(), this->len - 1)) == -1)
        res = npos;
    return res;
}

void m_hstring::hstring::SetStr(const char* str)
{
	*this = str;
}

void m_hstring::hstring::swap(hstring& hstr2)
{
	int temp_len = this->len;
	int temp_num = this->Number;
	this->len = hstr2.len;
	hstr2.len = temp_len;
	this->Number = hstr2.Number;
	hstr2.Number = temp_num;
}

size_t m_hstring::hstring::size()
{
    return size_t(len);
}

bool m_hstring::hstring::empty()
{
    return len == 0;
}

void m_hstring::hstring::clear()
{
    (*this) = "";
}

size_t m_hstring::hstring::kmp(const char* p, int len1, const char* s, int len2)
{
    std::vector<int> next(len1 + 1);
    getNext(p, len1, next);

    int i = 0, j = 0;
    while (i < len2 && j < len1) {
        if (j == -1 || s[i] == p[j]) {
            i++;
            j++;
        }
        else {
            j = next[j];
        }
    }

    if (j == len1) {
        return i - j;  // Æ¥Åä³É¹¦£¬·µ»ØÆ¥ÅäÆðÊ¼Î»ÖÃ
    }
    else {
        return -1;     // Æ¥ÅäÊ§°Ü£¬·µ»Ø-1
    }
}

void m_hstring::hstring::getNext(const char* p, int len, std::vector<int>& next)
{
    int i = 0, j = -1;
    next[0] = -1;

    while (i < len) {
        if (j == -1 || p[i] == p[j]) {
            i++;
            j++;
            next[i] = j;
        }
        else {
            j = next[j];
        }
    }
}


hstring m_hstring::operator+(hstring& hstr1, hstring& hstr2)
{
    int fulllen = hstr1.len + hstr2.len;
    char* t = new char[fulllen];
    memcpy(t, hstr1.c_str(), hstr1.len - 1);
    memcpy(t + hstr1.len - 1, hstr2.c_str(), hstr2.len);
    hstring temp = hstring(t);
    delete[] t;
    return temp;
}

bool m_hstring::operator==(hstring& hstr1, hstring& hstr2)
{
    const char* ptr1 = hstr1.c_str();
    const char* ptr2 = hstr2.c_str();
    return strcmp(ptr1, ptr2) == 0;
}

bool m_hstring::operator!=(hstring& hstr1, hstring& hstr2)
{
    const char* ptr1 = hstr1.c_str();
    const char* ptr2 = hstr2.c_str();
    return strcmp(ptr1, ptr2) != 0;
}

bool m_hstring::operator>(hstring& hstr1, hstring& hstr2)
{
    const char* ptr1 = hstr1.c_str();
    const char* ptr2 = hstr2.c_str();
    return strcmp(ptr1, ptr2) > 0;
}

bool m_hstring::operator<(hstring& hstr1, hstring& hstr2)
{
    const char* ptr1 = hstr1.c_str();
    const char* ptr2 = hstr2.c_str();
    return strcmp(ptr1, ptr2) < 0;
}

std::ostream& m_hstring::operator<<(std::ostream& out, hstring& hstr)
{
    std::cout << hstr.c_str();
    return out;
}

std::istream& m_hstring::operator>>(std::istream& in, hstring& hstr)
{
    std::cin.getline(hstring::only_pool->search(hstr.Number), 50);
    return in;
}

void m_hstring::swap(hstring& h1, hstring& h2)
{
	h1.swap(h2);
}

void m_hstring::Memory_Pool::Element::setStr(const char* str, int len)
{
	memcpy(piece, str, len);
}

void m_hstring::Memory_Pool::Element::clean_ptr(Element* aim)
{
	if (aim->pre)	aim->pre->next = aim->next;
	if (aim->next)	aim->next->pre = aim->pre;
	aim->next = nullptr;
	aim->pre = nullptr;
}

void m_hstring::Memory_Pool::Element::link_ptr(Element* aim1, Element* aim2)
{
	if (aim2->pre) { aim2->pre->next = aim1; }
	aim1->pre = aim2->pre;
	if (aim1->next) { aim1->next->pre = aim2; }
	aim2->next = aim1->next;
	aim1->next = aim2;
	aim2->pre = aim1;
}

void m_hstring::Memory_Pool::Element::clean_ptr()
{
	if (this->pre)	this->pre->next = this->next;
	if (this->next)	this->next->pre = this->pre;
	this->next = nullptr;
	this->pre = nullptr;
}

Memory_Pool* m_hstring::Memory_Pool::getInstance()
{
    static Memory_Pool myPool;
    return &myPool;
}

m_hstring::Memory_Pool::Memory_Pool() :used_pieces(nullptr)
{
    free_pieces = new Element();
    Element* temp_piece = free_pieces;
    for (int i = 1; i < piecenum; i++)
    {
        temp_piece->next = new Element();
        temp_piece->next->pre = temp_piece;
        temp_piece = temp_piece->next;
    }
}

int m_hstring::Memory_Pool::getMemory(int size, const char* str)
{
    Element* temp;
    if (size > free_pieces->standardSize())
    {
        temp = new Element(size);
    }
    else
    {
        assert(isfull());
        temp = pop(free_pieces->Number, free);
    }
    temp->setStr(str, size);
    push(temp, used);
    return temp->Number;
}

void m_hstring::Memory_Pool::deleteMemory(int numb)
{
    Element* t = pop(numb, used);
    push(t, free);
}

char* m_hstring::Memory_Pool::search(int numb)
{
    Element* t = search(numb, used);
    return t->piece;
}

Memory_Pool::Element* m_hstring::Memory_Pool::pop(int aim, source status)
{
    Element* temp = search(aim, status);
    assert(temp);
    if (status == used)
    {
        if (temp == used_pieces)
            used_pieces = used_pieces->next;
        temp->clean_ptr();
    }
    else
    {
        if (temp == free_pieces)
            free_pieces = free_pieces->next;
        temp->clean_ptr();
    }
    return temp;
}

void m_hstring::Memory_Pool::push(Element* temp, source aim)
{
    if (aim == free)
    {
        if (free_pieces)
            Element::link_ptr(free_pieces, temp);
        else
            free_pieces = temp;
    }
    else
    {
        if (used_pieces)
            Element::link_ptr(used_pieces, temp);
        else
            used_pieces = temp;
    }
    return;
}

Memory_Pool::Element* m_hstring::Memory_Pool::search(int aim, source status)
{
    Element* temp;
    if (status == free)
    {
        temp = free_pieces;
        if (temp->Number == aim)
        {
            return temp;
        }
    }
    else
    {
        temp = used_pieces;
        if (temp->Number == aim)
        {
            return temp;
        }
    }
    temp = temp->next;
    while (temp != nullptr)
    {
        if (temp->Number == aim)
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}