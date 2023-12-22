#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

struct Item 
{
	int article;
	string name;
	double price;

	Item(int article, string name, double price)
	{
		this->article = article % 1000000;
		this->name = name;
		this->price = price;
	}
};

template<class T> struct ListNode
{
	T data = NULL;
	ListNode* next = nullptr;

	ListNode() = default;

	ListNode(T data)
	{
		this->data = data;
		this->next = nullptr;
	}

	ListNode(T data, ListNode* next)
	{
		this->data = data;
		this->next = next;
	}
};

template<class T, class TofKey> T* findInList(ListNode<T> node, TofKey toFind);
template<class T, class TofKey> void deleteFromList(ListNode<T>& node, TofKey toDelete);

template <class T> struct HashTable
{
	int len = 10;
	int numOfElements = 0;
	ListNode<T>* arr = new ListNode<T>[len](T());
	
	HashTable() = default;
};

template<class T> void displayItem(T a) {};
//template<class T> void displayList(ListNode<T> listNode);
template<class T> void displayHashTable(HashTable<T> hashTable);

template<class T> int getKey(T elem) {};
template<class T> int getValueOfKey(T elem) {};

template<class T> void insertToHashTable(HashTable<T>& hashTable, T elem);
template<class TofElem, class TofKey> void deleteFromHashTable(HashTable<TofElem>& hashTable, TofKey key);
template<class TofElem, class TofKey> TofElem* findByKey(HashTable<TofElem> hashTable, TofKey key);
template<class T> void rehash(HashTable<T>& hashTable);

