#include <string>  // string class 
#include <cstdlib>  // system, atoi 
#include <iostream>
#include <new>

#define MAX_LEN 255  // maximum string length

using namespace std;

class expLIST{   
    typedef struct qN   // structure of each node in list
    {   string value;
        struct qN*next;  // next element
    }   listNode;
    listNode*head,*tail;    // only two data members

public:
    expLIST():head(NULL),tail(NULL)     // constructor with initialization
    {}  // end expLIST initializer

    bool isEmpty() const
    {
        return head == NULL;
    }   // end expLIST::isEmpty

	void ins( const string inValue ){		// appppend one into list
		try{ 
			listNode *temp = new listNode;
        	temp->value = inValue;
        	temp->next = NULL;
        	
        	if ( head == NULL ) {
            	head = temp;
            	tail = head;
        	} else {
            	tail->next = temp;
            	tail = temp;
        	}
        	
		} // end try
		catch ( std::bad_alloc& ba ){	// unable to allocate space
			std :: cerr << endl << "bad_alloc on stack caught:" << ba.what() << endl;
		}	// end catch
	}	// end expList::ins

    void clearUp(){  // clear up the entire list
    	listNode *temp ;
        while( head != NULL ){
        	temp = head->next;
        	delete head;
        	head = temp;
		}
    }   // end expLIST::clearUp
    
    void printall(){	// �N�Ҧ��L�X�� 
    	listNode *cur = head;
    	if( cur != NULL ){
    		cout << cur->value;
    		cur = cur->next;
		}
    	while( cur != NULL ){
    		cout << ", " << cur->value;
    		cur = cur->next;
		}
	}
    
    ~expLIST()  // destructor
    {
        clearUp();
    }   // end destructor
};  // end expLIST class 

class expSTACK{ 
    typedef struct sN{
       	char value;
        struct sN*next;
    }   stackNode;
    stackNode *topPtr;

public:
    expSTACK():topPtr(NULL){} //end expSTACK initializer

    bool isEmpty()  const{
       return topPtr == NULL;
    }   //end expSTACK::isEmpty

    void push(const char inValue){   // �N�Ÿ��ǤJstack�� 
		try{
            stackNode* temp = new stackNode;
        	temp->value = inValue;
        	temp->next = topPtr;
        	topPtr = temp;
        } // end try
        catch(std::bad_alloc& ba){
           std::cerr << endl << "bad_alloc on stack caught:"<< ba.what() << endl;
        } //end catch
    } // end expSTACK::push

	char getTop(){	// ���top���� 
        if ( !isEmpty() ) {
            return topPtr->value;
        } 
        
        return '\0';
		
	}

    void pop(){	// �Ntop�R�� 
        if ( !isEmpty() ) {
            stackNode* temp = topPtr;
            topPtr = topPtr->next;
            temp->next = NULL;
            delete temp;
        }
        else {
            return;
        }
    }//end expSTACK::pop without output parameter

    ~expSTACK(){	// �R�����stack 
    	stackNode* temp;
       	while ( topPtr != NULL ){
       		temp = topPtr->next;
       		delete topPtr;
       		topPtr = temp;
		}
            
    }   //end destructor
};    //end expSTACK class 

int priority( char op ){  //���B��l�Ƨ� 
    if( op == '+' || op == '-' )
    	return 1;
    else if( op == '*' || op == '/' )
    	return 2;
    else
        return 0;
} 
void str2list( const string infixS, expLIST & list, expSTACK & stack ){ 	// �N�r��ѪR�����
	char temp;
	string benson;
	string num;
	int nowop, lastop;
	for ( int i = 0; i < infixS.size(); i++ ){
		if( infixS[i] >= '0' && infixS[i] <= '9' ){		//�p�G�O�Ʀr 
			while( infixS[i] >= '0' && infixS[i] <= '9' ){	// �p�G�O�Ʀr�N�i�j�� 
				if( i == infixS.size() ){	// 	�p�Gi�Ȥj��r����״N�����o��function 
					list.ins( num );	
					return;
				} 
				num += infixS[i];	//�O�Ʀr���ܴN�⥦��_�� 
				i++; 
			}
			list.ins( num );	//��Ʀr��i��C 
			num = "";
			i--;
		}

		else{
			if( infixS[i] == '(' ){ 
				stack.push( infixS[i] );
			}
			else if( infixS[i] == '+' || infixS[i] == '-' || infixS[i] == '*' || infixS[i] == '/' ){ //�p�G�O+-*/ 
				if( !stack.isEmpty() ){	//���O�Ū��� 
					nowop = priority( infixS[i] );
					lastop = priority( stack.getTop() );
					if( lastop > nowop ){	// ����u���� �j�󪺸ܴN��̭�����X�� 
						temp = stack.getTop();
						stack.pop();
						benson.push_back( temp ); 
						list.ins( benson );
						stack.push( infixS[i] );
						stack.pop();
					}
					else if ( lastop == nowop ){
						temp = stack.getTop();
						stack.pop();
						benson.push_back( temp ); 
						list.ins( benson );
						stack.push( infixS[i] );
					}
					else{
						stack.push( infixS[i] );
					}
				}
				else{
					stack.push( infixS[i] );
				}	
			}
			
			else if( infixS[i] == ')' ){
				temp = stack.getTop();
				stack.pop();
				while( temp != '(' ){	//Ū��O(���� 
					benson.push_back( temp ); //��benson�qchar�নstring 
					list.ins( benson );
					temp = '\0';
					benson = "";
					temp = stack.getTop();
					stack.pop();
				}
			} 
		} 
		
		temp = '\0';
		benson = "";
	}
	
	while( !stack.isEmpty() ){	//�Nstack�̪��F��Ū���A���F( 
		temp = stack.getTop();
		stack.pop();
		if( temp != '(') { 
			benson.push_back( temp ); //��benson�qchar�নstring 
			list.ins( benson );
		} 
	} 
};

