#include <windows.h>
#include <tchar.h>
#include <windowsX.h.>

#include "notepad.h"
#include "saver.h"
#include "loader.h"

const TCHAR szWinClass[] = _T("Win32SampleApp");
const TCHAR szWinName[] = _T("Win32SampleWindow");
/* HWND hwnd;               This is the handle for our window */
HBRUSH hBrush;           /* Current brush */

Config cfg;             /* check config.h to more info */

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

void RunNotepad(void) {
	STARTUPINFO sInfo;
	PROCESS_INFORMATION pInfo;
	ZeroMemory(&sInfo, sizeof(STARTUPINFO));
	CreateProcess(_T("C:\\Windows\\Notepad.exe"),
                    NULL, NULL, NULL, FALSE, 0,
                    NULL, NULL, &sInfo, &pInfo);
}

/**************************** MAIN ****************************************************/
#include <memory>

std::unique_ptr<ILoader> CreateLoader(int x, std::string path, Config cfg) {
  switch (x) {
  case 1:
    return std::make_unique<StreamLoader>(path, cfg);

  case 2:
    return std::make_unique<CstyleLoader>(path, cfg);

  case 3:
    return std::make_unique<MapLoader>(path, cfg);

  case 4:
    return std::make_unique<wFileLoader>(path, cfg);
  }

  return nullptr;
}

std::unique_ptr<ISaver> CreateSaver(int x, std::string path, Config cfg) {
  switch (x) {
  case 1:
    return std::make_unique<StreamSaver>(path, cfg);

  case 2:
    return std::make_unique<CstyleSaver>(path, cfg);

  case 3:
    return std::make_unique<MapSaver>(path, cfg);

  case 4:
    return std::make_unique<wFileSaver>(path, cfg);
  }

  return nullptr;
}

/**************************** MAIN ****************************************************/

int main(int argc, char *argv[]) {
	int loadConfig = 0;
  std::string path("./config.txt");

	int n = 10;
	if (argc > 1) {
		n = std::strtol(argv[1], nullptr, 10);
		if (argc == 3) {
			loadConfig = std::strtol(argv[2], nullptr, 10);
		}
	}

  /* load data from config fle */
  auto loader = CreateLoader(loadConfig, path, cfg);
  if (loader.get() != nullptr) {
    cfg = loader->load();
  }

	cfg.N = (n == -1)?(cfg.N):(n);

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
  hBrush = CreateSolidBrush(cfg.groundColor);
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
      cfg.WIDTH,                 /* The programs width */
      cfg.HEIGHT,                 /* and height in pixels */
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

	/* store data to config file */
  auto saver = CreateSaver(loadConfig, path, cfg);
  if (saver.get() != nullptr) {
    saver->save();
  }

  return 0;
}
/********************************************************************************************/

/***************************** WND PROCEDURE ************************************************/

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  static ShapeMap map(R"(.\points.txt)", &cfg);
	static LONG xSize;
	static LONG ySize;

	/* handle the messages */
  switch (message) {

  case WM_DESTROY: {
    RECT rect;
    GetWindowRect(hwnd, &rect);
		cfg.WIDTH = rect.right - rect.left;
		cfg.HEIGHT = rect.bottom - rect.top;
    PostQuitMessage(0);
    } 
    return 0;


  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    hBrush = CreateSolidBrush(cfg.groundColor);
    DrawGrid(hdc, &cfg);

    map.draw(cfg.WIDTH, cfg.HEIGHT, hdc);

    DeleteObject(hBrush);
    EndPaint(hwnd, &ps);
  }
    return 0;
    
  case WM_SIZE: {
	  RECT rect;
	  GetClientRect(hwnd, &rect);

	  cfg.WIDTH = rect.right - rect.left;
	  cfg.HEIGHT = rect.bottom - rect.top;
	  InvalidateRect(hwnd, nullptr, TRUE);
  }
	  return 0;

  case WM_RBUTTONDOWN: {
    LONG xPos = GET_X_LPARAM(lParam);
    LONG yPos = GET_Y_LPARAM(lParam);

    map.update(cfg.WIDTH, cfg.HEIGHT, xPos, yPos, 1);
    InvalidateRect(hwnd, nullptr, TRUE);
  }

    return 0;

  case WM_LBUTTONDOWN: {
    LONG xPos = GET_X_LPARAM(lParam);
    LONG yPos = GET_Y_LPARAM(lParam);

	  map.update(cfg.WIDTH, cfg.HEIGHT, xPos, yPos, 2);
    InvalidateRect(hwnd, nullptr, TRUE);
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

	  case VK_RETURN: ChangeBackgroundColor(hwnd, &cfg);
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
    ChangeGridColor(delta, &cfg);
    InvalidateRect(hwnd, nullptr, TRUE);
  }
    return 0;
  }


  /* for messages that we don't deal with */
  return DefWindowProc(hwnd, message, wParam, lParam);
}


