#pragma once
#include "general.h"

class ConsoleFor2 : public Console
{
public:
	ConsoleFor2();
	~ConsoleFor2();
	int run();
};

class Book
{
public:
	string isbn = "";
	string author = "";
	string name = "";
	Book() = default;
	Book(string isbn, string author, string name)
	{
		this->isbn = isbn;
		this->author = author;
		this->name = name;
	};
};

vector<Book> randBooks(int n);
string makeIsbn(long long n);
string randStr(string alphabet);

void writeStr(string str, ofstream& fout);
void writeBook(Book book, ofstream& fout, vector<pair<long long, iostream::pos_type>>& offsetTable);

string readStr(iostream::pos_type& pos, ifstream& fin);
Book readBook(iostream::pos_type& pos, ifstream& fin);

iostream::pos_type linearSearch(string key, ifstream& fin, int size);

iostream::pos_type uniBinSearch(long long key, vector<pair<long long, iostream::pos_type>>& offsetTable, int m, int delta);
iostream::pos_type getOffset(long long key, vector<pair<long long, iostream::pos_type>>& offsetTable);