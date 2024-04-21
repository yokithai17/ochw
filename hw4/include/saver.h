#pragma once

#ifndef COOLAPP__SAVER_H
#define COOLAPP__SAVER_H

#include <type_traits>
#include <iostream>
#include <fstream>
#include <string>
#include <windef.h>

#include "config.h"

/******************************** Stream *****************************************/

class StreamSaver {
private:
	std::ofstream out;

	void save_helper() {};

	template<typename Head, typename... Tail>
	void save_helper(const Head &head, const Tail &... tail) {
		out << head << '\n';
		save_helper(tail...);
	}

public:

	explicit StreamSaver(std::string path);

	~StreamSaver();

	void save(Config* cfg) {
		save_helper(
				cfg->N,
				cfg->WIDTH,
				cfg->HEIGHT,
				cfg->groundColor,
				cfg->gridColor
				);
	}

};

/****************************** C-style *******************************************/

class CstyleSaver {
private:
	FILE* fl;
	bool isOpened;

	CstyleSaver() = default;
public:
	explicit CstyleSaver(const char*);

	~CstyleSaver();

	void save(int, int, int, COLORREF, COLORREF);
};

/***************************** Wmaping ********************************************/

class MapSaver {
private:
	std::string path;

	MapSaver() = default;

public:
	explicit MapSaver(std::string  path);

	~MapSaver();

	void save(Config* cfg);
};

/******************************** WINAPI *****************************************/

class wFileSaver {
private:
	std::string path;

	wFileSaver() = default;
public:
	explicit wFileSaver(std::string path);

	void save(Config* cfg);
};


#endif //COOLAPP__SAVER_H
