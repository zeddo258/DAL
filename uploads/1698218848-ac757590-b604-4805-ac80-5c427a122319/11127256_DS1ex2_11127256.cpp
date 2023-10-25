//11127256,¿½¤Ñ»y 
#include<iostream> 	//endl
#include<new>		//new
#include<string>	//string class
#include<cstdlib>	//system,atoi
#define MAX_LEN 255	//maximum string lenth
using namespace std;	//standard naming space
void DeleteWhitespaces(string& );	//delete the whitespaces that are in string
bool isExp(string&);	//check the validty of each symbol
bool isBalanced(const string);	//chaeck the validity of balanced parentheses
bool isLegal(const string);	//check whether it is a legal expression
void infixtopostfix(string);			//ready to start transform infixS into postfixS

class expSTACK
{	typedef struct sN	//structure of each element in stack
	{	char value;
		struct sN	*next;	//next element
	}	stackNode;
	stackNode*topPtr;	//only one data member
public:
	expSTACK():topPtr(NULL)	//constructor with initialization
	{}//end expSTACK initializer
	
	bool isEmpty() const			//decide whether stack is empty
	{	return topPtr == NULL;
	}	//end expSTACK::isEmpty
	
	void push(const char inValue)	//add one element into stack
	{	try
		{	
			stackNode*newptr=new stackNode;
			newptr->value=inValue;
			newptr->next=topPtr;
			topPtr = newptr;
			newptr = NULL;
			delete newptr;
			//???
		}//end try
		catch(std::bad_alloc& ba) //unable to allocate space
		{	std::cerr<<endl<<"bad_alloc on stack caught: "<<ba.what()<<endl;
		} // end catch
	}//end expSTACK::push
	
	void getTop(char& outvalue)	//get the top of stack without removal
	{
		if(!isEmpty()){
			outvalue = topPtr->value;
		}
		//???
	}//end expSTACK::getTop
	
	void pop()	//remove the top of stack
	{
		if(!isEmpty()){
			stackNode*temp = topPtr;
			topPtr = topPtr ->next;
			temp->next=NULL;
			delete temp;
		}
			
		
	}//end expSTACK::pop without output parameter
	
	void pop(char& outvalue)	//get the top of stack and remove it
	{
		if(!isEmpty()){
			outvalue = topPtr->value;
			stackNode*temp=topPtr;
			topPtr = topPtr->next;
			temp->next=NULL;
			delete temp;
		}
		//???
	}//end expSTACK::pop with output parameter
	
	
	~expSTACK()		//destructor
	{	while(!isEmpty()){
			pop();
		}
	}//end destructor
};	//end expSTACK class

void DeleteWhitespaces(string&str){ //delete the whitespaces that are in string
	int length = 0,length_0 = 0;
	length = str.length();
	string noWhitespaces;
	while(length_0<length){
		if(str[length_0]!=' '){
			noWhitespaces = noWhitespaces+str[length_0];
		}
		length_0++;
	}
	str = noWhitespaces;
}//void DeleteWhitespaces(&string)
		
bool isExp(string&str){	//check the validty of each symbol
	int length = 0,length_0 = 0;													//length of string
	length = str.length();
	while(length_0<length){																					//find if there are illegal char in string or not
		if((str[length_0]!='+'&&str[length_0]!='-'&&str[length_0]!='*'
			&&str[length_0]!='/'&&str[length_0]!='('&&str[length_0]!=')')&&(isdigit(str[length_0])==0)){
			cout<<"Error 1: "<<str[length_0]<<" is not a legitimate character."<<endl;
			length = -1;
			break;
		}
		length_0++;
	}
	
	if(length!=-1){																							//if there are not illegal char in string then return true
		return true;
	}
	else{
		return false;
	}
}// bool isExp(string&)

