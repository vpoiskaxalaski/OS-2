// CallDll.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "Dll.h"
#include<iostream>
#include<conio.h>

int main()
{
	int x = PutInt(5);
	LetterList();
	std::cout << x;
	_getch();
	return 0;
}
