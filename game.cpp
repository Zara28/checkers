#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include "stdio.h"
#define WIN32_LEAN_AND_MEAN            
#include <stdlib.h>  
#include "framework.h"

#include "shashki.h"
// Файлы заголовков среды выполнения C
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "windowsx.h"

#include "windows.h"
#include "winuser.h"
#include <clocale>
//индексы
// 0 - пустота
// 1, 2 - шашки первого и второго игроков
// -1 - подсветка возможного хода
int field[8][8] = {
	{0, 2, 0, 2, 0, 2, 0, 2},
	{2, 0, 2, 0, 2, 0, 2, 0},
	{0, 2, 0, 2, 0, 2, 0, 2},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 1, 0, 1, 0, 1, 0},
	{0, 1, 0, 1, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 0, 1, 0},
};
int numberPlayer = 1;
bool turn_field = false;
int game_checker_i;
int game_checker_j;
int sizeX = 40;
int sizeY = 40;
//поворот поля на 180 градусов
void turn()
{
	int b[8][8];

	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
		{
			b[i][j] = field[8 - j - 1][i];
		}
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
		{
			field[i][j] = b[8 - j - 1][i];
		}
	turn_field = !turn_field;
	numberPlayer = 3 - numberPlayer;
}

//подсветка мест, куда может сходить шашка
void light(int i, int j)
{
	bool left_1 = j - 1 >= 0;
	bool left_2 = j - 2 >= 0;
	bool right_1 = j + 1 < 8;
	bool right_2 = j + 2 < 8;

	bool top_1 = i - 1 >= 0;
	bool top_2 = i - 2 >= 0;
	bool bottom_1 = i + 1 < 8;
	bool bottom_2 = i + 2 < 8;
	if (field[i - 1][j - 1] == 0 && (left_1 && top_1))
	{
		field[i - 1][j - 1] = -1;
	}
	else if (field[i - 1][j - 1] != 0 && field[i - 2][j - 2] == 0 && (left_2 && top_2))
	{
		field[i - 2][j - 2] = -1;
	}
	if (field[i - 1][j + 1] == 0 && (right_1 && top_1))
	{
		field[i - 1][j + 1] = -1;
	}
	else if (field[i - 1][j + 1] != 0 && field[i - 2][j + 2] == 0 && (right_2 && top_2))
	{
		field[i - 2][j + 2] = -1;
	}
	if (field[i + 1][j - 1] == 0 && (left_1 && bottom_1))
	{
		field[i + 1][j - 1] = -1;
	}
	else if (field[i + 1][j - 1] != 0 && field[i + 2][j - 2] == 0 &&  (left_2 && bottom_2))
	{
		field[i + 2][j - 2] = -1;
	}
	if (field[i + 1][j + 1] == 0 && (right_1 && bottom_1))
	{
		field[i + 1][j + 1] = -1;
	}
	else if (field[i + 1][j + 1] != 0 && (field[i + 2][j + 2] == 0) && (right_2 && bottom_2))
	{
		field[i + 2][j + 2] = -1;
	}
}
	
