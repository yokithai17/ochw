#include <windows.h>
#include <tchar.h>
#include <windowsX.h.>

#include "notepad.h"
#include "saver.h"


const TCHAR szWinClass[] = _T("Win32SampleApp");
const TCHAR szWinName[] = _T("Win32SampleWindow");
/* HWND hwnd;               This is the handle for our window */
HBRUSH hBrush;           /* Current brush */

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

/**************************** MAIN ****************************************************/

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
      WIDTH,                 /* The programs width */
      HEIGHT,                 /* and height in pixels */
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

	FileSaver(R"(.\points.txt)").save();

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
