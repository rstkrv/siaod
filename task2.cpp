#pragma once
#include "task2.h"

ConsoleFor2::ConsoleFor2()
{
}

ConsoleFor2::~ConsoleFor2()
{
}

int ConsoleFor2::run()
{
	cout << "Выберите номер задания из работы 2:\n";
	cout << "1. Создать бинарный файл из записей книг\n";
	cout << "2. Вывести первые 10 записей\n";
	cout << "3. Найти запись книги (линейный поиск)\n";
	cout << "4. Найти запись книги (однородный бинарный поиск)\n";
	cout << "0. Перейти к выбору работы\n";
	string key;
	int num;
	
	ifstream fin("C:\\Users\\ivanp\\source\\repos\\siaod1\\test.bin", ios::binary);
	vector<pair<long long, iostream::pos_type>> offsetTable;
	while (1)
	{
		getline(cin, key);
		if (!numcheck(key, 0, 4))
		{
			cout << "Некорректный ввод! Попробуйте ещё раз: ";
			continue;
		}
		num = stoi(key);
		if (num == 1)
		{
			ofstream fout("C:\\Users\\ivanp\\source\\repos\\siaod1\\test.bin", ios::out | ios::binary);
			ofstream foo("C:\\Users\\ivanp\\source\\repos\\siaod1\\test.txt");
			cout << "Введите количество записей: ";
			int n = inpInt(1, 10000);
			vector<Book> books = randBooks(n);
			for (Book b : books)
			{
				cout << b.isbn << " " << b.author << " " << b.name << endl;
				writeBook(b, fout, offsetTable);
				foo << b.isbn << endl << b.author << endl << b.name << endl;
			}
			sort(offsetTable.begin(), offsetTable.end());
			fout.close();
			foo.close();
		}
		if (num == 2)
		{
			ifstream fin("C:\\Users\\ivanp\\source\\repos\\siaod1\\test.bin", ios::in | ios::binary);
			iostream::pos_type pos = 0;
			for (int i = 0; i < 10; i++)
			{
				Book b = readBook(pos, fin);
				cout << i << ". " << b.isbn << " " << b.author << " " << b.name << endl;
			}
			fin.close();
		}
		if (num == 3)
		{
			cout << "Введите ключ для поиска: ";
			string key;
			getline(cin, key);
			auto start = chrono::steady_clock::now();
			iostream::pos_type pos = linearSearch(key, fin, filesystem::file_size("C:\\Users\\ivanp\\source\\repos\\siaod1\\test.bin"));
			auto end = chrono::steady_clock::now();
			cout << "Поиск занял " << fixed << chrono::duration<double>{end - start} << endl;
			if (pos == -1)
				cout << "Записи с таким ключом не существует!" << endl;
			else
			{
				Book b = readBook(pos, fin);
				cout << b.isbn << " " << b.author << " " << b.name << endl;
			}
		}
		if (num == 4)
		{
			cout << "Введите ключ для поиска: ";
			string key;
			getline(cin, key);
			auto start = chrono::steady_clock::now();
			iostream::pos_type pos = getOffset(stoll(key), offsetTable);
			auto end = chrono::steady_clock::now();
			cout << "Поиск занял " << fixed << chrono::duration<double>{end - start} << endl;
			if (pos == -1)
				cout << "Записи с таким ключом не существует!" << endl;
			else
			{
				Book b = readBook(pos, fin);
				cout << b.isbn << " " << b.author << " " << b.name << endl;
			}
		}
		else if (num == 0)
			break;
		cout << "Выберите номер из меню: ";
	}
	return 0;
}

vector<Book> randBooks(int n)
{
	vector<Book> books;
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		int r = rand();
		books.push_back(Book(makeIsbn(r), "author" + to_string(r), "Book" + to_string(r)));
	}

	return books;
}

string makeIsbn(long long n)
{
	string str = to_string(n);
	while (str.length() < 12)
		str = '0' + str;
	while (str.length() > 12)
		str.erase(0);
	return str;
}

string randStr(string alphabet)
{
	int len = randInt(10, 20);
	string str = "";
	for (int i = 0; i < len; i++)
		str += alphabet[randInt(0, alphabet.size())];
	return str;
}

void writeStr(string str, ofstream& fout)
{
	size_t size = str.length();
	fout.write((char*)&size, sizeof(size_t));
	fout.write((char*)str.c_str(), size);
}

void writeBook(Book book, ofstream& fout, vector<pair<long long, iostream::pos_type>>& offsetTable)
{
	offsetTable.push_back(make_pair(stoll(book.isbn), fout.tellp()));
	writeStr(book.isbn, fout);
	writeStr(book.author, fout);
	writeStr(book.name, fout);
}

string readStr(iostream::pos_type& pos, ifstream& fin)
{
	fin.seekg(pos);
	size_t size;
	fin.read((char*)&size, sizeof(size));
	char* data = new char[size + 1];
	fin.read(data, size);
	data[size] = '\0';

	pos += sizeof(size) + sizeof(char) * size;
	
	return string(data);
}

Book readBook(iostream::pos_type& pos, ifstream& fin)
{
	string isbn = readStr(pos, fin);
	string author = readStr(pos, fin);
	string name = readStr(pos, fin);

	return Book(isbn, author, name);
}

iostream::pos_type linearSearch(string key, ifstream& fin, int size)
{
	iostream::pos_type pos = 0;
	while (pos < size)
	{
		string isbn = readStr(pos, fin);
		if (isbn == key)
			return pos - (iostream::pos_type)sizeof(size_t) - sizeof(char) * isbn.length();
		isbn = readStr(pos, fin);
		isbn = readStr(pos, fin);
	}
	return -1;
}

iostream::pos_type uniBinSearch(long long key, vector<pair<long long, iostream::pos_type>>& offsetTable, int m, int delta)
{
	if (offsetTable[m].first == key)
		return offsetTable[m].second;
	if (delta == 0)
		return -1;

	if (offsetTable[m].first > key)
		return uniBinSearch(key, offsetTable, m - ceil((double)delta / 2), floor((double)delta / 2));
	else
		return uniBinSearch(key, offsetTable, m + ceil((double)delta / 2), floor((double)delta / 2));
}

iostream::pos_type getOffset(long long key, vector<pair<long long, iostream::pos_type>>& offsetTable)
{
	int m = ceil(offsetTable.size() / 2);
	int delta = floor(offsetTable.size() / 2);

	return uniBinSearch(key, offsetTable, m, delta);
}

vector<Book>* createBooks(int n)
{
	vector<Book>* books = new vector<Book>;
	string alphabet = "qwertyuiopasdfghjklzxcvbnm";
	for (int i = 0; i < n; i++)
	{
		Book book(makeIsbn(i), randStr(alphabet), randStr(alphabet));
		books->push_back(book);
	}
	return books;
}
