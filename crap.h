#ifndef __CRAP_H
#define __CRAP_H

#include <string>
#include "crapErrors.h"

using namespace std;

class Crap {
	public:
		int runFile( string file_path );
		int runPrompt();
};

#endif
