#pragma once
#include "task8.h"

int ConsoleFor8::run()
{
	cout << "Выберите номер задания из работы 8:\n";
	cout << "1. Задача о рюкзаке\n";
	cout << "0. Перейти к выбору работы\n";
	string key;
	int num;
	while (1)
	{
		getline(cin, key);
		if (!numcheck(key, 0, 1))
		{
			cout << "Некорректный ввод! Попробуйте ещё раз: ";
			continue;
		}
		num = stoi(key);
		if (num == 1)
		{
			cout << "Введите количество предметов: ";
			int n = inpInt(1, 1000);
			cout << "Введите вместимость рюкзака: ";
			int volume = inpInt(1, 10000);
			vector<int> weights, costs;
			for (int i = 0; i < n; i++)
			{
				weights.push_back(randInt(1, 10));
				costs.push_back(randInt(1, 100));
				cout << "Предмет " << i + 1 << ": вес = " << weights[i] << ", стоимость = " << costs[i] << endl;
			}
			vector<vector<int>> knapsack(n + 1, vector<int>(volume + 1, 0));
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= volume; j++)
					if (j >= weights[i - 1])
						knapsack[i][j] = max(knapsack[i - 1][j], knapsack[i - 1][j - weights[i - 1]] + costs[i - 1]);
					else
						knapsack[i][j] = knapsack[i - 1][j];
			cout << "        ";
			for (int i = 1; i <= volume; i++)
				cout << setw(10) << i;
			cout << endl;
			for (int i = 0; i <= n; i++)
			{
				cout << "k = " << setw(4) << i;
				for (int j = 1; j <= volume; j++)
					cout << setw(10) << knapsack[i][j];
				cout << endl;
			}
			vector<int> items = {};
			itemsInKnapsack(knapsack, weights, n, volume, items);
			cout << "В рюкзаке объёмом " << volume << " лежат предметы под номерами:\n";
			for (int i : items)
				cout << i << " ";
			cout << endl << "С общей стоимостью " << knapsack[n][volume] << endl;
		}
		else if (num == 0)
			break;
		cout << "Выберите номер из меню: ";
	}
	return 0;
}

ConsoleFor8::ConsoleFor8()
{
}

ConsoleFor8::~ConsoleFor8()
{
}

void itemsInKnapsack(vector<vector<int>> knapsack, vector<int> weights, int k, int s, vector<int>& items)
{
	if (knapsack[k][s] == 0)
		return;
	if (knapsack[k - 1][s] == knapsack[k][s])
		itemsInKnapsack(knapsack, weights, k - 1, s, items);
	else
	{
		itemsInKnapsack(knapsack, weights, k - 1, s - weights[k - 1], items);
		items.push_back(k);
	}
}
