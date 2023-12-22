#include "task4.h"

ConsoleFor4::ConsoleFor4()
{
}

ConsoleFor4::~ConsoleFor4()
{
}

int ConsoleFor4::run()
{
	cout << "Выберите номер задания из работы 4:\n";
	cout << "1. Вывести пары слов с минимальным расстоянием из предложения\n";
	cout << "2. Найти вхождение подстроки в строку\n";
	cout << "0. Перейти к выбору работы\n";
	string key;
	int num;
	while (1)
	{
		getline(cin, key);
		if (!numcheck(key, 0, 8))
		{
			cout << "Некорректный ввод! Попробуйте ещё раз: ";
			continue;
		}
		num = stoi(key);
		if (num == 1)
		{
			cout << "Введите предложение:\n";
			string sentence;
			getline(cin, sentence);
			vector<array<string, 2>>* pairs = findMinHDpairs(*parseSentence(sentence));
			cout << "Пары слов с наименьшим расстоянием:\n";
			for (auto e : *pairs)
			{
				cout << e[0] << " " << e[1] << endl;
			}
		}
		if (num == 2)
		{
			cout << "Введите строку:\n";
			string source;
			getline(cin, source);
			cout << "Введите подстроку:\n";
			string pat;
			getline(cin, pat);
			vector<int> ans = turboBMsearch(source, pat);
			cout << "Найдено " << ans.size() << " вхождений\n";
			if (ans.size() > 0)
				for (int i : ans)
					cout << "на позиции " << i << endl;
		}
		else if (num == 0)
			break;
		cout << "Выберите номер из меню: ";
	}
	return 0;
}

map<int, vector<string>>* parseSentence(string toParse) // создание карты: количество букв в слове -> массив подходящих слов
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

vector<array<string, 2>>* findMinHDpairs(map<int, vector<string>> map) // поиск пар слов с минмальным расстоянием
{
	vector<array<string, 2>>* pairs = new vector<array<string, 2>>; // создание массива пар
	int minDist = 1000000;
	
	for (auto kv : map) // для каждого вхождения карты
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
					if (kv.second[index1][i] != kv.second[index2][i]) // посимвольное сравнение слов
						dist++;
					if (dist > minDist) // если расстояние больше минимального, можно перейти к следующей паре
						break;
				}
				if (dist < minDist) // если расстояние меньше текущего минимального, необходимо очистить массив пар
					// и добавить найденную
				{
					minDist = dist;
					pairs->clear();
					pairs->push_back(array<string, 2> { { kv.second[index1], kv.second[index2] } });
				}
				else if (dist == minDist) // если расстояние равно минимальному, просто добавляем найденную
				{
					pairs->push_back(array<string, 2> { { kv.second[index1], kv.second[index2] } });
				}
			}
		}
	}

	return pairs; // возврат массива найденных пар
}

vector<int> makeBadCharTable(string s) // создание таблицы стоп-символов
{
	vector<int> table(ALPHABET_LENGTH, s.length());
	for (int i = 0; i < s.length() - 1; i++)
		table[s[i]] = s.length() - i - 1;
	return table;
}

vector<int> makeSuffTable(string s) // создание таблицы суффиксов
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

vector<int> makeGoodSuffTable(string s) // переход к таблице совпадающих суффиксов
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

vector<int> turboBMsearch(string source, string pattern) // поиск Бойера-Мура с турбосдвигом
{
	int len = pattern.length();
	vector<int> badCTable = makeBadCharTable(pattern);
	vector<int> goodSTable = makeGoodSuffTable(pattern); // создание необходимых таблиц
	vector<int> ans;

	int shift = len;
	int j = 0, u = 0;
	while (j <= source.length() - len) // j - позиция символа, начиная с которого ведётся поиск, в исходной строке
	{
		int i = len - 1;
		while (i >= 0 && pattern[i] == source[j + i])
		{
			i--;
			if (u != 0 && i == len - 1 - shift)
				i -= u;
		} // получение количества совпавших символов
		if (i < 0)
		{
			ans.push_back(j);
			shift = goodSTable[0];
			u = len - shift;
		} // вхождение найдено: позиция записана в массив ответов
		else
		{
			int v = len - 1 - i; // расчёт длины текущего совпавшего суффикса
			int turboShift = u - v; // расчёт турбосдвига
			int badCShift = badCTable[source[i + j]] - len + 1 + i; // расчёт сдвига по таблице стоп-символов
			shift = max(turboShift, badCShift); // 
			shift = max(shift, goodSTable[i]); // выбор максимального сдвига
			if (shift == goodSTable[i])
				u = min(len - shift, v); // изменение длины предыдущего совпавшего суффикса
			else
			{
				if (turboShift < badCShift)
					shift = max(shift, u + 1);
				u = 0; // обнуление совпавшего суффикса (переход был совершен по таблице стоп-символов)
			}
		} // вхождение не найдено
		j += shift; // смещение позиции
	}

	return ans; // возврат найденных позиций
}