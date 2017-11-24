#ifndef InfixPrefix_h
#define InfixPrefix_h
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stack>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

class InfixPrefix
{
	public:
		float evaluate(const char* expr, bool immediate);
		InfixPrefix();
		~InfixPrefix();
		string convert(char * s);
	private:
		int isOperator(string s);
		int precedence(string s);
};
#endif
