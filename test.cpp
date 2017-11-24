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
		InfixPrefix();
		~InfixPrefix();
		string convert(char * s);
	private:
		int isOperator(string s);
		int precedence(string s);
};
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
			while(!opStack.empty() && precedence(opStack.top()) <= precedence(toks[i]))
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
	for(string token; getline(buf2, token, ' '); ){
		cout<< token + " " << endl;	
		backwards.push_back(token);
	}
	//for(int i = backwards.size()-1; i >=0; i--)
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
struct node
{
	bool filled = false;
	string val;
	node *left;
	node *right;
};
class Tree{
	public:
		Tree(string &s);
		~Tree();
		void insert(string &val);
		void destroy_tree(node *leaf);
	private:
		void print(node *root);
		int isOperator(string &s);
		void insert(string& val, node*leaf);
		void destroy(node *leaf);
		node *search(int key, node *leaf);
		node *root;
		vector<string> ops;
	};
	Tree::Tree(string &s)
	{
		string expr = s;
		root = NULL;
		istringstream buf(expr);
		for(string token; getline(buf, token, ' ');)
			ops.push_back(token);

		for(unsigned int i = 0; i < ops.size(); i++)
			insert(ops[i+1]);
	
	}
	
	Tree::~Tree()
	{
		destroy_tree(root);
	}
	void Tree::insert(string& val)
	{
		if(root == NULL)
		{
			root = new node;
			root->val = val;
			root->right = NULL;
			root->left = NULL;
		}
		else
		{
			insert(val, root);
		}
	}
	void Tree::insert(string& val, node *leaf)
	{
		cout << "Value of current node" + leaf->val << endl;
		// If current node has no left child insert next token  as left child
		if(leaf->left == NULL){
			cout << val + " inserted as left child of " + leaf->val << endl;
			leaf->left = new node;
			leaf->left->val = val;
			leaf->left->left = NULL;
			leaf->left->right = NULL;
		// If left child is operator travel to this node
		}else if(isOperator(leaf->left->val)){
			insert(val, leaf->left);
		// If current node has no right child insert next token as right child
		}else if(leaf->right == NULL){
			cout << val + " inserted as right child of " + leaf->val << endl;
			leaf->right = new node;
			leaf->right->val = val;
			leaf->right->right = NULL;
			leaf->right->left = NULL;
		}else if(isOperator(leaf->right->val)){
			insert(val,leaf->right);
		}

	}
	void Tree::destroy_tree(node *leaf)
	{
		if(leaf != NULL)
		{
			destroy_tree(leaf->left);
			destroy_tree(leaf->right);
			delete leaf;
		}
	}
	int Tree::isOperator(string& s)
	{
		cout << " checking if" + s + "is an operator" << endl;
		if(s.compare("+") == 0)
			return true;
		else if(s.compare("-") == 0)
			return true;
		else if(s.compare("*") == 0)
			return true;
		else if(s.compare("/") == 0)
			return true;
		cout << " This is not an operator " << endl;
		return false;
	}
	float evaluate (const char* expr, bool immediate_result)
	{
		string s;
		InfixPrefix beeKool;
		s = beeKool.convert((char*)expr);	
		Tree tree(s);
		cout << s << endl;	
		return 0.0;
	}
	int main()
	{
		 printf ("Test 1 %f\n", evaluate ("2.0 * 3.0 + 4 / 5", true));
		 /*
 		InfixPrefix test;
 		test.convert((char*)"2.0 * 3.0");
		test.convert((char*)"2.0 + 3.0 * 4.0");
		test.convert((char*)"2.0 * 3.0 + 4.0");
		test.convert((char*)"2.0 * 3.0 + 4.0 / 5.0");
		*/
		return 0;
	}

