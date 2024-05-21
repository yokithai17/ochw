#pragma once

#ifndef CONFIG_H
#define CONFIG_H

#include <windows.h>
#include <sstream>

struct Config {
	int N = 10; /* Size of the grid */
	int WIDTH = 320; /* width of window */
	int HEIGHT = 240; /* height of window */
	const int COLOR_INCREMENT = 3; /* smooth color changer constanta (magic number) */
	COLORREF gridColor = RGB(255, 0, 0); /* default grid color */
	COLORREF groundColor = RGB(0, 0, 255); /* default background color */

	Config() = default;

	Config(const Config& cfg);

	Config& operator=(const Config& other);

	~Config() = default;
};

/**************************** HANDLERS **********************************************/

class ConfigHandler {
private:
	Config cfg_;

	std::ostream& serialize(std::ostream& out) const;

	Config CharToConfig() const;

public:
	explicit ConfigHandler(const Config& cfg): cfg_(cfg) {}

	explicit ConfigHandler(char* cfgText) {
		std::istringstream in(cfgText);
		this->serialize(in);
	};

	~ConfigHandler() = default;

	std::istream& serialize(std::istream& in);

	std::string getCfgLine() const;

	void setConfigFromText(const std::string& text);

	Config getConfig() const;
};

#endif //CONFIG_H
