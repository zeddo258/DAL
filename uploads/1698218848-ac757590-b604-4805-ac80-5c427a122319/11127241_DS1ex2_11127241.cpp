// 11127241 資訊二乙 謝沐龍 
//  我用devC++只能跑一次但我用GDB online Debugger 就可以一直跑不知道哪裡出問題 
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
    {   return topPtr == NULL ;				//  判斷是否存在 
    }   //end expSTACK::isEmpty

    void push(const T inValue) {			//  把inValue存取到stackNode這個linkedlist 
    	stackNode* newNode = new stackNode ;
    	newNode->value = inValue ;
    	newNode->next = topPtr ;
    	topPtr = newNode ;
	}   //  end expSTACK::push

    void getTop(T& outValue)            //  get the top of stack without removal
    {									//  把最top的值給取出來 
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
 int command = 0; // 使用者命令
 
 
 do {
  expLIST<string> savelist ;  //  拿來儲存str轉list的 linkedlist 
  
  string infixS;
  cout << endl << "* Arithmetic Expression Evaluator *";
  cout << endl << "* 0. QUIT                         ";
  cout << endl << "* 1. Infix2postfix Transformation  ";
  cout << endl << "*******************************";
  cout << endl << "Input a choice(0, 1): ";
  cin >> command;  // 得到一個命令
  cin.ignore (MAX_LEN, '\n');  
  switch (command) {
   case 0: break;
   case 1: cout << endl << "Input an infix expression: ";
   getline (cin, infixS); 
  
   if (isExp(infixS) &&  // 檢查每個符號並刪除無用的符號
       isBalanced (infixS) && // 檢查括號的有效性 是否對稱 
       isLegal(infixS)) {  // 檢查它是否為合法的表達式
        
        str2list(infixS, savelist ) ; // 將字串解析為linked list
        
        infix2postfix(savelist) ; // 將 中序 轉換為後序 
        cout << endl ;
		
   } // if
   
   	
	
   	break;
   
   default: cout << endl << "Command does not exist!" << endl;
  } // switch()  
  
  
   while (!savelist.isEmpty()) {  //  記得把list的記憶體給釋放出去 
    	string test;
    	savelist.del(test);
	}
 } while (command != 0);  
  
 system ("pause");  // 暫停顯示
 return 0;
 
} // main

