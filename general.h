#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <bitset>
#include <cctype>
#include <iomanip>
#include <random>
#include <set>
#include <map>
#include <array>
#include <limits>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <codecvt>
#include <Windows.h>
#include <queue>

using namespace std;

//bool isnumber(string str);
bool numcheck(string str, double lower, double upper);

class Base
{
public:
	virtual int run() = 0;
};

class Console : public Base
{
	int run();
public:
	Console();
	~Console();
};

Base * setup();

int callRun(Base& cnsl);

long long inpInt(long long lower, long long upper);

vector<long long>* inpVecOfInt(long long maxLen, long long lower, long long upper);

int randInt(int lower, int upper);

istream& getManyLines(istream& stream, string& str);
