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
class ISaver {
protected:
	ConfigHandler cfgHNDL_;

	explicit ISaver();

public:
	explicit ISaver(const Config& cfg): cfgHNDL_(cfg) {}

	virtual ~ISaver(){}

	virtual void save() const = 0;
};
/****************************** StreamSaver *******************************************/

class StreamSaver : public ISaver {
private:
	std::string path_;

public:
	explicit StreamSaver(const std::string& path, const Config& cfg): ISaver(cfg), path_(path) {}

	void save() const final;
};

/****************************** C-style *******************************************/

class CstyleSaver : public ISaver {
private:
	std::string path_;

public:
	explicit CstyleSaver(const std::string& path, const Config& cfg): ISaver(cfg), path_(path) {}

	void save() const final;
};

/***************************** Wmaping ********************************************/

class MapSaver : public ISaver {
private:
	std::string path_;

public:
	explicit MapSaver(const std::string& path, const Config& cfg) : ISaver(cfg), path_(path) {}

	void save() const final;
};

/******************************** WINAPI *****************************************/

class wFileSaver : public ISaver {
private:
	std::string path_;

public:
	explicit wFileSaver(const std::string& path, const Config& cfg) : ISaver(cfg), path_(path) {}

	void save() const final;
};

#endif //COOLAPP__SAVER_H
