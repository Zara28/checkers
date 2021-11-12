#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include "stdio.h"
#define WIN32_LEAN_AND_MEAN            
#include <stdlib.h>  
#include "framework.h"

#include "shashki.h"
// ‘айлы заголовков среды выполнени€ C
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "windowsx.h"

#include "windows.h"
#include "winuser.h"
#include <clocale>

#include <string>
//индексы
// 0 - пустота
// 1, 2 - шашки первого и второго игроков
// -1 - подсветка возможного хода
// —труктура с информацией о рекорде
struct Record {
	char name[20];
	int gold;
	int steps;
	unsigned int year;
	unsigned int month;
	unsigned int day;
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
};

// ћаксимальное количество рекордов в таблице
#define MAX_NUM_RECORDS 10

// “аблица рекордов
struct Record records[MAX_NUM_RECORDS + 1];
// текущее количество рекордов в таблице
int numRecords = 0;
int kol_hodov_1 = 0;
int kol_hodov_2 = 0;
int kol_b = 0;
int kol_w = 0;
	int game_checker_i;
	int game_checker_j;
int startfield[8][8] = {
	{0, 2, 0, 2, 0, 2, 0, 2},
	{2, 0, 2, 0, 2, 0, 2, 0},
	{0, 2, 0, 2, 0, 2, 0, 2},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 1, 0, 1, 0, 1, 0},
	{0, 1, 0, 1, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 0, 1, 0}
};

int field[8][8] = {
	{0, 2, 0, 2, 0, 2, 0, 2},
	{2, 0, 2, 0, 2, 0, 2, 0},
	{0, 2, 0, 2, 0, 2, 0, 2},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 1, 0, 1, 0, 1, 0},
	{0, 1, 0, 1, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 0, 1, 0}
};
int numberPlayer = 1;
bool turn_field = false;

struct kletka
{
	int sizeX = 40;
	int sizeY = 40;
};

void addRecord(char name[])
{
	//if (numRecords >= MAX_NUM_RECORDS) {
	//numRecords = numRecords - 1;
	//}

	strcpy(records[numRecords].name, name);
	records[numRecords].gold = kol_w;
	records[numRecords].steps = kol_hodov_1;

	SYSTEMTIME st;
	// ѕолучаем текущее врем€
	GetLocalTime(&st);

	// и разбрасываем его по пол€м в таблицу рекордов
	records[numRecords].year = st.wYear;
	records[numRecords].month = st.wMonth;
	records[numRecords].day = st.wDay;

	records[numRecords].hour = st.wHour;
	records[numRecords].minute = st.wMinute;
	records[numRecords].second = st.wSecond;
	// —ледующий раз будем записывать рекорд в следующий элемент	
	numRecords++;
}
int CompareRecords(int index1, int index2)
{
	if (records[index1].gold < records[index2].gold)
		return -1;
	if (records[index1].gold > records[index2].gold)
		return +1;

	// if (records[index1].gold == records[index2].gold) {

	if (records[index1].steps > records[index2].steps)
		return -1;
	if (records[index1].steps < records[index2].steps)
		return +1;

	//   if (records[index1].steps == records[index2].steps) {
	return 0;
	//    } 
	//  }

}
void InsertRecord(char name[])
{
	strcpy(records[numRecords].name, name);
	records[numRecords].gold = kol_w;
	records[numRecords].steps = kol_hodov_1;

	SYSTEMTIME st;
	// ѕолучаем текущее врем€
	GetLocalTime(&st);

	// и разбрасываем его по пол€м в таблицу рекордов
	records[numRecords].year = st.wYear;
	records[numRecords].month = st.wMonth;
	records[numRecords].day = st.wDay;

	records[numRecords].hour = st.wHour;
	records[numRecords].minute = st.wMinute;
	records[numRecords].second = st.wSecond;
	// ѕродвигаем запись к началу массива - если в ней 
		// хороший результат
	int i = numRecords;
	while (i > 0) {
		if (CompareRecords(i - 1, i) < 0) {
			struct Record temp = records[i];
			records[i] = records[i - 1];
			records[i - 1] = temp;
		}
		i--;
	}
	// ≈сли таблица заполнена не полностью
	if (numRecords < MAX_NUM_RECORDS)
		// следующий раз новый рекорд будет занесен в новый элемент
		numRecords++;
}
void DrawRecords(HDC hdc) {
	HFONT hFont;
	hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET, 0, 0, 0, 0,
		L"Courier New"
	);
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(0, 64, 64));

	TCHAR  string1[] = _T("! No ! ƒата       ! ¬рем€    ! »м€                  ! «олото ! ’одов !");
	TextOut(hdc, 10, 50, (LPCWSTR)string1, _tcslen(string1));

	int i;
	for (i = 0; i < numRecords; i++) {
		TCHAR  string2[80];
		char str[80];
		sprintf(str, "! %2d ! %02d.%02d.%04d ! %02d:%02d:%02d ! %-20s ! %4d   ! %5d !",
			i + 1,
			records[i].day, records[i].month, records[i].year,
			records[i].hour, records[i].minute, records[i].second,
			records[i].name, records[i].gold, records[i].steps
		);
		OemToChar(str, string2);
		TextOut(hdc, 10, 24 * (i + 1) + 50, (LPCWSTR)string2, _tcslen(string2));
	}
	DeleteObject(hFont);
}

