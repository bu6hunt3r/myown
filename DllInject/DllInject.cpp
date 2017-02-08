// DllInject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <TlHelp32.h>
#include <Windows.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	typedef HINSTANCE (*fpLoadLibrary)(char*);
	char FileToInject[]="";
	char ProcessName[]="";
	return 0;
}

