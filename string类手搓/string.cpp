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

	//构造函数
	string::string(const char* str)
		:_size(strlen(str))
	{
		_str = new char[_size + 1];
		_capacity = _size;
		strcpy(_str, str);
	}
	//深拷贝
	string::string(const string& s)
	{
		_str = new char[s._capacity + 1];
		strcpy(_str, s._str);
		_size = s._size;
		_capacity = s._capacity;
	}

	//析构函数
	string::~string()
	{
		delete[] _str;
		_str = nullptr;
		_size = 0;
		_capacity = 0;
	}
	//返回头指针
	const char* string::c_str() const
	{
		return _str;
	}

	//返回大小
	size_t string::size() const
	{
		return _size;
	}
	//运算符重载
	char& string::operator[](size_t pos)
	{
		return _str[pos];
	}
	const char& string::operator[](size_t pos)const
	{
		return _str[pos];
	}
	//空间扩容
	void string::reserve(size_t n)
	{
		if (n > _capacity)
		{
			//多开辟一个空间
			char* tmp = new char[n + 1];
			//拷贝数据
			strcpy(tmp, _str);
			//释放以前空间
			delete[] _str;
			//更新空间
			_str = tmp;
			_capacity = n;
		}
	}
	//尾插一个字符
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

	//尾插一个字符串
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

	//运算符重载+=操作
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
	//插入操作，插入一个字符串和插入一个字符
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
		//从最后一个位置的字符开始插入
		size_t end = len - 1;//len是字符的长度，所以len-1就是最后一个字符的位置
		while (end >= 0)
		{
			insert(pos, str[end]);
			end--;
		}
	}
	//删除某段字符
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
	//查找某个字符串或者字符
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
	//交换函数
	void string::swap(string& s)
	{
		std::swap(s._str, _str);
		std::swap(_capacity, s._capacity);
		std::swap(_size, s._size);
	}
	//取子串
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
	//比较函数运算符重载
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

	//非成员函数，，重载流插入和流提取
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
