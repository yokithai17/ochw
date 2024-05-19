#include <iostream>
#include <algorithm>
#include <windows.h>
#include <tchar.h>
#include <random>
#include <ctime>
#include <vector>
#include <windowsX.h.>

#define BUFF_SIZE 1024
#define PLAYER_BUFF_SIZE 10

#define STACK_SIZE (64*1024)

#define CROSS_PLAYER 1
#define CIRCLE_PLAYER 2
#define ERROR_PLAYER -1

HANDLE hMapFilePlayer = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		PLAYER_BUFF_SIZE,
		_T("ChatLine9847589345673246758")
);

char* pBufPlayer = (char*)MapViewOfFile(
		hMapFilePlayer,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		BUFF_SIZE
);

HANDLE hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		BUFF_SIZE,
		_T("ChatLine9847589345673246759")
);

char* pBuf = (char*)MapViewOfFile(
		hMapFile,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		BUFF_SIZE
);

/******************* GLOBAL VARIABLES ****************************************/
int N = 3; /* Size of the grid*/
const int COLOR_INCREMENT = 3; /* smooth color changer constanta (magic number) */
const TCHAR szWinClass[] = _T("Win32SampleApp");
const TCHAR szWinName[] = _T("Win32SampleWindow");
COLORREF gridColor = RGB(255, 0, 0); /* default grid color */
COLORREF groundColor = RGB(0, 0, 255); /* default background color */
//HWND hwnd;               /* This is the handle for our window */
HBRUSH hBrush;           /* Current brush */

int player;
/******************************* Thread Stuff ************************************/

HANDLE mtx;
HANDLE threadHNDL;
bool pauseThread;

int priority;
bool flagAnim = true;


void colorChanger(COLORREF* colorRef, long delta);

/*****************************************************************************/

/******************************** function ************************************/
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

DWORD WINAPI Paint(void* hwnd);

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

void RunNotepad();

void DrawGrid(HDC hdc, LONG xSize, LONG ySize);

void DrawCross(HDC hdc, LONG posX, LONG posY, LONG step);

void DrawCircle(HDC hdc, LONG left, LONG top, LONG right, LONG bottom);

void ChangeGridColor(int delta);

void SmoothChangeGridColor(int delta);
/*****************************************************************************/

/******************************* Helper functions ******************************/
template<class T>
const T& mmin(const T& a, const T& b) {
  return (b < a) ? b : a;
}


template<class T>
const T& mmax(const T& a, const T& b) {
  return (a < b) ? b : a;
}

/*******************************************************************************/
/******************************* ShapeMap ***************************************/

/* used to store info about points */
class ShapeMap {
private:
	char* pBuf_;
	int steps_;
  std::vector<std::vector<int>> map_;

	int checkDiagonal() const;

	int checkLines() const;

	std::pair<int, int> getPos(int width, int height, int x, int y) const;



public:
	explicit ShapeMap() = default;

  explicit ShapeMap(int n, char* pBuf) :
			pBuf_(pBuf)
			, steps_(0)
			, map_(std::vector<std::vector<int>>(n, std::vector<int>(n, 0))) {};

  ~ShapeMap() = default;

  void update(int width, int height, int x, int y, int status);

  void draw(LONG width, LONG height, HDC hdc) const;

	bool canChange(int width, int height, int x, int y) const;

	void loadFromMapping();

	int getSteps() const;

	void incSteps();

	int checkGameOver() const;

};
/***********************************************************************************/
ShapeMap* pMap = nullptr;
/**************************** MAIN *************************************************/

