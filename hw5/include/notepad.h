#pragma once

#ifndef COOLAPP__NOTEPAD_H
#define COOLAPP__NOTEPAD_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <windows.h>
#include <time.h>

#include "config.h"

/*************************** map ***************************************/

/* used to store info about points */
class ShapeMap {
private:
	Config* cfg_;
	std::vector<std::vector<int>> map_;
	std::string path_;
	char* pBuf_;

	explicit ShapeMap() = default;

public:

	explicit ShapeMap(std::string path, Config* cfg, char* pbuf);

	~ShapeMap() = default;

	void update(LONG width, LONG height, LONG x, LONG y, int status);

	void draw(LONG width, LONG height, HDC hdc) const;

	Config* getConfigPointer();

	size_t Size() const;

	void loadFromMapping();

};
/**********************************************************************************/

/*************************** draw functions ***************************************/

void DrawCross(HDC hdc, LONG posX, LONG posY, LONG step);

void DrawCircle(HDC hdc, LONG left, LONG top, LONG right, LONG bottom);

void DrawGrid(HDC hdc, RECT rect, Config* cfg);

void ChangeBackgroundColor(HWND hwnd, Config* cfg);

void ChangeGridColor(int delta, Config* cfg);

void SmoothChangeGridColor(int delta, Config* cfg);

/***********************************************************************************/

/*************************** helper function ***************************************/
template<class T>
const T& mmin(const T& a, const T& b);

template<class T>
const T& mmax(const T& a, const T& b);

#endif //COOLAPP__NOTEPAD_H
