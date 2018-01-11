#include <string>
#include <iostream>
#include <map>
#include "crapScanner.h"
#include "crapParser.h"

#include "crap.h"

using namespace std;

struct Object {
        string obj_value;
        Object* parent;
        map<string, Object*> slots;
        map< string, map<string, Object*> > child_slots;
};

map<string, Object> objects;

int Crap::runFile( string file_path ) {
	return 0;
}

int Crap::runPrompt() {
	string input;

	while ( true ) {
		cout << ">> ";
		getline( cin, input );
		if ( input == "qq" ) break;
		ErrorLog e;
		Scanner s(input, &e);
		vector<Token> tokens = s.scanTokens();
		for ( auto &i : tokens ) {
			string out = i.toString();
			cout << out << endl;
		}
		cout << e.toString() << endl;
	}

	return 0;
}
