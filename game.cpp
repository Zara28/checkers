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
bool turn_field = false;
int steps = 0;
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
void DrawField(HDC hdc) {

	HBRUSH hBrushEmptyCellBlack; //создаём кисть для пустого поля
	hBrushEmptyCellBlack = CreateSolidBrush(RGB(128, 64, 0)); // серый
	HBRUSH hBrushEmptyCellWhite; //создаём кисть для пустого поля
	hBrushEmptyCellWhite = CreateSolidBrush(RGB(255, 255, 128)); // серый
	

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

				DeleteObject(hBrusWhite);
			}
			else if (field[i][j] == 2) {
				HBRUSH hBrushBlack;
				hBrushBlack = CreateSolidBrush(RGB(0, 0, 0)); // желтый
				SelectObject(hdc, hBrushBlack);
				Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);

				DeleteObject(hBrushBlack);
			}
			else {
				// тут никогда не должны оказаться
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

	TCHAR  string1[] = _T("сделано ходов:");
	TextOut(hdc, 10, sizeY * (8 + 1), (LPCWSTR)string1, _tcslen(string1));
	char sSteps[5];
	TCHAR  tsSteps[5];
	sprintf_s(sSteps, "%d", steps);
	OemToChar(sSteps, tsSteps);
	TextOut(hdc, 220, sizeY * (8 + 1), (LPCWSTR)tsSteps, _tcslen(tsSteps));

	
	DeleteObject(hFont);
	DeleteObject(hBrushEmptyCellBlack);

	DeleteObject(hBrushEmptyCellWhite);

}