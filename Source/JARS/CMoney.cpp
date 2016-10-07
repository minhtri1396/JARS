#include "stdafx.h"
#include "CMoney.h"
#include "CText.h"

#define MSG_EMPTY_ERROR L"Money and Interest Rate must be fill in completely.", L"Empty error"
#define MSG_DOT_ERROR L"You wrote invalid dots.\
					\n  Some invalid dots:\n    + 1.2.\n    + 10.5.256\n\
					\n  Some valid dots:\n    + 5.\n    + .5\n    + 10.000.000", L"Dot error"
#define MSG_CHARACTER_ERROR L"You wrote invalid characters. Valid characters:\
					\n    + Dot (.)\n\n    + Whitespace\n\n    + 0 -> 9", L"Character error"

_Success_(return == FALSE)
BOOL CMoney::IsInvalid(_In_opt_ LPWSTR lpwStr)
{
	if (lpwStr == nullptr)
	{
		MessageBox(0, MSG_EMPTY_ERROR, 0);
		return TRUE;
	}

	BOOL fValidSyntax = TRUE;
	SHORT countDigit = 0; //the number of digit after dot.
	SHORT countDot = 0;
	for (INT i = wcslen(lpwStr) - 1; i >= 0; --i)
	{
		if (lpwStr[i] == '.') //checking if it's real or integer number
		{
			++countDot;
			if (countDigit != 3)
				fValidSyntax = FALSE; //maybe this number is a real number, so the first wrong we ignore
			if (countDot > 1 && !fValidSyntax)
			{
				MessageBox(0, MSG_DOT_ERROR, 0);
				return TRUE;
			}
			countDigit = 0;
		}
		else if (lpwStr[i] != 32 && ((lpwStr[i] - 48) > 9 || (lpwStr[i] - 48) < 0)) //whether string contains invalid character
		{
			MessageBox(0, MSG_CHARACTER_ERROR, 0);
			return TRUE;
		}
		else if (lpwStr[i] != 32) ++countDigit;
	}

	return FALSE;
}

//Before running this function, you should run IsInvalid funtion
//Clear whitespaces and dots to calculate conveniently. Ex: 10.000.000 => 10000000
size_t CMoney::Standardize(_Inout_opt_ LPWSTR& lpwStr)
{
	SHORT countDot = 0, i = -1;
	INT oldLen = wcslen(lpwStr);
	LPWSTR lpwNewStr = new WCHAR[oldLen + 1];
	//Clear dots if it's not the decimal point
	while (lpwStr[++i])
	{
		if (lpwStr[i] == '.')
		{
			++countDot;
			if (countDot == 1) lpwNewStr[i] = lpwStr[i]; //suppose that this Dot is decimal point
		}
		else lpwNewStr[i - (countDot > 1 ? countDot - 1 : 0)] = lpwStr[i]; //countDot - 1 <=> eliminate decimal point
	}
	lpwNewStr[i - (countDot > 1 ? countDot - 1 : 0)] = 0;

	delete[]lpwStr;
	if (countDot > 1) //it's not a decimal point
	{
		lpwStr = new WCHAR[oldLen - countDot + 1];
		int j = 0;
		for (int i = 0; lpwNewStr[i]; ++i)
		{
			if (lpwNewStr[i] != '.') lpwStr[j++] = lpwNewStr[i];
		}
		lpwStr[j] = 0;
	}
	else lpwStr = _wcsdup(lpwNewStr);
	delete[]lpwNewStr;
	//Clear whitespaces
	CText::CleanWString(lpwStr);

	return wcslen(lpwStr);
}

//Before running this function, you should run Standardize function
//Ex: 10000 => 10.000
size_t CMoney::AddDots(_Inout_opt_ LPWSTR& lpwStr)
{
	SHORT numberOfDots = wcslen(lpwStr) / 3; //the number of dot need to add in number
	if (numberOfDots * 3 == wcslen(lpwStr)) --numberOfDots; //Ex: 500 => numberOfDots = 0, 50 000 => numberOfDots = 1

	SHORT countDigit = 0;
	INT k = numberOfDots + wcslen(lpwStr) - 1;
	LPWSTR lpwNewStr = new WCHAR[k + 2];
	for (INT i = wcslen(lpwStr) - 1; i >= 0; --i)
	{
		if (lpwStr[i] == '.') //this number is a real number
		{
			delete[]lpwNewStr;
			return wcslen(lpwStr);
		}

		++countDigit;
		lpwNewStr[k--] = lpwStr[i];
		if (countDigit == 3 && i > 0)
		{
			countDigit = 0;
			lpwNewStr[k--] = ',';
		}
	}
	lpwNewStr[numberOfDots + wcslen(lpwStr)] = 0;

	delete[]lpwStr;
	lpwStr = lpwNewStr;

	return wcslen(lpwStr);
}

wchar_t* CMoney::GetNecessary()
{
	return &m_szNecessary[0];
}

wchar_t* CMoney::GetInvestment()
{
	return &m_szInvestment[0];
}

wchar_t* CMoney::GetEducation()
{
	return &m_szEducation[0];
}

wchar_t* CMoney::GetLongTerm()
{
	return &m_szLongTerm[0];
}

wchar_t* CMoney::GetEnjoyment()
{
	return &m_szEnjoyment[0];
}

wchar_t* CMoney::GetGiving()
{
	return &m_szGiving[0];
}

void CMoney::RemoveMemory()
{
	delete[]m_szNecessary;
	delete[]m_szInvestment;
	delete[]m_szEducation;
	delete[]m_szLongTerm;
	delete[]m_szEnjoyment;
	delete[]m_szGiving;
}

CMoney::CMoney()
{
	m_szNecessary = m_szInvestment = m_szEducation = m_szLongTerm = NULL;
	m_szEnjoyment = m_szGiving = NULL;
}

CMoney::~CMoney()
{
	RemoveMemory();
}

bool CMoney::SetMoney(wchar_t *&szMoney)
{
	CText::CleanWString(szMoney);
	if (IsInvalid(szMoney))
	{
		return false;
	}

	RemoveMemory();
	Standardize(szMoney);

	double money = _wtof(szMoney);

	//Necessary
	double necessary = money * 0.55; // 55%
	m_szNecessary = CText::NumberToWCS(necessary, 2);
	AddDots(m_szNecessary);

	//Investment
	double investment = money * 0.1; // 10%
	m_szInvestment = CText::NumberToWCS(investment, 2);
	AddDots(m_szInvestment);

	//Education
	double education = money * 0.1; // 10%
	m_szEducation = CText::NumberToWCS(education, 2);
	AddDots(m_szEducation);

	//Long-term
	double longterm = money * 0.1; // 10%
	m_szLongTerm = CText::NumberToWCS(longterm, 2);
	AddDots(m_szLongTerm);

	//Enjoying
	double enjoying = money * 0.1; // 10%
	m_szEnjoyment = CText::NumberToWCS(enjoying, 2);
	AddDots(m_szEnjoyment);

	//Giving
	double giving = money - (necessary + investment + education + longterm + enjoying);
	m_szGiving = CText::NumberToWCS(giving, 2);
	AddDots(m_szGiving);

	return true;
}
