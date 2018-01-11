#ifndef __CRAPERRORS_H
#define __CRAPERRORS_H

#include <string>
#include <vector>
#include "crapTokens.h"

using namespace std;

class ErrorLogEntry {
	Token token;
	string message;
	bool critical_flag;

	public:
		ErrorLogEntry( Token t, string m, bool crit ) {
			token = t;
			message = m;
			critical_flag = crit;
		}
		string toString() {
			string error_type;
			if ( critical_flag ) error_type = "---CRITICAL ERROR---\n";
			else error_type = "---WARNING---\n";
			return error_type + token.lexeme + " Line: " + to_string(token.line) + ", Character: " + 
				to_string(token.first_char) + " --> " + message + "\n";
		}
};

class ErrorLog {
	vector<ErrorLogEntry> log;
	bool critical_flag = false;
	int num_crit_errors = 0;
	int num_warnings = 0;
	public:
		void logError( Token t, string message, bool crit ) {
			if ( crit ) {
				critical_flag = true;
				num_crit_errors++;
			} else num_warnings++;
			log.push_back( ErrorLogEntry( t, message, crit ) );
		}
		bool isCritical() { return critical_flag; }
		string toString() {
			string out;
			for ( auto &i : log ) {
				out += i.toString();
			}
			return out + "-- Warnings: " + to_string(num_warnings) +
				" -- Errors: " + to_string(num_crit_errors) + " --\n";
		}
};

#endif