bool isBalanced(const string str){	//chaeck the validity of balanced parentheses
	int length = 0,length_0 = 0;													//string of length
	int open = 0,close = 0;															//count how many open and close parentheses there are
	int rightfirst = 0;																// to find if close is first than open parenthesis or not
	int extra = 0;
	length = str.length();
	
	while(length_0<length){			
		if(rightfirst<0){															//  close cannot first than open parenthesis if their quantity are same
			cout<<"Error 2: there is one extra close parenthesis."<<endl;	
			return false;
		}										
		if(str[length_0]=='('){														//find how many open and close parentheses there are
			rightfirst++;
			open++;
		}
		else if(str[length_0]==')'){
			close++;
			rightfirst--;
		}		
		length_0++;
	}
		
	if(open==close){																//if the open and close parentheses are balanced return true
		return true;
	}
	else if(open>close){															//if open parentheses are more than close parentheses and return false
		extra = open - close;	
		cout<<"Error 2: there is one extra open parenthesis."<<endl;
		/*													
		if(extra == 1){																//count how many open parentheses are more than close parentheses
			cout<<"Error 2: there is one extra open parenthesis."<<endl;
		}
		else{
			cout<<"Error 2: there are "<<extra<<" extra open parentheses."<<endl;
		}*/ 
		return false;
	}
	else if(open<close){															//if close parentheses are more than open parentheses and return false
		extra = close - open;	
		cout<<"Error 2: there is one extra close parenthesis."<<endl;
		/*													
		if(extra == 1){																//count how many close parentheses are more than open parentheses
			cout<<"Error 2: there is one extra close parenthesis."<<endl;
		}
		else{
			cout<<"Error 2: there are "<<extra<<" extra close parentheses."<<endl;
		}
		*/ 
		return false;
	}
}//bool isBalanced(const string)

bool isLegal(const string str){	//check whether it is a legal expression
	int length = 0,length_0 = 0;
	length = str.length();
	if(length==1||length == 0){											//only one operator or no string is error
		if(str =="="||str=="-"||str=="*"||str=="/"){				
			cout<<"Error 3: there is one extra operator."<<endl;
			return false;
		}
		else{
			cout<<"It is a legitimate infix expression."<<endl;
			return true;
		}
	}
	else{																//not only one operator and there is more than one char exist
		while(length_0<length-1){
			if(str[length_0]=='+'||str[length_0]=='-'||str[length_0]=='*'		//if current char is operator then check whether legal or not
			||str[length_0]=='/'||str[length_0]=='('||str[length_0]==')'){
				if(str[length_0]=='('||str[length_0]==')'){
					if( str[length_0]=='(' ){											
						if( str[length_0+1]==')'||str[length_0+1]=='+'								//check it is infix or not like "(+"
						||str[length_0+1]=='-'||str[length_0+1]=='*'||str[length_0+1]=='/' ){
							cout<<"Error 3: it is not infix in the parentheses."<<endl;
							length = -1;
							break;
						}
						if(length_0>0){																//to check if there is extra operand like "19("
							if(str[length_0-1]!='+'&&str[length_0-1]!='-'&&str[length_0-1]!='*'
								&&str[length_0-1]!='/'){
								cout<<"Error 3: there is one extra operand."<<endl; 
								length = -1;
								break;
							}
						}
					}	
					else if( str[length_0]==')' ){
						if( str[length_0+1]=='(' ){													//to check if there is extra operand like ")("
							cout<<"Error 3: there is one extra operand."<<endl; 
							length = -1;
							break;
						}
						if(str[length_0+1]!='+'&&str[length_0+1]!='-'&&str[length_0+1]!='*'			//to check if there is extra operand like ")19"
							&&str[length_0+1]!='/'&&str[length_0+1]!=')'){ 
							cout<<"Error 3: there is one extra operand."<<endl;
							length = -1;
							break;
						}
					}
				}
				else{																				
					if(str[length_0+1]=='+'||str[length_0+1]=='-'||str[length_0+1]=='*'				//to check if there is extra operand like "+-"
						||str[length_0+1]=='/'){
						cout<<"Error 3: there is one extra operator."<<endl;
						length = -1;
						break;
					}
				}
			}
			length_0++;																				//trun to the next char
		} 
		if(length==-1){																				//if there is error
			return false;
		}
		else{																						//if no error
			cout<<"It is a legitimate infix expression."<<endl;
			return true;
		}
	}
}//bool isLegal(const string)