//выбор шашки, проверка, своей ли шашкой хочет сходить игрок
void ChooseElem(int x, int y)
{
	int i = y / sizeY;
	int j = x / sizeX;

	if (field[i][j] == numberPlayer)
	{
		game_checker_i = i;
		game_checker_j = j;

		light(i, j);
	}
}
//перемещение шашки
void MoveElem(int x, int y)
{
	int i = y / sizeY;
	int j = x / sizeX;
	if (i < 8 && j < 8)
	{
		if (abs(i - game_checker_i) == abs(j - game_checker_j) && abs(i - game_checker_i) == 1)
		{
			if (field[i][j] == 0)
			{
				field[i][j] = field[game_checker_i][game_checker_j];
				field[game_checker_i][game_checker_j] = 0;
			}
		}
		else if (abs(i - game_checker_i) == abs(j - game_checker_j) && abs(i - game_checker_i) == 2)
		{
			if (i - game_checker_i < 0)
			{
				if (j - game_checker_j < 0)
				{
					if (field[game_checker_i - 1][game_checker_j - 1] != 0)
					{
						field[i][j] = field[game_checker_i][game_checker_j];
						field[game_checker_i][game_checker_j] = 0;
						field[game_checker_i - 1][game_checker_j - 1] = 0;
					}
				}
				else
				{
					if (field[game_checker_i - 1][game_checker_j + 1] != 0)
					{
						field[i][j] = field[game_checker_i][game_checker_j];
						field[game_checker_i][game_checker_j] = 0;
						field[game_checker_i - 1][game_checker_j + 1] = 0;
					}
				}
			}
			else
			{
				if (j - game_checker_j < 0)
				{
					if (field[game_checker_i + 1][game_checker_j - 1] != 0)
					{
						field[i][j] = field[game_checker_i][game_checker_j];
						field[game_checker_i][game_checker_j] = 0;
						field[game_checker_i + 1][game_checker_j - 1] = 0;
					}
				}
				else
				{
					if (field[game_checker_i + 1][game_checker_j + 1] != 0)
					{
						field[i][j] = field[game_checker_i][game_checker_j];
						field[game_checker_i][game_checker_j] = 0;
						field[game_checker_i + 1][game_checker_j + 1] = 0;
					}
				}
			}
		}
		Sleep(100);
		turn();
	}
		
}
//проверка на наличие шашек у игроков
bool kol()
{
	int nw = 0;
	int nb = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (field[i][j] == 1)
			{
				nw++;
			}
			else if (field[i][j] == 2)
			{
				nb++;
			}
		}
	}
	return (nw == 0 || nb == 0);
}
//прорисовка меню
void DrawMenu(HDC hdc, HBITMAP hBitmap)
{
	HDC hdcMem;
	HGDIOBJ oldBitmap;

	BITMAP bitmap;
	hdcMem = CreateCompatibleDC(hdc);
	oldBitmap = SelectObject(hdcMem, hBitmap);

	GetObject(hBitmap, sizeof(bitmap), &bitmap);
	BitBlt(hdc, 10, 0, 340, 600, hdcMem, 0, 0, SRCCOPY);

	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);


	HFONT hFont;
	hFont = CreateFont(30,
		0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, 0,
		L"Courier New"
	);
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(128, 0, 0));

	TCHAR  string0[] = _T("Нажмите");
	TextOut(hdc, 10, sizeY * (8), (LPCWSTR)string0, _tcslen(string0));

	TCHAR  string1[] = _T("P - чтобы начать игру");
	TextOut(hdc, 10, sizeY * (8 + 1), (LPCWSTR)string1, _tcslen(string1));

	TCHAR  string2[] = _T("I - чтобы открыть инструкцию");
	TextOut(hdc, 10, sizeY * (8 + 2), (LPCWSTR)string2, _tcslen(string2));

	TCHAR  string3[] = _T("M - открыть меню в процессе игры");
	TextOut(hdc, 10, sizeY * (8 + 3), (LPCWSTR)string3, _tcslen(string3));

	DeleteObject(hFont);
}

void SaveField()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	setlocale(LC_ALL, "rus");
	FILE* fout;
	fout = fopen("field.txt", "wt");
	if (fout == NULL) {
		return;
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			fprintf(fout, "%5d", field[i][j]);
		}
	}
	fclose(fout);
}

