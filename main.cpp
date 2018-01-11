#include <string>
#include <iostream>
#include "crap.h"

using namespace std;

int main( int argc, char* argv[] ) {

	Crap crap;

	if ( argc > 2 ) {
		cout << "Usage: crap [file]";
	} else if ( argc == 2 ) {
		crap.runFile( argv[0] );
	} else {
		crap.runPrompt();
	}

	return 0;
}
