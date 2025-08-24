
#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <vector>

class Token {
public:
	char kind;
	double value;
};

class Token_stream {
public:
	Token get();
	void putback(Token t);
private:
	bool full{ false };
	Token buffer;

};

extern Token_stream  ts;

double expression();
double term();
double primary();

#endif