int main(int argc, char *argv[]) {
  if (argc >= 2) {
    N = std::strtol(argv[1], nullptr, 10);
  } else {
    N = 10;
  }

	static ShapeMap map = ShapeMap(N, pBuf);
	pMap = &map;

	char tmp = pBufPlayer[0];
	if (tmp == '2') {
		player = ERROR_PLAYER;
	} else if (tmp == '1'){
		player = CIRCLE_PLAYER;
		pBufPlayer[0] = '2';
	} else {
		player = CROSS_PLAYER;
		pBufPlayer[0] = '1';
	}

	if (player == ERROR_PLAYER) {
		UnmapViewOfFile(pBuf);
		UnmapViewOfFile(pBufPlayer);
		CloseHandle(hMapFile);
		CloseHandle(hMapFilePlayer);

		return 0;
	}

  BOOL bMessageOk;
  MSG message;            /* Here message to the application are saved */
  WNDCLASS wincl = {0};         /* Data structure for the windowclass */

  /* Harcode show command num when use non-winapi entrypoint */
  int nCmdShow = SW_SHOW;
  /* Get handle */
  HINSTANCE hThisInstance = GetModuleHandle(nullptr);

  /* The Window structure */
  wincl.hInstance = hThisInstance;
  wincl.lpszClassName = szWinClass;
  wincl.lpfnWndProc = WindowProcedure;      /* This function is called by Windows */

  /* Use custom brush to paint the background of the window */
  hBrush = CreateSolidBrush(groundColor);
  wincl.hbrBackground = hBrush;

  /* Register the window class, and if it fails quit the program */
  if (!RegisterClass(&wincl))
    return 0;

  /* The class is registered, let's create the program*/
  HWND hwnd = CreateWindow(
      szWinClass,          /* Classname */
      szWinName,       /* Title Text */
      WS_OVERLAPPEDWINDOW, /* default window */
      CW_USEDEFAULT,       /* Windows decides the position */
      CW_USEDEFAULT,       /* where the window ends up on the screen */
      320,                 /* The programs width */
      240,                 /* and height in pixels */
      HWND_DESKTOP,        /* The window is a child-window to desktop */
      nullptr,                /* No menu */
      hThisInstance,       /* Program Instance handler */
      nullptr                 /* No Window Creation data */
  );

  /* Make the window visible on the screen */
  ShowWindow(hwnd, nCmdShow);

	threadHNDL = CreateThread(NULL, STACK_SIZE, Paint, hwnd, 0, NULL);

  /* Run the message loop. It will run until GetMessage() returns 0 */
  while ((bMessageOk = GetMessage(&message, nullptr, 0, 0)) != 0) {
    if (bMessageOk == -1) {
      GetLastError();
      break;
    }
    /* Translate virtual-key message into character message */
    TranslateMessage(&message);
    /* Send message to WindowProcedure */
    DispatchMessage(&message);
  }

  /* Cleanup stuff */
  DestroyWindow(hwnd);
  UnregisterClass(szWinClass, hThisInstance);
  DeleteObject(hBrush);

	CloseHandle(threadHNDL);
	CloseHandle(mtx);

	UnmapViewOfFile(pBuf);
	UnmapViewOfFile(pBufPlayer);
	CloseHandle(hMapFile);
	CloseHandle(hMapFilePlayer);

  return 0;
}
/********************************************************************************************/

/***************************** WND PROCEDURE ************************************************/

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static LONG xSize;
	static LONG ySize;

  switch (message)                  /* handle the messages */
  {
	/* send a WM_QUIT to the message queue */
  case WM_DESTROY: {
		PostQuitMessage(0);
	}
    return 0;

    return 0;
  case WM_SIZE: {
	  RECT rect;
	  GetClientRect(hwnd, &rect);
    
	  xSize = rect.right - rect.left;
	  ySize = rect.bottom - rect.top;
    InvalidateRect(hwnd, nullptr, TRUE);
  }
    return 0;

  case WM_LBUTTONDOWN: {
    int xPos = GET_X_LPARAM(lParam);
    int yPos = GET_Y_LPARAM(lParam);

	  int status = pMap->getSteps() ? (2) : (1);

		if (player != status) {
			MessageBox(hwnd, _T("NOT UR TURN"), _T(""), MB_OK);
			return 0;
		}

		if (pMap->canChange(xSize, ySize, xPos, yPos)) {
			pMap->update(xSize, ySize, xPos, yPos, status);
			pMap->incSteps();
			EnumWindows(EnumWindowsProc, TRUE);
		}

	  pMap->checkGameOver();
  }
	return 0;

  case WM_KEYDOWN:
    switch (wParam) {

    case VK_ESCAPE:PostQuitMessage(0);
      break;

    case 'Q':
      if (GetKeyState(VK_CONTROL) < 0) {
        PostQuitMessage(0);
      }
      break;

    case VK_RETURN:
      break;

    case 'C':
      if (GetKeyState(VK_SHIFT) < 0) {
        RunNotepad();
      }
      break;
    }

    return 0;

  case WM_MOUSEWHEEL: {
    int delta = (GET_WHEEL_DELTA_WPARAM(wParam) > 0) ? (5) : (-5);
    ChangeGridColor(delta);
    InvalidateRect(hwnd, nullptr, TRUE);
  }
    return 0;
  }


  /* for messages that we don't deal with */
  return DefWindowProc(hwnd, message, wParam, lParam);
}
/*********************************************************************************************/

