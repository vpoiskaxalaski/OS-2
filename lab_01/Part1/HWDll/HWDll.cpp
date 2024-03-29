// HWDll.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "direct.h"
#include<fstream>
#include<iostream>


extern "C++" __declspec(dllexport) void WriteToFile(char* filePath, char* textToWrite)
{
	std::ofstream fout;
	fout.open(filePath);
	fout << textToWrite;
	fout.close();
}

extern "C++" __declspec(dllexport) void RunNewProcess()
{
	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;
	TCHAR buf[] = TEXT("mspaint.exe");
	

	if (!(CreateProcess(NULL, buf, NULL, NULL, FALSE, 0, NULL, NULL, &cif, &pi)))
		std::wcout << "Error " << '\n';

}

extern "C++" __declspec(dllexport) void IsFileInDir(wchar_t* file, wchar_t* dirPath)
{
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA ffd;
	SetCurrentDirectory(dirPath);
	hFind = FindFirstFile(dirPath, &ffd);
	if (INVALID_HANDLE_VALUE == hFind) {
		std::cout << "Dir is empty!" << std::endl;
	}

	do
	{
		if (wcscmp(ffd.cFileName, file) == 0)
			std::wcout <<"File is found: "<< file << std::endl;
	} while (FindNextFile(hFind, &ffd) != 0);
}

