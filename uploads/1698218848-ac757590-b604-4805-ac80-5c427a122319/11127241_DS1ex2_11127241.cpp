// 11127241 ��T�G�A �¨N�s 
//  �ڥ�devC++�u��]�@�����ڥ�GDB online Debugger �N�i�H�@���]�����D���̥X���D 
# include <iostream>
# include <new>
# include <string>  // string class 
# include <cstdlib>  // system, atoi
# include <map>
# include <cctype>

using namespace std;


template <class T>                          // type template for data value in stack node
class expSTACK
{   typedef struct sN                       // structure of each element in stack
    {   T       value;
        struct sN   *next;                  // next element
    }   stackNode;

    stackNode *topPtr;                      // only one data member

public:
    expSTACK():topPtr(NULL)                 // constructor with initialization
    {} // end expSTACK initializer

    bool isEmpty()  const                   // decide whether stack is empty
    {   return topPtr == NULL ;				//  �P�_�O�_�s�b 
    }   //end expSTACK::isEmpty

    void push(const T inValue) {			//  ��inValue�s����stackNode�o��linkedlist 
    	stackNode* newNode = new stackNode ;
    	newNode->value = inValue ;
    	newNode->next = topPtr ;
    	topPtr = newNode ;
	}   //  end expSTACK::push

    void getTop(T& outValue)            //  get the top of stack without removal
    {									//  ���top���ȵ����X�� 
        if (!isEmpty()) {
        outValue = topPtr->value;
    	} 
		
    }  //  end expSTACK::getTop

    void pop()              //  remove the top of stack
    {
        if (!isEmpty()) {
        	stackNode* temp = topPtr;
       		topPtr = topPtr->next;
       	 	delete temp;
       	}
    }  //  end expSTACK::pop without output parameter

    void pop(T& outValue)           //  get the top of stack and remove it
    {   getTop(outValue) ;
    }   // end expSTACK::pop with output parameter

    ~expSTACK()             // destructor
    {   while (!isEmpty()) {
    		T outValue;
        	pop(outValue); 
		}
    }   // end destructor

};      // end expSTACK class
 



template<class T>   // type template for data value in list node
class expLIST
{
public:    // only two data members
   typedef struct qN   // structure of each node in list
    {   T       value;
        struct qN       *next;  // next element
    } listNode ;
	listNode*head,*tail;
    


	
	
    expLIST():head(NULL),tail(NULL)     //  constructor with initialization
    {}  // end expLIST initializer

    bool isEmpty() const
    {
        return head == NULL;
    }   // end expLIST::isEmpty

	void ins(const T inValue)	{		// append one value into list
		listNode* newNode = new listNode ;
  	 	newNode->value = inValue ;
  	 	newNode->next = NULL ;

    	if (isEmpty()) {
        	head = newNode ;
        	tail = newNode ;
    	} 
		else {
        	tail->next = newNode ;
        	tail = newNode ;
    	}
	}	// end expLIST::ins



    void getHead(T& outValue)   // get the head of list without removal
    {
        if (isEmpty()) {
    	} 
		else {
        	outValue = head->value ;
        	
   		}
    }   // end expLIST::getHead

    void del()  // remove the head of list
    {
        if (isEmpty()) {
    	} 
		else {
        	listNode* temp = head ;
        	head = head->next ;
        	delete temp ; 
    	}
    }   // end expLIST::del outout parameter

    void del(T& outValue)   // get the head of stack and remove it
    {
        if (isEmpty()) {
    	} 
		else {
        	outValue = head->value ;
        	listNode* temp = head ;
        	head = head->next ;
        	delete temp ; 
    	}
    }   // end expLIST::del outout parameter

};  // end expLIST class





#define MAX_LEN 255  // maximum string length

bool isExp(string & ) ;  
bool isBalanced( const string );  
bool isLegal(const string); 
void str2list( string, expLIST<string>& savelist ); 
void infix2postfix(expLIST<string>& savelist); 




   int main (void) {
 int command = 0; // �ϥΪ̩R�O
 
 
 do {
  expLIST<string> savelist ;  //  �����x�sstr��list�� linkedlist 
  
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
  
   if (isExp(infixS) &&  // �ˬd�C�ӲŸ��çR���L�Ϊ��Ÿ�
       isBalanced (infixS) && // �ˬd�A�������ĩ� �O�_��� 
       isLegal(infixS)) {  // �ˬd���O�_���X�k����F��
        
        str2list(infixS, savelist ) ; // �N�r��ѪR��linked list
        
        infix2postfix(savelist) ; // �N ���� �ഫ����� 
        cout << endl ;
		
   } // if
   
   	
	
   	break;
   
   default: cout << endl << "Command does not exist!" << endl;
  } // switch()  
  
  
   while (!savelist.isEmpty()) {  //  �O�o��list���O���鵹����X�h 
    	string test;
    	savelist.del(test);
	}
 } while (command != 0);  
  
 system ("pause");  // �Ȱ����
 return 0;
 
} // main

