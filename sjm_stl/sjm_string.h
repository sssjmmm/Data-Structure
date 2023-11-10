#ifndef _SJM_STRING
#define _SJM_STRING

#define STRING_DEFAULT_SIZE 50

#include<iostream>

class String
{
private:
	char* elements;
	int size;
	int capacity;

	//扩容
	void expand();
public:
	//求指定字符串常量的长度
	static int length_of_str(const char* ptr);
	//判断是否为数字
	static inline bool isdigit(char word)
	{
		return word >= '0' && word <= '9';
	}
	//判断是否为大写字母
	static inline bool isupper(char word)
	{
		return word >= 'A' && word <= 'Z';
	}
	//判断是否为小写字母
	static inline bool islower(char word)
	{
		return word >= 'a' && word <= 'z';
	}
	//判断是否为字母
	static inline bool isalpha(char word)
	{
		return isupper(word) || islower(word);
	}
	//判断是否为空
	static inline bool isblank(char word)
	{
		return word == '\0';
	}
public:
	//默认构造函数
	String();
	//复制构造函数
	String(const String&);
	//字符串常量方式的构造
	String(const char*);
	//指定长度的构造方式
	String(const char*, int);
	//字符成倍的构造
	String(int, char);

	//析构函数
	~String();

	//重载取下标运算符
	inline char& operator[](int index);
	//重载等号运算符
	String& operator=(const String& s);
	//重载字符串常量的等号运算符
	String& operator=(const char*);
	//重载输入输出
	friend std::istream& operator>>(std::istream& in, String& s);
	friend std::ostream& operator<<(std::ostream& out, const String& s);
	//重载==运算符
	bool operator==(const String& s);
	//重载+运算符
	String operator+(const String& s);
	//重载+=运算符
	String& operator+=(const String& s);

	//重载+运算符 对于char
	String operator+(const char& ch);
	//重载+=运算符 对于char
	String& operator+=(const char& ch);

	//清空字符串
	void clear();

	//返回字符串常量
	const char* c_str()const;

	//返回字符串长度
	int length()const;

	//友元类
	friend class BigInterger;
};

//默认构造函数
String::String()
{
	this->capacity = STRING_DEFAULT_SIZE;
	this->size = 0;
	//根据默认容量大小分配空间
	this->elements = new char[capacity];
	this->elements[0] = '\0';
}

//复制构造函数
String::String(const String& s)
{
	this->capacity = s.capacity;
	this->size = s.size;
	//分配空间
	this->elements = new char[capacity];


	//复制
	for (int i = 0; i <= size && i < capacity; ++i)
		this->elements[i] = s.elements[i];
}

//字符串常量方式的构造
String::String(const char* s)
{
	//获取字符串常量长度
	int size = 0;
	while (s[size] != '\0')
		size++;

	this->size = size;
	this->capacity = (size / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	this->elements = new char[capacity];

	//一一复制
	for (int i = 0; i <= size; ++i)
		this->elements[i] = s[i];
}

//指定长度的构造方式
String::String(const char* s, int length)
{
	int strLength = this->length_of_str(s);
	this->capacity = (length / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	//计算有效长度
	if (strLength >= length)
		this->size = length;
	else
		this->size = strLength;
	//申请空间
	this->elements = new char[capacity];
	for (int i = 0; i < size; ++i)
		this->elements[i] = s[i];
	this->elements[size] = '\0';
}

//字符成倍的构造
String::String(int num, char word)
{
	this->size = num;
	this->capacity = (size / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	this->elements = new char[capacity];
	for (int i = 0; i < size; ++i)
		this->elements[i] = word;
	this->elements[size] = '\0';

}

//析构函数
String::~String()
{
	delete[]elements;
}

//重载取下标运算符
inline char& String::operator[](int index)
{
	if (index < 0 || index >= size)
		cout << "存取位置过大！";

	return elements[index];
}

//重载等号运算符
String& String::operator=(const String& s)
{
	if (this->elements == s.elements)
		return *this;

	//清空所有元素
	delete[] elements;

	//一一对应
	this->capacity = s.capacity;
	this->size = s.size;
	//分配空间
	this->elements = new char[capacity];


	//复制
	for (int i = 0; i <= size && i < capacity; ++i)
		this->elements[i] = s.elements[i];

	return *this;
}

//重载字符串常量的等号运算符
String& String::operator=(const char* s)
{
	//清空所有元素
	delete[] elements;

	//获取字符串常量长度
	int size = 0;
	while (s[size] != '\0')
		size++;

	this->size = size;
	this->capacity = (size / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	this->elements = new char[capacity];

	//一一复制
	for (int i = 0; i <= size; ++i)
		this->elements[i] = s[i];

	return *this;
}


//清空字符串
void String::clear()
{
	//清空所有元素
	delete[] elements;

	//调用默认构造函数
	this->capacity = STRING_DEFAULT_SIZE;
	this->size = 0;
	//根据默认容量大小分配空间
	this->elements = new char[capacity];

}

//扩大容量
void String::expand()
{
	this->capacity = this->capacity + STRING_DEFAULT_SIZE;

	char* oldElements = this->elements;

	//复制
	this->elements = new char[capacity];
	for (int i = 0; i <= size && i < capacity; ++i)
		elements[i] = oldElements[i];

	delete[] oldElements;
}

std::istream& operator>>(std::istream& in, String& s)
{
	in >> s.elements;
	//注意需要更改size
	s.size = s.length_of_str(s.elements);
	return in;
}

std::ostream& operator<<(std::ostream& out, const String& s)
{
	out << s.elements;
	return out;
}

//重载==运算符
bool String::operator==(const String& s)
{
	//判断长度
	if (this->size != s.size)
		return false;
	//逐一对比
	for (int i = 0; i < this->size; ++i)
		if (this->elements[i] != s.elements[i])
			return false;

	return true;
}

//重载+运算符
String String::operator+(const String& s)
{
	String str(this->elements, this->size + s.size);
	str.size = this->size + s.size;
	for (int i = this->size; i < str.size; ++i)
		str.elements[i] = s.elements[i - this->size];
	str.elements[str.size] = '\0';
	return str;
}

String String::operator+(const char& ch)
{
	String str(this->elements, this->size + 1);
	str.size = this->size + 1;
	str.elements[str.size - 1] = ch;
	str.elements[str.size] = '\0';
	return str;
}

//重载+=运算符
String& String::operator+=(const String& s)
{
	this->capacity = ((this->size + s.size) / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	char* newStr = new char[capacity];
	for (int i = 0; i < this->size; ++i)
		newStr[i] = this->elements[i];
	this->size += s.size;
	for (int i = this->size - s.size; i < this->size; ++i)
		newStr[i] = s.elements[i - this->size + s.size];
	newStr[this->size] = '\0';
	delete this->elements;
	this->elements = newStr;
	return *this;
}

String& String::operator+=(const char& ch)
{
	this->capacity = ((this->size + 1) / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	char* newStr = new char[capacity];
	for (int i = 0; i < this->size; ++i)
		newStr[i] = this->elements[i];
	this->size += 1;
	newStr[this->size - 1] = ch;
	newStr[this->size] = '\0';
	delete this->elements;
	this->elements = newStr;
	return *this;
}

//求指定字符串常量的长度
int String::length_of_str(const char* ptr)
{
	int size = 0;
	while (ptr[size] != '\0')
		++size;
	return size;
}

//返回字符串常量
const char* String::c_str()const
{
	return elements;
}

int String::length()const
{
	return this->length_of_str(this->c_str());
}




#endif // !_MY_STRING

