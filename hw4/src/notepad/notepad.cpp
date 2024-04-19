#include "notepad.h"


/*************************** ShapeMap ********************************************/

	ShapeMap::ShapeMap(int n, std::string path) :
			map_(std::vector<std::vector<int>>(n, std::vector<int>(n, 0)))
			, path_(std::move(path))
	{};

	ShapeMap::~ShapeMap() {}

	void ShapeMap::update(LONG width, LONG height,
	            LONG x, LONG y, int status) {
		LONG posX = mmin(9L, static_cast<LONG>(x / (width / N)));
		LONG posY = mmin(9L, static_cast<LONG>(y / (height / N)));
		map_[posX][posY] = status;
	}

	void ShapeMap::draw(LONG width, LONG height, HDC hdc) const {
		LONG stepX = width / N;
		LONG stepY = height / N;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				LONG posX = i * stepX + stepX / 2;
				LONG posY = j * stepY + stepY / 2;
				switch (map_[i][j]) {
				case 1: {
					DrawCross(hdc, posX, posY, mmin(stepY, stepX) / 3);
				}
					break;
				case 2: {
					LONG step = mmin(stepY, stepX) / 3;
					DrawCircle(hdc, posX - step, posY + step, posX + step, posY - step);
				}
					break;
				}
			}
		}
	}

/******************************************************************************************/

/*************************** helper functions ********************************************/

template<class T>
const T& mmin(const T& a, const T& b) {
	return (b < a) ? b : a;
}


template<class T>
const T& mmax(const T& a, const T& b) {
	return (a < b) ? b : a;
}

/*********************************************************************************************/

/***************************** Draw functions ************************************************/

void DrawCross(HDC hdc, LONG posX, LONG posY, LONG step) {
	MoveToEx(hdc, posX - step, posY - step, nullptr);
	LineTo(hdc, posX + step, posY + step);
	MoveToEx(hdc, posX - step, posY + step, nullptr);
	LineTo(hdc, posX + step, posY - step);
}

void DrawCircle(HDC hdc, LONG left, LONG top, LONG right, LONG bottom) {
	Ellipse(hdc, left, top, right, bottom);
}


void DrawGrid(HDC hdc, RECT rect) {
	LONG cellWidth = rect.right / N;
	LONG cellHeight = rect.bottom / N;

	HPEN hPen = CreatePen(PS_SOLID, 1, gridColor);
	HPEN holdPen = (HPEN) SelectObject(hdc, hPen);

	/* Draw verticals lines */
	for (int i = 1; i < N; ++i) {
		LONG x = i * cellWidth;
		MoveToEx(hdc, x, 0, nullptr);
		LineTo(hdc, x, rect.bottom);
	}

	/* Draw horizontal lines */
	for (int i = 1; i < N; ++i) {
		LONG y = i * cellHeight;
		MoveToEx(hdc, 0, y, nullptr);
		LineTo(hdc, rect.right, y);
	}

	SelectObject(hdc, holdPen);
	DeleteObject(hPen);
}

/*********************************************************************************************/

/***************************** CHANGE COLOR FUNCTIONS*****************************************/

void ChangeBackgroundColor(HWND hwnd) {
	srand((unsigned) time(0));
	groundColor = RGB(rand() % 256, rand() % 256, rand() % 256);
	InvalidateRect(hwnd, nullptr, 0);
}

void ChangeGridColor(int delta) {
	static DWORD lastScrollTime = 0;
	DWORD currentTime = GetTickCount();
	if (currentTime - lastScrollTime > 100) {
		lastScrollTime = currentTime;
		SmoothChangeGridColor(delta);
	}
}

void SmoothChangeGridColor(int delta) {
	static int r = GetRValue(gridColor);
	static int g = GetGValue(gridColor);
	static int b = GetBValue(gridColor);

	r = mmax(0, mmin(255, r + delta * COLOR_INCREMENT));
	g = mmax(0, mmin(255, g + delta * COLOR_INCREMENT));
	b = mmax(0, mmin(255, b + delta * COLOR_INCREMENT));

	gridColor = RGB(r, g, b);
}

/*********************************************************************************************/

