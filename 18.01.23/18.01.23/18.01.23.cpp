﻿#include <iostream>
#include <ctime>
using namespace std;

class String
{
	char* text = nullptr;
	unsigned int length = 0;
	unsigned int capacity = 80;

public:
	String() : String("", 80) {}

	String(const char* text) : String(text, 80) {}

	String(unsigned int capacity) : String("", capacity) {}

	String(const String& original) : String(original.text, original.capacity) {}

	String(const char* text, unsigned int capacity)
	{
		SetString(text, capacity);
	}

private:
	void SetString(const char* text, unsigned int capacity = 80)
	{
		length = strlen(text);

		if (length == 0)
		{
			this->capacity = 80;
		}
		else
		{
			if (capacity > length * 10)
				capacity = length * 10;

			if (capacity <= length)
				capacity = length + 1;

			this->capacity = capacity;
		}


		if (this->text != nullptr)
			delete[] this->text;

		this->text = new char[this->capacity];
		strcpy_s(this->text, length + 1, text);
	}

public:
	~String()
	{
		if (text != nullptr)
		{
			delete[] text;
			text = nullptr;
		}
	}

	String GetString() const
	{
		String copy = text;
		return copy;
	}

	int GetLength() const
	{
		return length;
	}


	int GetCapacity() const
	{
		return capacity;
	}

	void Clear()
	{
		text[0] = '\0';
		length = 0;
	}

	void ShrinkToFit()
	{
		if (length + 1 <= capacity)
		{
			return;
		}

		capacity = length + 1;
		char* temp = new char[capacity];
		strcpy_s(temp, capacity, text);
		delete[] text;
		text = temp;
	}