void infixtopostfix(string str){	//ready to start transform infix into postfix
	cout<<"Postfix expression: ";
	int length = 0,length_0 = 0,copy0 = 0;	//length of string and a int of string of the char
	int comma = 0;							//if comma>0 then print','
	char theoperator;						//keep the operator
	expSTACK trans;							//create a new stack
	length = str.length();
	while(length_0<=length){				//change to postfix
		if(length_0==length){				//if all char are all done then print out the rest of operators
			while(!trans.isEmpty()){
				trans.pop(theoperator);
				if(comma>0){
					cout<<",";
				}
				cout<<theoperator;
			}
			break;
		}
		if(isdigit(str[length_0])){			//if the current char is digit
			if(comma>0){
				cout<<",";
			}
			comma++;
			cout<<str[length_0];
			if(length_0+1!=length){			//to check the data whether out of index or not  
				copy0 = length_0+1;	
				while(isdigit(str[copy0])){		//print next char if it is digit
					cout<<str[copy0];
					copy0++;
				}				
				trans.getTop(theoperator);
				if(theoperator=='*'||theoperator=='/'){		//if the top of the stack operator is * or /,then print it and move it out of stack
					trans.pop(theoperator);
					if(comma>0){
						cout<<",";
					}
					cout<<theoperator;
					comma++;
				}
				length_0=copy0-1;						//let the current char to be the last number digit
				copy0=0;								//reset the copy length
			}
		}
		else if(str[length_0]=='('||str[length_0]=='+'||str[length_0]=='-'||	//if the current char is operator
			str[length_0]=='*'||str[length_0]=='/'){
			if(trans.isEmpty()||str[length_0]=='('){							//if stack is empty or the current char is '('
				trans.push(str[length_0]);
			}
			else{
				trans.getTop(theoperator);
				if(theoperator=='+'||theoperator=='-'){							//if the top of the operator is '+' or '-'
					if(str[length_0]=='+'||str[length_0]=='-'){					//if the current char is '+' or '-'
						trans.pop(theoperator);									//move operator out and put the current operator into stack
						trans.push(str[length_0]);								
						if(comma>0){
							cout<<",";
						}
						cout<<theoperator;
						comma++;
					}
					else if(str[length_0]=='*'||str[length_0]=='/'){			//if the current char is '*' or '/'
						trans.push(str[length_0]);								
					}
				}
				else if(theoperator=='*'||theoperator=='/'){					//if the top of the operator is '*' or '/ '
					trans.pop(theoperator);										//move operator out and put the current operator into stack
					trans.push(str[length_0]);									
					if(comma>0){
						cout<<",";
					}
					cout<<theoperator;
					comma++;
				}
				else{															//for example:'('
					trans.push(str[length_0]);									//put current char into stack
				}
			}						
		}
		else if(str[length_0]==')'){											//if current char is ')'
			trans.getTop(theoperator);
			while(theoperator!='('){											//print out the operator in stack until '('
				trans.pop(theoperator);
				if(comma>0){
					cout<<",";
				}
				comma++;
				cout<<theoperator;
				trans.getTop(theoperator);
			}
			trans.pop();														//move out the '('
		}
		length_0++;																//turn to the nxt char
	}	
	cout<<endl;		
	trans.~expSTACK();															//release memory
}//void infixtopostfix(string str)

int main(void)
{	int command = 0;	//user command
	
	do
	{	string	infixS;
		cout<<endl<<"* Arithmetic Expression Evaluator *";
		cout<<endl<<"* 0. QUIT		          *";
		cout<<endl<<"* 1. Infix2postfix Transformation *";
		cout<<endl<<"***********************************";
		cout<<endl<<"Input a choice(0,1):";
		cin>>command;										//get a command
		cin.ignore(MAX_LEN,'\n');							//clear the input buffer
		switch(command)
		{	case 0:break;
			case 1:cout<<endl<<"Input an infix expression: ";
				getline(cin,infixS);
				DeleteWhitespaces(infixS);					//delete whitespaces in string
				if(isExp(infixS)&&							//check each symbol&remove useless ones
					isBalanced(infixS)						//check the validity of balanced parenthesis
					&&isLegal(infixS))						//check whether it is a legal expression
				{
					infixtopostfix(infixS);			//ready to start transform infixS into postfixS
				
				}//end if
				break;
			default: cout<<endl<<"Command does not exist!"<<endl;
		}//end switch
	}while(command!=0);										//'0':stop the program
	system("pause");										//pause the display
	return 0;
}	//end main