/***************************** DRAW FUNCTIONS ************************************************/

void DrawGrid(HDC hdc, LONG right, LONG bottom) {

	HPEN hPen = CreatePen(PS_SOLID, 1, gridColor);
	HPEN holdPen = (HPEN) SelectObject(hdc, hPen);

	/* Draw verticals lines */
	for (int i = 1; i < N; ++i) {
		LONG x = i * right / N;
		MoveToEx(hdc, x, 0, nullptr);
		LineTo(hdc, x, bottom);
	}

	/* Draw horizontal lines */
	for (int i = 1; i < N; ++i) {
		LONG y = i * bottom / N;
		MoveToEx(hdc, 0, y, nullptr);
		LineTo(hdc, right, y);
	}

	SelectObject(hdc, holdPen);
	DeleteObject(hPen);
}

void DrawCross(HDC hdc, LONG posX, LONG posY, LONG step) {
  MoveToEx(hdc, posX - step, posY - step, nullptr);
  LineTo(hdc, posX + step, posY + step);
  MoveToEx(hdc, posX - step, posY + step, nullptr);
  LineTo(hdc, posX + step, posY - step);
}

void DrawCircle(HDC hdc, LONG left, LONG top, LONG right, LONG bottom) {
  Ellipse(hdc, left, top, right, bottom);
}
/************************************** SHAPE MAP **************************************************/
void ShapeMap::draw(LONG width, LONG height, HDC hdc) const {
    LONG stepX = width / N;
    LONG stepY = height / N;

    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        LONG posX = i * width / N + stepX / 2;
        LONG posY = j * height / N + stepY / 2;
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

std::pair<int, int> ShapeMap::getPos(int width, int height, int x, int y) const {
	double cellWidth = width / static_cast<double>(N);
	double cellHeight = height / static_cast<double>(N);

	int posX = std::floor(x / cellWidth);
	int posY = std::floor(y / cellHeight);

	posX = mmin(posX, N - 1);
	posY = mmin(posY, N - 1);

	return {posX, posY};
}

void ShapeMap::loadFromMapping() {
	int size =  map_.size();
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			map_[i][j] = static_cast<int>(pBuf_[i + size * j]) - static_cast<int>('0');
		}
	}
}

void ShapeMap::update(int width, int height,
                      int x, int y, int status) {
	std::pair<int, int> point = getPos(width, height, x, y);

	map_[point.first][point.second] = status;
}

bool ShapeMap::canChange(int width, int height, int x, int y) const {
	std::pair<int, int> point = getPos(width, height, x, y);

	return map_[point.first][point.second] == 0;
}

void ShapeMap::incSteps() {
	++steps_;
}

int ShapeMap::getSteps() const {
	return steps_;
}

int ShapeMap::checkDiagonal() const {
	int n = map_.size();
	int x = 0;

	for (int i = 0; i < n; ++i) {
		x += map_[i][i];
	}

	if (x % n == 0) {
		return x / n;
	}

	x = 0;
	for (int i = 0; i < n; ++i) {
		x += map_[i][n - 1 + i];
	}

	if (x % n == 0) {
		return x / n;
	}

	return 0;
}

