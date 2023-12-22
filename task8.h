#pragma once
#include "general.h"

class ConsoleFor8 : public Console
{
public:
	ConsoleFor8();
	~ConsoleFor8();
	int run();
};

void itemsInKnapsack(vector<vector<int>> knapsack, vector<int> weights, int k, int s, vector<int>& items);