//поворот пол€ на 180 градусов
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
	struct kletka m;
	int i = y / m.sizeY;
	int j = x / m.sizeX;

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
	struct kletka m;
	int i = y / m.sizeY;
	int j = x / m.sizeX;
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
		if (numberPlayer == 1)
		{
			kol_hodov_1 += 1;
		}
		else
		{
			kol_hodov_2 += 1;
		}
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
	kol_b = nb;
	kol_w = nw;
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
	BitBlt(hdc, 0, 0, 650, 490, hdcMem, 0, 0, SRCCOPY);

	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);


}

void RandomField()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	setlocale(LC_ALL, "rus");
	int n = rand() % 2;
	FILE* fout;
	fout = fopen("ex1.txt", "rt");
	switch (n)
	{
	case 0:
		fout = fopen("ex1.txt", "rt");
		break;
	case 1:
		fout = fopen("ex2.txt", "rt");
		break;
	}
	if (fout == NULL) {
		return;
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			fscanf(fout, "%5d", &field[i % 8][j]);
		}
	
	}
	fclose(fout);
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

	TCHAR  string0[] = _T("„тобы выбрать шашку, нажмите на нее левой кнопкой мыши.");
	TextOut(hdc, 5, 10, (LPCWSTR)string0, _tcslen(string0));

	TCHAR  string1[] = _T("ѕодсветка покажет вам, куда вы можете сходить ");
	TextOut(hdc, 5, 30, (LPCWSTR)string1, _tcslen(string1));

	TCHAR  string2[] = _T("ѕереместите шашку нажав правой кнопкой мыши на нужное поле");
	TextOut(hdc, 5, 50, (LPCWSTR)string2, _tcslen(string2));

	TCHAR  string3[] = _T("ѕобеждает тот, кто первый съест все шашки соперника");
	TextOut(hdc, 5, 70, (LPCWSTR)string3, _tcslen(string3));

	TCHAR  string4[] = _T("¬ игре на врем€ на ход игроку даетс€ 10 секунд");
	TextOut(hdc, 5, 90, (LPCWSTR)string4, _tcslen(string4));

	DeleteObject(hFont);
}
//прорисовка игрового пол€
void DrawField(HDC hdc, bool newfield, TCHAR name1[]) {
	struct kletka m;
	if (newfield)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				field[i][j] = startfield[i][j];
			}
		}
		
	}
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
				RECT rect = { j * m.sizeX, i * m.sizeY,  (j + 1) * m.sizeX,(i + 1) * m.sizeY };
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

		TCHAR  string1[] = _T("¬сего белых:");
		TextOut(hdc, m.sizeX*(8+1), 10, (LPCWSTR)string1, _tcslen(string1));
		char sKolWhite[5];
		TCHAR  tsKolWhite[5];
		sprintf_s(sKolWhite, "%d", kol_white);
		OemToChar(sKolWhite, tsKolWhite);
		TextOut(hdc, m.sizeX*(8 + 5), 10, (LPCWSTR)tsKolWhite, _tcslen(tsKolWhite));

		TCHAR  string2[] = _T("¬сего черных:");
		TextOut(hdc, m.sizeX* (8 + 1), 30, (LPCWSTR)string2, _tcslen(string2));
		char sKolBlack[5];
		TCHAR  tsKolBlack[5];
		sprintf_s(sKolBlack, "%d", kol_black);
		OemToChar(sKolBlack, tsKolBlack);
		TextOut(hdc, m.sizeX* (8 + 5), 30, (LPCWSTR)tsKolBlack, _tcslen(tsKolBlack));

		TCHAR  string3[] = _T("’од игрока под номером ");
		TextOut(hdc, m.sizeX* (8 + 1), 50, (LPCWSTR)string3, _tcslen(string3));
		char sNum[5];
		TCHAR  tsNum[5];
		sprintf_s(sNum, "%d %s", numberPlayer, name1);
		OemToChar(sNum, tsNum);
		TextOut(hdc, m.sizeX* (8 + 7), 50, (LPCWSTR)tsNum, _tcslen(tsNum));

		DeleteObject(hFont);
	}
	
	
	DeleteObject(hBrushEmptyCellBlack);

	DeleteObject(hBrushEmptyCellWhite);

}