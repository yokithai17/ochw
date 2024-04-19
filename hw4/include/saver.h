#pragma once

#ifndef COOLAPP__SAVER_H
#define COOLAPP__SAVER_H

#include <type_traits>
#include <iostream>
#include <fstream>
#include <string>

class ISaver {
public:
	virtual ~ISaver() {};

	virtual void save() = 0;
};

class FileSaver: public ISaver {
private:
	std::string path;
	std::ofstream out;

	FileSaver() = default;

public:
	FileSaver(const std::string& path);

	~FileSaver() final;

	void save() final;

	template <typename Head, typename... Tail>
	void save(const Head& head,const Tail&... tail);

};

#endif //COOLAPP__SAVER_H
