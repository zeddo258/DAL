#include <iostream>
#include <string>
using namespace std;

struct point {
	string str;
	int level;
	point * next;
};

int Erro2( string infix) {
	int open = 0;
	int close = 0;
	for ( int i = 0 ; i < infix.length() ; i++) {
		if ( infix[i] =='(')open++;
		else if ( infix[i] == ')') close++;
	}
	return (open - close);
}

bool Isnum ( char ch) {
	int i = ch -48;
	if ( i >9 || i < 0) return false;
	else return true;
}

bool Isoperator ( char ch){
	if ( (ch =='-' ||  ch =='/') ||(ch - 40 >= 0 && ch-40 <= 3)) return true;
	return false;
}

bool ReadString(string infix,char &w)
{
	for ( int i = 0 ; i < infix.length() ; i++ ) {
		if ( infix[i]-48 <0 || infix[i] -48 > 9) {
			if ( !Isnum(infix[i])) {
				if ( !Isoperator(infix[i])){	
						if ( infix[i] !=' '){
							w = infix[i];
							return false;
						}
					
				}	 
			}
		}
	}
	return true;
}

bool Error3 ( string infix){
	for ( int i = 0 ; i < infix.length() ; i++){
		if ( Isoperator(infix[i])){
			if ( i == 0) {
				if ( infix[i] != '(') return false;
				else {
					int n = 1;
					while ( infix[i+n] == ' ' ) n++;
					if ( Isoperator(infix[i+n])) {
						if ( infix[i+n] != '(') return false;
					}
				}
			}
			else if ( i+1 == infix.length()){
				if ( infix[i] != ')')return false;
			} 
			else {
				int n =1;
				int m = 1;
				while ( infix[i-n] == ' ') n++;
				while ( infix[i+m] == ' ') m++;
				if ( infix[i] == '(') {
					if ( Isnum(infix[i-n]) || infix[i-n] == ')') return false;
					if ( Isoperator(infix[i+m]) && infix[i+m] != '('){
						cout << endl << infix[i+n];
						return false;
					}
				}
				else if ( infix[i] == ')'){
					 if ( Isoperator(infix[i-n]) && infix[i-n] != ')')return false;
					 if ( Isnum(infix[i+m]) || infix[i+m] == '(') return false;
				}
				else {
					if ( Isoperator(infix[i+n])){
						if ( infix[i+m] != '(' && infix[i+m] != ')')return false;
					}
					if ( Isoperator(infix[i-n])){
						if ( infix[i-n] != '(' && infix[i-n] != ')')return false;
					}
				}
			}
				
			
		}
	}
	return true;
}
void P(point*&head,point*temp, point*pr){
	if ( head != NULL) {
		if ( Isnum(head ->str[0])){	
			cout <<head->str << ", ";
			P(head->next,temp,pr);
		}
		else if ( head->str[0]== '(' ){
			if ( temp == NULL ) temp = pr;
			else {
				pr->next = temp;
				temp = pr;
			}
			P(head->next,temp,NULL);
		}
		else if ( head->str[0]== ')') {
			if ( pr!= NULL){
				cout << pr->str << ", ";
				if ( temp->next != NULL)P(head->next,temp->next,temp);
				else cout<<temp->str;
			}
		} 
		else if ( head->str[0]!= '(' && head->str[0] != ')') {
			if ( pr == NULL) {
				pr = new point;
				pr->str = head->str;
				pr->level = head->level;
				pr->next = NULL;
			}
			else {
				if ( pr->level >= head->level){
					cout << pr->str << ", ";

				pr->str = head->str;
				pr->level = head->level;
				pr->next = NULL;
				}
				else {
					cout << head->next->str << ", ";
					cout << head->str << ", "; 
					head = head->next;
				}
			}
			P(head->next,temp,pr);
		}
	}
	else {
		if ( pr != NULL)cout << pr->str;
	}
}

void Trans( string infix) {
	point * postfix = NULL;
	point * tail;
	for ( int i = 0 ; i < infix.length() ; i++ ) {	
	/*
		if ( Isnum(infix[i])) {
			string t;
			while ( Isnum(infix[i]) ) {
				t += infix[i];
				i++;
			}
			point * temp = new point;
			temp->str = t;
			temp->next = postfix;
			postfix = temp;
		}
		if ( Isoperator(infix[i])) {
				point *temp = new point;
				temp->str = infix[i];
				temp->next = postfix;
				postfix = temp;
		}
		*/
		
		if ( Isnum(infix[i])) {
			string t;
			while ( Isnum(infix[i]) ) {
				t += infix[i];
				i++;
			}
			if ( postfix == NULL ) {
				postfix = new point;
				postfix->str = t;
				postfix->next = NULL;
				tail = postfix;
			}
			else{
			point *temp = new point;
			temp->str = t;
			temp->next = NULL;
			tail->next =temp ;
			tail = temp;
			}
		}
		if ( Isoperator(infix[i])) {
			if ( postfix == NULL ) {
				postfix = new point;
				postfix->str = infix[i];
				if (infix[i] == '+'|| infix[i] == '-' ) postfix->level = 1;
				if (infix[i] == '*'|| infix[i] == '/' ) postfix->level = 2;
				if (infix[i] == '('|| infix[i] == ')' ) postfix->level = 0;
				postfix->next = NULL;
				tail = postfix;
			}
			else{
			point *temp = new point;
			temp->str = infix[i];
			if (infix[i] == '+'|| infix[i] == '-' ) temp->level = 1;
			if (infix[i] == '*'|| infix[i] == '/' ) temp->level = 2;
			if (infix[i] == '('|| infix[i] == ')' ) temp->level = 0;
			temp->next = NULL;
			tail->next =temp ;
			tail = temp;
			}
	}
		
	}
	point * head = postfix;
	cout << endl<< "Postfix expression: ";
	P(head,NULL,NULL);

	
	
}

int main()
{
     int cmd = 0;
     do
     {
          cout << endl
               << "*Aruthmetic Expression Evaluator *";
          cout << endl
               << "*0.QUIT                          *";
          cout << endl
               << "*1.Infix2postfix Transformation  *";
          cout << endl
               << "**********************************";
          cout << endl
               << "Input a choice(0, 1): ";
          cin >> cmd;
          if (cmd == 0)
               break;
		else
          {
          		cout << endl << "Input an infix expression: ";
          		cin.ignore(100,'\n');
                string a;
                getline(cin,a);
                char wrongcase;
                if (!ReadString(a,wrongcase) ) cout << endl << "Error 1: "<< wrongcase << " is not a legitimate character.";
                else {
                	if ( Erro2(a) >0) cout << endl << "Error 2: there is one extra open parenthesis.";
                	else if ( Erro2(a)<0) cout << endl << "Error 2: there is one extra close parenthesis.";
                	else {
                		if ( !Error3(a)) cout << endl << "Error 3: there is one extra operand."; 
                		else {
							cout << endl << "It is a legitimate infix expression.";
							Trans(a); 
						}
					}
				}
			}
                point * ptr = new point;

               
            
     } while (true);
}
