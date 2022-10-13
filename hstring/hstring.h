#pragma once
#include<iostream>
#include<cassert>
namespace m_hstring {
	class Memory_Pool		//为了防止重复创建内存池，使用单例模式来避免
	{
	private:									//内存片相关
		static const int piecenum = 1000;		//内存片个数
		struct Element {						//内存片，采用单链表连接
			char* piece;
			Element* next;
			Element* pre;
			int Number;
			int msize;
		private:
			static int num;
		private:
			enum { piece_size = 50 };	//内存片大小
		public:
			void setStr(const char* str,int len)
			{
				memcpy(piece, str, len);
			}
			static int standardSize() { return piece_size; }
			static void clean_ptr(Element* aim)
			{
				if (aim->pre)	aim->pre->next = aim->next;
				if (aim->next)	aim->next->pre = aim->pre;
				aim->next = nullptr;
				aim->pre = nullptr;
			}
			static void link_ptr(Element* aim1, Element* aim2)
			{
				if (aim2->pre) { aim2->pre->next = aim1; }
				aim1->pre = aim2->pre;
				if (aim1->next) { aim1->next->pre = aim2; }
				aim2->next = aim1->next;
				aim1->next = aim2;
				aim2->pre = aim1;
			}
			void clean_ptr()
			{
				if (this->pre)	this->pre->next = this->next;
				if (this->next)	this->next->pre = this->pre;
				this->next = nullptr;
				this->pre = nullptr;
			}
		public:
			Element() : piece(new char[piece_size]), pre(nullptr), next(nullptr), msize(piece_size), Number(num) { num++; }
			Element(int size) : piece(new char[size]), pre(nullptr), next(nullptr), msize(size), Number(num) { num++; }
			Element(const Element& source) : pre(nullptr), next(nullptr), msize(source.msize), Number(num) { num++; piece = new char[msize]; memcpy(piece, source.piece, msize); }
			~Element() { delete[] piece; num--; }
		};
		Element* free_pieces;		//指向空闲内存链表
		Element* used_pieces;		//指向使用内存链表

	public:						//构造函数
		Memory_Pool() :used_pieces(nullptr)
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
	private:
		Memory_Pool(const Memory_Pool&) = delete;
		Memory_Pool& operator = (const Memory_Pool&) = delete;
	private:
		bool isfull() { return (bool)free_pieces; }
	public:
		int getMemory(int size = 1, const char* str = "")
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
		void deleteMemory(int numb)
		{
			Element* t = pop(numb, used);
			push(t, free);
		}
	public:
		char* search(int numb)
		{
			Element* t = search(numb, used);
			return t->piece;
		}
	private:
		enum source { free, used };
		Element* pop(int aim, source status)
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
		void push(Element* temp, source aim)
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
		Element* search(int aim, source status)
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
	};

	class hstring
	{
	private:
		friend class Memory_Pool;
		static Memory_Pool* only_pool;
		int Number;
		unsigned short len;
	private:
		unsigned short length(const char* str)
		{
			unsigned short len{};
			while (str[len++]);
			return len;
		}
	public:
		hstring() : Number(only_pool->getMemory()),len(1) {}
		hstring(const char* str) : Number(only_pool->getMemory(length(str), str)),len(length(str)) {}
		hstring(char* str) : Number(only_pool->getMemory(length(str), str)), len(length(str)) {}
		hstring(const hstring& hstr) : Number(only_pool->getMemory(hstr.len,hstr.Show())), len(hstr.len) {}
		~hstring() { only_pool->deleteMemory(Number); };
		hstring& operator=(const char* str)
		{
			this->only_pool->deleteMemory(this->Number);
			this->Number = this->only_pool->getMemory(length(str), str);
			this->len = length(str);
			return *this;
		}
		hstring& operator=(hstring hstr)
		{
			this->only_pool->deleteMemory(this->Number);
			this->Number = this->only_pool->getMemory(hstr.len, hstr.Show());
			this->len = hstr.len;
			return *this;
		}
	public:
		char& operator[](int n)
		{
			assert(len >n);
			char* temp = only_pool->search(Number);
			return temp[n];
		}
		friend hstring operator+(hstring& hstr1,hstring& hstr2)
		{
			int fulllen = hstr1.len + hstr2.len;
			char* t = new char[fulllen];
			memcpy(t, hstr1.Show(), hstr1.len-1);
			memcpy(t + hstr1.len-1, hstr2.Show(), hstr2.len);
			hstring temp = hstring(t);
			delete[] t;
			return temp;
		}
		friend std::ostream& operator<<(std::ostream& out, hstring& hstr)
		{
			std::cout << hstr.Show();
			return out;
		}
		friend std::istream& operator>>(std::istream& in, hstring& hstr) 
		{
			std::cin.getline(only_pool->search(hstr.Number), 50);
			return in;
		}
		
		const char* Show() const
		{
			return only_pool->search(Number);
		}
		int find(const char* prt) 
		{
			int l_prt = length(prt);
			return kmp(prt, l_prt-1, this->only_pool->search(Number), len-1);
		}
		int find(hstring& hstr)
		{
			return this->find(hstr.Show());
		}
		void SetStr(const char* str)
		{
			*this = str;
		}
		void swap(hstring& hstr2)
		{ 
			int temp_len = this->len;
			int temp_num = this->Number;
			this->len = hstr2.len;
			hstr2.len = temp_len;
			this->Number = hstr2.Number;
			hstr2.Number = temp_num;
		}
		friend void swap(hstring& h1, hstring& h2)
		{
			h1.swap(h2);
		}
	private:
		int kmp(const char* p,int len1, const char* s,int len2) {
			if (len2 < len1)
				return -1;
			int pmt[50]={0};
			for (int i = 0, j = 0; i < len2; ++i) {
				while (j && s[i] != p[j]) j = pmt[j - 1];
				if (s[i] == p[j]) j++;
				if (j == len1) {
					return i - j + 1;
				}
			}
			return -1;
		}
	};

	
}

