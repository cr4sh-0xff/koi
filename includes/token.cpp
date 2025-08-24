#include "token.h"

//std::vector<Token> token;


void Token_stream::putback(Token t)
{
	if (Token_stream::full)
	{
		std::cout << "[+]Buffer is full";
	}
	Token_stream::buffer = t;
	Token_stream::full = true;
}

Token Token_stream::get()
{
	if (Token_stream::full)
	{
		Token_stream::full = false;
		return Token_stream::buffer;
	}
	char ch;
	std::cin >> ch;
	if (isdigit(ch) || ch == '.')
		std::cin.putback(ch);
	switch (ch)
	{
	case 'q': case '(': case ')': case '+': case '-': case '*': case '/':
		return Token{ ch };
	case '.': case '0': case '1': case '2': case '3': case '4': case '5':
	case '6': case '7': case '8': case '9':
		std::cin.putback(ch);
		double val;
		std::cin >> val;
		return Token{ '8', val };
	default:
		std::cout << "[+]Bad lexeme";
	}
}

Token_stream ts;

double expression()
{
	double left = term();
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case '+':
			left += term();
			t = ts.get();
			break;
		case '-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

double term()
{
	double left = primary();
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0)
			{
				std::cout << "[+]Division by zero";
			}
			left /= d;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

/*double primary()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')')
		{
			throw std::runtime_error("[+]Required ')'");
		}
		return d;
	}
	case '8':
		return t.value;
	default:
		throw std::runtime_error("[+]Primary expression required");
	}
}*/

double primary()
{
	Token t = ts.get();
	double d;
	if (t.kind == '(')
	{
		d = expression();
		t = ts.get();
		if (t.kind != ')')
		{
			throw std::runtime_error("[+]Required ')'");
		}
		return d;
	}
	if (t.kind == '8')
	{
		return t.value;
	}
	
}

