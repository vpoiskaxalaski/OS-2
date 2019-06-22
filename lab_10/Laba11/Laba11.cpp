#include "stdafx.h"
#include <windows.h>
#include <iostream>

using namespace std;

#define WIN_32_LEAN_AND_MEAN

void writeToRegistry(void)
{
	DWORD lRv;
	HKEY hKey;

	lRv = RegOpenKeyEx(    
		HKEY_CURRENT_USER,
		L"Software\\ALENA",
		0,
		KEY_WRITE,         
		&hKey
	);

	if (lRv != ERROR_SUCCESS)
	{
		DWORD dwDisposition;

		lRv = RegCreateKeyEx(   
			HKEY_CURRENT_USER,
			L"Software\\ALENA",
			0,
			NULL,
			REG_OPTION_NON_VOLATILE, // Этот ключ не является изменчивым; это по умолчанию. Информация хранится в файле и сохраняется при перезапуске системы.
			KEY_ALL_ACCESS,         
			NULL,                    
			&hKey,
			&dwDisposition
		);

		DWORD dwValue = 14;
		TCHAR  sr[] = TEXT("notepad.exe");

		RegSetValueEx( 
			hKey,
			L"Number",
			0,
			REG_DWORD,
			reinterpret_cast<BYTE *>(&dwValue), 
			sizeof(dwValue) 
		);

		RegSetValueEx(
			hKey,
			L"NotePad",
			0,
			REG_SZ,
			reinterpret_cast<BYTE *>(&sr),
			24
		);

		RegCloseKey(hKey);
	}
}

void readValueFromRegistry(void)
{
	HKEY hKey;

	DWORD lRv = RegOpenKeyEx(
		HKEY_CURRENT_USER,
		L"Software\\ALENA",
		0,
		KEY_READ,
		&hKey
	);

	if (lRv == ERROR_SUCCESS)
	{
		DWORD BufferSize = sizeof(DWORD);
		DWORD dwRet;
		DWORD cbData;
		DWORD cbVal = 0;

		dwRet = RegQueryValueEx( 
			hKey,
			L"Number",
			NULL,
			NULL,
			(LPBYTE)&cbVal, 
			&cbData 
		);

		if (dwRet == ERROR_SUCCESS)
		{
			cout << "\nValue of Number is " << cbVal << endl;
		}
		else
		{
			cout << "\nRegQueryValueEx failed " << dwRet << endl;
		}

		BYTE byteArray[100];
		DWORD dataSize = sizeof(byteArray);

		dwRet = RegQueryValueEx(
			hKey,
			L"NotePad",
			NULL,
			NULL,
			reinterpret_cast<BYTE*>(&byteArray),
			&dataSize
		);

		LPWSTR text = reinterpret_cast<LPWSTR>(&byteArray);

		if (dwRet == ERROR_SUCCESS)
		{
			char nameproc[100];
			cout << "\nValue of notepad is ";
			for (int i = 0; i < dataSize / sizeof(WCHAR); i++)
			{
				nameproc[i] = (char)text[i];
				cout << (char)text[i];
			}
			nameproc[dataSize / sizeof(WCHAR)] = '\0';
			cout << endl;
			system(nameproc);
		}
		else
		{
			cout << "\nRegQueryValueEx failed " << dwRet << endl;
		}
	}
	else
	{
		cout << "RegOpenKeyEx failed " << lRv << endl;
	}
}

int DeleteRegistryKey()
{
	int lReturn = RegDeleteKey(HKEY_CURRENT_USER, L"Software\\ALENA");
	return lReturn;
}

bool FindRegistryKey(const wchar_t a[])
{
	DWORD lRv;
	HKEY hKey;

	lRv = RegOpenKeyEx(
		HKEY_CURRENT_USER,
		a,
		0,
		KEY_WRITE,
		&hKey
	);

	if (lRv == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GetAll(void)
{
	HKEY hKey;

	DWORD lRv = RegOpenKeyEx(
		HKEY_CURRENT_USER,
		L"Компьютер",
		0,
		KEY_READ,
		&hKey
	);

	if (lRv == ERROR_SUCCESS)
	{
		DWORD BufferSize = sizeof(DWORD);
		DWORD dwRet;
		DWORD cbData;
		DWORD cbVal = 0;

		dwRet = RegQueryValueEx(
			hKey,
			L"Number",
			NULL,
			NULL,
			(LPBYTE)&cbVal,
			&cbData
		);

		if (dwRet == ERROR_SUCCESS)
		{
			cout << "\nValue of Number is " << cbVal << endl;
		}
		else
		{
			cout << "\nRegQueryValueEx failed " << dwRet << endl;
		}

		BYTE byteArray[100];
		DWORD dataSize = sizeof(byteArray);

		dwRet = RegQueryValueEx(
			hKey,
			L"NotePad",
			NULL,
			NULL,
			reinterpret_cast<BYTE*>(&byteArray),
			&dataSize
		);

		LPWSTR text = reinterpret_cast<LPWSTR>(&byteArray);

		if (dwRet == ERROR_SUCCESS)
		{
			char nameproc[100];
			cout << "\nValue of notepad is ";
			for (int i = 0; i < dataSize / sizeof(WCHAR); i++)
			{
				nameproc[i] = (char)text[i];
				cout << (char)text[i];
			}
			nameproc[dataSize / sizeof(WCHAR)] = '\0';
			cout << endl;
			system(nameproc);
		}
		else
		{
			cout << "\nRegQueryValueEx failed " << dwRet << endl;
		}
	}
	else
	{
		cout << "RegOpenKeyEx failed " << lRv << endl;
	}
}

int main()
{
	//GetAll();
	cout << "Write keys?" << endl;
	//system("pause"); 
	writeToRegistry();

	cout << "Read keys and open notepad.exe?" << endl;
	system("pause"); 
	readValueFromRegistry();
	
	cout << "Find PAA " << FindRegistryKey(L"Software\\ALENA") << endl;	
	cout << "Find PEE " << FindRegistryKey(L"Software\\PEE") << endl;

	cout << "Delete keys?" << endl;
	system("pause"); 
	DeleteRegistryKey();
	cout << "Keys are deleted" << endl;

	system("pause");
	return 0;
}