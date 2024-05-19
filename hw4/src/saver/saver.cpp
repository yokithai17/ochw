#include "saver.h"

#include <utility>

/****************************** StreamSaver ***************************************/
void StreamSaver::save() const {
	std::ofstream out(this->path_);
	out << cfgHNDL_.getCfgLine();
	out.close();
}

/**************************** C-style Saver **************************************/
void CstyleSaver::save() const {
	FILE* fl = fopen(path_.c_str(), "w");

	if (fl != nullptr) {
		fprintf(fl, "%s", cfgHNDL_.getCfgLine().c_str());
	}
	
	fclose(fl);
}
/*******************************************************************************/

/**************************** Wmaping **************************************/

void MapSaver::save() const {
	HANDLE hFile = CreateFile(path_.c_str(), GENERIC_WRITE | GENERIC_READ,
														0, nullptr, CREATE_ALWAYS,
														FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hFile == INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
		return;
	}

	std::string cfgLine = cfgHNDL_.getCfgLine();
	size_t size = cfgLine.size();


	HANDLE hMapping = CreateFileMapping(hFile, nullptr, PAGE_READWRITE,
	                                    0, size, nullptr);

	if (hMapping == nullptr) {
		CloseHandle(hMapping);
		CloseHandle(hFile);
		return;
	}
	
	char* pData = (char*)MapViewOfFile(hMapping, FILE_MAP_WRITE, 0, 0, size);

	if (pData == nullptr) {
		CloseHandle(hMapping);
		CloseHandle(hFile);
		return;
	}

	sprintf(pData, "%s", cfgLine.c_str());

	UnmapViewOfFile(pData);
	CloseHandle(hMapping);
	CloseHandle(hFile);
}
/*********************************************************************************/

/******************************** WINAPI *****************************************/
void wFileSaver::save() const {
	HANDLE hFile = CreateFile(path_.c_str(), GENERIC_WRITE,
	                          0, nullptr, CREATE_ALWAYS,
	                          FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hFile == INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
		return;
	}

	std::string cfgLine = cfgHNDL_.getCfgLine();

	WriteFile(hFile, cfgLine.c_str(), cfgLine.size(), 0, 0);

	CloseHandle(hFile);
}