#pragma once

#include "resource.h"
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#define WIN32_LEAN_AND_MEAN            
#include <stdlib.h>


#include "framework.h"
void DrawField(HDC hdc, bool newfield, TCHAR name1[], TCHAR name2[]);
bool kol();
void turn();
void light(int i, int j);
void ChooseElem(int x, int y);
void MoveElem(int x, int y); 
void DrawMenu(HDC hdc, HBITMAP hBitmap);
void DrawIncstruction(HDC hdc, HBITMAP hBitmap);
void SaveField();
void DownloadField();
void RandomField();
void DrawRecords(HDC hdc);
void InsertRecord(char name[]);
int CompareRecords(int index1, int index2);
int play_timer();
void LoadRecordsEncoded();
void SaveRecordsEncoded();
void addRecord(struct Player player);
int encodeChar(int ch);
int decodeChar(int ch);
void encodeString(char str[]);
void decodeString2(char* str);
void SaveRecordsEncoded();