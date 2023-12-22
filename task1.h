#pragma once
#include "general.h"

class ConsoleFor1 : public Console
{
public:
	ConsoleFor1();
	~ConsoleFor1();
	void com1();
	void com2();
	void com3();
	void com4();
	void com5();
	void com6();
	void com7();
	int run();
};

unsigned char bit5to0(unsigned char num);

unsigned char bit7to0(unsigned char num);

void toBin(unsigned int x);

void ucharSort(vector<long long>& arr);