#ifndef LOADER_H
#define LOADER_H

#include <type_traits>
#include <iostream>
#include <fstream>
#include <string>
#include <windef.h>
#include <sstream>

#include "config.h"

/******************************** Stream *****************************************/
struct StreamLoader {
	static void load(const std::string& path,Config* cfg);
};

/****************************** C-style *******************************************/

struct CstyleLoader {
	static void load(const std::string& path, Config* cfg);
};

/***************************** Wmapoing ********************************************/

struct MapLoader {
	static void load(const std::string& path, Config* cfg);
};

/******************************** WINAPI *****************************************/

struct wFileLoader {
	static void load(const std::string& path, Config* cfg);
};

#endif //LOADER_H
