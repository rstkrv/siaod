#include "general.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include "task5.h"
#include "task6.h"
#include "task7.h"
#include "task8.h"

int main()
{
	setlocale(LC_ALL, "");
	system("chcp 1251");
	Base* cnsl = setup();
	while (cnsl != nullptr)
	{
		callRun(*cnsl);
		cnsl = setup();
	}
}