	void Print() const
	{
		cout << "Text: " << text << "\n";
		cout << "Length: " << length << "\n";
		cout << "Capacity: " << capacity << "\n";
	}
	void FromKeybord()
	{
		cout << "Input text: ";
		cin >> text;
		length = strlen(text);
	}
	bool CompareTo(String text2)
	{
		int currLength = 0;
		if (length > text2.length)
		{
			currLength = length;
		}
		else
		{
			currLength = text2.length;
		}
		for (int i = 0; i < currLength; i++)
		{
			if (text[i] != text2.text[i])
			{
				cout << "not equal\n";
				return false;
			}

		}
		cout << "equal\n";
		return true;
	}
	bool Contains(String text2)
	{
		int i = 0;
		int j = 0;
		int start = 0;
		int countOfCoincidence = 0;

		while (i < length)
		{
			if (text[i] == text2.text[j])
			{
				countOfCoincidence++;
				j++;
				i++;
				if (countOfCoincidence == text2.length)
				{
					cout << "true\n";
					return true;
				}
			}
			else
			{
				start++;
				i = start;
				j = 0;
				countOfCoincidence = 0;
			}
		}
		cout << "false\n";
		return false;
	}
	void Concat(String text2)
	{
		int end = length;
		int start = 0;
		length += text2.length;
		ShrinkToFit();
		for (int i = end; i < length; i++)
		{
			text[i] = text2.text[start];
			start++;
		}
		text[length] = '\0';
	}
	bool EndsWith(String text2)
	{
		if (length < text2.length or length == 0 or text2.length == 0)
		{
			throw(length);
			return false;
		}
		int i = 0;
		int j = 0;
		int start = length - text2.length;
		for (int i = start; i < length; i++)
		{
			if (text[i] == text2.text[j])
			{
				j++;

			}
			else
			{
				cout << "false\n";
				return false;
			}
		}
		cout << "true\n";
		return true;
	}
	bool StartWith(String text2)
	{
		if (length < text2.length or length == 0 or text2.length == 0)
		{
			throw(length);
			return false;
		}
		int j = 0;
		for (int i = 0; i < text2.length; i++)
		{
			if (text[i] == text2.text[j])
			{
				j++;
			}
			else
			{
				cout << "false\n";
				return false;
			}
		}
		cout << "true\n";
		return true;
	}
	int IndexOf(char character)
	{
		for (int i = 0; i < length; i++)
		{
			if (text[i] == character)
			{
				cout << "index of character = " << i << "\n";
				return i;
			}
		}
		cout << "Not found\n";
		return -1;
	}
	int LastIndexOf(char character)
	{
		for (int i = length; i >= 0; i--)
		{
			if (text[i] == character)
			{
				cout << "index of character = " << i << "\n";
				return i;
			}
		}
		cout << "Not found\n";
		return -1;
	}
	void Remove(int index)
	{
		if (index < 0 or index >= length)
		{
			throw(index);
		}
		text[index] = '\0';
		length = index;
	}
	void Remove(int start, int count)
	{
		if (start < 0 or start >= length or start + count > length)
		{
			throw(start);
		}
		int j = start + count;
		for (int i = start; i < length; i++)
		{
			text[i] = text[j];
			j++;

		}
		length = length - count;
	}
	void Replace(char oldChar, char newChar)
	{
		for (int i = 0; i < length; i++)
		{
			if (text[i] == oldChar)
			{
				text[i] = newChar;
			}
		}
	}
	String ToLower()
	{
		String lowerString = String(text, capacity);
		for (int i = 0; i < length; i++)
		{
			if (lowerString.text[i] >= 65 and lowerString.text[i] <= 90)
			{
				lowerString.text[i] = char((int)lowerString.text[i] + 32);
			}
		}
		return lowerString;
	}
	String ToUpper()
	{
		String upperString = String(text, capacity);
		for (int i = 0; i < length; i++)
		{
			if (upperString.text[i] >= 97 and upperString.text[i] <= 122)
			{
				upperString.text[i] = char((int)upperString.text[i] - 32);
			}
		}
		return upperString;
	}
	void Reverse()
	{
		char temp;
		int end = length - 1;
		for (int i = 0; i < length / 2; i++)
		{
			temp = text[end];
			text[end] = text[i];
			text[i] = temp;
			end--;
		}
	}
	void SortAZ()
	{
		int temp;
		int i = 0;
		int j = 1;
		int countOfCoincidence = 0;
		while (countOfCoincidence < length)
		{
			if (text[i] > text[j] and j < length)
			{
				temp = text[i];
				text[i] = text[j];
				text[j] = temp;
				i++;
				j++;
				countOfCoincidence = 0;
			}
			else if (j == length)
			{
				i = 0;
				j = 1;
			}
			else
			{
				i++;
				j++;
				countOfCoincidence++;
			}
		}
	}
	void SortZA()
	{
		int temp;
		int i = 0;
		int j = 1;
		int countOfCoincidence = 0;
		while (countOfCoincidence < length)
		{
			if (text[i] < text[j] and j < length)
			{
				temp = text[i];
				text[i] = text[j];
				text[j] = temp;
				i++;
				j++;
				countOfCoincidence = 0;
			}
			else if (j == length)
			{
				i = 0;
				j = 1;
			}
			else
			{
				i++;
				j++;
				countOfCoincidence++;
			}
		}
	}
	void Shuffle()
	{
		for (int i = 0; i < length; i++)
		{
			int x = rand() % length;
			int y = rand() % length;
			int temp;
			temp = text[x];
			text[x] = text[y];
			text[y] = temp;
		}
	}
	void RandomFill()
	{
		length = capacity;
		ShrinkToFit();
		for (int i = 0; i < capacity; i++)
		{
			int random = 65 + rand() % (128 - 65 + 1);
			if ((char)random == '0' and text[i - 1] == '\\')
			{
				continue;
			}
			text[i] = (char)random;
		}
	}
};

int main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL));

	String d("Sasha", 30);
	String b("Sasha", 20);
	char character = 'A';
	char oldChar = 'a';
	char newChar = 'b';
	int index = 3;
	int start = 3;
	int count = 2;
	d.RandomFill();
	d.Print();


	e.Print();*/
}