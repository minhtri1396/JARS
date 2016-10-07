#include "stdafx.h"
#include "CText.h"
#include <math.h>

LPWSTR CText::GetInfoFrom(_In_ HWND hWnd, _Out_ size_t& uiInfoLength)
{
	uiInfoLength = GetWindowTextLength(hWnd);
	if (uiInfoLength)
	{
		LPWSTR lpwStr = new WCHAR[uiInfoLength + 1];
		GetWindowText(hWnd, lpwStr, uiInfoLength + 1);
		return lpwStr;
	}
	return nullptr;
}

//Clear whitespaces
size_t CText::CleanWString(_Inout_opt_ LPWSTR& lpwStr)
{
	INT k = 0;
	LPWSTR lpwNewStr = new WCHAR[wcslen(lpwStr) + 1];
	for (INT i = 0; lpwStr[i]; ++i)
	{
		if (lpwStr[i] != 32)
		{
			lpwNewStr[k++] = lpwStr[i];
		}
	}

	lpwNewStr[k] = 0;
	delete[]lpwStr;
	lpwStr = lpwNewStr;

	return wcslen(lpwStr);
}

int CountDigitOf(long value)
{
	int count = 0;
	while (value)
	{
		++count;
		value /= 10;
	}

	return count;
}

//Convert integer or real number to UNICODE (LPWSTR)
LPWSTR CText::NumberToWCS(_In_ double number, _In_ SHORT nDecimalPlaces)
{
	LPWSTR lpwTemp = new WCHAR[20];
	LPWSTR lpwStr = new WCHAR[20];
	lpwStr[0] = 0;
	if (number < 0) wcscat(lpwStr, L"-");
	//Get integer place (lpwTemp saves integer place of number now)
	double integer = floor(number);
	if (integer != 0) {
		INT numberOfDigit = (INT)log10(integer) + 1;
		lpwTemp[numberOfDigit] = 0;
		WCHAR wcDigit[2];
		while (numberOfDigit > 0)
		{
			INT digit = INT(integer - 10 * floor(integer / 10));
			_itow(digit, wcDigit, 10);
			lpwTemp[--numberOfDigit] = wcDigit[0];
			integer /= 10;
		}
	}
	else
	{
		lpwTemp[0] = '0', lpwTemp[1] = 0;
	}
	wcscat(lpwStr, lpwTemp);
	//Get decimal place (lpwTemp saves decimal place of number now)
	integer = floor(number);
	long decimal = (number - integer) * pow(10, nDecimalPlaces); //get n decimal places
	if (decimal != 0) //it has decimal place
	{
		wcscat(lpwStr, L"."); //decimal point
		int nDigits = CountDigitOf(decimal);
		if (nDigits != nDecimalPlaces)
		{
			for (int i = nDecimalPlaces - nDigits; i > 0; --i)
			{
				wcscat(lpwStr, L"0");
			}
		}
		wcscat(lpwStr, _itow(decimal, lpwTemp, 10));
	}
	delete[]lpwTemp;

	return lpwStr;
}
