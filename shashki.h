#pragma once

#include "resource.h"
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#define WIN32_LEAN_AND_MEAN            
#include <stdlib.h>

#include "framework.h"
void DrawField(HDC hdc);
bool kol();
void turn();
void light(int i, int j);
void ChooseElem(int x, int y);
void MoveElem(int x, int y); 
void DrawMenu(HDC hdc, HBITMAP hBitmap);
void DrawIncstruction(HDC hdc, HBITMAP hBitmap);