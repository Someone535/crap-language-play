#ifndef __CRAPPARSER_H
#define __CRAPPARSER_H

#include <string>
#include "crapTokens.h"

class Expr {

	template <class R>
	class Visitor {
		virtual R visitBinary( Binary b ) = 0;
	};

	virtual void accept( Visitor visitor) = 0;

	class Binary : public Expr {
		Expr left;
		Token op;
		Expr right;

		Binary( Expr left, Token op, Expr right ) : left(left), op(op), right(right) {}
		void accept( Visitor visitor ) { visitor.visitBinary(this); }
	};
};

#endif
