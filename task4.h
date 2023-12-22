#pragma once
#include "general.h"
#define ALPHABET_LENGTH 128

class ConsoleFor4 : public Console
{
public:
	ConsoleFor4();
	~ConsoleFor4();
	int run();
};

map<int, vector<string>>* parseSentence(string s);

vector<array<string, 2>>* findMinHDpairs(map<int, vector<string>>);


vector<int> makeBadCharTable(string s);
vector<int> makeSuffTable(string s);
vector<int> makeGoodSuffTable(string s);
vector<int> turboBMsearch(string source, string pattern);
