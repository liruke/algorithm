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
		//������
		iterator begin();
		iterator end();
		const_iterator begin()const;
		const_iterator end()const;
		//���캯��
		string(const char* str = "");
		string(const string& s);
		//��������
		~string();
		//
		const char* c_str() const;
		//���ش�С
		size_t size() const;
		//���������
		char& operator[](size_t pos);
		const char& operator[](size_t pos)const;
		//�ռ�����
		void reserve(size_t n);
		//β��һ���ַ�
		void push_back(char ch);
		//β��һ���ַ���
		void append(const char* str);
		//���������+=����
		string& operator+=(char ch);
		string& operator+=(const char* str);
		//�������������һ���ַ����Ͳ���һ���ַ�
		void insert(size_t pos, char ch);
		void insert(size_t pos, const char* str);
		//ɾ��ĳ���ַ�
		void erase(size_t pos = 0, size_t len = npos);

		//����ĳ���ַ��������ַ�
		size_t find(char ch, size_t pos = 0);
		size_t find(const char* str, size_t pos = 0);
		//��ֵ����
		string& operator=(const string& s);
		//��������
		void swap(string& s);
		//ȡ�Ӵ�
		string substr(size_t pos = 0, size_t len = npos);
		//�ȽϺ������������
		bool operator<(const string& s)const;
		bool operator<=(const string& s)const;
		bool operator>(const string& s)const;
		bool operator>=(const string& s)const;
		bool operator==(const string& s)const;
		//����
		void clear();
	private:
		size_t _size;
		size_t _capacity;

		char* _str;
		const static size_t npos;
	};
	//�ǳ�Ա�����������������������ȡ
	istream& operator>>(istream& is, string& str);
	ostream& operator<<(ostream& is, string& str);
}
