#pragma once
#include<iostream>
#include<vector>
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
			void setStr(const char* str, int len);
			static int standardSize() { return piece_size; }
			static void clean_ptr(Element* aim);
			static void link_ptr(Element* aim1, Element* aim2);
			void clean_ptr();
		public:
			Element() : piece(new char[piece_size]), pre(nullptr), next(nullptr), msize(piece_size), Number(num) { num++; }
			Element(int size) : piece(new char[size]), pre(nullptr), next(nullptr), msize(size), Number(num) { num++; }
			Element(const Element& source) : pre(nullptr), next(nullptr), msize(source.msize), Number(num) { num++; piece = new char[msize]; memcpy(piece, source.piece, msize); }
			~Element() { delete[] piece; num--; }
		};
		Element* free_pieces;		//指向空闲内存链表
		Element* used_pieces;		//指向使用内存链表

	public:
		static Memory_Pool* getInstance();

	private:						//构造函数
		Memory_Pool();
	private:
		Memory_Pool(const Memory_Pool&) = delete;
		Memory_Pool& operator = (const Memory_Pool&) = delete;
	private:
		bool isfull() { return (bool)free_pieces; }
	public:
		int getMemory(int size = 1, const char* str = "");
		void deleteMemory(int numb);
	public:
		char* search(int numb);
	private:
		enum source { free, used };
		Element* pop(int aim, source status);
		void push(Element* temp, source aim);
		Element* search(int aim, source status);
	};

	class hstring
	{
	private:
		friend class Memory_Pool;
		static Memory_Pool* only_pool;
		unsigned short len;
		int Number;
	public:
		static const size_t npos;
	private:
		unsigned short length(const char* str)
		{
			unsigned short len{};
			while (str[len++]);
			return len;
		}
	public:
		hstring() : Number(only_pool->getMemory()),len(1) {}
		hstring(const char* str) : Number(only_pool->getMemory(len, str)),len(length(str)) {}
		hstring(char* str) : Number(only_pool->getMemory(len, str)), len(length(str)) {}
		hstring(const hstring& hstr) : Number(only_pool->getMemory(hstr.len,hstr.c_str())), len(hstr.len) {}
		~hstring() { only_pool->deleteMemory(Number); };
		hstring& operator=(const char* str);
		hstring& operator=(hstring hstr);
	public:
		char& operator[](int n);
		friend hstring operator+(hstring& hstr1, hstring& hstr2);
		friend bool operator==(hstring& hstr1, hstring& hstr2);
		friend bool operator!=(hstring& hstr1, hstring& hstr2);
		friend bool operator>(hstring& hstr1, hstring& hstr2);
		friend bool operator<(hstring& hstr1, hstring& hstr2);
		friend std::ostream& operator<<(std::ostream& out, hstring& hstr);
		friend std::istream& operator>>(std::istream& in, hstring& hstr);
		hstring& operator+=(hstring& hstr2);
		const char* c_str() const;
	public:
		size_t find(hstring hstr);
		void SetStr(const char* str);
		void swap(hstring& hstr2);
		friend void swap(hstring& h1, hstring& h2);
		size_t size();
		bool empty();
		void clear();

	private:
		size_t kmp(const char* p, int len1, const char* s, int len2);
		void getNext(const char* p, int len, std::vector<int>& next);
	};
}

