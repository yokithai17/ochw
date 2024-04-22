#include "saver.h"

#include <utility>

/*******************************************************************************/

/******************************* Stream Saver ************************************/

StreamSaver::StreamSaver(std::string path): out(std::ofstream(path)) {}

StreamSaver::~StreamSaver() {
	out.close();
}

/*******************************************************************************/

/**************************** C-style Saver **************************************/

CstyleSaver::CstyleSaver(const std::string& path): fl(fopen(path.c_str(), "w")) {
	isOpened = (fl != nullptr);
}

CstyleSaver::~CstyleSaver() {
	fclose(fl);
}

void CstyleSaver::save(Config* cfg) {
	if (isOpened) {
		fprintf(fl
						, "%d\n%d\n%d\n%ld\n%ld\n"
						, cfg->N, cfg->WIDTH, cfg->HEIGHT, cfg->groundColor, cfg->gridColor);
	}
}
/*******************************************************************************/

/**************************** Wmaping **************************************/

MapSaver::MapSaver(std::string path): path(std::move(path)) {}

MapSaver::~MapSaver() {}

void MapSaver::save(Config *cfg) {
	HANDLE hFile = CreateFile(path.c_str(), GENERIC_WRITE | GENERIC_READ,
														0, nullptr, CREATE_ALWAYS,
														FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hFile == INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
		return;
	}

	size_t size = 0;

	std::string nStr = std::to_string(cfg->N);
	nStr.push_back('\n');
	size += nStr.size();

	std::string wStr = std::to_string(cfg->WIDTH);
	wStr.push_back('\n');
	size += wStr.size();

	std::string hStr = std::to_string(cfg->HEIGHT);
	hStr.push_back('\n');
	size += hStr.size();


	std::string groundStr = std::to_string(cfg->groundColor);
	groundStr.push_back('\n');
	size += groundStr.size();

	std::string gridStr = std::to_string(cfg->gridColor);
	gridStr.push_back('\n');
	size += gridStr.size();


	HANDLE hMapping = CreateFileMapping(hFile, nullptr, PAGE_READWRITE,
	                                    0, size, nullptr);

	if (hMapping == nullptr) {
		CloseHandle(hMapping);
		CloseHandle(hFile);
		return;
	}


	char* pData = (char*)MapViewOfFile(hMapping,
																		 FILE_MAP_WRITE,
																		 0, 0, size);

	size_t it = 0;

	memcpy(pData, nStr.c_str(), nStr.size());
	it += nStr.size();

	memcpy(pData + it, wStr.c_str(), wStr.size());
	it += wStr.size();

	memcpy(pData + it, hStr.c_str(), hStr.size());
	it += hStr.size();

	memcpy(pData + it, groundStr.c_str(), groundStr.size());
	it += groundStr.size();

	memcpy(pData + it, gridStr.c_str(), gridStr.size());

	if (pData == nullptr) {
		CloseHandle(hMapping);
		CloseHandle(hFile);
		return;
	}

	UnmapViewOfFile(pData);
	CloseHandle(hMapping);
	CloseHandle(hFile);
}
/*********************************************************************************/

/******************************** WINAPI *****************************************/

wFileSaver::wFileSaver(std::string path): path(std::move(path)) {}

void wFileSaver::save(Config* cfg) {
	HANDLE hFile = CreateFile(path.c_str(), GENERIC_WRITE,
	                          0, nullptr, CREATE_ALWAYS,
	                          FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hFile == INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
		return;
	}

	size_t size = 0;

	std::string nStr = std::to_string(cfg->N);
	nStr.push_back('\n');
	WriteFile(hFile, nStr.c_str(), nStr.size(), 0, 0);

	std::string wStr = std::to_string(cfg->WIDTH);
	wStr.push_back('\n');
	WriteFile(hFile, wStr.c_str(), wStr.size(), 0, 0);

	std::string hStr = std::to_string(cfg->HEIGHT);
	hStr.push_back('\n');
	WriteFile(hFile, hStr.c_str(), hStr.size(), 0, 0);


	std::string groundStr = std::to_string(cfg->groundColor);
	groundStr.push_back('\n');
	WriteFile(hFile, groundStr.c_str(), groundStr.size(), 0, 0);

	std::string gridStr = std::to_string(cfg->gridColor);
	gridStr.push_back('\n');
	WriteFile(hFile, gridStr.c_str(), gridStr.size(), 0, 0);

	CloseHandle(hFile);
}