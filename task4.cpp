#include "task4.h"

ConsoleFor4::ConsoleFor4()
{
}

ConsoleFor4::~ConsoleFor4()
{
}

int ConsoleFor4::run()
{
	cout << "�������� ����� ������� �� ������ 4:\n";
	cout << "1. ������� ���� ���� � ����������� ����������� �� �����������\n";
	cout << "2. ����� ��������� ��������� � ������\n";
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
		{
			cout << "������� �����������:\n";
			string sentence;
			getline(cin, sentence);
			vector<array<string, 2>>* pairs = findMinHDpairs(*parseSentence(sentence));
			cout << "���� ���� � ���������� �����������:\n";
			for (auto e : *pairs)
			{
				cout << e[0] << " " << e[1] << endl;
			}
		}
		if (num == 2)
		{
			cout << "������� ������:\n";
			string source;
			getline(cin, source);
			cout << "������� ���������:\n";
			string pat;
			getline(cin, pat);
			vector<int> ans = turboBMsearch(source, pat);
			cout << "������� " << ans.size() << " ���������\n";
			if (ans.size() > 0)
				for (int i : ans)
					cout << "�� ������� " << i << endl;
		}
		else if (num == 0)
			break;
		cout << "�������� ����� �� ����: ";
	}
	return 0;
}

map<int, vector<string>>* parseSentence(string toParse) // �������� �����: ���������� ���� � ����� -> ������ ���������� ����
{
	map<int, vector<string>>* strings = new map<int, vector<string>>;
	size_t prev = 0, pos;
    while ((pos = toParse.find_first_of(" ,", prev)) != string::npos)
    {
        int len = pos - prev;
        if (len > 0)
        {
            if (strings->count(len))
                (*strings)[len].push_back(toParse.substr(prev, len));
            else
                strings->insert({ len, vector<string>({toParse.substr(prev, len)}) });
        }
        prev = pos + 1;
    }
    if (prev < toParse.length())
    {
        int len = toParse.length() - prev;
        if (strings->count(len))
            (*strings)[len].push_back(toParse.substr(prev, len));
        else
            strings->insert({ len, vector<string>({toParse.substr(prev, len)}) });
    }
	return strings;
}

vector<array<string, 2>>* findMinHDpairs(map<int, vector<string>> map) // ����� ��� ���� � ���������� �����������
{
	vector<array<string, 2>>* pairs = new vector<array<string, 2>>; // �������� ������� ���
	int minDist = 1000000;
	
	for (auto kv : map) // ��� ������� ��������� �����
	{
		if (kv.second.size() < 2)
			continue;
		for (int index1 = 0; index1 < kv.second.size() - 1; index1++)
		{
			for (int index2 = index1 + 1; index2 < kv.second.size(); index2++)
			{
				int dist = 0;
				for (int i = 0; i < kv.first; i++)
				{
					if (kv.second[index1][i] != kv.second[index2][i]) // ������������ ��������� ����
						dist++;
					if (dist > minDist) // ���� ���������� ������ ������������, ����� ������� � ��������� ����
						break;
				}
				if (dist < minDist) // ���� ���������� ������ �������� ������������, ���������� �������� ������ ���
					// � �������� ���������
				{
					minDist = dist;
					pairs->clear();
					pairs->push_back(array<string, 2> { { kv.second[index1], kv.second[index2] } });
				}
				else if (dist == minDist) // ���� ���������� ����� ������������, ������ ��������� ���������
				{
					pairs->push_back(array<string, 2> { { kv.second[index1], kv.second[index2] } });
				}
			}
		}
	}

	return pairs; // ������� ������� ��������� ���
}

vector<int> makeBadCharTable(string s) // �������� ������� ����-��������
{
	vector<int> table(ALPHABET_LENGTH, s.length());
	for (int i = 0; i < s.length() - 1; i++)
		table[s[i]] = s.length() - i - 1;
	return table;
}

vector<int> makeSuffTable(string s) // �������� ������� ���������
{
	int len = s.length();
	vector<int> suff(len);
	int f, g = len - 1;

	suff[len - 1] = len;
	for (int i = len - 2; i >= 0; i--)
		if (i > g && suff[i + len - 1 - f] < i - g)
			suff[i] = suff[i + len - 1 - f];
		else
		{
			if (i < g)
				g = i;
			f = i;
			while (g >= 0 && s[g] == s[g + len - 1 - f])
				g--;
			suff[i] = f - g;
		}
	return suff;
}

vector<int> makeGoodSuffTable(string s) // ������� � ������� ����������� ���������
{
	int len = s.length();
	vector<int> table(len, len);
	vector<int> suffTable = makeSuffTable(s);

	int j = 0;
	for (int i = len - 1; i >= 0; i--)
		if (suffTable[i] == i + 1)
			for (; j < len - 1 - i; j++)
				if (table[j] == len)
					table[j] = len - 1 - i;
	for (int i = 0; i <= len - 2; i++)
		table[len - 1 - suffTable[i]] = len - 1 - i;
	
	return table;
}

vector<int> turboBMsearch(string source, string pattern) // ����� ������-���� � ������������
{
	int len = pattern.length();
	vector<int> badCTable = makeBadCharTable(pattern);
	vector<int> goodSTable = makeGoodSuffTable(pattern); // �������� ����������� ������
	vector<int> ans;

	int shift = len;
	int j = 0, u = 0;
	while (j <= source.length() - len) // j - ������� �������, ������� � �������� ������ �����, � �������� ������
	{
		int i = len - 1;
		while (i >= 0 && pattern[i] == source[j + i])
		{
			i--;
			if (u != 0 && i == len - 1 - shift)
				i -= u;
		} // ��������� ���������� ��������� ��������
		if (i < 0)
		{
			ans.push_back(j);
			shift = goodSTable[0];
			u = len - shift;
		} // ��������� �������: ������� �������� � ������ �������
		else
		{
			int v = len - 1 - i; // ������ ����� �������� ���������� ��������
			int turboShift = u - v; // ������ �����������
			int badCShift = badCTable[source[i + j]] - len + 1 + i; // ������ ������ �� ������� ����-��������
			shift = max(turboShift, badCShift); // 
			shift = max(shift, goodSTable[i]); // ����� ������������� ������
			if (shift == goodSTable[i])
				u = min(len - shift, v); // ��������� ����� ����������� ���������� ��������
			else
			{
				if (turboShift < badCShift)
					shift = max(shift, u + 1);
				u = 0; // ��������� ���������� �������� (������� ��� �������� �� ������� ����-��������)
			}
		} // ��������� �� �������
		j += shift; // �������� �������
	}

	return ans; // ������� ��������� �������
}