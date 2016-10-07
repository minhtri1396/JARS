#include <Windows.h>

#ifndef CTEXT
#define CTEXT

class CText
{
public:
	static LPWSTR GetInfoFrom(_In_ HWND hWnd, _Out_ size_t& uiInfoLength);
	//Clear whitespaces
	static size_t CleanWString(_Inout_opt_ LPWSTR& lpwStr);
	//Convert integer or real number to UNICODE (LPWSTR)
	static LPWSTR NumberToWCS(_In_ double number, _In_ SHORT nDecimalPlaces);
};


#endif