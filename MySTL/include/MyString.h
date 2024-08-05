#ifndef STRING_H
#define STRING_H


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

	class string
	{
	public:
		string() : sizeValue(0), capacityValue(15) {
			str = new char[capacityValue];
			str[0] = '\0';
		};
		string(const char* s) : str(nullptr), sizeValue(strlen(s)), capacityValue(15) {
			while (capacityValue <= sizeValue)
				capacityValue += 16;
			str = new char[capacityValue];
			strcpy_s(str, sizeValue, s);
		}
		string(const string& other) : sizeValue(other.sizeValue), capacityValue(other.capacityValue) {
			str = new char[capacityValue];
			strcpy_s(str, sizeValue, other.str);
		};
		string(string&& other) noexcept : sizeValue(other.sizeValue), capacityValue(other.capacityValue) {
			str = other.str;
			other.str = nullptr;
			other.sizeValue = 0;
			other.capacityValue = 0;
		}
		~string() { delete[] str; };

		string& operator=(const char* s);
		string& operator=(const string& other);
		string& operator=(string&& other) noexcept;
		string& operator+=(const char* s);
		string operator+(const char* s);
		char& operator[](int index);
		bool operator==(string& other);

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

	string& string::operator=(const char* s)
	{
		delete[] str;
		sizeValue = strlen(s);
		while (capacityValue <= sizeValue)
			capacityValue += 16;
		str = new char[capacityValue];
		strcpy_s(str, sizeValue, s);
		return *this;
	}

	string& string::operator=(const string& other)
	{
		delete[] str;
		sizeValue = other.sizeValue;
		capacityValue = other.capacityValue;
		str = new char[capacityValue];
		strcpy_s(str, sizeValue, other.str);
		return *this;
	}

	string& string::operator=(string&& other) noexcept
	{
		sizeValue = other.sizeValue;
		capacityValue = other.capacityValue;
		str = other.str;
		other.str = nullptr;
		other.sizeValue = 0;
		other.capacityValue = 0;
		return *this;
	}

	string& string::operator+=(const char* s)
	{
		sizeValue += strlen(s);
		resizeString(true);
		for (int i = sizeValue - strlen(s), j = 0; i < sizeValue; i++, j++) {
			str[i] = s[j];
		}
		str[sizeValue] = '\0';
		return *this;
	}

	string string::operator+(const char* s)
	{
		string temp = *this;
		temp.sizeValue += strlen(s);
		for (int i = temp.sizeValue - strlen(s), j = 0; i < temp.sizeValue; i++, j++) {
			temp.str[i] = s[j];
		}
		temp.str[temp.sizeValue] = '\0';
		return temp;
	}

	bool string::operator==(string& other)
	{
		if (sizeValue != other.sizeValue)
			return 0;

		for (int i = 0; i < sizeValue; i++) {
			if (str[i] != other.str[i])
				return 0;
		}
		return 1;
	}

	char& string::operator[](int index)
	{
		if (index >= 0 && index < sizeValue) {
			return str[index];
		}
		std::cout << "Index out of range 'at()'" << std::endl;
	}

	void string::resizeString(bool flag)
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

	char& string::at(int index)
	{
		if (index >= 0 && index < sizeValue) {
			return str[index];
		}
		std::cout << "Index out of range 'at()'" << std::endl;
	}

	void string::push_back(char s)
	{
		sizeValue++;
		if (capacityValue <= sizeValue) {
			resizeString(true);
		}
		str[sizeValue - 1] = s;
		str[sizeValue] = '\0';
	}

	void string::pop_back()
	{
		string temp;
		for (int i = 0; i < sizeValue - 1; i++) {
			temp.str[i] = str[i];
		}
		temp.str[sizeValue - 1] = '\0';
		strcpy_s(str, sizeValue, temp.str);
		sizeValue--;
	}
}

#endif