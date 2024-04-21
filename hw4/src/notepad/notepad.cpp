#include "notepad.h"

#include <utility>


/*************************** ShapeMap ********************************************/

	ShapeMap::ShapeMap(std::string path, Config* cfg) :
			path_(std::move(path))
			, cfg_(cfg)
			,map_(std::vector<std::vector<int>>(cfg_->N, std::vector<int>(cfg_->N, 0)))
	{};

	void ShapeMap::update(LONG width, LONG height,
	            LONG x, LONG y, int status) {
		LONG posX = mmin(9L, static_cast<LONG>(x / (width / cfg_->N)));
		LONG posY = mmin(9L, static_cast<LONG>(y / (height / cfg_->N)));
		map_[posX][posY] = status;
	}

	void ShapeMap::draw(LONG width, LONG height, HDC hdc) const {
		LONG stepX = width / cfg_->N;
		LONG stepY = height / cfg_->N;
		for (int i = 0; i < cfg_->N; ++i) {
			for (int j = 0; j < cfg_->N; ++j) {
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

	Config* ShapeMap::getConfigPointer() {
		return this->cfg_;
	}
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


void DrawGrid(HDC hdc, RECT rect, Config* cfg) {
	LONG cellWidth = rect.right / cfg->N;
	LONG cellHeight = rect.bottom / cfg->N;

	HPEN hPen = CreatePen(PS_SOLID, 1, cfg->gridColor);
	HPEN holdPen = (HPEN) SelectObject(hdc, hPen);

	/* Draw verticals lines */
	for (int i = 1; i < cfg->N; ++i) {
		LONG x = i * cellWidth;
		MoveToEx(hdc, x, 0, nullptr);
		LineTo(hdc, x, rect.bottom);
	}

	/* Draw horizontal lines */
	for (int i = 1; i < cfg->N; ++i) {
		LONG y = i * cellHeight;
		MoveToEx(hdc, 0, y, nullptr);
		LineTo(hdc, rect.right, y);
	}

	SelectObject(hdc, holdPen);
	DeleteObject(hPen);
}

/*********************************************************************************************/

/***************************** CHANGE COLOR FUNCTIONS*****************************************/

void ChangeBackgroundColor(HWND hwnd, Config* cfg) {
	srand((unsigned) time(nullptr));
	cfg->groundColor = RGB(rand() % 256, rand() % 256, rand() % 256);
	InvalidateRect(hwnd, nullptr, 0);
}

void ChangeGridColor(int delta, Config* cfg) {
	static DWORD lastScrollTime = 0;
	DWORD currentTime = GetTickCount();
	if (currentTime - lastScrollTime > 100) {
		lastScrollTime = currentTime;
		SmoothChangeGridColor(delta, cfg);
	}
}

void SmoothChangeGridColor(int delta, Config* cfg) {
	static int r = GetRValue(cfg->gridColor);
	static int g = GetGValue(cfg->gridColor);
	static int b = GetBValue(cfg->gridColor);

	r = mmax(0, mmin(255, r + delta * cfg->COLOR_INCREMENT));
	g = mmax(0, mmin(255, g + delta * cfg->COLOR_INCREMENT));
	b = mmax(0, mmin(255, b + delta * cfg->COLOR_INCREMENT));

	cfg->gridColor = RGB(r, g, b);
}

/*********************************************************************************************/

