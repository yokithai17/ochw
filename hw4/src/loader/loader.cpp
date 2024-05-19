#include "loader.h"

/******************************* ILOAD ****************************************/

Config ILoader::loadHelper(std::istream& in) {
	cfgHNDL_.serialize(in);
	return cfgHNDL_.getConfig();
}

Config ILoader::load() {
	std::string text = loadText();
	std::istringstream in(text);
	return loadHelper(in);
}

/**********************************************************************************/

/******************************** Stream *****************************************/
Config StreamLoader::load() {
	std::ifstream in(path_);
	auto cfg = loadHelper(in);
	in.close();
	return cfg;
}

/**********************************************************************************/

/****************************** C-style *******************************************/

std::string CstyleLoader::loadText() {
	FILE* fl = fopen(path_.c_str(), "r");
	if (fl == nullptr) {
		return std::string();
	}

	char cfgText[1024];
	
	char ch;
	int i = 0;
	while ((ch = fgetc(fl)) != EOF) {
		cfgText[i++] = ch;
	}
	cfgText[i] = '\0';	

	return std::string(cfgText);
}

/**********************************************************************************/
/****************************** Wmapping *******************************************/

std::string MapLoader::loadText() {
	HANDLE hFile = CreateFile(path_.c_str(), GENERIC_WRITE | GENERIC_READ,
	                          0, nullptr, OPEN_EXISTING,
	                          FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hFile == INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
		return  std::string();
	}

	int size = GetFileSize(hFile, nullptr);

	HANDLE hMapping = CreateFileMapping(hFile, nullptr, PAGE_READWRITE,
	                                    0, size, nullptr);

	if (hMapping == nullptr) {
		CloseHandle(hMapping);
		CloseHandle(hFile);
		return  std::string();
	}


	char* pData = (char*)MapViewOfFile(hMapping,
	                                   FILE_MAP_WRITE,
	                                   0, 0, size);

	if (pData == nullptr) {
		CloseHandle(hMapping);
		CloseHandle(hFile);
		return std::string();
	}

	std::string str(pData, size);

	UnmapViewOfFile(pData);
	CloseHandle(hMapping);
	CloseHandle(hFile);

	return str;
}

/**********************************************************************************/
/****************************** WFileLoader ****************************************/
std::string wFileLoader::loadText() {
	HANDLE hFile = CreateFile(path_.c_str(), GENERIC_READ,
														0, nullptr, OPEN_EXISTING,
														FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hFile == INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
		return std::string();
	}

	DWORD size;
	Config cfg;
	char buffer[1024];
	std::string str;

	if (ReadFile(hFile, buffer, sizeof(buffer), &size, nullptr)) {
		str = std::string(buffer, size);
	}

	CloseHandle(hFile);

	return str;
}