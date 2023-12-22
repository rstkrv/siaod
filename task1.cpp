#pragma once
#include "task1.h"

unsigned char bit5to0(unsigned char num)
{
	unsigned char mask = 1;
	return num & (~(mask << 4));
}

unsigned char bit7to0(unsigned char num)
{
	unsigned char mask = 1;
	return num & (~(mask << 6));
}

void toBin(unsigned int x)
{
	const int n = sizeof(int) * 8;
	unsigned mask = (1 << n - 1);
	cout << "��������� ��� �����: " << bitset<n>(mask) << endl;
	cout << "���������: ";
	for (int i = 1; i <= n; i++)
	{
		cout << ((x & mask) >> (n - i));
		mask = mask >> 1;
	}
	cout << endl;
}


void ucharSort(vector<long long>& arr)
{
	unsigned char sorter = 0;
	const unsigned char ONE = 1;
	for (int v : arr)
	{
		sorter = (sorter | (ONE << v));
	}
	int currNum = 0;
	int currIndex = 0;
	for (int i = 0; i < sizeof(unsigned char) * 8; i++)
	{
		if ((sorter & (ONE << i)) >> i)
		{
			arr[currIndex] = currNum;
			currIndex++;
		}
		currNum++;
	}

}

void ullSort(vector<long long>& arr)
{
	unsigned long long sorter = 0;
	const unsigned long long ONE = 1;
	for (int v : arr)
	{
		sorter = (sorter | (ONE << v));
	}
	int currNum = 0;
	int currIndex = 0;
	for (int i = 0; i < sizeof(unsigned long long) * 8; i++)
	{
		if ((sorter & (ONE << i)) >> i)
		{
			arr[currIndex] = currNum;
			currIndex++;
		}
		currNum++;
	}

}


void arrOfUcharSort(vector<long long>& arr)
{
	unsigned char sorter[8] = {};
	const unsigned char ONE = 1;

	for (int v : arr)
	{
		sorter[v / 8] = (sorter[v / 8] | (ONE << (v % 8)));
	}

	int currNum = 0;
	int currIndex = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((sorter[i] & (ONE << j)) >> j)
			{
				arr[currIndex] = currNum;
				currIndex++;
			}
			currNum++;
		}
	}
}


int ConsoleFor1::run()
{
	cout << "�������� ����� ������� �� ������ 1:\n";
	cout << "1. �������� 5-� ��� ������ �����\n";
	cout << "2. �������� 7-� ��� ������ �����\n";
	cout << "3. ����� ��������� ���� ������ �����\n";
	cout << "4. ���������� ������� �������� � ���� unsigned char\n";
	cout << "5. ���������� ������� �������� � ���� unsigned long long\n";
	cout << "6. ���������� ������� �������� � ���� ���������� unsigned char\n";
	cout << "7. ���������� �� ����� ������� ��������\n";
	cout << "0. ������� � ������ ������\n";
	string key;
	int num;
	while (1)
	{
		getline(cin, key);
		if (!numcheck(key, 0, 8))
		{
			cout << "������������ ����! ���������� ��� ���: ";
			continue;
		}
		num = stoi(key);
		if (num == 1)
			this->com1();
		else if (num == 2)
			com2();
		else if (num == 3)
			com3();
		else if (num == 4)
			com4();
		else if (num == 5)
			com5();
		else if (num == 6)
			com6();
		else if (num == 7)
			com7();
		else if (num == 0)
			break;
		cout << "�������� ����� �� ����: ";
	}
	return 0;
}

ConsoleFor1::ConsoleFor1()
{
}

ConsoleFor1::~ConsoleFor1()
{
}

void ConsoleFor1::com1()
{
	int num = inpInt(0, 255);
	unsigned char N = num;
	cout << "��������� ��������� 5-�� ����: " << int(bit5to0(N)) << endl;
	cout << "����� " << (bitset<8>(N)[4] == 0 ? "�� " : "") << "����������, ��� ��� 5-� ��� ��� ����� " << bitset<8>(N)[4] << endl;
}

void ConsoleFor1::com2()
{
	int num = inpInt(0, 255);
	unsigned char N = num;
	cout << "��������� ��������� 7-�� ����: " << int(bit7to0(N)) << endl;
	cout << "����� " << (bitset<8>(N)[6] == 0 ? "�� " : "") << "����������, ��� ��� 7-� ��� ��� ����� " << bitset<8>(N)[6] << endl;
}

void ConsoleFor1::com3() 
{
	unsigned int x = inpInt(0, 4294967295);
	toBin(x);
}

void ConsoleFor1::com4()
{
	vector<long long>* arr = inpVecOfInt(8, 0, 7);
	cout << "��������� ������:\n";
	for (long long a : *arr)
		cout << " " << a;
	ucharSort(*arr);
	cout << "\n��������������� ������:\n";
	for (long long a : *arr)
		cout << " " << a;
	cout << endl;
}

void ConsoleFor1::com5()
{
	vector<long long>* arr = inpVecOfInt(64, 0, 63);
	cout << "��������� ������:\n";
	for (long long a : *arr)
		cout << " " << a;
	ullSort(*arr);
	cout << "\n��������������� ������:\n";
	for (long long a : *arr)
		cout << " " << a;
	cout << endl;
}

void ConsoleFor1::com6()
{
	vector<long long>* arr = inpVecOfInt(64, 0, 63);
	cout << "��������� ������:\n";
	for (long long a : *arr)
		cout << " " << a;
	arrOfUcharSort(*arr);
	cout << "\n��������������� ������:\n";
	for (long long a : *arr)
		cout << " " << a;
	cout << endl;
}

void ConsoleFor1::com7()
{
}
