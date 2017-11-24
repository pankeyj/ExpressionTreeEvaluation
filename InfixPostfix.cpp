#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

class InfixPostfix 
{
	public:
		char * convert(char *result);
		InfixPostfix();
		~InfixPostfix();
	private:
		int inputPrecedence(string s);
		int isOperator(string s);
};
InfixPostfix::InfixPostfix()
{

}

InfixPostfix::~InfixPostfix()
{

}
int InfixPostfix::isOperator(string s)
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

int InfixPostfix::inputPrecedence(string s)
{
	int val = 0;

	
}

int main()
{
	InfixPostfix test;
	printf("%d\n", test.isOperator("+"));
}