bool isExp( string & infixS ) {
    int i = 0 ;
    while ( i < infixS.size() ) {						//  全部的字元只能是+-*/()數字和空白 
        if ( infixS[i] == '0' || infixS[i] == '1' || infixS[i] == '2' || infixS[i] == '3' ||
             infixS[i] == '4' || infixS[i] == '5' || infixS[i] == '6' || infixS[i] == '7' ||
             infixS[i] == '8' || infixS[i] == '9' || infixS[i] == '+' || infixS[i] == '-' ||
             infixS[i] == '*' || infixS[i] == '/' || infixS[i] == ' ' || infixS[i] == '(' ||
             infixS[i] == ')' ) {
            if ( infixS[i] == ' ' ) {   				//  把空白給吃掉 
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

bool isBalanced ( const string infixS ) {  //  把左括號設為+1，右括號設為-1，
    int i = 0 ;
    int thetestnumber = 0 ;  //  
    while ( i != infixS.size() ) {
        if ( infixS[i] == '(' ) {
            thetestnumber++ ;
        }
        else if ( infixS[i] == ')' ) {
            thetestnumber-- ;
        }

        if ( thetestnumber < 0 ) { 					//  當右括號在一瞬間數量高過左括號，括號就會有對不上的問題 
            cout << "Error 2: there is one extra close parenthesis." << endl ;
            return false ;
        }

        i++ ;
    }

    if ( thetestnumber != 0 ) {  //  括號數量不一樣 
        cout << "Error 2: there is one extra open parenthesis." << endl ;
        return false ;
    }

    return true ;
}

bool isLegal ( const string infixS ) {
    //  總共有3個error 
    //  Error 3: there is one extra operand.  Ex: (1+1)19 
    //  Error 3: there is one extra operator. Ex: 1++1
    //  Error 3: it is not infix in the parentheses. Ex: ()
    //  判斷錯誤的順序是從算式的左邊到右邊先發生先error


    int i = 1 ;
    while ( i < infixS.size() ) {
        if ( infixS[i] == '+' || infixS[i] == '-' || infixS[i] == '*' || infixS[i] == '/' ) {    
            if ( infixS[i-1] == '+' || infixS[i-1] == '-' || infixS[i-1] == '*' || infixS[i-1] == '/' ) {  				//  +-*/前面不能是+-*/  
                cout << "Error 3: there is one extra operator." << endl ;
                return false ;
            }
            else if ( infixS[i-1] == '(' ) {				//  +-*/前面不能是左括號不然不能算是一個中序式 
                cout << "Error 3: it is not infix in the parentheses." << endl ;
                return false ;
            }
        }
        else if ( infixS[i] == '(' ) {						//  左括號前面不能是數字  不能當成*在用 
            if ( infixS[i-1] == '0' || infixS[i-1] == '1' || infixS[i-1] == '2' || infixS[i-1] == '3' || infixS[i-1] == ')' ||
                 infixS[i-1] == '4' || infixS[i-1] == '5' || infixS[i-1] == '6' || infixS[i-1] == '7' || infixS[i-1] == '8' ||
                 infixS[i-1] == '9' ) {
                cout << "Error 3: there is one extra operand." << endl ;
                return false ;
            }
            
        }
        else if ( infixS[i] == ')' ) {						//  右括號前面不能是+-*/(不然不能成為一個中序式 
            if ( infixS[i-1] == '+' || infixS[i-1] == '-' || infixS[i-1] == '*' || infixS[i-1] == '/' || infixS[i-1] == '(' ) {
                cout << "Error 3: it is not infix in the parentheses." << endl ;
                return false ;
            }
        }
        else if ( i == infixS.size() - 1 ) {				//  最後一個字元不能是+-*/ 
            if ( infixS[i] == '+' || infixS[i] == '-' || infixS[i] == '*' || infixS[i] == '/' ) {
                cout << "Error 3: there is one extra operator." << endl ;
                return false ;
            }
        }
        else if ( infixS[0] == '+' || infixS[0] == '-' || infixS[0] == '*' || infixS[0] == '/' ) {				//    第一個不能是+-*/ 
            cout << "Error 3: there is one extra operator." << endl ;
            return false ;
        }
		else if ( infixS[i] == '0' || infixS[i] == '1' || infixS[i] == '2' || infixS[i] == '3' || infixS[i] == '4' ||
		          infixS[i] == '5' || infixS[i] == '6' || infixS[i] == '7' || infixS[i] == '8' || infixS[i] == '9' ) {
			if ( infixS[i-1] == ')' ) {					//  數字前面不能是右括號，不能當*再用 
				cout << "Error 3: there is one extra operand." << endl ;
                return false ;
			}
		}
		
        i++ ;
        
    }

    return true ;
}

void str2list(string infixS, expLIST<string>& savelist) {				//  把題目給的string轉成list 
    
    int i = 0 ;
    string num ;
    while ( i < infixS.size() ) {
        if ( infixS[i] >= '0' && infixS[i] <= '9') {					//  如果是數字的話先把他用成一個黏起來的string像是把1 1 變成11再把他丟到list裡面 
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
        else {														//   把+-*/()丟到list裡面 
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
	expLIST<string> coutlist ;  //  拿來存取coutlist的鏈結串列 ，也就是把中序變成後序的排法 
	map<string, int> precedence;		//  這個是拿來判斷+-*/的優先級，如果是*/就設為2，+-就設為1 
	precedence["+"] = 1 ;
	precedence["-"] = 1 ;
	precedence["*"] = 2 ;
	precedence["/"] = 2 ;
	
	expSTACK<string> stack ;
	expLIST<string> list ;
	list.head = savelist.head ;
	string thetop ;
	while( !list.isEmpty() ) {				//  從list的head開始，一直取list的頭，跑過再把它刪掉，跑到不存在為止 
		
		string item ;
		list.getHead(item) ;
		if ( !item.empty() ) {
			if ( item != "+" && item != "-" && item != "*" && item != "/" && item != ")" && item != "(" ) {  //  除了符號就是數字，把數字放進去coutlist裡面 
  				coutlist.ins(item) ;
			}
			else if ( item == "(" ) {  //  把左括號放入stack裡面 
				stack.push(item) ;
			}
			else if ( item == ")" ) {  //  把 ( 到 ) 之前的東西全部丟進coutlist裡 
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
			else {  //  剩下+ - * / 的處理 
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
	
	
	while ( !stack.isEmpty() ) {			//  如果list都跑完了 那把stack裡的東西照順序釋放出來 
		stack.getTop(thetop) ;
		coutlist.ins(thetop) ;
		stack.pop() ;
		
	}
	
	
	
	cout << "Postfix expression: " ;
	expLIST<string>::listNode* temp = new expLIST<string>::listNode;
	while ( coutlist.head->next != NULL ) {				//  把coutlist的部分給cout出去 
		cout << coutlist.head->value << ", " ;
		temp = coutlist.head ;
		coutlist.head = coutlist.head->next ;
		delete temp;
		
	}
	
	cout << coutlist.head->value ;
	delete coutlist.head ;
	coutlist.head = NULL ;

}
