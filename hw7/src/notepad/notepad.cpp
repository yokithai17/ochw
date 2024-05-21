#include "notepad.h"

#include <utility>
#include <cmath>
#include <random>
#include <ctime>

/*************************** ShapeMap ********************************************/

ShapeMap::ShapeMap(std::string path, Config* cfg, char* pBuf) :
		path_(std::move(path))
		, cfg_(cfg)
		, map_(std::vector<std::vector<int>>(cfg_->N, std::vector<int>(cfg_->N, 0)))
		, pBuf_(pBuf)
{};

void ShapeMap::update(int width, int height,
						int x, int y, int status) {
	double cellWidth = width / static_cast<double>(cfg_->N);
	double cellHeight = height / static_cast<double>(cfg_->N);

	int posX = std::floor(x / cellWidth);
	int posY = std::floor(y / cellHeight);

	posX = mmin(posX, cfg_->N - 1);
	posY = mmin(posY, cfg_->N - 1);
	
	pBuf_[posX + posY * map_.size()] = static_cast<char>(status + static_cast<int>('0'));
	map_[posX][posY] = status;
}

void ShapeMap::draw(LONG width, LONG height, HDC hdc) const {
	LONG stepX = width / cfg_->N;
	LONG stepY = height / cfg_->N;
	for (int i = 0; i < cfg_->N; ++i) {
		for (int j = 0; j < cfg_->N; ++j) {
			LONG posX = i * width / cfg_->N + stepX / 2;
			LONG posY = j * height / cfg_->N + stepY / 2;
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

void ShapeMap::loadFromMapping() {
	int size =  map_.size();
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			map_[i][j] = static_cast<int>(pBuf_[i + size * j]) - static_cast<int>('0');
		}
	}
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


void DrawGrid(HDC hdc, Config* cfg) {
	HPEN hPen = CreatePen(PS_SOLID, 1, cfg->gridColor);
	HPEN holdPen = (HPEN) SelectObject(hdc, hPen);

	/* Draw verticals lines */
	for (int i = 1; i < cfg->N; ++i) {
		LONG x = i * cfg->WIDTH / cfg->N;
		MoveToEx(hdc, x, 0, nullptr);
		LineTo(hdc, x, cfg->HEIGHT);
	}

	/* Draw horizontal lines */
	for (int i = 1; i < cfg->N; ++i) {
		LONG y = i * cfg->HEIGHT / cfg->N;
		MoveToEx(hdc, 0, y, nullptr);
		LineTo(hdc, cfg->WIDTH, y);
	}

	SelectObject(hdc, holdPen);
	DeleteObject(hPen);
}

/*********************************************************************************************/

/***************************** CHANGE COLOR FUNCTIONS*****************************************/

void ChangeBackgroundColor(HWND hwnd, Config* cfg) {
	std::mt19937 engine;
	engine.seed(std::time(nullptr));
	cfg->groundColor = RGB(engine() % 256, engine() % 256, engine() % 256);
	HBRUSH Brush = CreateSolidBrush(cfg->groundColor);
	ULONG_PTR DelBrush = SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)Brush);
	DeleteObject(HGDIOBJ(DelBrush));
	InvalidateRect(hwnd, nullptr, TRUE);
}

void ChangeBackgroundColorT(HWND hwnd, Config* cfg) {
	std::mt19937 engine;
	engine.seed(std::time(nullptr));
	cfg->groundColor = RGB(engine() % 256, engine() % 256, engine() % 256);
	HBRUSH Brush = CreateSolidBrush(cfg->groundColor);
	ULONG_PTR DelBrush = SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)Brush);
	DeleteObject(HGDIOBJ(DelBrush));
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

