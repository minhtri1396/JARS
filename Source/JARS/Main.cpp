// JARS.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Main.h"
#include "CMoney.h"
#include "CText.h"

#include <windowsx.h>
#include <commdlg.h>
#include <commctrl.h>
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND hwndAmountOfMoney;
HWND hwndNecessary;
HWND hwndInvestment;
HWND hwndEducation;
HWND hwndLongTerm;
HWND hwndEnjoyment;
HWND hwndGiving;

CMoney controlMoney;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//Command functions
VOID				OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
BOOL				OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
VOID				OnPaint(HWND hWnd);
HBRUSH				OnCtlColor(HWND hwnd, HDC hdc, HWND hwndChild, int type);
VOID				OnDestroy(HWND hWnd);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_JARS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_JARS));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_JARS));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_JARS);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0, 1010, 625, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_CTLCOLORSTATIC, OnCtlColor);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);

	// Get system font
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont32 = CreateFont(32, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	HFONT hFont20 = CreateFont(20, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	HFONT hFont18 = CreateFont(18, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	//Title background
	CreateWindowEx(0, WC_STATIC, L"", WS_CHILD | WS_VISIBLE | SS_CENTER,
		0, 20, 1000, 75, hWnd, (HMENU)IDC_BACK_TITLE, hInst, NULL);

	HWND wnd = CreateWindowEx(0, WC_STATIC, L"MANAGER MONEY WITH JARS", WS_CHILD | WS_VISIBLE | SS_CENTER,
		10, 40, 1000, 28, hWnd, (HMENU)IDC_TITLE, hInst, NULL);
	SendMessage(wnd, WM_SETFONT, (WPARAM)hFont32, TRUE);

	//Instruction
	wnd = CreateWindowEx(0, WC_STATIC, L"INSTRUCTION:", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		15, 100, 125, 38, hWnd, (HMENU)IDC_TEXT, hInst, NULL);
	SendMessage(wnd, WM_SETFONT, (WPARAM)hFont20, TRUE);

	wnd = CreateWindowEx(0, WC_STATIC, L"1. Input amount of money you want to divide.", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		25, 125, 350, 38, hWnd, (HMENU)IDC_TEXT, hInst, NULL);
	SendMessage(wnd, WM_SETFONT, (WPARAM)hFont18, TRUE);

	wnd = CreateWindowEx(0, WC_STATIC, L"2. Click on button \"Start\" to start dividing.", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		25, 150, 350, 38, hWnd, (HMENU)IDC_TEXT, hInst, NULL);
	SendMessage(wnd, WM_SETFONT, (WPARAM)hFont18, TRUE);

	wnd = CreateWindowEx(0, WC_STATIC, L"3. Receive the result.", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		25, 175, 350, 38, hWnd, (HMENU)IDC_TEXT, hInst, NULL);
	SendMessage(wnd, WM_SETFONT, (WPARAM)hFont18, TRUE);


	//Input money
	wnd = CreateWindowEx(0, WC_BUTTON, L"START", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		800, 125, 100, 38, hWnd, (HMENU)IDC_BTN_START, hInst, NULL);
	SendMessage(wnd, WM_SETFONT, (WPARAM)hFont20, TRUE);

	hwndAmountOfMoney = CreateWindowEx(0, WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
		570, 125, 200, 38, hWnd, (HMENU)IDC_TEXT, hInst, NULL);
	SendMessage(hwndAmountOfMoney, WM_SETFONT, (WPARAM)hFont32, TRUE);


	int moveBoxY = 100; //cause when design boxes, we have set some y for boxes and we need to move these boxes now,
					   //so we use this variable (moveBoxY) to move the boxes.
	//Necessary
	CreateWindowEx(0, WC_STATIC, L"", WS_CHILD | WS_VISIBLE,
		0, 120 + moveBoxY, 500, 100, hWnd, (HMENU)IDC_NECESSARY, hInst, NULL);

	wnd = CreateWindowEx(0, WC_STATIC, L"FOR NECESSARY (55%)", WS_CHILD | WS_VISIBLE | SS_CENTER,
		0, 125 + moveBoxY, 500, 22, hWnd, (HMENU)IDC_NECESSARY, hInst, NULL);
	SendMessage(wnd, WM_SETFONT, (WPARAM)hFont20, TRUE);

	hwndNecessary = CreateWindowEx(0, WC_STATIC, L"0 VND", WS_CHILD | WS_VISIBLE | SS_CENTER,
		0, 165 + moveBoxY, 500, 50, hWnd, (HMENU)IDC_NECESSARY, hInst, NULL);
	SendMessage(hwndNecessary, WM_SETFONT, (WPARAM)hFont32, TRUE);

	//Investment
	CreateWindowEx(0, WC_STATIC, L"", WS_CHILD | WS_VISIBLE,
		505, 120 + moveBoxY, 500, 100, hWnd, (HMENU)IDC_INVESTMENT, hInst, NULL);

	wnd = CreateWindowEx(0, WC_STATIC, L"FOR INVESTMENT (10%)", WS_CHILD | WS_VISIBLE | SS_CENTER,
		505, 125 + moveBoxY, 500, 22, hWnd, (HMENU)IDC_INVESTMENT, hInst, NULL);
	SendMessage(wnd, WM_SETFONT, (WPARAM)hFont20, TRUE);

	hwndInvestment = CreateWindowEx(0, WC_STATIC, L"0 VND", WS_CHILD | WS_VISIBLE | SS_CENTER,
		505, 165 + moveBoxY, 500, 50, hWnd, (HMENU)IDC_INVESTMENT, hInst, NULL);
	SendMessage(hwndInvestment, WM_SETFONT, (WPARAM)hFont32, TRUE);

	//Education
	CreateWindowEx(0, WC_STATIC, L"", WS_CHILD | WS_VISIBLE,
		0, 230 + moveBoxY, 500, 100, hWnd, (HMENU)IDC_EDUCATION, hInst, NULL);

	wnd = CreateWindowEx(0, WC_STATIC, L"FOR EDUCATION (10%)", WS_CHILD | WS_VISIBLE | SS_CENTER,
		0, 235 + moveBoxY, 500, 22, hWnd, (HMENU)IDC_EDUCATION, hInst, NULL);
	SendMessage(wnd, WM_SETFONT, (WPARAM)hFont20, TRUE);

	hwndEducation = CreateWindowEx(0, WC_STATIC, L"0 VND", WS_CHILD | WS_VISIBLE | SS_CENTER,
		0, 275 + moveBoxY, 500, 50, hWnd, (HMENU)IDC_EDUCATION, hInst, NULL);
	SendMessage(hwndEducation, WM_SETFONT, (WPARAM)hFont32, TRUE);

	//Long-term
	CreateWindowEx(0, WC_STATIC, L"", WS_CHILD | WS_VISIBLE,
		505, 230 + moveBoxY, 500, 100, hWnd, (HMENU)IDC_LONG_TERM, hInst, NULL);

	wnd = CreateWindowEx(0, WC_STATIC, L"FOR LONG-TERM (10%)", WS_CHILD | WS_VISIBLE | SS_CENTER,
		505, 235 + moveBoxY, 500, 22, hWnd, (HMENU)IDC_LONG_TERM, hInst, NULL);
	SendMessage(wnd, WM_SETFONT, (WPARAM)hFont20, TRUE);

	hwndLongTerm = CreateWindowEx(0, WC_STATIC, L"0 VND", WS_CHILD | WS_VISIBLE | SS_CENTER,
		505, 275 + moveBoxY, 500, 50, hWnd, (HMENU)IDC_LONG_TERM, hInst, NULL);
	SendMessage(hwndLongTerm, WM_SETFONT, (WPARAM)hFont32, TRUE);

	//Enjoyment
	CreateWindowEx(0, WC_STATIC, L"", WS_CHILD | WS_VISIBLE,
		0, 340 + moveBoxY, 500, 100, hWnd, (HMENU)IDC_ENJOYMENT, hInst, NULL);

	wnd = CreateWindowEx(0, WC_STATIC, L"FOR ENJOYMENT (10%)", WS_CHILD | WS_VISIBLE | SS_CENTER,
		0, 345 + moveBoxY, 500, 22, hWnd, (HMENU)IDC_ENJOYMENT, hInst, NULL);
	SendMessage(wnd, WM_SETFONT, (WPARAM)hFont20, TRUE);

	hwndEnjoyment = CreateWindowEx(0, WC_STATIC, L"0 VND", WS_CHILD | WS_VISIBLE | SS_CENTER,
		0, 385 + moveBoxY, 500, 50, hWnd, (HMENU)IDC_ENJOYMENT, hInst, NULL);
	SendMessage(hwndEnjoyment, WM_SETFONT, (WPARAM)hFont32, TRUE);

	//Giving
	CreateWindowEx(0, WC_STATIC, L"", WS_CHILD | WS_VISIBLE,
		505, 340 + moveBoxY, 500, 100, hWnd, (HMENU)IDC_GIVING, hInst, NULL);

	wnd = CreateWindowEx(0, WC_STATIC, L"FOR GIVING (5%)", WS_CHILD | WS_VISIBLE | SS_CENTER,
		505, 345 + moveBoxY, 500, 22, hWnd, (HMENU)IDC_GIVING, hInst, NULL);
	SendMessage(wnd, WM_SETFONT, (WPARAM)hFont20, TRUE);

	hwndGiving = CreateWindowEx(0, WC_STATIC, L"0 VND", WS_CHILD | WS_VISIBLE | SS_CENTER,
		505, 385 + moveBoxY, 500, 50, hWnd, (HMENU)IDC_GIVING, hInst, NULL);
	SendMessage(hwndGiving, WM_SETFONT, (WPARAM)hFont32, TRUE);

	return TRUE;
}

VOID OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	int wmId = id;
	// Parse the menu selections:
	switch (wmId)
	{
	case IDC_BTN_START:
	{
		size_t lengthMoney;
		wchar_t *szMoney = CText::GetInfoFrom(hwndAmountOfMoney, lengthMoney);

		if (!lengthMoney)
		{
			MessageBox(0, L"Amount of money can not be blank.", L"Empty error", 0);
		}
		else
		{
			if (controlMoney.SetMoney(szMoney))
			{
				wchar_t szMoney[20]; //Ex: 100.000.000.000 VND + '\0' = 20

				wcscpy(szMoney, controlMoney.GetNecessary());
				wcscat(szMoney, L" VND");
				SetWindowText(hwndNecessary, szMoney);

				wcscpy(szMoney, controlMoney.GetInvestment());
				wcscat(szMoney, L" VND");
				SetWindowText(hwndInvestment, szMoney);

				wcscpy(szMoney, controlMoney.GetEducation());
				wcscat(szMoney, L" VND");
				SetWindowText(hwndEducation, szMoney);

				wcscpy(szMoney, controlMoney.GetLongTerm());
				wcscat(szMoney, L" VND");
				SetWindowText(hwndLongTerm, szMoney);

				wcscpy(szMoney, controlMoney.GetEnjoyment());
				wcscat(szMoney, L" VND");
				SetWindowText(hwndEnjoyment, szMoney);

				wcscpy(szMoney, controlMoney.GetGiving());
				wcscat(szMoney, L" VND");
				SetWindowText(hwndGiving, szMoney);
			}

			delete[]szMoney;
		}
	}
		break;
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	}
}

VOID OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	// TODO: Add any drawing code that uses hdc here...
	EndPaint(hWnd, &ps);
}