void DownloadField()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	setlocale(LC_ALL, "rus");
	FILE* fin;
	char k;
	fin = fopen("field.txt", "rt");
	if (fin == NULL) {
		return;
	}
	//fscanf(fin, "%c", &k);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			fscanf(fin, "%5d", &field[i][j]);
		}
	}
	fclose(fin);
}
//прорисовка инструкциии
void DrawIncstruction(HDC hdc, HBITMAP hBitmap)
{
	HDC hdcMem;
	HGDIOBJ oldBitmap;

	BITMAP bitmap;

	hdcMem = CreateCompatibleDC(hdc);
	oldBitmap = SelectObject(hdcMem, hBitmap);

	GetObject(hBitmap, sizeof(bitmap), &bitmap);
	BitBlt(hdc, 10, 100, 600, 600, hdcMem, 0, 0, SRCCOPY);

	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);


	HFONT hFont;
	hFont = CreateFont(20,
		0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, 0,
		L"Courier New"
	);
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(128, 0, 0));

	TCHAR  string0[] = _T("Чтобы выбрать шашку, нажмите на нее левой кнопкой мыши.");
	TextOut(hdc, 0, 10, (LPCWSTR)string0, _tcslen(string0));

	TCHAR  string1[] = _T("Подсветка покажет вам, куда вы можете сходить ");
	TextOut(hdc, 0, 30, (LPCWSTR)string1, _tcslen(string1));

	TCHAR  string2[] = _T("Переместите шашку нажав правой кнопкой мыши на нужное поле");
	TextOut(hdc, 0, 50, (LPCWSTR)string2, _tcslen(string2));

	TCHAR  string3[] = _T("Побеждает тот, кто первый съест все шашки соперника");
	TextOut(hdc, 0, 70, (LPCWSTR)string3, _tcslen(string3));

	TCHAR  string4[] = _T("Для сохранения расположения шашек в процессе игры нажмите S");
	TextOut(hdc, 0, 90, (LPCWSTR)string4, _tcslen(string4));

	TCHAR  string5[] = _T("Для загрузки последнего сохранения в процессе игры нажите D");
	TextOut(hdc, 0, 110, (LPCWSTR)string5, _tcslen(string5));

	DeleteObject(hFont);
}
//прорисовка игрового поля
void DrawField(HDC hdc) {
	int kol_white = 0;
	int kol_black = 0;
	HBRUSH hBrushEmptyCellBlack;
	hBrushEmptyCellBlack = CreateSolidBrush(RGB(128, 64, 0)); 
	HBRUSH hBrushEmptyCellWhite; 
	hBrushEmptyCellWhite = CreateSolidBrush(RGB(255, 255, 128)); 
	bool stop = kol();
	if (!stop)
	{
		int i, j;
		i = 0;
		while (i < 8) {
			j = 0;
			while (j < 8) {
				RECT rect = { j * sizeX, i * sizeY,  (j + 1) * sizeX,(i + 1) * sizeY };
				if (turn_field == false)
				{
					if (i % 2 == 0) {
						if (j % 2 == 1)
						{

							FillRect(hdc, &rect, hBrushEmptyCellBlack);
						}
						else
						{
							FillRect(hdc, &rect, hBrushEmptyCellWhite);
						}
					}
					else
					{
						if (j % 2 == 1)
						{
							FillRect(hdc, &rect, hBrushEmptyCellWhite);

						}
						else
						{
							FillRect(hdc, &rect, hBrushEmptyCellBlack);

						}
					}
				}
				else
				{
					if (i % 2 == 0) {
						if (j % 2 == 0)
						{
							FillRect(hdc, &rect, hBrushEmptyCellWhite);

						}
						else
						{
							FillRect(hdc, &rect, hBrushEmptyCellBlack);
						}
					}
					else
					{
						if (j % 2 == 0)
						{
							FillRect(hdc, &rect, hBrushEmptyCellBlack);

						}
						else
						{
							FillRect(hdc, &rect, hBrushEmptyCellWhite);

						}
					}
				}
				if (field[i][j] == 1) {
					HBRUSH hBrusWhite;
					hBrusWhite = CreateSolidBrush(RGB(255, 255, 255)); 
					SelectObject(hdc, hBrusWhite);
					Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
					kol_white++;
					DeleteObject(hBrusWhite);
				}
				else if (field[i][j] == 2) {
					HBRUSH hBrushBlack;
					hBrushBlack = CreateSolidBrush(RGB(0, 0, 0));
					SelectObject(hdc, hBrushBlack);
					Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
					kol_black++;
					DeleteObject(hBrushBlack);
				}
				else if (field[i][j] == -1)
				{
					HBRUSH hBrushEmptyCel; 
					hBrushEmptyCel = CreateSolidBrush(RGB(255, 216, 163));
					FillRect(hdc, &rect, hBrushEmptyCel);
					field[i][j] = 0;
				}
				else {
				}
				j++;
			}
			i++;
		}

		HFONT hFont;
		hFont = CreateFont(20,
			0, 0, 0, 0, 0, 0, 0,
			DEFAULT_CHARSET,
			0, 0, 0, 0,
			L"Courier New"
		);
		SelectObject(hdc, hFont);
		SetTextColor(hdc, RGB(0, 128, 128));

		TCHAR  string1[] = _T("Всего белых:");
		TextOut(hdc, 10, sizeY * (8 + 1), (LPCWSTR)string1, _tcslen(string1));
		char sKolWhite[5];
		TCHAR  tsKolWhite[5];
		sprintf_s(sKolWhite, "%d", kol_white);
		OemToChar(sKolWhite, tsKolWhite);
		TextOut(hdc, 220, sizeY * (8 + 1), (LPCWSTR)tsKolWhite, _tcslen(tsKolWhite));

		TCHAR  string2[] = _T("Всего черных:");
		TextOut(hdc, 10, sizeY * (8 + 2), (LPCWSTR)string2, _tcslen(string2));
		char sKolBlack[5];
		TCHAR  tsKolBlack[5];
		sprintf_s(sKolBlack, "%d", kol_black);
		OemToChar(sKolBlack, tsKolBlack);
		TextOut(hdc, 220, sizeY * (8 + 2), (LPCWSTR)tsKolBlack, _tcslen(tsKolBlack));

		TCHAR  string3[] = _T("Ход игрока под номером ");
		TextOut(hdc, 10, sizeY * (8 + 3), (LPCWSTR)string3, _tcslen(string3));
		char sNum[5];
		TCHAR  tsNum[5];
		sprintf_s(sNum, "%d", numberPlayer);
		OemToChar(sNum, tsNum);
		TextOut(hdc, 235, sizeY * (8 + 3), (LPCWSTR)tsNum, _tcslen(tsNum));

		DeleteObject(hFont);
	}
	
	
	DeleteObject(hBrushEmptyCellBlack);

	DeleteObject(hBrushEmptyCellWhite);

}