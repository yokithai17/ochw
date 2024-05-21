#include <tchar.h>
#include <windows.h>
#include <windowsX.h.>

#include "notepad.h"
#include "saver.h"
#include "loader.h"

#define BUFF_SIZE 1024

const TCHAR szWinClass[] = _T("Win32SampleApp");
const TCHAR szWinName[] = _T("Win32SampleWindow");
/* HWND hwnd;               This is the handle for our window */
HBRUSH hBrush;           /* Current brush */

Config cfg;             /* check config.h to more info */

HANDLE hMapFile;
char* pBuf = nullptr;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

void RunNotepad();
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
auto MapName = _T("ChatLine9847589345673246758");
HANDLE PaintThreadHNDL;

int strcmp(const char *lhs, const char *rhs );

#define TEAM1 1
#define TEAM2 2

void parser(char* argv[], int argc, int* player) {
  for (int i = 0; i < argc; ++i) {
    if (strcmp(argv[i], "-t1") == 0) {
      *player = TEAM1;
    }

    if (strcmp(argv[i], "-t2") == 0) {
      *player = TEAM2;
    }
  }
}

int team = TEAM1;
LONG move = TEAM1;
HANDLE movesem;
HANDLE paintsem;
LONG countMoves = 0;

struct ThreadArgs {
  HWND hwnd_;
  ShapeMap* pmap_;
  explicit ThreadArgs(HWND hwnd, ShapeMap* map): hwnd_(hwnd), pmap_(map) {}
};

ShapeMap map;

void paintHelper(HWND, ShapeMap*);
DWORD WINAPI paint(void* args);
CRITICAL_SECTION gameover;


/*************************************************************************************/
int main(int argc, char *argv[]) {
	int loadConfig = 0;
  DWORD dwThread;
  std::string path("./config.txt");

  movesem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, _T("STARIY_BOG"));

  if (movesem == NULL) {
    movesem = CreateSemaphore(NULL, 2, 3, _T("STARIY_BOG"));
  }

  parser(argv, argc, &team);

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

  
  hMapFile = OpenFileMapping(
                   FILE_MAP_ALL_ACCESS,   // read/write access
                   FALSE,                 // do not inherit the name
                   MapName
  );

  bool flag = hMapFile == NULL;

  if (flag) {
    hMapFile = CreateFileMapping(
    INVALID_HANDLE_VALUE,
    NULL,
    PAGE_READWRITE,
    0,
    BUFF_SIZE,
    MapName
    );
  }

  pBuf = (char*)MapViewOfFile(
  hMapFile,
  FILE_MAP_ALL_ACCESS,
  0,
  0,
  BUFF_SIZE
  );


  if (flag) {
    cfg.N = (n == -1)?(cfg.N):(n);
    for (int i = 0; i < cfg.N * cfg.N; ++i) {
			pBuf[i] = '0';
		}

    CreateSaver(1, path, cfg)->save();
  } else {
    cfg = CreateLoader(1, path, cfg)->load();
  }
  map = ShapeMap(R"(.\points.txt)", &cfg, pBuf);

  /* if we create another window */

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
  TCHAR tmp[6] = _T("team ");
  if (team == TEAM1) {
    tmp[5] = L'1';
  } else {
    tmp[5] = L'2';
  }

  HWND hwnd = CreateWindow(
      szWinClass,          /* Classname */
      tmp,       /* Title Text */
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
  ThreadArgs tArgs(hwnd, &map);
  /*
  std::ofstream out("team.txt", std::ios::app);
  out << team;
  out.close();
  */
  InitializeCriticalSection(&gameover);
  PaintThreadHNDL = CreateThread(NULL, 0, paint, &tArgs, 0, &dwThread);

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
  CloseHandle(PaintThreadHNDL);
  UnregisterClass(szWinClass, hThisInstance);
  DeleteObject(hBrush);

	/* store data to config file */
  auto saver = CreateSaver(loadConfig, path, cfg);
  if (saver.get() != nullptr) {
    saver->save();
  }

  /* CLEAN UP mapping stuff */
  UnmapViewOfFile(pBuf);
  CloseHandle(hMapFile);

  return 0;
}
/********************************************************************************************/
/***************************** WND PROCEDURE ************************************************/
bool isRendering = true;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
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
    
  case WM_SIZE: {
	  RECT rect;
	  GetClientRect(hwnd, &rect);

	  cfg.WIDTH = rect.right - rect.left;
	  cfg.HEIGHT = rect.bottom - rect.top;
	  //InvalidateRect(hwnd, nullptr, TRUE);
  }
	  return 0;
