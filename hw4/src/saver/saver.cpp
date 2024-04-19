#include "saver.h"

/********************************************************************************/

/***************************** FILE SAVER **************************************/

FileSaver::FileSaver(const std::string &path) {
	out.open(path);
}

FileSaver::~FileSaver() {
	out.close();
}

void FileSaver::save() {
	return;
}

template<typename Head, typename ...Tail>
void FileSaver::save(const Head &head, const Tail &...tail) {
	out << head << '\n';
	save(tail...);
}

/********************************************************************************/

/********************************************************************************/