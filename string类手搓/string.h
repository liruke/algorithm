#pragma once
#pragma once
#define _CRT_SECURE_NO_WARNINGS 0
#include<iostream>
#include<assert.h>
using namespace std;
namespace lyrics
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		//迭代器
		iterator begin();
		iterator end();
		const_iterator begin()const;
		const_iterator end()const;
		//构造函数
		string(const char* str = "");
		string(const string& s);
		//析构函数
		~string();
		//
		const char* c_str() const;
		//返回大小
		size_t size() const;
		//运算符重载
		char& operator[](size_t pos);
		const char& operator[](size_t pos)const;
		//空间扩容
		void reserve(size_t n);
		//尾插一个字符
		void push_back(char ch);
		//尾插一个字符串
		void append(const char* str);
		//运算符重载+=操作
		string& operator+=(char ch);
		string& operator+=(const char* str);
		//插入操作，插入一个字符串和插入一个字符
		void insert(size_t pos, char ch);
		void insert(size_t pos, const char* str);
		//删除某段字符
		void erase(size_t pos = 0, size_t len = npos);

		//查找某个字符串或者字符
		size_t find(char ch, size_t pos = 0);
		size_t find(const char* str, size_t pos = 0);
		//赋值拷贝
		string& operator=(const string& s);
		//交换函数
		void swap(string& s);
		//取子串
		string substr(size_t pos = 0, size_t len = npos);
		//比较函数运算符重载
		bool operator<(const string& s)const;
		bool operator<=(const string& s)const;
		bool operator>(const string& s)const;
		bool operator>=(const string& s)const;
		bool operator==(const string& s)const;
		//清理
		void clear();
	private:
		size_t _size;
		size_t _capacity;

		char* _str;
		const static size_t npos;
	};
	//非成员函数，，重载流插入和流提取
	istream& operator>>(istream& is, string& str);
	ostream& operator<<(ostream& is, string& str);
}
