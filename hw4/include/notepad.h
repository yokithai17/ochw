#pragma once

#ifndef COOLAPP__NOTEPAD_H
#define COOLAPP__NOTEPAD_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <windows.h>

/************************** color variables *****************************/

int N = 10; /* Size of the grid */
int WIDTH = 320; /* width of window */
int HEIGHT = 240; /* height of window */
const int COLOR_INCREMENT = 3; /* smooth color changer constanta (magic number) */
COLORREF gridColor = RGB(255, 0, 0); /* default grid color */
COLORREF groundColor = RGB(0, 0, 255); /* default background color */

/*************************** map ***************************************/

/* used to store info about points */
class ShapeMap {
private:
	std::vector<std::vector<int>> map_;
	std::string path_;

	explicit ShapeMap() = default;

public:

	explicit ShapeMap(int n, std::string path);

	~ShapeMap();

	void update(LONG width, LONG height, LONG x, LONG y, int status);

	void draw(LONG width, LONG height, HDC hdc) const;

};
/**********************************************************************************/

/*************************** draw functions ***************************************/

void DrawCross(HDC hdc, LONG posX, LONG posY, LONG step);

void DrawCircle(HDC hdc, LONG left, LONG top, LONG right, LONG bottom);

void DrawGrid(HDC hdc, RECT rect);

void ChangeBackgroundColor(HWND hwnd);

void ChangeGridColor(int delta);

void SmoothChangeGridColor(int delta);

/***********************************************************************************/

/*************************** helper function ***************************************/
template<class T>
const T& mmin(const T& a, const T& b);

template<class T>
const T& mmax(const T& a, const T& b);

#endif //COOLAPP__NOTEPAD_H
