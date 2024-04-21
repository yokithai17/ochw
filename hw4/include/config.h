#pragma once

#ifndef CONFIG_H
#define CONFIG_H

#include <windows.h>

struct Config {
	int N = 10; /* Size of the grid */
	int WIDTH = 320; /* width of window */
	int HEIGHT = 240; /* height of window */
	const int COLOR_INCREMENT = 3; /* smooth color changer constanta (magic number) */
	COLORREF gridColor = RGB(255, 0, 0); /* default grid color */
	COLORREF groundColor = RGB(0, 0, 255); /* default background color */
};

#endif //CONFIG_H
