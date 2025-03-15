#pragma
#include <iostream>


namespace myStd
{
	int strlen(const char* str)
	{
		int count = 0;
		for (;;) {
			if (str[count] == '\0')
				return count;
			count++;
		}
	}

	void strcpy_s(char* str1, int size, const char* str2)
	{
		for (int i = 0; i <= size; i++) {
			str1[i] = str2[i];
		}
	}

	class String
	{
	public:
		String() : sizeValue(0), capacityValue(15) {
			str = new char[capacityValue];
			str[0] = '\0';
		};
		String(const char* s) : str(nullptr), sizeValue(strlen(s)), capacityValue(15) {
			while (capacityValue <= sizeValue)
				capacityValue += 16;
			str = new char[capacityValue];
			strcpy_s(str, sizeValue, s);
		}
		String(const String& other) : sizeValue(other.sizeValue), capacityValue(other.capacityValue) {
			str = new char[capacityValue];
			strcpy_s(str, sizeValue, other.str);
		};
		String(String&& other) noexcept : sizeValue(other.sizeValue), capacityValue(other.capacityValue) {
			str = other.str;
			other.str = nullptr;
			other.sizeValue = 0;
			other.capacityValue = 0;
		}
		~String() { delete[] str; };

		String& operator=(const char* s);
		String& operator=(const String& other);
		String& operator=(String&& other) noexcept;
		String& operator+=(const char* s);
		String operator+(const char* s);
		char& operator[](int index);
		bool operator==(String& other);

		int size() { return sizeValue; };
		int capacity() { return capacityValue; };
		void push_back(char s);
		void pop_back();
		char& at(int index);

		const char* c_str() const {
			if (str == nullptr)
				return "";
			return str;
		}

	private:
		char* str;
		int sizeValue;
		int capacityValue;

		void resizeString(bool flag);
	};

	String& String::operator=(const char* s)
	{
		delete[] str;
		sizeValue = strlen(s);
		while (capacityValue <= sizeValue)
			capacityValue += 16;
		str = new char[capacityValue];
		strcpy_s(str, sizeValue, s);
		return *this;
	}

	String& String::operator=(const String& other)
	{
		delete[] str;
		sizeValue = other.sizeValue;
		capacityValue = other.capacityValue;
		str = new char[capacityValue];
		strcpy_s(str, sizeValue, other.str);
		return *this;
	}

	String& String::operator=(String&& other) noexcept
	{
		sizeValue = other.sizeValue;
		capacityValue = other.capacityValue;
		str = other.str;
		other.str = nullptr;
		other.sizeValue = 0;
		other.capacityValue = 0;
		return *this;
	}

	String& String::operator+=(const char* s)
	{
		sizeValue += strlen(s);
		resizeString(true);
		for (int i = sizeValue - strlen(s), j = 0; i < sizeValue; i++, j++) {
			str[i] = s[j];
		}
		str[sizeValue] = '\0';
		return *this;
	}

	String String::operator+(const char* s)
	{
		String temp = *this;
		temp.sizeValue += strlen(s);
		for (int i = temp.sizeValue - strlen(s), j = 0; i < temp.sizeValue; i++, j++) {
			temp.str[i] = s[j];
		}
		temp.str[temp.sizeValue] = '\0';
		return temp;
	}

	bool String::operator==(String& other)
	{
		if (sizeValue != other.sizeValue)
			return 0;

		for (int i = 0; i < sizeValue; i++) {
			if (str[i] != other.str[i])
				return 0;
		}
		return 1;
	}

	char& String::operator[](int index)
	{
		if (index >= 0 && index < sizeValue) {
			return str[index];
		}
		std::cout << "Index out of range 'at()'" << std::endl;
	}

	void String::resizeString(bool flag)
	{
		if (flag)
			while (capacityValue <= sizeValue)
				capacityValue += 16;
		else
			while (capacityValue >= sizeValue)
				capacityValue -= 16;
		char* newStr = new char[capacityValue];
		for (int i = 0; i < sizeValue + 1; i++) {
			newStr[i] = str[i];
		}
		delete[] str;
		str = newStr;
	}

	char& String::at(int index)
	{
		if (index >= 0 && index < sizeValue) {
			return str[index];
		}
		std::cout << "Index out of range 'at()'" << std::endl;
	}

	void String::push_back(char s)
	{
		sizeValue++;
		if (capacityValue <= sizeValue) {
			resizeString(true);
		}
		str[sizeValue - 1] = s;
		str[sizeValue] = '\0';
	}

	void String::pop_back()
	{
		String temp;
		for (int i = 0; i < sizeValue - 1; i++) {
			temp.str[i] = str[i];
		}
		temp.str[sizeValue - 1] = '\0';
		strcpy_s(str, sizeValue, temp.str);
		sizeValue--;
	}
}