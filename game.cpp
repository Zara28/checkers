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
#include "winuser.h"

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
int numberPlayer = 0;
bool turn_field = false;
int game_checker_i;
int game_checker_j;
int sizeX = 30;
int sizeY = 30;
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
}

void ChooseElem(int x, int y)
{
	int i = y / sizeY;
	int j = x / sizeX;
	game_checker_i = i;
	game_checker_j = j;
}
void MoveElem(int x, int y)
{
	int i = y / sizeY;
	int j = x / sizeX;
	bool right = j > game_checker_j;
	int bottom = i > game_checker_i;
	if ((abs(i - game_checker_i) == 1 && abs(j - game_checker_j) == 1))
	{
		field[i][j] = field[game_checker_i][game_checker_j];
		field[game_checker_i][game_checker_j] = 0;
		game_checker_i = 1000;
		game_checker_j = 1000;
		numberPlayer = !numberPlayer;
		//turn();
	}
	else if (abs(j - game_checker_j) == 2 && abs(i - game_checker_i) == 2)
	{
		if (right)
		{
			if (bottom)
			{
				if (field[i + 1][j + 1] != 0)
				{
					field[i][j] = field[game_checker_i][game_checker_j];
					field[game_checker_i][game_checker_j] = 0;
					field[i + 1][j + 1] = 0;
				}
			}
			else
			{
				if (field[i - 1][j + 1] != 0)
				{
					field[i][j] = field[game_checker_i][game_checker_j];
					field[game_checker_i][game_checker_j] = 0;
					field[i - 1][j + 1] = 0;
				}
			}
			
		}
		else
		{
			if (!bottom)
			{
				if (field[i - 1][j - 1] != 0)
				{
					field[i][j] = field[game_checker_i][game_checker_j];
					field[game_checker_i][game_checker_j] = 0;
					field[i - 1][j - 1] = 0;
				}
			}
			else
			{
				if (field[i + 1][j - 1] != 0)
				{
					field[i][j] = field[game_checker_i][game_checker_j];
					field[game_checker_i][game_checker_j] = 0;
					field[game_checker_i - 1][game_checker_j + 1] = 0;
				}
			}
		}
		
		game_checker_i = 1000;
		game_checker_j = 1000;
		numberPlayer = !numberPlayer;
	}
}
void DrawField(HDC hdc) {

	HBRUSH hBrushEmptyCellBlack; //создаём кисть для пустого поля
	hBrushEmptyCellBlack = CreateSolidBrush(RGB(128, 64, 0)); // серый
	HBRUSH hBrushEmptyCellWhite; //создаём кисть для пустого поля
	hBrushEmptyCellWhite = CreateSolidBrush(RGB(255, 255, 128)); // серый

	int kol_white = 0;
	int kol_black = 0;

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
				hBrusWhite = CreateSolidBrush(RGB(255, 255, 255)); // желтый
				SelectObject(hdc, hBrusWhite);
				Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
				kol_white++;
				DeleteObject(hBrusWhite);
			}
			else if (field[i][j] == 2) {
				HBRUSH hBrushBlack;
				hBrushBlack = CreateSolidBrush(RGB(0, 0, 0)); // желтый
				SelectObject(hdc, hBrushBlack);
				Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
				kol_black++;
				DeleteObject(hBrushBlack);
			}
			else  {
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

	
	DeleteObject(hFont);
	DeleteObject(hBrushEmptyCellBlack);

	DeleteObject(hBrushEmptyCellWhite);

}