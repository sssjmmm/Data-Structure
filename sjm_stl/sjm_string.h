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

	//����
	void expand();
public:
	//��ָ���ַ��������ĳ���
	static int length_of_str(const char* ptr);
	//�ж��Ƿ�Ϊ����
	static inline bool isdigit(char word)
	{
		return word >= '0' && word <= '9';
	}
	//�ж��Ƿ�Ϊ��д��ĸ
	static inline bool isupper(char word)
	{
		return word >= 'A' && word <= 'Z';
	}
	//�ж��Ƿ�ΪСд��ĸ
	static inline bool islower(char word)
	{
		return word >= 'a' && word <= 'z';
	}
	//�ж��Ƿ�Ϊ��ĸ
	static inline bool isalpha(char word)
	{
		return isupper(word) || islower(word);
	}
	//�ж��Ƿ�Ϊ��
	static inline bool isblank(char word)
	{
		return word == '\0';
	}
public:
	//Ĭ�Ϲ��캯��
	String();
	//���ƹ��캯��
	String(const String&);
	//�ַ���������ʽ�Ĺ���
	String(const char*);
	//ָ�����ȵĹ��췽ʽ
	String(const char*, int);
	//�ַ��ɱ��Ĺ���
	String(int, char);

	//��������
	~String();

	//����ȡ�±������
	inline char& operator[](int index);
	//���صȺ������
	String& operator=(const String& s);
	//�����ַ��������ĵȺ������
	String& operator=(const char*);
	//�����������
	friend std::istream& operator>>(std::istream& in, String& s);
	friend std::ostream& operator<<(std::ostream& out, const String& s);
	//����==�����
	bool operator==(const String& s);
	//����+�����
	String operator+(const String& s);
	//����+=�����
	String& operator+=(const String& s);

	//����+����� ����char
	String operator+(const char& ch);
	//����+=����� ����char
	String& operator+=(const char& ch);

	//����ַ���
	void clear();

	//�����ַ�������
	const char* c_str()const;

	//�����ַ�������
	int length()const;

	//��Ԫ��
	friend class BigInterger;
};

//Ĭ�Ϲ��캯��
String::String()
{
	this->capacity = STRING_DEFAULT_SIZE;
	this->size = 0;
	//����Ĭ��������С����ռ�
	this->elements = new char[capacity];
	this->elements[0] = '\0';
}

//���ƹ��캯��
String::String(const String& s)
{
	this->capacity = s.capacity;
	this->size = s.size;
	//����ռ�
	this->elements = new char[capacity];


	//����
	for (int i = 0; i <= size && i < capacity; ++i)
		this->elements[i] = s.elements[i];
}

//�ַ���������ʽ�Ĺ���
String::String(const char* s)
{
	//��ȡ�ַ�����������
	int size = 0;
	while (s[size] != '\0')
		size++;

	this->size = size;
	this->capacity = (size / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	this->elements = new char[capacity];

	//һһ����
	for (int i = 0; i <= size; ++i)
		this->elements[i] = s[i];
}

//ָ�����ȵĹ��췽ʽ
String::String(const char* s, int length)
{
	int strLength = this->length_of_str(s);
	this->capacity = (length / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	//������Ч����
	if (strLength >= length)
		this->size = length;
	else
		this->size = strLength;
	//����ռ�
	this->elements = new char[capacity];
	for (int i = 0; i < size; ++i)
		this->elements[i] = s[i];
	this->elements[size] = '\0';
}

//�ַ��ɱ��Ĺ���
String::String(int num, char word)
{
	this->size = num;
	this->capacity = (size / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	this->elements = new char[capacity];
	for (int i = 0; i < size; ++i)
		this->elements[i] = word;
	this->elements[size] = '\0';

}

//��������
String::~String()
{
	delete[]elements;
}

//����ȡ�±������
inline char& String::operator[](int index)
{
	if (index < 0 || index >= size)
		cout << "��ȡλ�ù���";

	return elements[index];
}

//���صȺ������
String& String::operator=(const String& s)
{
	if (this->elements == s.elements)
		return *this;

	//�������Ԫ��
	delete[] elements;

	//һһ��Ӧ
	this->capacity = s.capacity;
	this->size = s.size;
	//����ռ�
	this->elements = new char[capacity];


	//����
	for (int i = 0; i <= size && i < capacity; ++i)
		this->elements[i] = s.elements[i];

	return *this;
}

//�����ַ��������ĵȺ������
String& String::operator=(const char* s)
{
	//�������Ԫ��
	delete[] elements;

	//��ȡ�ַ�����������
	int size = 0;
	while (s[size] != '\0')
		size++;

	this->size = size;
	this->capacity = (size / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	this->elements = new char[capacity];

	//һһ����
	for (int i = 0; i <= size; ++i)
		this->elements[i] = s[i];

	return *this;
}


//����ַ���
void String::clear()
{
	//�������Ԫ��
	delete[] elements;

	//����Ĭ�Ϲ��캯��
	this->capacity = STRING_DEFAULT_SIZE;
	this->size = 0;
	//����Ĭ��������С����ռ�
	this->elements = new char[capacity];

}

//��������
void String::expand()
{
	this->capacity = this->capacity + STRING_DEFAULT_SIZE;

	char* oldElements = this->elements;

	//����
	this->elements = new char[capacity];
	for (int i = 0; i <= size && i < capacity; ++i)
		elements[i] = oldElements[i];

	delete[] oldElements;
}

std::istream& operator>>(std::istream& in, String& s)
{
	in >> s.elements;
	//ע����Ҫ����size
	s.size = s.length_of_str(s.elements);
	return in;
}

std::ostream& operator<<(std::ostream& out, const String& s)
{
	out << s.elements;
	return out;
}

//����==�����
bool String::operator==(const String& s)
{
	//�жϳ���
	if (this->size != s.size)
		return false;
	//��һ�Ա�
	for (int i = 0; i < this->size; ++i)
		if (this->elements[i] != s.elements[i])
			return false;

	return true;
}

//����+�����
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

//����+=�����
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

//��ָ���ַ��������ĳ���
int String::length_of_str(const char* ptr)
{
	int size = 0;
	while (ptr[size] != '\0')
		++size;
	return size;
}

//�����ַ�������
const char* String::c_str()const
{
	return elements;
}

int String::length()const
{
	return this->length_of_str(this->c_str());
}




#endif // !_MY_STRING

