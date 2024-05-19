#ifndef LOADER_H
#define LOADER_H

#include <type_traits>
#include <iostream>
#include <fstream>
#include <string>
#include <windef.h>
#include <sstream>

#include "config.h"

/******************************** ILoader *****************************************/
class ILoader {
protected:
	ConfigHandler cfgHNDL_;

	Config loadHelper(std::istream& in);
	
	virtual std::string loadText() = 0;

public:
	explicit ILoader();

	explicit ILoader(const Config& cfg): cfgHNDL_(cfg) {}

	virtual ~ILoader(){}

	virtual Config load();
};

/******************************** Stream *****************************************/
class StreamLoader : public ILoader {
private:
	std::string path_;

	std::string loadText() final {}

public:
	explicit StreamLoader(const std::string& path, const Config& cfg): ILoader(cfg), path_(path) {}

	Config load() final;
};

/****************************** C-style *******************************************/

class CstyleLoader : public ILoader {
private:
	std::string path_;

	std::string loadText() final;

public:
	explicit CstyleLoader(const std::string& path, const Config& cfg): ILoader(cfg), path_(path) {}
};

/***************************** Wmapoing ********************************************/

class MapLoader : public ILoader {
private:
	std::string path_;

	std::string loadText() final;

public:
	explicit MapLoader(const std::string& path, const Config& cfg) : ILoader(cfg), path_(path) {}
};

/******************************** WINAPI *****************************************/

class wFileLoader : public ILoader  {
private:
	std::string path_;

	std::string loadText() final;

public:
	explicit wFileLoader(const std::string& path, const Config& cfg) : ILoader(cfg), path_(path) {}
};

#endif //LOADER_H
