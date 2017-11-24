#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stack>
#include <vector>
#include <sstream>
#include <iterator>
#include "InfixPrefix.h"
using namespace std;

InfixPrefix::InfixPrefix(){}
InfixPrefix::~InfixPrefix(){}
string InfixPrefix::convert(char *chs)
{
	stack<string> opStack;
	string solution, temp;
	string s = string(chs);
	vector<string> toks;
	istringstream buf(s);
	// Tokenize the input string and place in a vector
	for(string token; getline(buf, token, ' '); )
		toks.push_back(token);
	// Iterate the vector backwards
	for(int i = toks.size()-1; i >= 0; i--)
	{
		//Operator -> Stack: Operand -> Out
		if(isOperator(toks[i])){
			while(!opStack.empty() && precedence(opStack.top()) >= precedence(toks[i]))
			{
				temp = opStack.top();
				opStack.pop();
				solution += " " + temp;
			}
			opStack.push(toks[i]);
		}else{
			solution += " " + toks[i];
		}
	}
	while(!opStack.empty())
	{
		temp = opStack.top();
		opStack.pop();
		solution += " " + temp;
	}
	temp = solution;
	solution = "";
	vector<string> backwards;
	istringstream buf2(temp);
	// Tokenize the input string and place in a vector
	for(string token; getline(buf2, token, ' '); )
		backwards.push_back(token);

	for(int i = backwards.size()-1; i >=0; i--)
		solution += " " + backwards[i];

	return solution;
}

int InfixPrefix::isOperator(string s)
{
	bool isOperator = false;
	if(s.compare("+") == 0){
		isOperator = true;
	}else if(s.compare("-") == 0){
		isOperator = true;
	}else if(s.compare("*") == 0){
		isOperator = true;
	}else if(s.compare("/") == 0){
		isOperator = true;
	}
	return isOperator;
}

int InfixPrefix::precedence(string s)
{
	int input = 0;
	if(s.compare("+") == 0 || s.compare("-") == 0){
		input = 1;
	}else if(s.compare("*") == 0 || s.compare("/") == 0){
		input = 2;
	}
	return input;
}
float InfixPrefix::evaluate (const char* expr, bool immediate_result)
{
	string s;
	InfixPrefix beeKool;
	s = beeKool.convert((char*)expr);	
	cout << s << endl;	
	return 0.0;
}

int main()
{
 printf ("Test 1 %f\n", evaluate ("2.0 + 3.0 * 4 - 5 / 6", true));
/*	InfixPrefix test;
	test.convert((char*)"2.0 * 3.0");
	test.convert((char*)"2.0 + 3.0 * 4.0");
	test.convert((char*)"2.0 * 3.0 + 4.0");
	test.convert((char*)"2.0 * 3.0 + 4.0 / 5.0");
*/
	return 0;
}

