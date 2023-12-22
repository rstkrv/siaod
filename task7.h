#pragma once
#include "general.h"

class ConsoleFor7 : public Console
{
public:
	ConsoleFor7();
	~ConsoleFor7();
	int run();
};

struct Symbol
{
	char name = '\0';
	int count = 0;
	double prob = 0;
	vector<bool> code = {};
	Symbol() = default;
	Symbol(char name, int count, double prob)
	{
		this->name = name;
		this->count = count;
		this->prob = prob;
	}
	bool operator < (const Symbol& s) const
	{
		return prob < s.prob;
	}
	bool operator== (const Symbol& s) const
	{
		return name == s.name;
	}
};

double totalProb(vector<Symbol>::iterator from, vector<Symbol>::iterator to);

void leftPart(vector<Symbol>& v, vector<Symbol>::iterator from, vector<Symbol>::iterator to);
void rightPart(vector<Symbol>& v, vector<Symbol>::iterator from, vector<Symbol>::iterator to);
void partition(vector<Symbol>& v, vector<Symbol>::iterator from, vector<Symbol>::iterator to);

pair<map<char, vector<bool>>, map<vector<bool>, char>> shannonFano(string s);
vector<bool> codeSF(string text, map<char, vector<bool>> codeTable);
string decodeSF(vector<bool> coded, map<vector<bool>, char> decodeTable);

pair<map<char, vector<bool>>, map<vector<bool>, char>> shannonFano(ifstream& in);
void codeSF(ifstream& in, ofstream& out, map<char, vector<bool>> codeTable);
void decodeSF(ifstream& in, ofstream& out, map<vector<bool>, char> decodeTable);


vector<bool> strToVec(string s);
string vecToStr(vector<bool> v);
vector<bool> parseInt(int n);
pair<vector<bool>, map<vector<bool>, vector<bool>>> codeLZ(vector<bool> v);
pair<vector<bool>, map<vector<bool>, vector<bool>>> decodeLZ(vector<bool> v);

vector<pair<unsigned char, char>> codeLZ78(string s);
string decodeLZ78(vector<pair<unsigned char, char>>);




struct HaffLeaf
{
	vector<pair<char, vector<bool>>> chars = {};
	int weight = 0;
	HaffLeaf() = default;
	HaffLeaf(char c, int w)
	{
		chars = { make_pair(c, vector<bool>{}) };
		weight = w;
	}
	bool operator== (const HaffLeaf& l) const
	{
		return chars == l.chars;
	}
	bool operator < (const HaffLeaf& l) const
	{
		return weight < l.weight;
	}
};

pair <map<char, vector<bool>>, map<vector<bool>, char>> haffman(string s);
vector<bool> codeHaffman(string text, map<char, vector<bool>> codeTable);
string decodeHaffman(vector<bool> coded, map<vector<bool>, char> decodeTable);

pair<map<char, vector<bool>>, map<vector<bool>, char>> haffman(ifstream& in);
void codeHaffman(ifstream& in, ofstream& out, map<char, vector<bool>> codeTable);
void decodeHaffman(ifstream& in, ofstream& out, map<vector<bool>, char> decodeTable);

void codeHaffman(ifstream& in, ofstream& out);
void decodeHaffman(ifstream& in, ofstream& out);