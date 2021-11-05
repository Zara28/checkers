﻿// shashki.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "shashki.h"
#include "resource1.h"

#include "windowsx.h"
#include "winuser.h"

#include "stdio.h"
#define WIN32_LEAN_AND_MEAN            
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LOADSTRING 100
int x, y;
int page = 0;
BOOL WINAPI MoveWindow(
    _In_  HWND hWnd,
    _In_  int X,
    _In_  int Y,
    _In_  int nWidth,
    _In_  int nHeight,
    _In_  BOOL bRepaint
);
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

POINT p;
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SHASHKI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SHASHKI));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SHASHKI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SHASHKI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 600, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//

//void Menu(HWND hwnd)
//{
//    HMENU menu = CreateMenu();
//    AppendMenu(menu, MF_POPUP, 1, L"Горячие клавиши");
//    SetMenu(hwnd, menu);
//}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case ID_Save:
                SaveField();
                break;
            case ID_Menu:
                page = 0;
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            case ID_Download:
                DownloadField();
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            case ID_Random:
                RandomField();
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            case ID_Inctruction:
                page = 2;
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            case ID_About:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case ID_Again:
                page = 1;
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_LBUTTONDOWN:
        x = GET_X_LPARAM(lParam);
        y = GET_Y_LPARAM(lParam);
        ChooseElem(x, y);
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_RBUTTONDOWN:
        x = GET_X_LPARAM(lParam);
        y = GET_Y_LPARAM(lParam);
        MoveElem(x, y);
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case 83:
            SaveField();
            break;
        case 68:
            DownloadField();
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case 82:
            RandomField();
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case 77:
            page = 0;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case 80:
            page = 1;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case 73:
            page = 2;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
    }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            HBITMAP hBitmap;
            HDC             hdcMem;
            HGDIOBJ         oldBitmap;
         //   MoveWindow(hWnd, 0, 0, 600, 600, NULL);
           // Menu(hWnd);
            switch (page)
            {
            case 0:
            {
                hBitmap = (HBITMAP)LoadImage(hInst, L"menu.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
                DrawMenu(hdc, hBitmap);
                break;
            }
            case 1:
            {
                DrawField(hdc);
                break;
            }
            case 2:

                hBitmap = (HBITMAP)LoadImage(hInst, L"rules.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
                DrawIncstruction(hdc, hBitmap);
                break;
            }


            EndPaint(hWnd, &ps);
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

// Обработчик сообщений для окна "О программе".
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



