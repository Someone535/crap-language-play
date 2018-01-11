#ifndef __CRAPTOKENS_H
#define __CRAPTOKENS_H

#include <string>
#include <stdlib.h>
#include "enumToString.h"

using namespace std;

DEFINE_ENUM_WITH_STRING_CONVERSIONS( tokenType, 
		(LEFT_PAREN)(RIGHT_PAREN)(LEFT_BRACE)(RIGHT_BRACE)
		(COMMA)(DOT)(SEMICOLON)(SLASH)(STAR)(PERCENT)(LEFT_SQUARE)(RIGHT_SQUARE)

		(BANG)(BANG_EQUAL)(EQUAL)(EQUAL_EQUAL)(GREATER)(GREATER_EQUAL)(LESS)(LESS_EQUAL)
		(PLUS)(PLUS_PLUS)(MINUS)(MINUS_MINUS)

		(IDENTIFIER)(NUMBER)(STRING)

		(IF)(ELSE)(END)(TRUE)(FALSE)(NILL)(AND)(OR)(NOT)(RETURN)(THIS)(END_OF_FILE))

class Literal {
	string s;
	public:
		Literal() : s("") {}
		Literal(string s) { this->s = s; }
		Literal(double d) { s = to_string(d); }
		operator double() { return atof(s.c_str()); }
};

class Token {
	public:
		tokenType type;
		string lexeme;
		Literal lit;
		int line;
		int first_char;

		Token() : type(NILL), lexeme(""), lit(Literal()), line(0), first_char(0) {}
		Token( tokenType type, string lexeme, Literal lit, int line, int first_char ) {
			this->type = type;
			this->lexeme = lexeme;
			this->lit = lit;
			this->line = line;
			this->first_char = first_char;
		}

		string toString() { 
			string out = ToString(type);
			out += " ";
			out += lexeme;
			out += " ";
			out += lit;
			return out; 
		}
};

#endif
