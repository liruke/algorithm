#include"string.h"

namespace lyrics
{
	const size_t string::npos = 1;
	string::iterator string::begin()
	{
		return _str;
	}
	string::iterator string::end()
	{
		return _str + _size;
	}
	string::const_iterator string::begin()const
	{
		return _str;
	}
	string::const_iterator string::end()const
	{
		return _str + _size;
	}

	//���캯��
	string::string(const char* str)
		:_size(strlen(str))
	{
		_str = new char[_size + 1];
		_capacity = _size;
		strcpy(_str, str);
	}
	//���
	string::string(const string& s)
	{
		_str = new char[s._capacity + 1];
		strcpy(_str, s._str);
		_size = s._size;
		_capacity = s._capacity;
	}

	//��������
	string::~string()
	{
		delete[] _str;
		_str = nullptr;
		_size = 0;
		_capacity = 0;
	}
	//����ͷָ��
	const char* string::c_str() const
	{
		return _str;
	}

	//���ش�С
	size_t string::size() const
	{
		return _size;
	}
	//���������
	char& string::operator[](size_t pos)
	{
		return _str[pos];
	}
	const char& string::operator[](size_t pos)const
	{
		return _str[pos];
	}
	//�ռ�����
	void string::reserve(size_t n)
	{
		if (n > _capacity)
		{
			//�࿪��һ���ռ�
			char* tmp = new char[n + 1];
			//��������
			strcpy(tmp, _str);
			//�ͷ���ǰ�ռ�
			delete[] _str;
			//���¿ռ�
			_str = tmp;
			_capacity = n;
		}
	}
	//β��һ���ַ�
	void string::push_back(char ch)
	{
		if (_size == _capacity)
		{
			size_t newpacity = _capacity == 0 ? 4 : _capacity * 2;
			reserve(newpacity);
		}
		_str[_size++] = ch;
		_str[_size] = '\0';
	}

	//β��һ���ַ���
	void string::append(const char* str)
	{
		size_t len = strlen(str);
		if (_capacity == _size)
		{
			reserve(len + _size);
		}
		strcpy(_str + _size, str);
		_size += len;
	}

	//���������+=����
	string& string::operator+=(char ch)
	{
		push_back(ch);
		return *this;
	}
	string& string::operator+=(const char* str)
	{
		append(str);
		return *this;
	}
	//�������������һ���ַ����Ͳ���һ���ַ�
	void string::insert(size_t pos, char ch)
	{
		if (_size == _capacity)
		{
			size_t newpacity = _capacity == 0 ? 4 : _capacity * 2;
			reserve(newpacity);
		}
		int end = (int)_size;
		while (end > (int)pos)
		{
			_str[end + 1] = _str[end];
			end--;
		}
		_str[pos] = ch;
		_size++;
	}
	void string::insert(size_t pos, const char* str)
	{
		size_t len = strlen(str);
		if (_capacity == _size)
		{
			reserve(len + _size);
		}
		//�����һ��λ�õ��ַ���ʼ����
		size_t end = len - 1;//len���ַ��ĳ��ȣ�����len-1�������һ���ַ���λ��
		while (end >= 0)
		{
			insert(pos, str[end]);
			end--;
		}
	}
	//ɾ��ĳ���ַ�
	void string::erase(size_t pos, size_t len)
	{
		assert(pos < _size);
		if (len >= _size - pos)
		{
			_str[pos] = '\0';
			_size = pos;
		}
		else
		{
			strcpy(_str + pos, _str + pos + len);
			_size -= len;
		}
	}
	//����ĳ���ַ��������ַ�
	size_t string::find(char ch, size_t pos)
	{
		for (size_t i = pos;i < _size;i++)
		{
			if (_str[i] == ch)
			{
				return i;
			}
		}
		return  npos;
	}
	size_t string::find(const char* str, size_t pos)
	{
		const char* sub = strstr(_str + pos, str);
		return sub - _str;
	}
	//��������
	void string::swap(string& s)
	{
		std::swap(s._str, _str);
		std::swap(_capacity, s._capacity);
		std::swap(_size, s._size);
	}
	//ȡ�Ӵ�
	string string::substr(size_t pos, size_t len)
	{
		if (len > _size - pos)
		{
			string sub(_str + pos);
			return sub;
		}
		else
		{
			string sub;
			sub.reserve(len);
			for (size_t i = 0;i < len;i++)
			{
				sub += _str[pos + i];
			}
			return sub;
		}
	}
	//�ȽϺ������������
	bool string::operator<(const string& s)const
	{
		return strcmp(_str, s._str) < 0;
	}
	bool string::operator<=(const string& s)const
	{
		return *this < s || *this == s;
	}
	bool string::operator>(const string& s)const
	{
		return !(*this <= s);
	}
	bool string::operator>=(const string& s)const
	{
		return !(*this < s);
	}
	bool string::operator==(const string& s)const
	{
		return strcmp(_str, s._str) == 0;
	}
	void string::clear()
	{
		_str[0] = '\0';
		_size = 0;
	}

	//�ǳ�Ա�����������������������ȡ
	istream& operator>>(istream& is, string& str)
	{
		str.clear();
		char ch = is.get();
		while (ch != ' ' && ch != '\n')
		{
			str += ch;
		}
		return is;
	}
	ostream& operator<<(ostream& os, string& str)
	{
		for (size_t i = 0;i < str.size();i++)
		{
			os << str[i];
		}
		return os;
	}

	string& string::operator=(const string& s)
	{
		char* tmp = new char[s._capacity + 1];
		strcpy(tmp, s._str);
		delete[] _str;
		_str = tmp;
		_size = s._size;
		_capacity = s._capacity;
		return *this;
	}
}
