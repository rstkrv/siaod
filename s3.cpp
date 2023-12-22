#include "s3.h"

template<class T, class TofKey> 
T* findInList(ListNode<T> node, TofKey toFind)
{
	if (getKey(node.data) == toFind)
		return &data;
	if (node.next == nullptr)
		return nullptr;
	return findInList(node.next, toFind);
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
	deleteFromList(node.next, toDelete);
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
	if (listNode.data == NULL)
		return;
	displayItem(listNode.data);
	cout << " | ";
	if (listNode.next != nullptr)
		displayList(listNode.next);
}

template<class T>
void displayHashTable(HashTable<T> hashTable)
{
	for (ListNode<T> list : hashTable.arr)
	{
		displayList(list);
		cout << endl;
	}
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
	if ((float)hashTable.numOfElements / (float)hashTable.len > 0.75)
		rehash(hashTable);
	int pos = getValue(elem) % hashTable.len;
	if (hashTable.arr[pos]->data == NULL)
		hashTable.arr[pos] = new ListNode<T>(elem);
	else
		hashTable.arr[pos] = new ListNode<T>(elem, hashTable.arr[pos]);
}

template<class TofElem, class TofKey> 
void deleteFromHashTable(HashTable<TofElem>& hashTable, TofKey key)
{
	int pos = getValueOfKey(key) % hashTable.len;
	if (hashTable.arr[pos]->data == NULL)
	{
		cout << "No item with this key!\n";
		return;
	}
	if (getKey(hashTable.arr[pos]->data) == key)
	{
		displayItem(hashTable.arr[pos]->data);
		cout << " has been DELETED\n";
		hashTable.arr[pos] = hashTable.arr[pos]->next;
		return;
	}
	else
		deleteFromList(hashTable.arr[pos], key);
}

template<class TofElem, class TofKey> 
TofElem* findByKey(HashTable<TofElem> hashTable, TofKey key)
{
	int pos = getValueOfKey(key) % hashTable.len;
	if (hashTable.arr[pos]->data == NULL)
	{
		cout << "No item with this key!\n";
		return;
	}
	TofElem* result = findInList(hashTable.arr[pos], key);
	if (result == nullptr)
		cout << "No element with this key value!";
	else
		displayItem(*result);
}

template<class T>
void rehash(HashTable<T>& hashTable)
{
	vector<T> allElems = {};
	for (ListNode list : hashTable.arr)
	{
		if (list.data != NULL)
		{
			allElems.push_back(list.data);
			while (list.next != nullptr)
			{
				list = list.next;
				allElems.push_back(list.data);
			}
		}
	}

	delete [] hashTable.arr;

	hashTable.len *= 2;
	hashTable.arr = new T[hashTable.len];

	for (T elem : allElems)
		insertToHashTable(hashTable, T);
}
