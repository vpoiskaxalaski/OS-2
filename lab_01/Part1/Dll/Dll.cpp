// Dll.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

extern "C++" __declspec(dllexport) void LetterList()
{
	std::cout << "This function was called from LetterList() " << std::endl;
}
extern "C++" __declspec(dllexport) int PutInt(int param)
{
	return param;
}