/*
  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    map.loadFromMapping();

    hBrush = CreateSolidBrush(cfg.groundColor);
    DrawGrid(hdc, &cfg);

    map.draw(cfg.WIDTH, cfg.HEIGHT, hdc);

    DeleteObject(hBrush);
    EndPaint(hwnd, &ps);
  }
    return 0;
    */

  case WM_LBUTTONDOWN: {
    LONG teamToMove = -1;

    ReleaseSemaphore(movesem, 1, &teamToMove);
    WaitForSingleObject(movesem, 0);

    std::ofstream f("team.txt", std::ios::app);
    f << teamToMove;
    f.close();

    if (teamToMove != team) {
      auto tmp1 = (teamToMove == TEAM1) ? (_T("team1 move")) : (_T("team2 move"));
      auto tmp2 = (team == TEAM1) ? (_T("ur in team1")) : (_T("ur in team2"));
      MessageBox(hwnd, tmp1, tmp2, MB_OK);
      return 0;
    }

    LONG xPos = GET_X_LPARAM(lParam);
    LONG yPos = GET_Y_LPARAM(lParam);

    if (!map.isValide(cfg.WIDTH, cfg.HEIGHT, xPos, yPos)) {
      MessageBox(hwnd, _T("STARIY BOG"), _T("U CANT PUT HERE"), MB_OK);
      return 0;
    }

    map.update(cfg.WIDTH, cfg.HEIGHT, xPos, yPos, team);
    InterlockedIncrement(&countMoves);
    
    if (map.checkWin(cfg.WIDTH, cfg.HEIGHT, xPos, yPos)) {
      EnterCriticalSection(&gameover);
      auto tmp = (team == TEAM1) ? (_T("TEAM1 WIN")) : (_T("TEAM2 WIN"));
      MessageBox(hwnd,  tmp, _T("STARIY BOG"), MB_OK);
      for (int i = 0; i < cfg.N * cfg.N; ++i) {
        pBuf[i] = '0';
      }
      LeaveCriticalSection(&gameover);
    }

    if (countMoves == cfg.N * cfg.N) {
      EnterCriticalSection(&gameover);
      MessageBox(hwnd,  _T("no one win"), _T("STARIY BOG"), MB_OK);
      for (int i = 0; i < cfg.N * cfg.N; ++i) {
        pBuf[i] = '0';
      }
      LeaveCriticalSection(&gameover);
    }
    
    if (team == TEAM1) {
      ReleaseSemaphore(movesem , 1, NULL);
    } else {
      WaitForSingleObject(movesem, INFINITE);
    }
    return 0;
	  //EnumWindows(EnumWindowsProc, TRUE);
  }

    return 0;
  /*
  case WM_LBUTTONDOWN: {
    if (move != TEAM2) {
      MessageBox(hwnd, _T("hello team2"), _T("not ur turn"), MB_OK);
      return 0;
    }

    LONG xPos = GET_X_LPARAM(lParam);
    LONG yPos = GET_Y_LPARAM(lParam);

	  map.update(cfg.WIDTH, cfg.HEIGHT, xPos, yPos, 2);
    InterlockedDecrement(&move);
    EnumWindows(EnumWindowsProc, TRUE);
  }
  */

    return 0;

  case WM_KEYDOWN:
	  switch (wParam) {
      
    case VK_SPACE: {
      auto it = ResumeThread(PaintThreadHNDL);
      if (it == 0) {
        SuspendThread(PaintThreadHNDL);
        paintHelper(hwnd, &map);
      }
    }
    break;

    case 	0x31: {
      SetThreadPriority(PaintThreadHNDL, 1);
    }
    break;

    case 0x32: {
      SetThreadPriority(PaintThreadHNDL, 2);
    }
    break;

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
    //InvalidateRect(hwnd, nullptr, TRUE);
  }
    return 0;
  }


  /* for messages that we don't deal with */
  return DefWindowProc(hwnd, message, wParam, lParam);
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
	TCHAR className[256];
	GetClassName(hwnd, className, sizeof(className));
  
	if (_tcscmp(szWinClass, szWinClass) == 0) {
		RedrawWindow(hwnd, nullptr, nullptr, RDW_ERASE | RDW_INTERNALPAINT | RDW_INVALIDATE);
	}

	return TRUE;
}

void RunNotepad() {
	STARTUPINFO sInfo;
	PROCESS_INFORMATION pInfo;
	ZeroMemory(&sInfo, sizeof(STARTUPINFO));
	CreateProcess(_T("C:\\Windows\\Notepad.exe"),
                    NULL, NULL, NULL, FALSE, 0,
                    NULL, NULL, &sInfo, &pInfo);
}

void paintHelper(HWND hwnd, ShapeMap* map) {
  ChangeBackgroundColor(hwnd, &cfg);

  PAINTSTRUCT ps;

  HDC hdc = BeginPaint(hwnd, &ps);

  //rgbChanger2(cfg);

  map->loadFromMapping();

  DrawGrid(hdc, &cfg);

  map->draw(cfg.WIDTH, cfg.HEIGHT, hdc);

  DeleteObject(hBrush);
  EndPaint(hwnd, &ps);
}

DWORD WINAPI paint(void* args) {
  ThreadArgs *ta = static_cast<ThreadArgs*>(args);
  while (true) {
    paintHelper(ta->hwnd_, ta->pmap_);
    Sleep(5);
  }
}