bool isExp( string & infixS ) {
    int i = 0 ;
    while ( i < infixS.size() ) {						//  �������r���u��O+-*/()�Ʀr�M�ť� 
        if ( infixS[i] == '0' || infixS[i] == '1' || infixS[i] == '2' || infixS[i] == '3' ||
             infixS[i] == '4' || infixS[i] == '5' || infixS[i] == '6' || infixS[i] == '7' ||
             infixS[i] == '8' || infixS[i] == '9' || infixS[i] == '+' || infixS[i] == '-' ||
             infixS[i] == '*' || infixS[i] == '/' || infixS[i] == ' ' || infixS[i] == '(' ||
             infixS[i] == ')' ) {
            if ( infixS[i] == ' ' ) {   				//  ��ťյ��Y�� 
                infixS.erase(i, 1); 
                i--;
            }
         }
         else {
            cout << "Error 1: " << infixS[i] << " is not a legitimate character." << endl ;
            return false ;
         }

        i++ ;
    }

    return true ;
}

bool isBalanced ( const string infixS ) {  //  �⥪�A���]��+1�A�k�A���]��-1�A
    int i = 0 ;
    int thetestnumber = 0 ;  //  
    while ( i != infixS.size() ) {
        if ( infixS[i] == '(' ) {
            thetestnumber++ ;
        }
        else if ( infixS[i] == ')' ) {
            thetestnumber-- ;
        }

        if ( thetestnumber < 0 ) { 					//  ��k�A���b�@�����ƶq���L���A���A�A���N�|���藍�W�����D 
            cout << "Error 2: there is one extra close parenthesis." << endl ;
            return false ;
        }

        i++ ;
    }

    if ( thetestnumber != 0 ) {  //  �A���ƶq���@�� 
        cout << "Error 2: there is one extra open parenthesis." << endl ;
        return false ;
    }

    return true ;
}

bool isLegal ( const string infixS ) {
    //  �`�@��3��error 
    //  Error 3: there is one extra operand.  Ex: (1+1)19 
    //  Error 3: there is one extra operator. Ex: 1++1
    //  Error 3: it is not infix in the parentheses. Ex: ()
    //  �P�_���~�����ǬO�q�⦡�������k����o�ͥ�error


    int i = 1 ;
    while ( i < infixS.size() ) {
        if ( infixS[i] == '+' || infixS[i] == '-' || infixS[i] == '*' || infixS[i] == '/' ) {    
            if ( infixS[i-1] == '+' || infixS[i-1] == '-' || infixS[i-1] == '*' || infixS[i-1] == '/' ) {  				//  +-*/�e������O+-*/  
                cout << "Error 3: there is one extra operator." << endl ;
                return false ;
            }
            else if ( infixS[i-1] == '(' ) {				//  +-*/�e������O���A�����M�����O�@�Ӥ��Ǧ� 
                cout << "Error 3: it is not infix in the parentheses." << endl ;
                return false ;
            }
        }
        else if ( infixS[i] == '(' ) {						//  ���A���e������O�Ʀr  �����*�b�� 
            if ( infixS[i-1] == '0' || infixS[i-1] == '1' || infixS[i-1] == '2' || infixS[i-1] == '3' || infixS[i-1] == ')' ||
                 infixS[i-1] == '4' || infixS[i-1] == '5' || infixS[i-1] == '6' || infixS[i-1] == '7' || infixS[i-1] == '8' ||
                 infixS[i-1] == '9' ) {
                cout << "Error 3: there is one extra operand." << endl ;
                return false ;
            }
            
        }
        else if ( infixS[i] == ')' ) {						//  �k�A���e������O+-*/(���M���ন���@�Ӥ��Ǧ� 
            if ( infixS[i-1] == '+' || infixS[i-1] == '-' || infixS[i-1] == '*' || infixS[i-1] == '/' || infixS[i-1] == '(' ) {
                cout << "Error 3: it is not infix in the parentheses." << endl ;
                return false ;
            }
        }
        else if ( i == infixS.size() - 1 ) {				//  �̫�@�Ӧr������O+-*/ 
            if ( infixS[i] == '+' || infixS[i] == '-' || infixS[i] == '*' || infixS[i] == '/' ) {
                cout << "Error 3: there is one extra operator." << endl ;
                return false ;
            }
        }
        else if ( infixS[0] == '+' || infixS[0] == '-' || infixS[0] == '*' || infixS[0] == '/' ) {				//    �Ĥ@�Ӥ���O+-*/ 
            cout << "Error 3: there is one extra operator." << endl ;
            return false ;
        }
		else if ( infixS[i] == '0' || infixS[i] == '1' || infixS[i] == '2' || infixS[i] == '3' || infixS[i] == '4' ||
		          infixS[i] == '5' || infixS[i] == '6' || infixS[i] == '7' || infixS[i] == '8' || infixS[i] == '9' ) {
			if ( infixS[i-1] == ')' ) {					//  �Ʀr�e������O�k�A���A�����*�A�� 
				cout << "Error 3: there is one extra operand." << endl ;
                return false ;
			}
		}
		
        i++ ;
        
    }

    return true ;
}

