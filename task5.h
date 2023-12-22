#pragma once
#include "general.h"

class ConsoleFor5 : public Console
{
public:
	ConsoleFor5();
	~ConsoleFor5();
	int run();
};

struct BinTree
{
	string key = "";
	BinTree* left = nullptr;
	BinTree* right = nullptr;
	BinTree* p = nullptr;

	BinTree() = default;
	BinTree(string s)
	{
		key = s;
	}
	BinTree(string s, BinTree* parent)
	{
		key = s;
		p = parent;
	}
};

void insertToTree(BinTree*& t, string key);

void preorderWalk(BinTree* t);

void inorderWalk(BinTree* t);

void stepOfAvg(BinTree* t, int& count, int& sum);
float avgOfKeys(BinTree* t);

void stepOfFind(BinTree* t, string key, int& currLen);
int findLenOfPath(BinTree* t, string key);

