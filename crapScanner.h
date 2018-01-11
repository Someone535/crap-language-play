#ifndef __CRAPSCANNER_H
#define __CRAPSCANNER_H

#include <string>
#include <vector>
#include "crapTokens.h"
#include "crapErrors.h"

using namespace std;

class Scanner {
	string source;
	vector<Token> tokens;
	int start = 0;
	int current = 0;
	int line = 1;
	ErrorLog* e;

	bool isAtEnd() { return current >= source.length(); }
	char advance() { 
		current++; 
		return source.at( current - 1 ); 
	}
	char peek() { if ( isAtEnd() ) return '\0'; return source.at( current ); }
	char peek_twice() { 
		if ( current + 1 >= source.length() ) return '\0';
		return source.at( current + 1 ); 
	}
	tokenType match( char m, tokenType ifMatch, tokenType ifNMatch ) { 
		if ( isAtEnd() ) { return ifNMatch; }
		if ( m != peek() ) { return ifNMatch; }
		current++;
		return ifMatch;
	}
	void addToken( tokenType type ) {
		addToken( type, "" );
	}
	void addToken( tokenType type, string literal ) {
		string text = source.substr( start, current - start );
		tokens.push_back( Token( type, text, literal, line, start ) );
	}
	void scanToken() {
		char c = advance();

		switch (c) {
			case '(': addToken(LEFT_PAREN); break;
			case ')': addToken(RIGHT_PAREN); break;
			case '{': addToken(LEFT_BRACE); break;
			case '}': addToken(RIGHT_BRACE); break;
			case ',': addToken(COMMA); break;
			case '.': addToken(DOT); break;
			case ';': addToken(SEMICOLON); break;
			case '*': addToken(STAR); break;
			case '%': addToken(PERCENT); break;
			case '[': addToken(LEFT_SQUARE); break;
			case ']': addToken(RIGHT_SQUARE); break;

			case '!': addToken( match( '=', BANG_EQUAL, BANG ) ); break;
			case '=': addToken( match( '=', EQUAL_EQUAL, EQUAL ) ); break;
			case '>': addToken( match( '=', GREATER_EQUAL, GREATER ) ); break;
			case '<': addToken( match( '=', LESS_EQUAL, LESS ) ); break;
			case '+': addToken( match( '+', PLUS_PLUS, PLUS ) ); break;
			case '-': addToken( match( '-', MINUS_MINUS, MINUS ) ); break;

			case '/': 
				  if ( peek() == '/' ) {
					  while ( peek() != '\n' && !isAtEnd() ) { advance(); }
				  } else {
					  addToken(SLASH);
				  }
				  break;

			case '\n': line++; 
			case ' ':
			case '\r':
			case '\t':
				  break;

			case '"': {
				   while ( peek() != '"' && !isAtEnd() ) {
					   if ( peek() == '\n' ) line++;
					   advance();
				   }
				   if ( !isAtEnd() ) advance();
				   string value = source.substr( start + 1, current - start - 2 );
				   addToken( STRING, value );
				   break; }

			default:
				   if ( isdigit(c) ) {
					   while ( isdigit( peek() ) ) advance();
					   if ( peek() == '.' && isdigit( peek_twice() ) ) {
						advance();
						while ( isdigit( peek() ) ) advance();
					   }
					   addToken(NUMBER);
					   break;
				   }

				   if ( isalpha(c) || c == '_' ) {
					   while ( isalnum( peek() ) || peek() == '_' ) advance();
					   string id = source.substr( start, current - start );
					   if ( id == "if" ) addToken(IF);
					   else if ( id == "else" ) addToken(ELSE);
					   else if ( id == "end" ) addToken(END);
					   else if ( id == "true" ) addToken(TRUE);
					   else if ( id == "false" ) addToken(FALSE);
					   else if ( id == "nill" ) addToken(NILL);
					   else if ( id == "and" ) addToken(AND);
					   else if ( id == "or" ) addToken(OR);
					   else if ( id == "not" ) addToken(NOT);
					   else if ( id == "return" ) addToken(RETURN);
					   else if ( id == "this" ) addToken(THIS);
					   else addToken(IDENTIFIER);
					   break;
				   }
					
				   string unknown_text = source.substr(start, current - start);
				   string message = "Ignoring unknown character.";
				   e->logError( Token( NILL, unknown_text, unknown_text, line, start ), 
						   message, false);

		}

		start = current;
	}

	public:
		Scanner(string source, ErrorLog* e) { this->source = source; this->e = e; }
		vector<Token> scanTokens() {
			while( !isAtEnd() ) {
				scanToken();
			}
			addToken( END_OF_FILE );
			return tokens;
		}
};

#endif