void str2list(string infixS, expLIST<string>& savelist) {				//  ���D�ص���string�নlist 
    
    int i = 0 ;
    string num ;
    while ( i < infixS.size() ) {
        if ( infixS[i] >= '0' && infixS[i] <= '9') {					//  �p�G�O�Ʀr���ܥ���L�Φ��@���H�_�Ӫ�string���O��1 1 �ܦ�11�A��L���list�̭� 
            num += infixS[i] ;
            while ( i + 1 < infixS.size() && isdigit(infixS[i+1]) ) {
                i++ ;
                num += infixS[i] ;
            }
            expLIST<string>::listNode* newNode = new expLIST<string>::listNode;
            newNode->value = num;
            newNode->next = NULL;
            
            if ( savelist.head == NULL ) {
                savelist.head = newNode;
                savelist.tail = newNode;
            } 
			else {
                savelist.tail->next = newNode;
                savelist.tail = newNode;
            }
            
            
            num.clear();
        }
        else {														//   ��+-*/()���list�̭� 
        	expLIST<string>::listNode* newNode = new expLIST<string>::listNode;
            newNode->value = string(1, infixS[i]);
            newNode->next = NULL;
            
            if (savelist.head == NULL) {
                savelist.head = newNode;
                savelist.tail = newNode;
            }
			else {
                savelist.tail->next = newNode;
                savelist.tail = newNode;
            }
            
            
        }
        
        i++ ;
        
    }
    
    
}


void infix2postfix( expLIST<string>& savelist ) {
	expLIST<string> coutlist ;  //  ���Ӧs��coutlist���쵲��C �A�]�N�O�⤤���ܦ���Ǫ��ƪk 
	map<string, int> precedence;		//  �o�ӬO���ӧP�_+-*/���u���šA�p�G�O*/�N�]��2�A+-�N�]��1 
	precedence["+"] = 1 ;
	precedence["-"] = 1 ;
	precedence["*"] = 2 ;
	precedence["/"] = 2 ;
	
	expSTACK<string> stack ;
	expLIST<string> list ;
	list.head = savelist.head ;
	string thetop ;
	while( !list.isEmpty() ) {				//  �qlist��head�}�l�A�@����list���Y�A�]�L�A�⥦�R���A�]�줣�s�b���� 
		
		string item ;
		list.getHead(item) ;
		if ( !item.empty() ) {
			if ( item != "+" && item != "-" && item != "*" && item != "/" && item != ")" && item != "(" ) {  //  ���F�Ÿ��N�O�Ʀr�A��Ʀr��i�hcoutlist�̭� 
  				coutlist.ins(item) ;
			}
			else if ( item == "(" ) {  //  �⥪�A����Jstack�̭� 
				stack.push(item) ;
			}
			else if ( item == ")" ) {  //  �� ( �� ) ���e���F�������icoutlist�� 
				stack.getTop(thetop) ;
				while ( thetop != "(" ) {
					coutlist.ins(thetop) ;
					stack.pop() ;
					stack.getTop(thetop) ;
				}
			
				if ( thetop == "(" ) {
					stack.pop() ;
				}
                
				
			}
			else {  //  �ѤU+ - * / ���B�z 
				stack.getTop(thetop) ;
				if ( !stack.isEmpty() && thetop != "(" && precedence[item] <= precedence[thetop] ) {
					coutlist.ins(thetop) ;
					stack.pop() ;
				}
			
				stack.push(item) ;
			
			}
		}
		
		list.del() ;
	}
	
	
	while ( !stack.isEmpty() ) {			//  �p�Glist���]���F ����stack�̪��F��Ӷ�������X�� 
		stack.getTop(thetop) ;
		coutlist.ins(thetop) ;
		stack.pop() ;
		
	}
	
	
	
	cout << "Postfix expression: " ;
	expLIST<string>::listNode* temp = new expLIST<string>::listNode;
	while ( coutlist.head->next != NULL ) {				//  ��coutlist��������cout�X�h 
		cout << coutlist.head->value << ", " ;
		temp = coutlist.head ;
		coutlist.head = coutlist.head->next ;
		delete temp;
		
	}
	
	cout << coutlist.head->value ;
	delete coutlist.head ;
	coutlist.head = NULL ;

}