void skipspace( string &infixS ){
	string temp ;
	for( int i = 0; i < infixS.size(); i++ ){  // ���O�ťժ��r���զ�temp 
		if( infixS[i] != ' ' ) { 
			temp += infixS[i];
		}
	}
	infixS = temp;
}
bool isExp( string &infixS ){
	skipspace( infixS );
	if ( infixS[infixS.size()-1] == '+' || infixS[infixS.size()-1] == '-'	  
	   	|| infixS[infixS.size()-1] == '*'	||infixS[infixS.size()-1] == '/' ){		// �p�G�̫�@��+-*/�N�O Error 3 �� return false
	   	cout << "Error 3: there is one extra operator." << endl;
	   	return false;
	}
	else if (infixS[0] == '+' || infixS[0] == '-' || infixS[0] == '*' ||infixS[0] == '/' ){ 	// �p�G�Ĥ@��+-*/�N�O Error 3 �� return false 
		cout << "Error 3: there is one extra operator." << endl;
	   	return false;
	}
	
    for( int i = 0; i < infixS.size(); i++ ){ 	//�u�n���O�Ʀr�B+-*/()�N�O Error 1�� return false 
        if( infixS[i] != '0' && infixS[i] != '1' && infixS[i] != '2' && infixS[i] != '3'
         && infixS[i] != '4' && infixS[i] != '5' && infixS[i] != '6' && infixS[i] != '7'
         && infixS[i] != '8' && infixS[i] != '9' && infixS[i] != '(' && infixS[i] != ')' 
       	 && infixS[i] != '+' && infixS[i] != '-' && infixS[i] != '*' && infixS[i] != '/' ){
       	 	cout << "Error 1:" << infixS[i] << "is not legitimate character." << endl;
            return false;
        }
    }

    return true;	// �X�k return true 
};  
bool isBalanced( const string infixS ){
    int a = 0, b = 0;
    for( int i = 0; i < infixS.size(); i++ ){
        if( infixS[i] == '(' )	// �p��(���ƶq 
            a++;
        else if( infixS[i] == ')' )	//�p��)���ƶq 
            b++;
        if( a < b ){	// �u�n)���ƶq�@��)�h�N�OError 2��return false 
            cout << "Error 2: there is one extra close parenthesis." << endl;
            return false;
        }
    }
    if( a == b ){	// 	(�M )���ƶq�۵��B�ƧǬO�X�z���Nreturn true 
        return true;
    }
    else if( a > b ){	// (���ƶq��)�h�N�OError 2��return false 
        cout << "Error 2: there is one extra open parenthesis." << endl;
        return false;
    }

    return true;
};
bool isLegal(const string infixS ){
    for( int i = 0; i < infixS.size(); i++ ) {
    	
    	if( infixS[i] == '(' ){
			if( infixS[i+1] == '+' || infixS[i+1] == '-' || infixS[i+1] == '*' || infixS[i+1] == '/' || infixS[i+1] == ')' ){
				cout << "Error 3: it is not infix in the parentheses." << endl;
            	return false;
			}
		}
		
    	else if ( infixS[i] == ')' ){
    		if( i == infixS.size() - 1 ) {
    			return true;
			}
       		else if( infixS[i+1] != '+' && infixS[i+1] != '-' && infixS[i+1] != '*' && infixS[i+1] != '/' && infixS[i+1] != ')' ){
            	cout << "Error 3: there is one extra operand." << endl;
            	return false;
            } 
		}
		
        else if( infixS[i] == '+' || infixS[i] == '-' || infixS[i] == '*' || infixS[i] == '/' ){ 	// �s����+-*/ 
        	if( infixS[i+1] == '+' || infixS[i+1] == '-' || infixS[i+1] == '*' || infixS[i+1] == '/' ){
            	cout << "Error 3: there is one extra operator." << endl;
            	return false;
            } 
            else if( infixS[i+1] == ')' ) {
            	cout << "Error 3: it is not infix in the parentheses." << endl;
            	return false;
			}
        }
    }
    
    return true;
}; 

int main (void) {
 	int command = 0; // �ϥΪ̩R�O
 	expLIST list;
 	expSTACK stack;
 	do {
  		string infixS;
  		cout << endl << "* Arithmetic Expression Evaluator *";
  		cout << endl << "* 0. QUIT                         ";
  		cout << endl << "* 1. Infix2postfix Transformation  ";
  		cout << endl << "*******************************";
  		cout << endl << "Input a choice(0, 1): ";
 		cin >> command;  // �o��@�өR�O
  		cin.ignore (MAX_LEN, '\n');  
  		switch (command) {
   			case 0: break;
   			case 1: cout << endl << "Input an infix expression: ";
   			getline (cin, infixS); 
   
   			if ( isExp(infixS) && isBalanced (infixS) && isLegal(infixS)) {
    			cout << "It is legitimate character." << endl;
    			str2list( infixS, list, stack ); // �N�r��ѪR�����
    		} // if 
    		list.printall();
   			stack.~expSTACK();
 			list.~expLIST();
   			break;
   
   			default: cout << endl << "Command does not exist!" << endl;
  		} // switch()  
   
 	} while (command != 0);
  
 	system ("pause");  // �Ȱ����
 	return 0;
 
} // main