HBRUSH OnCtlColor(HWND hwnd, HDC hdc, HWND hwndChild, int type)
{
	DWORD CtrlID = GetDlgCtrlID(hwndChild); //Window Control ID

	switch (CtrlID)
	{
	case IDC_TITLE:
	{
		HBRUSH hBrush = CreateSolidBrush(RGB(153, 209, 211));
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(153, 209, 211));
		return hBrush;
	}
	case IDC_BACK_TITLE:
	{
		HBRUSH hBrush = CreateSolidBrush(RGB(153, 209, 211));
		return hBrush;
	}
	case IDC_TEXT:
	{
		HBRUSH hBrush = CreateSolidBrush(RGB(240, 240, 240));
		SetTextColor(hdc, RGB(54, 54, 54));
		SetBkColor(hdc, RGB(240, 240, 240));
		return hBrush;
	}
	case IDC_NECESSARY:
	{
		HBRUSH hBrush = CreateSolidBrush(RGB(131, 199, 93));
		SetTextColor(hdc, RGB(54, 54, 54));
		SetBkColor(hdc, RGB(131, 199, 93));
		return hBrush;
	}
	case IDC_INVESTMENT:
	{
		HBRUSH hBrush = CreateSolidBrush(RGB(103, 191, 127));
		SetTextColor(hdc, RGB(54, 54, 54));
		SetBkColor(hdc, RGB(103, 191, 127));
		return hBrush;
	}
	case IDC_EDUCATION:
	{
		HBRUSH hBrush = CreateSolidBrush(RGB(200, 226, 177));
		SetTextColor(hdc, RGB(54, 54, 54));
		SetBkColor(hdc, RGB(200, 226, 177));
		return hBrush;
	}
	case IDC_LONG_TERM:
	{
		HBRUSH hBrush = CreateSolidBrush(RGB(0, 132, 137));
		SetTextColor(hdc, RGB(54, 54, 54));
		SetBkColor(hdc, RGB(0, 132, 137));
		return hBrush;
	}
	case IDC_ENJOYMENT:
	{
		HBRUSH hBrush = CreateSolidBrush(RGB(148, 170, 214));
		SetTextColor(hdc, RGB(54, 54, 54));
		SetBkColor(hdc, RGB(148, 170, 214));
		return hBrush;
	}
	case IDC_GIVING:
	{
		HBRUSH hBrush = CreateSolidBrush(RGB(210, 166, 199));
		SetTextColor(hdc, RGB(54, 54, 54));
		SetBkColor(hdc, RGB(210, 166, 199));
		return hBrush;
	}
	default:
		return CreateSolidBrush(COLOR_BTNFACE);
	} //switch
}

VOID OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
}
