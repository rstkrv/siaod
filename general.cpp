#pragma once
#include "general.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include "task5.h"
#include "task6.h"
#include "task7.h"
#include "task8.h"


int callRun(Base& cnsl)
{
	cnsl.run();
	return 0;
}

long long inpInt(long long lower, long long upper)
{
	cout << "Введите целое число от " << lower << " до " << upper << ":\n";
	string inp = "";
	while (1)
	{
		getline(cin, inp);
		if (!numcheck(inp, lower, upper))
		{
			cout << "Некорректное значение! Попробуйте ещё раз:\n";
			continue;
		}

		return stoll(inp);
	}
}

vector<long long>* inpVecOfInt(long long maxLen, long long lower, long long upper)
{
	cout << "Количество элементов. ";
	long long len = inpInt(1, maxLen);
	vector <long long>* ans = new vector<long long>(0);
	for (int i = 0; i < len; i++)
	{
		cout << "Элемент " << i << ".";
		(*ans).push_back(inpInt(lower, upper));
	}
	return ans;
}

int Console::run()
{
	Base* Cnsl;

	while (1)
	{
		Cnsl = setup();
		if (Cnsl != nullptr)
			callRun(*Cnsl);
		else
			break;
	};

	delete Cnsl;

	return 0;
}

Console::Console()
{
}

Console::~Console()
{
}

//bool isnumber(string str)
//{
//	for (int i = 0; i < str.length(); i++)
//		if (!isdigit(str[i]))
//			return false;
//	return true;
//}

bool numcheck(string str, double lower, double upper)
{
	if (str == "")
		return false;
	if (!isdigit(str[0]) && str[0] != '-')
		return false;
	for (int i = 1; i < str.length(); i++)
		if (!isdigit(str[i]))
			return false;
	int num = stoi(str);
	if (num < lower || num > upper)
		return false;
	else
		return true;
}

Base * setup()
{
	string inp;
	cout << "Выберите номер практической работы от 1 до 8 или завершите работу по коду 0:\n";
	while (1)
	{
		getline(cin, inp);
		if (!numcheck(inp, 0, 8))
		{
			cout << "Некорректный ввод! Попробуйте ещё раз: ";
			continue;
		}
		break;
	}
	int num = stoi(inp);
	if (num == 1)
		return new ConsoleFor1();
	if (num == 2)
		return new ConsoleFor2();
	if (num == 3)
		return new ConsoleFor3();
	if (num == 4)
		return new ConsoleFor4();
	if (num == 5)
		return new ConsoleFor5();
	if (num == 6)
		return new ConsoleFor6();
	if (num == 7)
		return new ConsoleFor7();
	if (num == 8)
		return new ConsoleFor8();
	else
		return nullptr;
}

int randInt(int lower, int upper)
{
	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<mt19937::result_type> dist6(lower, upper);

	return dist6(rng);
}

istream& getManyLines(istream& stream, string& str)
{
	char c;
	str.clear();
	bool flag = true;
	while (flag)
	{
		stream.get(c);
		if (c == '\n')
			if (GetKeyState(VK_SHIFT) & 0x8000)
				str += c;
			else
				return stream;
		else
			str += c;
	}
}

