#include "task5.h"

ConsoleFor5::ConsoleFor5()
{
}

ConsoleFor5::~ConsoleFor5()
{
}

int ConsoleFor5::run()
{
	cout << "Выберите номер задания из работы 5:\n";
	cout << "1. Вставить элемент\n";
	cout << "2. Прямой обход дерева\n";
	cout << "3. Симметричный обход дерева\n";
	cout << "4. Найти среднее арифметическое узлов дерева\n";
	cout << "5. Найти длину пути от корня до заданного значения\n";
	cout << "0. Перейти к выбору работы\n";
	string key;
	int num;
	BinTree* binTree = nullptr;
	while (1)
	{
		getline(cin, key);
		if (!numcheck(key, 0, 5))
		{
			cout << "Некорректный ввод! Попробуйте ещё раз: ";
			continue;
		}
		num = stoi(key);
		if (num == 1)
		{
			cout << "Введите строку для вставки в дерево:\n";
			string key;
			getline(cin, key);
			insertToTree(binTree, key);
		}
		if (num == 2)
		{
			cout << "Обход узлов дерева в прямом порядке:\n";
			preorderWalk(binTree);
		}
		if (num == 3)
		{
			cout << "Обход узлов дерева в центрированном порядке:\n";
			inorderWalk(binTree);
		}
		if (num == 4)
		{
			float avg = avgOfKeys(binTree);
			if (avg == 0)
				cout << "Дерево пустое!\n";
			else
				cout << "Средняя длина строк-узлов равна " << avg << endl;
		}
		if (num == 5)
		{
			cout << "Введите строку для поиска в дереве:\n";
			string key;
			getline(cin, key);
			int len = findLenOfPath(binTree, key);
			if (len == -1)
				cout << "Дерево не содержит ключа!\n";
			else
				cout << "Длина пути до данной строки равна " << len << endl;
		}
		else if (num == 0)
			break;
		cout << "Выберите номер из меню: ";
	}
	return 0;
}

void insertToTree(BinTree*& t, string key)
{
	if (t == nullptr)
	{
		t = new BinTree(key);
		return;
	}
	BinTree* parent = nullptr;
	BinTree* curr = t;
	while (curr != nullptr)
	{
		parent = curr;
		if (key < curr->key)
			curr = curr->left;
		else
			curr = curr->right;
	}
	BinTree* newNode = new BinTree(key, parent);
	if (parent != nullptr)
		if (key < parent->key)
			parent->left = newNode;
		else
			parent->right = newNode;
}

void preorderWalk(BinTree* t)
{
	if (t != nullptr)
	{
		cout << t->key << endl;
		preorderWalk(t->left);
		preorderWalk(t->right);
	}
}

void inorderWalk(BinTree* t)
{
	if (t != nullptr)
	{
		inorderWalk(t->left);
		cout << t->key << endl;
		inorderWalk(t->right);
	}
}

void stepOfAvg(BinTree* t, int& count, int& sum)
{
	if (t != nullptr)
	{
		count++;
		sum += t->key.length();
		stepOfAvg(t->left, count, sum);
		stepOfAvg(t->right, count, sum);
	}
}

float avgOfKeys(BinTree* t)
{
	if (t == nullptr)
		return 0;

	int count = 0, sum = 0;
	stepOfAvg(t, count, sum);

	return (float)sum/(float)count;
}

void stepOfFind(BinTree* t, string key, int& currLen)
{
	if (t == nullptr)
		currLen = -1;
	else if (t->key == key)
		return;
	else if (key < t->key)
	{
		currLen++;
		stepOfFind(t->left, key, currLen);
	}
	else
	{
		currLen++;
		stepOfFind(t->right, key, currLen);
	}
}

int findLenOfPath(BinTree* t, string key)
{
	int len = 0;

	stepOfFind(t, key, len);

	return len;
}
