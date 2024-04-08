#include <iostream>
#include <algorithm>
#include <windows.h>
#include <tchar.h>
#include <time.h>
#include <utility>
#include <vector>
#include <fstream>
#include <windowsX.h.>
#include <string>

/******************* GLOBAL VARIABLES ****************************************/
int N = 10; /* Size of the grid*/
const int COLOR_INCREMENT = 3; /* smooth color changer constanta (magic number) */
const TCHAR szWinClass[] = _T("Win32SampleApp");
const TCHAR szWinName[] = _T("Win32SampleWindow");
COLORREF gridColor = RGB(255, 0, 0); /* default grid color */
COLORREF groundColor = RGB(0, 0, 255); /* default background color */
/* HWND hwnd;               This is the handle for our window */
HBRUSH hBrush;           /* Current brush */
/*****************************************************************************/

/******************************** function ************************************/
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

void DrawGrid(HDC hdc, RECT rect);

void DrawCross(HDC hdc, LONG posX, LONG posY, LONG step);

void DrawCircle(HDC hdc, LONG left, LONG top, LONG right, LONG bottom);

void ChangeBackgroundColor(HWND hwnd);

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
  std::vector<std::vector<int>> map_;
  std::string path_;

  explicit ShapeMap() = default;

public:

  explicit ShapeMap(int n, std::string path) :
      map_(std::vector<std::vector<int>>(n, std::vector<int>(n, 0)))
      , path_(std::move(path))
  {
    this->load();
  };

  ~ShapeMap() {
    this->save();
  }

  void update(LONG width, LONG height,
              LONG x, LONG y, int status) {
    LONG posX = mmin(9L, static_cast<LONG>(x / (width / N)));
    LONG posY = mmin(9L, static_cast<LONG>(y / (height / N)));
    map_[posX][posY] = status;
  }

  void draw(LONG width, LONG height, HDC hdc) const {
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

  void load() {
    std::ifstream in(path_);
    std::string str;
    in >> str;
    int size = static_cast<int>(str.size());
    if (N * N != size) {
      return;
    }

    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        map_[i][j] = static_cast<int>(str[i * N + j]) - static_cast<int>('0');
      }
    }

    in.close();
  }

  void save() const {
    std::ofstream out(path_);
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        out << static_cast<char>(map_[i][j] + static_cast<int>('0'));
      }
    }
    out.close();
  }
};
/***********************************************************************************/

/**************************** MAIN *************************************************/

int main(int argc, char *argv[]) {
  if (argc >= 2) {
    N = std::strtol(argv[1], nullptr, 10);
  } else {
    N = 10;
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

  return 0;
}
/********************************************************************************************/

/***************************** WND PROCEDURE ************************************************/

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  static ShapeMap map(N, R"(.\points.txt)");

  switch (message)                  /* handle the messages */
  {
  case WM_DESTROY:PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
    return 0;

  case WM_ERASEBKGND:return 0;

  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    RECT rect;
    GetClientRect(hwnd, &rect);

    DeleteObject(hBrush);
    hBrush = CreateSolidBrush(groundColor);

    FillRect(hdc, &rect, hBrush);
    DrawGrid(hdc, rect);

    map.draw(rect.right, rect.bottom, hdc);
    EndPaint(hwnd, &ps);
  }
    return 0;
  case WM_SIZE: {
    InvalidateRect(hwnd, nullptr, 0);
  }
    return 0;

  case WM_RBUTTONDOWN: {
    LONG xPos = GET_X_LPARAM(lParam);
    LONG yPos = GET_Y_LPARAM(lParam);

    RECT rect;
    GetClientRect(hwnd, &rect);
    map.update(rect.right, rect.bottom, xPos, yPos, 1);
    InvalidateRect(hwnd, nullptr, 0);
  }

    return 0;

  case WM_LBUTTONDOWN: {
    LONG xPos = GET_X_LPARAM(lParam);
    LONG yPos = GET_Y_LPARAM(lParam);

    RECT rect;
    GetClientRect(hwnd, &rect);
    map.update(rect.right, rect.bottom, xPos, yPos, 2);
    InvalidateRect(hwnd, nullptr, 0);
  }

    return 0;

  case WM_KEYDOWN:
    switch (wParam) {

    case VK_ESCAPE:PostQuitMessage(0);
      break;

    case 'Q':
      if (GetKeyState(VK_CONTROL)) {
        PostQuitMessage(0);
      }
      break;

    case VK_CONTROL:
      if (GetKeyState('Q')) {
        PostQuitMessage(0);
      }
      break;

    case VK_RETURN: ChangeBackgroundColor(hwnd);
      break;

    case VK_SHIFT:
      if (GetKeyState('C')) {
        ShellExecute(nullptr, "open", "notepad.exe",
                     nullptr, nullptr, SW_SHOWNORMAL);
      }
      break;

    case 'C':
      if (GetKeyState(VK_SHIFT)) {
        ShellExecute(nullptr, "open", "notepad.exe",
                     nullptr, nullptr, SW_SHOWNORMAL);
      }
      break;
    }

    return 0;

  case WM_MOUSEWHEEL: {
    int delta = (GET_WHEEL_DELTA_WPARAM(wParam) > 0) ? (5) : (-5);
    ChangeGridColor(delta);
    InvalidateRect(hwnd, nullptr, 0);
  }
    return 0;
  }


  /* for messages that we don't deal with */
  return DefWindowProc(hwnd, message, wParam, lParam);
}
/*********************************************************************************************/

/***************************** DRAW FUNCTIONS ************************************************/

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

void DrawCross(HDC hdc, LONG posX, LONG posY, LONG step) {
  MoveToEx(hdc, posX - step, posY - step, nullptr);
  LineTo(hdc, posX + step, posY + step);
  MoveToEx(hdc, posX - step, posY + step, nullptr);
  LineTo(hdc, posX + step, posY - step);
}

void DrawCircle(HDC hdc, LONG left, LONG top, LONG right, LONG bottom) {
  Ellipse(hdc, left, top, right, bottom);
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
/***************************************************************************************/
