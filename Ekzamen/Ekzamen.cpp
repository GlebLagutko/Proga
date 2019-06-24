#include "stdafx.h"
#include "Resource.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <ostream>
#include <iostream>
#include <commdlg.h>
#include <string>
#include <xlocmon>


//===============================================================
//===============================================================

//Function i*i - 3*i + 3
#define DLGTITLE  L"My dialog"
#define DLGFONT   L"MS Shell Dlg"

extern "C" { int __fastcall DecToBin(int y, int* x); }

bool down = false;
bool changes = false;
int a;
int b;
int* c =  new int[16] ;
bool ok = false;

int answer = 0;

DWORD rgbPar = RGB(0, 200, 100);
DWORD rgbSin = RGB(100, 0, 200);
HMENU hMenubar;
HMENU hMenu;




namespace Control
{
	int const IDC_TestTextBoxB = 1001;
	int const IDC_TestTextBoxA = 1002;
	int const IDC_TestButton = 1003;
	int const IDC_TestTextBoxC = 1004;
	int const IDC_TestARadioButton = 1005;
	int const IDC_TestBRadioButton = 1006;
	int const IDC_TestComboBox = 1007;
	int const IDC_InvisibleButton = 1008;
	int const IDC_Test2GroupBox = 1009;
	int const IDC_TestCRadioButton = 1010;
	int const IDC_TestDRadioButton = 1011;
	int const IDC_MessageButton = 1012;
	int const IDC_TestLabel = 1013;
}

#pragma pack(push, 4)                 
static struct
{
	DWORD  style;
	DWORD  dwExtendedStyle;
	WORD   ccontrols; // ?????????? ?????????. ???????? ????? ????????? ????? ???, ? ???? ????????? ????? ???? ?????, ?? ??????
	short  x;
	short  y;
	short  cx;
	short  cy;
	WORD   menu;
	WORD   windowClass;
	WCHAR  wszTitle[ARRAYSIZE(DLGTITLE)];
	short  pointsize; // ??????????????? ?????????. ??. FromUnit ??? ?????????????? ?????????.
	WCHAR  wszFont[ARRAYSIZE(DLGFONT)];
}
EmptyDialogTemplate =
{
   DS_SHELLFONT | DS_SETFONT | DS_MODALFRAME | DS_FIXEDSYS | WS_POPUP | WS_CAPTION | WS_SYSMENU, // ?????????!
   0x0,
   0,
   0, 0, 400, 200,
   0,                       // menu: none
   0,                       // window class: none
   DLGTITLE,                // Window caption
   8,                       // font pointsize
   DLGFONT,
};
#pragma pack(pop)




double GetNewParamm(HWND hWnd)
{
	auto textLength = GetWindowTextLengthW(hWnd);
	auto buffer = new wchar_t[textLength + 1];
	GetWindowText(hWnd, buffer, textLength + 1);
	double result = wcstod(buffer, NULL);
	return result;
}


//===============================================================
//===============================================================

#define MAX_LOADSTRING 100
HWND hWnd;
HWND hwndDlg;
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING] = L"Drawing";
WCHAR szWindowClass[MAX_LOADSTRING] = L"Drawing_App";

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HWND _hDialog;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDRAWING));

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



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = nullptr;



	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);



	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}



INT_PTR CALLBACK DlgProc(HWND hwndDlg, UINT msg, WPARAM wParam,
	LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		CreateWindowEx(NULL, TEXT("STATIC"), TEXT("Input a : "),
			WS_CHILD | WS_VISIBLE, 30, 10, 60,
			20, hwndDlg, nullptr, nullptr, nullptr);
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE, 100, 10, 60,
			20, hwndDlg, (HMENU)Control::IDC_TestTextBoxA, nullptr, nullptr);

		CreateWindowEx(NULL, TEXT("STATIC"), TEXT("Input b : "),
			WS_CHILD | WS_VISIBLE, 30, 40, 60,
			20, hwndDlg, nullptr, nullptr, nullptr);
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE, 100, 40, 60,
			20, hwndDlg, (HMENU)Control::IDC_TestTextBoxB, nullptr, nullptr);

		CreateWindowEx(NULL, TEXT("STATIC"), TEXT("Answer : "),
			WS_CHILD | WS_VISIBLE, 30, 70, 60,
			20, hwndDlg, nullptr, nullptr, nullptr);
		CreateWindowEx(NULL, TEXT("STATIC"), TEXT("result "),
			WS_CHILD | WS_VISIBLE, 100, 70, 300,
			20, hwndDlg, (HMENU)Control::IDC_TestTextBoxC, nullptr, nullptr);


		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Button"), TEXT("Ok"),
			WS_CHILD | WS_VISIBLE, 100, 100, 30,
			20, hwndDlg, (HMENU)Control::IDC_TestButton, NULL, NULL);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
	{
		if (wParam == Control::IDC_TestButton)
		{
			auto TextA = GetDlgItem(hwndDlg, Control::IDC_TestTextBoxA);
			auto TextB = GetDlgItem(hwndDlg, Control::IDC_TestTextBoxB);
			auto Label = GetDlgItem(hwndDlg,Control::IDC_TestTextBoxC);
			if (GetWindowTextLengthW(TextA) != 0)
				a = GetNewParamm(TextA);

			if (GetWindowTextLengthW(TextB) != 0)
				b = GetNewParamm(TextB);

			for (int i = 0;i < 16; i++)
			{
				c[i] = 0;
			}

			__asm
			{
			      mov ecx,a
				  mov edx,c
				  call DecToBin
				
				
			}
			

			std::wstring result;
			int k = 0;

			while (c[k] == 0)
				k++;

			for (int i = k; i < 16; i++)
			{

				int d = c[i];
				result += std::to_wstring(c[i]);
			}

			

			SendMessageW(Label, WM_SETTEXT, 10, (LPARAM)&result[0]);
			//EndDialog(hwndDlg, IDCANCEL);
		}
	}
	break;
	case WM_CLOSE:
	{
		EndDialog(hwndDlg, 0);
		return FALSE;
	}
	}
	return FALSE;

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	RECT rc;
	static HDC hdcCompat;    // DC for copying bitmap  
	static RECT rcBmp;       // rectangle that encloses bitmap  
	static RECT rcTarget;    // rectangle to receive bitmap  
	static RECT rcClient;    // client-area rectangle  
	static BOOL fDragRect;   // TRUE if bitmap rect. is dragged  
	static HBITMAP hbmp;     // handle of bitmap to display  
	static HBRUSH hbrBkgnd;  // handle of background-color brush  
	static COLORREF crBkgnd; // color of client-area background  
	static POINT pt;
	static HPEN hpenDot;


	PAINTSTRUCT ps;

	switch (message)
	{
	


	case WM_LBUTTONDOWN:
	{
		hdc = GetDC(hWnd);
		DialogBoxIndirectParamW(hInst, (LPCDLGTEMPLATEW)&EmptyDialogTemplate, hWnd, DlgProc, NULL);
		GetClientRect(hWnd, &rc);
		FillRect(hdc, &rc, (HBRUSH)(COLOR_WINDOW + 1));


		ReleaseDC(hWnd, hdc);

	}
	break;
	


	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
