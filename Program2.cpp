/****************************************
 * Author: Jacob Pankey
 * Program: Parallel Expression Evaluation
 * Professor: Dulimarta
 * Course: CS452
 * *************************************/
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stack>
#include <vector>
#include <sstream>
#include <iterator>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
using namespace std;

/*****************************************
 * The purpose of this class is to parse
 * an infix arithmetic expression and
 * convert the expression to prefix format
 * **************************************/
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
/****************************************
 * Convert is the main function used to
 * transform the infix expression.
 * Tokenizes input expression. Next,
 * iterate the tokens backwards.When
 * an operator is encountered, pop stack
 * until current token has higher precedence
 * than stack token. Empty stack at the
 * end then reverse the expression
 ***************************************/
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
			while(!opStack.empty() && precedence(opStack.top()) > precedence(toks[i]))
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
/**********************************************
 * Helper function accepts string as arg.
 * Returns true if the string represents an
 * operator.
 * *******************************************/
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
/******************************************
 * Helper function returns precedence of
 * the operator passed in string s.
 * ***************************************/
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
/*****************************************
 * Struct node used to construct a binary
 * expression tree using the prefix expr
 * **************************************/
struct node
{
	string val;
	node *left;
	node *right;
};

class Tree{
	public:
		Tree(string &s);
		~Tree();
		void insert(string &val);
		float calculate();
		void destroy_tree(node *leaf);
		void sigHandler(int);
		void sigHandlerU1(int);
	private:
		void destroy_Tree();	
		float operate(string &op, float val1, float val2);
		float calculate(node *root);
		node * buildTree(vector<string> expr);
		void traverse(node* root);
		void print(node *root);
		int isOperator(string &s);
		void insert(string& val, node*leaf);
		void destroy(node *leaf);
		node *search(int key, node *leaf);
		// Root of the expression tree
		node *root;
		// Vector of strings representing prefix toks
		vector<string> ops;
	};
	/******************************************
 	* Constructor tokenized prefix expression
 	* and passes the tokens to buildTree and
 	* constructs the tree
 	*******************************************/
	Tree::Tree(string &s)
	{
		string expr = s;
		root = NULL;
		istringstream buf(expr);
		for(string token; getline(buf, token, ' ');)
			ops.push_back(token);
		root = buildTree(ops);
	}
	
	Tree::~Tree()
	{
		destroy_Tree();
	}
	void Tree::destroy_Tree()
	{
		destroy_tree(root);
	}
	/******************************************
 	* Helper function used for testing
	******************************************/
	void Tree::traverse(node *root)
	{	
		if ( root ) 
		{
			traverse(root->left);
			cout << root->val << endl;
	       		traverse(root->right);                   
		}	
		
	}
	/******************************************
 	* Accepts a vector of strings representing
 	* prefix expression. Returns a pointer to
 	* root node of the expression tree
 	* ****************************************/ 
	node* Tree::buildTree(vector<string> expr){
		stack<node*> st;
		node *n1, *n2, *n3;
		int i;
		for(i = expr.size()-1; i != 0; i--)
		{
			if(!isOperator(expr[i])){
				n1 = new node;
				n1->val = expr[i];
				n1->left = NULL;
				n1->right = NULL;
				st.push(n1);
			}
			else
			{
				n1 = new node;
				n1->val = expr[i];
				n2 = st.top();
				st.pop();
				n3 = st.top();
				st.pop();
				n1->left = n2;
				n1->right = n3;
				st.push(n1);
			}	
		}
		n1 = st.top();
		return n1;
	}
	/***************************************
 	* Memory cleanup. Deletes tree
 	* *************************************/
	void Tree::destroy_tree(node *leaf)
	{
		if(leaf){
			destroy_tree(leaf->left);
			destroy_tree(leaf->right);
			cout << "Deleting Node: " << leaf->val << endl;
		 	delete(leaf);
		}
		
	}
	/***************************************
 	* Accepts a string arg. Returns true if
 	* string represents an operator
 	***************************************/
	int Tree::isOperator(string& s)
	{
		if(s.compare("+") == 0)
			return true;
		else if(s.compare("-") == 0)
			return true;
		else if(s.compare("*") == 0)
			return true;
		else if(s.compare("/") == 0)
			return true;
		return false;
	}
	/*************************************
 	* This function forks a single time to
 	* evaluate the operator at the root of
 	* the expression tree.
 	* ***********************************/
	float Tree::calculate(){


		pid_t pid;
		float temp, result;
		int pvc[2], status;
		if((pipe(pvc)) == -1)
			perror("Bad Pipe");
		if((pid = fork()) < 0)
			perror("Bad Fork");
		if(pid == 0)
		{
			cout << "Root Process " << getpid() << " is Calculating " << root->val << endl;
			close(pvc[0]);
			temp = calculate(root);
			cout << "Root Process: " << getpid() << " returning " <<  temp << endl;
			write(pvc[1], &temp, sizeof(float));
			close(pvc[1]);
		//	sleep(5);
			exit(0);
		}else{
			close(pvc[1]);
			waitpid(pid, &status, 0);
			read(pvc[0], &result, sizeof(float));
			close(pvc[0]);
		}
		return result;
	}
	/***********************************
 	* This recursive function call forks
 	* every time a child node is an operator
 	* and then calculates the value of
 	* that subtree
 	* *********************************/
	float Tree::calculate(node *root)
	{
		int pvcL[2],pvcR[2], status;
		string::size_type sz;
		string op;
		float rightVal, leftVal, result, temp;
		pid_t pidL, pidR;
		
		// If both children are operancds:
		// fork to calculate
		if(isOperator(root->left->val))
		{
			if(pipe(pvcL) == -1)
				perror("BAD PIPE!!!!");

			// Left child is an operator requires a fork
			pidL = fork();

			if(pidL < 0 )
				perror("Bad Fork");

			//Left child fork
			if(pidL == 0)
			{
				cout << "Child Process: " << getpid() << " computing " << root->left->val << endl;
				close(pvcL[0]);	// Child does not read
				temp = calculate(root->left);
				cout << "Child Process: " << getpid() << " returning result " << temp << endl;
				write(pvcL[1],&temp, sizeof(float));
				close(pvcL[1]);
		//		sleep(5);
				exit(0);				
			}
			else
			{
				close(pvcL[1]); // Parent does not write
				waitpid(pidL,&status, 0);
				read(pvcL[0], &leftVal, sizeof(float));
				close(pvcL[0]);
			}

		}else{
			leftVal = stof(root->left->val, &sz);	
		}

		if(isOperator(root->right->val))
		{

			if(pipe(pvcR) == -1)
				perror("BAD PIPE!!!");
			
			// Right child is an operator requires a fork
			pidR = fork();
			
			if(pidR < 0)
				perror("BAD FORK !!!");
			
			// Right child forked
			if(pidR == 0)
			{
				cout << "Child Process: " << getpid() << " computing " << root->right->val << endl;
				close(pvcR[0]);  // Child does not read
				temp = calculate(root->right);
				cout << "Child Process: " << getpid() << " returning result " << temp << endl;
				write(pvcR[1],&temp, sizeof(float));
				close(pvcR[1]);
		//		sleep(5);
				exit(0);
			}else{
				close(pvcR[1]);  //Parent does not write
				waitpid(pidR, &status, 0);
				read(pvcR[0], &rightVal, sizeof(float));
				close(pvcR[0]);
			}
		}else{
			rightVal = stof(root->right->val, &sz);
		}
	
		op = root->val;	
		result = operate(op, leftVal, rightVal);
		return result;
	}
	/******************************************
 	* Helper function to calculate. Performs
 	* the correct arithmetic calculation and
 	* returns the result
 	******************************************/
	float Tree::operate(string & op, float val1, float val2)
	{
		
		if(op.compare("+") == 0)
			return val1 + val2;
		else if(op.compare("-") == 0)
			return (val1 - val2);
		else if(op.compare("*") == 0)
			return val1 * val2;
		else if(op.compare("/") == 0)
			return val1 / val2;
		perror("Bad Operator Comarison");

		return 0.0;
	}
	float evaluate (const char* expr, bool immediate_result)
	{
		string s;
		InfixPrefix beeKool;
		float result;
		s = beeKool.convert((char*)expr);	
		Tree tree(s);
		result = tree.calculate();
		//tree.~Tree();
		return result;
	}
	int main()
	{
	
		// 1 operator 
		 printf("Test  1 ===> %7.3f\n", evaluate("17.0 - 16.0", true));
		 printf("Test  2 ===> %7.3f\n", evaluate("10.0 - 8.0", true));
		 printf("Test  3 ===> %7.3f\n", evaluate("18.0 - 15.0", true));
		/*
		 printf("Test  4 ===> %7.3f\n", evaluate("15.0 - 11.0", true));
		 printf("Test  5 ===> %7.3f\n", evaluate("11.0 - 6.0", true));
		 printf("Test  6 ===> %7.3f\n", evaluate("3.0 + 3.0", true));
		 printf("Test  7 ===> %7.3f\n", evaluate("7.0 + 0.0", true));
		 printf("Test  8 ===> %7.3f\n", evaluate("11.0 - 3.0", true));
		 printf("Test  9 ===> %7.3f\n", evaluate("4.0 + 5.0", true));
		 printf("Test 10 ===> %7.3f\n", evaluate("15.0 - 5.0", true));
		 // 2 operators 
		 printf("Test 11 ===> %7.3f\n", evaluate("75.8 / 14.0 + 5.58571428571", true));
		 printf("Test 12 ===> %7.3f\n", evaluate("57.6 - 6.0 - 39.6", true));
		 printf("Test 13 ===> %7.3f\n", evaluate("14.0 * 1.0 - 1.0", true));
		 printf("Test 14 ===> %7.3f\n", evaluate("163.3 / 4.0 - 26.825", true));
		 printf("Test 15 ===> %7.3f\n", evaluate("48.9 / 15.0 + 11.74", true));
		 printf("Test 16 ===> %7.3f\n", evaluate("106.7 / 14.0 + 8.37857142857", true));
		 printf("Test 17 ===> %7.3f\n", evaluate("40.6 + 20.0 - 43.6", true));
		 printf("Test 18 ===> %7.3f\n", evaluate("136.4 + 1.0 - 119.4", true));
		 printf("Test 19 ===> %7.3f\n", evaluate("176.3 - 7.0 - 150.3", true));
		 printf("Test 20 ===> %7.3f\n", evaluate("124.7 + 9.0 - 113.7", true));
		 // 3 operators 
		 printf("Test 21 ===> %7.3f\n", evaluate("137.5 - 124.3 + 10.0 - 2.2", true));
		 printf("Test 22 ===> %7.3f\n", evaluate("137.7 / 84.9 * 9.0 + 7.40282685512", true));
		 printf("Test 23 ===> %7.3f\n", evaluate("6.6 + 75.5 / 14.0 + 11.0071428571", true));
		 printf("Test 24 ===> %7.3f\n", evaluate("62.5 * 48.2 + 13.0 - 3001.5", true));
		 printf("Test 25 ===> %7.3f\n", evaluate("70.6 * 21.6 / 18.0 - 59.72", true));
		 printf("Test 26 ===> %7.3f\n", evaluate("148.5 + 6.5 * 7.0 - 168.0", true));
		 printf("Test 27 ===> %7.3f\n", evaluate("37.2 - 167.5 - 17.0 + 174.3", true));
		 printf("Test 28 ===> %7.3f\n", evaluate("143.3 + 115.0 * 7.0 - 920.3", true));
		 printf("Test 29 ===> %7.3f\n", evaluate("158.8 + 154.6 - 15.0 - 269.4", true));
		 printf("Test 30 ===> %7.3f\n", evaluate("151.5 - 48.7 - 10.0 - 62.8", true));
		// // 4 operators 
		 printf("Test 31 ===> %7.3f\n", evaluate("82.5 + 142.4 * 77.3 + 18.0 - 11077.02", true));
		 printf("Test 32 ===> %7.3f\n", evaluate("130.5 - 159.2 / 18.9 / 20.0 - 98.0788359788", true));
		 printf("Test 33 ===> %7.3f\n", evaluate("84.1 / 140.4 - 186.7 * 15.0 + 2832.90099715", true));
		 printf("Test 34 ===> %7.3f\n", evaluate("42.4 / 144.2 * 143.8 / 9.0 + 29.3019571583", true));
		 printf("Test 35 ===> %7.3f\n", evaluate("54.2 * 105.0 - 188.9 - 9.0 - 5458.1", true));
		 printf("Test 36 ===> %7.3f\n", evaluate("33.9 / 128.9 + 187.5 + 16.0 - 167.762994569", true));
		 printf("Test 37 ===> %7.3f\n", evaluate("86.2 * 95.4 * 182.4 - 20.0 - 1499905.752", true));
		 printf("Test 38 ===> %7.3f\n", evaluate("50.1 + 69.9 + 169.5 / 1.0 - 251.5", true));
		 printf("Test 39 ===> %7.3f\n", evaluate("123.7 / 104.6 / 143.9 + 17.0 + 21.9917817903", true));
		 printf("Test 40 ===> %7.3f\n", evaluate("161.3 * 119.5 / 80.7 * 15.0 - 3542.77881041", true));
		 // 5 operators 
		 printf("Test 41 ===> %7.3f\n", evaluate("180.2 / 81.8 - 174.8 - 199.7 + 7.0 + 406.297066015", true));
		 printf("Test 42 ===> %7.3f\n", evaluate("2.9 + 100.1 / 44.7 + 144.1 / 14.0 + 26.5677692554", true));
		 printf("Test 43 ===> %7.3f\n", evaluate("147.6 * 130.1 * 41.4 - 140.1 - 4.0 - 794807.164", true));
		 printf("Test 44 ===> %7.3f\n", evaluate("10.0 / 174.4 + 106.9 * 56.8 * 16.0 - 97106.7773394", true));
		 printf("Test 45 ===> %7.3f\n", evaluate("1.2 - 70.7 / 122.0 - 74.1 / 16.0 + 49.0107581967", true));
		 printf("Test 46 ===> %7.3f\n", evaluate("64.6 + 56.1 + 74.6 - 193.1 * 18.0 + 3326.5", true));
		 printf("Test 47 ===> %7.3f\n", evaluate("41.1 * 87.8 + 101.0 * 122.3 + 18.0 - 15931.88", true));
		 printf("Test 48 ===> %7.3f\n", evaluate("22.4 * 55.2 - 69.1 + 124.9 + 13.0 - 1257.28", true));
		 printf("Test 49 ===> %7.3f\n", evaluate("151.8 - 187.1 * 9.3 * 46.6 / 20.0 + 3951.4699", true));
		 printf("Test 50 ===> %7.3f\n", evaluate("136.2 * 157.3 * 101.8 / 104.0 - 8.0 - 20913.0545", true));
		 // 6 operators 
		 printf("Test 51 ===> %7.3f\n", evaluate("195.3 + 52.6 - 139.3 * 64.3 - 156.1 * 14.0 + 10945.49", true));
		 printf("Test 52 ===> %7.3f\n", evaluate("117.8 / 49.2 + 127.7 / 78.0 * 110.4 / 2.0 - 40.7666166354", true));
		 printf("Test 53 ===> %7.3f\n", evaluate("62.6 * 28.1 - 80.6 * 153.8 - 44.1 * 6.0 + 10954.82", true));
		 printf("Test 54 ===> %7.3f\n", evaluate("198.4 / 129.5 / 57.5 / 48.4 - 185.5 + 4.0 + 235.499449498", true));
		 printf("Test 55 ===> %7.3f\n", evaluate("38.9 * 122.5 * 47.9 / 6.3 - 158.9 - 18.0 - 35999.1277778", true));
		 printf("Test 56 ===> %7.3f\n", evaluate("75.4 / 114.0 / 123.9 / 42.8 / 83.6 / 11.0 + 55.9999998644", true));
		 printf("Test 57 ===> %7.3f\n", evaluate("4.8 * 22.6 - 78.2 - 4.5 / 84.8 + 5.0 + 21.7730660377", true));
		 printf("Test 58 ===> %7.3f\n", evaluate("10.8 / 46.3 - 57.0 * 178.1 + 21.2 * 17.0 + 9849.06673866", true));
		 printf("Test 59 ===> %7.3f\n", evaluate("132.3 / 49.5 / 30.5 / 59.5 + 200.6 + 10.0 - 151.60147278", true));
		 printf("Test 60 ===> %7.3f\n", evaluate("106.9 * 137.5 - 94.5 / 103.4 - 181.0 + 1.0 - 14457.8360735", true));
		 // 7 operators 
		 printf("Test 61 ===> %7.3f\n", evaluate("94.8 * 13.1 / 7.5 - 51.5 * 51.1 - 71.7 - 2.0 + 2600.766", true));
		 printf("Test 62 ===> %7.3f\n", evaluate("20.3 - 115.2 * 3.0 - 84.0 + 171.4 / 23.2 / 6.0 + 470.068678161", true));
		 printf("Test 63 ===> %7.3f\n", evaluate("38.1 + 34.0 - 42.0 * 192.1 / 78.0 / 148.9 + 17.0 - 25.4053159064", true));
		 printf("Test 64 ===> %7.3f\n", evaluate("67.9 * 193.1 + 43.7 - 91.9 - 155.7 - 13.6 * 19.0 - 12585.19", true));
		 printf("Test 65 ===> %7.3f\n", evaluate("35.9 / 168.2 + 149.8 * 95.4 * 5.7 / 10.1 / 3.0 - 2623.60432747", true));
		 printf("Test 66 ===> %7.3f\n", evaluate("28.3 / 31.3 + 115.6 * 20.4 + 145.9 + 68.7 / 6.0 - 2450.49415335", true));
		 printf("Test 67 ===> %7.3f\n", evaluate("91.5 + 11.9 * 177.4 + 143.2 / 164.3 * 170.6 * 5.0 - 2879.01465612", true));
		 printf("Test 68 ===> %7.3f\n", evaluate("177.7 / 198.2 * 34.0 * 122.2 / 153.5 * 41.6 + 8.0 - 949.529121573", true));
		 printf("Test 69 ===> %7.3f\n", evaluate("27.8 - 152.4 + 94.1 + 124.2 * 150.6 + 181.0 + 13.0 - 18799.02", true));
		 printf("Test 70 ===> %7.3f\n", evaluate("151.9 - 194.5 + 59.2 + 46.7 + 112.5 * 176.1 * 3.0 - 59427.05", true));
		 // 8 operators 
		 printf("Test 71 ===> %7.3f\n", evaluate("90.7 / 29.8 / 57.7 / 154.5 + 110.8 - 67.9 * 133.7 - 5.0 + 9043.42965858", true));
		 printf("Test 72 ===> %7.3f\n", evaluate("12.6 - 32.4 / 150.6 / 33.4 * 27.0 - 80.1 - 147.7 - 8.0 + 295.373915118", true));
		 printf("Test 73 ===> %7.3f\n", evaluate("138.6 * 132.5 + 82.8 / 41.3 + 157.9 / 72.0 - 106.8 * 15.0 - 16693.6978982", true));
		 printf("Test 74 ===> %7.3f\n", evaluate("112.3 + 126.3 - 139.2 * 19.6 + 114.6 - 107.9 * 159.6 - 7.0 + 19676.96", true));
		 printf("Test 75 ===> %7.3f\n", evaluate("189.6 * 56.3 + 1.9 / 43.3 * 185.3 * 171.3 * 129.3 * 17.0 - 3072181.74275", true));
		 printf("Test 76 ===> %7.3f\n", evaluate("69.2 - 199.9 / 77.3 + 176.2 + 160.2 * 47.5 + 35.1 - 15.0 - 7796.41397154", true));
		 printf("Test 77 ===> %7.3f\n", evaluate("94.8 - 183.4 + 57.0 / 27.0 - 120.3 - 182.3 + 95.7 * 5.0 - 12.4111111111", true));
		 printf("Test 78 ===> %7.3f\n", evaluate("170.8 + 94.9 + 186.2 + 171.0 + 197.5 - 96.9 / 45.9 / 4.0 - 741.872222222", true));
		 printf("Test 79 ===> %7.3f\n", evaluate("7.5 - 146.4 + 80.4 - 27.0 - 97.2 * 9.8 * 145.3 + 15.0 + 138556.468", true));
		 printf("Test 80 ===> %7.3f\n", evaluate("75.9 * 21.7 * 58.3 * 27.1 + 120.8 / 177.5 / 168.2 + 20.0 - 2602132.11195", true));
		*/
		return 0;
	}

