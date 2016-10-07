#include <Windows.h>

#ifndef CMONEY
#define CMONEY

class CMoney
{
private:
	wchar_t *m_szNecessary; //Ex: 100.000.000.000 VND + '\0' = 20
	wchar_t *m_szInvestment; //Ex: 100.000.000.000 VND + '\0' = 20
	wchar_t *m_szEducation; //Ex: 100.000.000.000 VND + '\0' = 20
	wchar_t *m_szLongTerm; //Ex: 100.000.000.000 VND + '\0' = 20
	wchar_t *m_szEnjoyment; //Ex: 100.000.000.000 VND + '\0' = 20
	wchar_t *m_szGiving; //Ex: 100.000.000.000 VND + '\0' = 20

	_Success_(return == FALSE)
		BOOL IsInvalid(_In_opt_ LPWSTR lpwStr);
	//Before running this function, you should run IsInvalid funtion
	//Clear whitespaces and dots to calculate conveniently. Ex: 10.000.000 => 10000000
	size_t Standardize(_Inout_opt_ LPWSTR& lpwStr);
	//Before running this function, you should run Standardize function
	//Ex: 10000 => 10.000
	size_t AddDots(_Inout_opt_ LPWSTR& lpwStr);

	void RemoveMemory();
public:
	wchar_t* GetNecessary();
	wchar_t* GetInvestment();
	wchar_t* GetEducation();
	wchar_t* GetLongTerm();
	wchar_t* GetEnjoyment();
	wchar_t* GetGiving();

	CMoney();
	~CMoney();
	bool SetMoney(wchar_t *&szMoney);
};

#endif