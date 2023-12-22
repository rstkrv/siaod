#include "task3.h"

template<class T, class TofKey>
T* findInList(ListNode<T> node, TofKey toFind)
{
	if (getKey(node.data) == toFind)
	{
		displayItem(node.data);
		cout << " has been found\n";
		return &node.data;
	}
	if (node.next == nullptr)
	{
		cout << "No item with this key!\n";
		return nullptr;
	}
	return findInList(*node.next, toFind);
}

template<class T, class TofKey>
void deleteFromList(ListNode<T>& node, TofKey toDelete)
{
	if (node.next == nullptr)
	{
		cout << "No item with such key!\n";
		return;
	}
	if (getKey(node.next->data) == toDelete)
	{
		displayItem(node.next->data);
		cout << " has been DELETED\n";
		node.next = node.next->next;
		return;
	}
	deleteFromList(*node.next, toDelete);
}

template<>
void displayItem<Item>(Item item)
{
	cout << "Article " << setfill('0') << setw(6) << item.article;
	cout << ": " << item.name << "; Price: " << item.price;
}

template<class T>
void displayList(ListNode<T> listNode)
{
	if (listNode.data.article == -1)
		return;
	displayItem(listNode.data);
	cout << " | ";
	if (listNode.next != nullptr)
		displayList(*listNode.next);
	else
		cout << endl;
}

template<class T>
void displayHashTable(HashTable<T> hashTable)
{
	for (int i = 0; i < hashTable.len; i++)
	{
		displayList(*hashTable.arr[i]);
	}
	cout << "В таблице " << hashTable.numOfElements << " элементов и " << hashTable.len << " допустимых значений хеша\n";
}

template<>
int getKey<Item>(Item elem)
{
	return elem.article;
}

template<>
int getValueOfKey<int>(int key)
{
	return key;
}

template<class T>
void insertToHashTable(HashTable<T>& hashTable, T elem)
{
	hashTable.numOfElements++;
	if ((float)hashTable.numOfElements / (float)hashTable.len > 0.75)
	{
		rehash(hashTable);
		hashTable.numOfElements++;
	}
	int pos = getKey(elem) % hashTable.len;
	if (hashTable.arr[pos]->data.article == -1)
		hashTable.arr[pos] = new ListNode<T>(elem);
	else
		hashTable.arr[pos] = new ListNode<T>(elem, hashTable.arr[pos]);
}

template<class TofElem, class TofKey>
void deleteFromHashTable(HashTable<TofElem>& hashTable, TofKey key)
{
	int pos = getValueOfKey(key) % hashTable.len;
	if (hashTable.arr[pos]->data.article == -1)
	{
		cout << "No item with this key!\n";
		return;
	}
	if (getKey(hashTable.arr[pos]->data) == key)
	{
		displayItem(hashTable.arr[pos]->data);
		cout << " has been DELETED\n";
		hashTable.arr[pos] = (hashTable.arr[pos]->next == nullptr) ? new ListNode<Item>() : hashTable.arr[pos]->next;
		hashTable.numOfElements--;
		return;
	}
	else
		deleteFromList(*hashTable.arr[pos], key);
}

template<class TofElem, class TofKey>
TofElem* findByKey(HashTable<TofElem> hashTable, TofKey key)
{
	int pos = getValueOfKey(key) % hashTable.len;
	if (hashTable.arr[pos]->data.article == -1)
	{
		cout << "No item with this key!\n";
		return nullptr;
	}
	TofElem* result = findInList(*hashTable.arr[pos], key);
	return result;
}

template<class T>
void rehash(HashTable<T>& hashTable)
{
	vector<T> allElems = {};
	for (int i = 0; i < hashTable.len; i++)
	{
		if (hashTable.arr[i]->data.article != -1)
		{
			allElems.push_back(hashTable.arr[i]->data);
			while (hashTable.arr[i]->next != nullptr)
			{
				hashTable.arr[i] = hashTable.arr[i]->next;
				allElems.push_back(hashTable.arr[i]->data);
			}
		}
	}

	delete[] hashTable.arr;

	hashTable.numOfElements = 0;
	hashTable.len *= 2;
	hashTable.arr = new ListNode<T>*[hashTable.len];
	for (int i = 0; i < hashTable.len; i++)
		hashTable.arr[i] = new ListNode<T>;
	for (T elem : allElems)
		insertToHashTable(hashTable, elem);
}

ConsoleFor3::ConsoleFor3()
{
}

ConsoleFor3::~ConsoleFor3()
{
}

int ConsoleFor3::run()
{
	cout << "Выберите номер задания из работы 3:\n";
	cout << "1. Показать содержимое хеш-таблицы\n";
	cout << "2. Добавить элемент\n";
	cout << "3. Удалить элемент по ключу\n";
	cout << "4. Найти элемент по ключу\n";
	cout << "5. Создать таблицу из семи случайных элементов\n";
	cout << "0. Перейти к выбору работы\n";
	string key;
	int num;
	HashTable<Item> ht;
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
			cout << "Текущая хеш-таблица:\n";
			displayHashTable<Item>(ht);
		}
		else if (num == 2)
		{
			int article = inpInt(0, 1000000);
			cout << "Введите название товара:\n";
			string name; 
			getline(cin, name);
			cout << "Введите стоимость товара:\n";
			string price;
			getline(cin, price);
			insertToHashTable(ht, Item(article, name, stod(price)));
		}
		else if (num == 3)
		{
			int key = inpInt(0, 1000000);
			deleteFromHashTable(ht, key);
		}
		else if (num == 4)
		{
			int key = inpInt(0, 1000000);
			findByKey(ht, key);
		}
		else if (num == 5)
		{
			ht = HashTable<Item>();
			for (int i = 0; i < 7; i++)
			{
				int article = randInt(0, 999999);
				string name = "Item" + to_string(article);
				double price = randInt(0, 1000);
				insertToHashTable(ht, Item(article, name, price));
			}
		}
		else if (num == 0)
			break;
		cout << "Выберите номер из меню: ";
	}
	return 0;
}