int ShapeMap::checkLines() const {
	int n = map_.size();

	for (int i = 0; i < n; ++i) {
		int x = 0;
		for (int j = 0; j < n; ++j) {
			x += map_[i][j];
		}
		if (x % n == 0) {
			return x / n;
		}
	}

	for (int i = 0; i < n; ++i) {
		int x = 0;
		for (int j = 0; j < n; ++j) {
			x += map_[j][i];
		}
		if (x % n == 0) {
			return x / n;
		}
	}

	return 0;
}

int ShapeMap::checkGameOver() const {
	if (this->checkLines() == 1 || this->checkDiagonal() == 1) {
		return 1;
	}

	if (this->checkLines() == 2 || this->checkDiagonal() == 2) {
		return  2;
	}

	return 0;
}
/*********************************************************************************************/

void RunNotepad(void) {
	STARTUPINFO sInfo;
	PROCESS_INFORMATION pInfo;
	ZeroMemory(&sInfo, sizeof(STARTUPINFO));
	CreateProcess(_T("C:\\Windows\\Notepad.exe"),
                    NULL, NULL, NULL, FALSE, 0,
                    NULL, NULL, &sInfo, &pInfo);
}

/***************************** CHANGE COLOR FUNCTIONS*****************************************/

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

void colorChanger(COLORREF* colorRef, long delta) {
  long r = GetRValue(*colorRef);
  long g = GetGValue(*colorRef);
  long b = GetBValue(*colorRef);

  struct Color {
    long r;
    long g;
    long b;
  };

  Color color = { r, g, b };

	if(delta > 0) {
		if (color.r >= 255 && color.g < 255 && color.b <= 0)
			color.g += delta;
		else if (color.r > 0 && color.g >= 255 && color.b <= 0)
			color.r -= delta;
		else if (color.r <= 0 && color.g >= 255 && color.b < 255)
			color.b += delta;
		else if (color.r <= 0 && color.g > 0 && color.b >= 255)
			color.g -= delta;
		else if (color.r < 255 && color.g <= 0 && color.b >= 255)
			color.r += delta;
		else if (color.r >= 255 && color.g <= 0 && color.b > 0)
			color.b -= delta;
	} else {
		if (color.r >= 255 && color.g > 0 && color.b <= 0)
			color.g += delta;
		else if (color.r < 255 && color.g >= 255 && color.b <= 0)
			color.r -= delta;
		else if (color.r <= 0 && color.g >= 255 && color.b > 0)
			color.b += delta;
		else if (color.r <= 0 && color.g < 255 && color.b >= 255)
			color.g -= delta;
		else if (color.r > 0 && color.g <= 0 && color.b >= 255)
			color.r += delta;
		else if (color.r >= 255 && color.g <= 0 && color.b < 255)
			color.b -= delta;
	}

	color.r = (color.r < 0) ? (255) : ((color.r > 255) ? 0 : color.r);
	color.g = (color.g < 0) ? (255) : ((color.g > 255) ? 0 : color.g);
	color.b = (color.b < 0) ? (255) : ((color.b > 255) ? 0 : color.b);

  *colorRef = RGB(color.r, color.b, color.b);
}
/***************************************************************************************/

DWORD WINAPI Paint(void* hWnd) {
	HWND hwnd = (HWND)hWnd;

	while (true) {
			if (pauseThread) {
				WaitForSingleObject(mtx, INFINITE);
			}

			colorChanger(&groundColor, 5);
			ULONG_PTR DelBrush = SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(groundColor));
			DeleteObject(HGDIOBJ(DelBrush));


			InvalidateRect(hwnd, nullptr, TRUE);

      RECT rect;
	    GetClientRect(hwnd, &rect);

      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hwnd, &ps);

      DrawGrid(hdc, rect.right, rect.bottom);

			pMap->draw(rect.right, rect.bottom, hdc);
			pMap->loadFromMapping();

			DeleteObject(hdc);
			EndPaint(hwnd, &ps);
			ReleaseMutex(mtx);

			Sleep(50);
	}

	return 0;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
	TCHAR className[256];
	GetClassName(hwnd, className, sizeof(className));

	if (_tcscmp(szWinClass, szWinClass) == 0) {
		RedrawWindow(hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
	}

	return TRUE;
}