#include "loader.h"

/******************************** Stream *****************************************/
void StreamLoader::load(const std::string& path, Config *cfg) {
	std::ifstream in(path);
	in >> cfg->N;
	in >> cfg->WIDTH;
	in >> cfg->HEIGHT;
	in >> cfg->groundColor;
	in >> cfg->gridColor;
	in.close();
}

/**********************************************************************************/

/****************************** C-style *******************************************/

void CstyleLoader::load(const std::string &path, Config* cfg) {

	FILE* fl = fopen(path.c_str(), "r");
	if (fl == nullptr) {
		return;
	}
	fscanf(fl, "%d\n%d\n%d\n%ld\n%ld\n", &cfg->N, &cfg->WIDTH, &cfg->HEIGHT, &cfg->groundColor, &cfg->gridColor);
}

/**********************************************************************************/
/****************************** Wmapping *******************************************/

void MapLoader::load(const std::string &path, Config *cfg) {

	HANDLE hFile = CreateFile(path.c_str(), GENERIC_WRITE | GENERIC_READ,
	                          0, nullptr, OPEN_EXISTING,
	                          FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hFile == INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
		return;
	}

	int size = GetFileSize(hFile, nullptr);

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

	if (pData == nullptr) {
		CloseHandle(hMapping);
		CloseHandle(hFile);
		return;
	}

	std::string line;
	std::istringstream in(pData);

	std::getline(in, line);
	cfg->N = std::atoi(line.c_str());

	std::getline(in, line);
	cfg->WIDTH = std::atoi(line.c_str());

	std::getline(in, line);
	cfg->HEIGHT = std::atoi(line.c_str());

	std::getline(in, line);
	cfg->groundColor = std::atol(line.c_str());

	std::getline(in, line);
	cfg->gridColor = std::atol(line.c_str());

	UnmapViewOfFile(pData);
	CloseHandle(hMapping);
	CloseHandle(hFile);

	return;
}

/**********************************************************************************/
/****************************** WFileLoader ****************************************/

void wFileLoader::load(const std::string &path, Config *cfg) {

}