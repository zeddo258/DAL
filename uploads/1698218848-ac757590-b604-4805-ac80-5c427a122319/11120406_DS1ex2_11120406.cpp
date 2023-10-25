#include<iostream>
#include<new>
#include <map>
#include <string>  // string class 
#include <cstdlib>  // system, atoi 
#define MAX_LEN 255  // maximum string length

using namespace std;

void Dspace(string &infixS){	//省略空白 
	string temp;
	for(int i=0;i<infixS.length();i++){
		if(infixS[i] != ' '){
			temp += infixS[i];
		}
	}
	infixS = temp;
}

bool isExp(string &infixS){	//限用文數字符號  
	Dspace(infixS);
	for(int i=0;i<infixS.length();i++){
		if((infixS[i] == '+' || infixS[i] == '-' || infixS[i] == '*' || infixS[i] == '/')
			||(infixS[i] == '(' || infixS[i] == ')')
				||(int(infixS[i]) >=48 && int(infixS[i] <=57))){
					return true;
		}
		else{
			cout<< "Error 1:"<<infixS[i]<<"is not a legitimate character." << endl;
				return false;
		}
	}
} 	

bool isBalanced(const string infixS){	//括號是否平衡	
	int flag1 = 0, flag2 = 0;
	for(int i=0;i<infixS.length();i++){
		if(infixS[i] == '('){
			flag1++;
		}else if(infixS[i] == ')'){
			flag2++;
		}
	
		if(flag2 > flag1 ){		//)(外括的問題 
			cout<< "Error 2: there is one extra close parenthesis." << endl;
			return false;
		}
	}
	if(flag1 == flag2 ){
	}
	else{
		if(flag1 > flag2 ){
			cout<< "Error 2: there is one extra open parenthesis." << endl;
			return false;
		}
		else if(flag2 > flag1 ){
			cout<< "Error 2: there is one extra close parenthesis." << endl;
			return false;
		}
	} 
	return true;  
}

bool isLegal(const string infixS){	//合法中序運算式 
	for(int i=0;i<infixS.length();i++){
		if(infixS[i] == '+' || infixS[i] == '-' || infixS[i] == '*' || infixS[i] == '/'){	//不能重複接運算子 
		 	if(infixS[i+1] == '+' || infixS[i+1] == '-' || infixS[i+1] == '*' || infixS[i+1] == '/'){
		 		cout<<"Error 3: there is one extra operator."<< endl;
		 		return false;
			 }
		}
		if(infixS[i] == '('){	//左括後不能接運算字 
			if(infixS[i+1] == '+' || infixS[i+1] == '-' || infixS[i+1] == '*' || infixS[i+1] == '/'){
				cout<<"Error 3: it is not infix in the parentheses."<< endl;
		 		return false;
			}
		}
		if(infixS[i] == ')'){	//右括前不能接運算字 
			if(infixS[i-1] == '+' || infixS[i-1] == '-' || infixS[i-1] == '*' || infixS[i-1] == '/'){
				cout<<"Error 3: it is not infix in the parentheses."<< endl;
		 		return false;
			}
		}
		if(infixS[i] == '('){	//左括號前不能接數字 
			if(int(infixS[i-1]) >= 48 && int(infixS[i-1] <= 57)){
				cout<<"Error 3: there is one extra operand."<< endl;
		 		return false;
			}
		}
		if(infixS[i] == ')'){	//右括號後不能接數字 
			if(int(infixS[i+1]) >= 48 && int(infixS[i+1] <= 57)){
				cout<<"Error 3: there is one extra operand."<< endl;
		 		return false;
			}
		}
		if(infixS[0] == '+' || infixS[0] == '-' || infixS[0] == '*' || infixS[0] == '/'){	//第一個位子不能是運算子 
			cout<<"Error 3: there is one extra operator."<< endl;
		 	return false;
		}
		if(infixS[infixS.length()-1] == '+' || infixS[infixS.length()-1] == '-' || infixS[infixS.length()-1] == '*' || infixS[infixS.length()-1] == '/'){	//最後一個位子不能是運算子 
			cout<<"Error 3: there is one extra operator."<< endl;
		 	return false;
		}
		
		if(infixS[i] == '('){	//括號內沒東西 
			if(infixS[i+1] == ')'){
				cout<<"Error 3: it is not infix in the parentheses."<< endl;
		 		return false;
			}
		}
	} 
	return true;
}

template<class T>   // type template for data value in list node
class expLIST
{   
	typedef struct qN   // structure of each node in list
    {   
		T	value;
        struct qN	*next;  // next element
    }	listNode;
    listNode*head,*tail;    // only two data members
public:
    expLIST():head(NULL),tail(NULL)     //constructor with initialization
    {}  // end expLIST initializer

    bool isEmpty() const	//decide whether list is empty
    {
        return head == NULL;
    }   // end expLIST::isEmpty
    
    void ins(const T invalue)
    {
    	try
    	{
    		listNode* newNode = new listNode;
        	newNode->value = invalue;
        	newNode->next = NULL;

        	if (head == NULL){
            	// 如果鏈結為空，將新節點設置為頭和尾
            	head = newNode;
            	tail = newNode;
        	} 
			else{
            	// 否則將新節點添加到鏈結的末尾
            	tail->next = newNode;
            	tail = newNode;
        	}
		}	//end try
		catch(std::bad_alloc&ba)
		{
			std::cerr<<endl<<"bad_alloc on stack caught:"<<ba.what()<<endl;
		}
	}	//end expList::ins

    void getHead(T& outValue)   // get the head of list without removal
    {
        if(head != NULL){
        	outValue = head->value;
		}
		else{
			isEmpty();
		}
    }   // end expLIST::getHead

    void del()  // remove the head of list
    {
        if (head != NULL){
        	listNode* temp = head;
        	head = head->next;
        	delete temp; // 釋放原頭節點的內存
    	} 
		else {
			isEmpty();
    	}
    }   // end expLIST::del outout parameter

    void del(T& outValue)   // get the head of stack and remove it
    {
        if (head != NULL) {
        	outValue = head->value; // 將頭節點的值儲存在 outValue 中
        	listNode* temp = head;
        	head = head->next;
        	delete temp; // 釋放原頭節點的內存
    	} 
		else {
 			isEmpty();
    	}
    }   // end expLIST::del outout parameter

    void clearUp()  // clear up the entire list
    {
        while (head != NULL) {
        	listNode* temp = head;
        	head = head->next;
        	delete temp; // 釋放節點的內存
    	}
    	// 在循環結束後，鏈結中的所有節點都已被刪除，head 指向 NULL
    }   // end expLIST::clearUp

    ~expLIST()  // destructor
    {
        clearUp();
    }   // end expLIST class
}; 


template <class T>
class expSTACK
{
	typedef struct sN
	{
		T	value;
		struct sN *next;	//next element
	}stackNode;
	stackNode *topPtr;
public:
    expSTACK():topPtr(NULL)
    {} //end expSTACK initializer


    bool isEmpty()  const
    {   
		return topPtr == NULL;
    }   //end expSTACK::isEmpty

    void push(const T inValue)
    {   try
        {
        	stackNode* newNode = new stackNode;
        	newNode->value = inValue;
        	newNode->next = topPtr;  // 新節點的下一個節點是目前的堆疊頂部

        	topPtr = newNode;  // 更新堆疊頂部為新節點
        } // end try
        catch(std::bad_alloc& ba)
        {   
			std::cerr << endl << "bad_alloc on stack caught:"<< ba.what() << endl;
        } //end catch
    } // end expSTACK::push

    string getTop(T& outValue)	//獲取堆疊的頂部值 
    {
          if(!isEmpty()){
          	outValue = topPtr->value;
          	return outValue;
		  }
		  else{
		  	isEmpty();
		  }
    } //end expSTACK::getTop

    void pop()	//刪除堆疊的頂部節點	
    {
        if (!isEmpty()){
            stackNode* temp = topPtr;
            topPtr = topPtr->next;
            delete temp;
        }
        else{
        	isEmpty();
		}
    }//end expSTACK::pop without output parameter

    void pop(T& outValue)	//獲取堆疊的頂部值並刪除
    { 
		getTop(outValue);
        pop();
    } //end exp::pop with output parameter

    ~expSTACK()
    {   while (!isEmpty())
            pop();
    }   //end destructor
};    //end expSTACK class

void str2list(const string infixS, expLIST<string> & list ){	//  parse a string into a linked list  
	int i = 0;
	
    while (i < infixS.length()){
        string token = "";

        if (isdigit(infixS[i])) {
            // 如果當前字符是數字，則將連續的數字字符合併成一個多位數字
            while (i < infixS.length() && isdigit(infixS[i])) {
                token += infixS[i];
                i++;
            }
        } else {
            // 如果當前字符不是數字，直接將它作為一個單字符的字符串
            token = infixS[i];
            i++;
        }

        // 將 token 添加到鏈結 
        list.ins(token);
    }
    
}

bool infix2postfix( string& infixS, string& postfixS, expLIST<string> & list ) {
    // 定義運算符的優先級
    map<string, int> precedence;
    precedence["+"] = 1;
    precedence["-"] = 1;
    precedence["*"] = 2;
    precedence["/"] = 2;

    expSTACK<string> operatorStack;
    expLIST<string> postlist ;
	string gettopitem ;
	
    while(!list.isEmpty()) {
    	//cout<<"BENSON"<<endl;
        string token ;
        list.getHead(token) ;
        if (token != "+" && token != "-" && token != "*" && token != "/" && token != "(" && token != ")") {
            // 如果數字，直接添加到後綴表示法中
            postlist.ins(token);
            //postlist += " ";
        } else if (token == "(") {
            // 如果是左括號，將其壓入運算符堆疊
            operatorStack.push(token);
        } else if (token == ")") {
            // 如果是右括號，將運算符堆疊中的運算符彈出，直到遇到左括號
            while (!operatorStack.isEmpty() && operatorStack.getTop(gettopitem) != "(" ) {
            	postlist.ins(operatorStack.getTop(gettopitem));
                //postfixS += " ";
                operatorStack.pop();
            }
            if (!operatorStack.isEmpty() && operatorStack.getTop(gettopitem) == "(" ){
                operatorStack.pop(); // 彈出左括號
            } else {
                // 括號不匹配，返回錯誤
                return false;
            }
        } else if (token == "+" || token == "-" || token == "*" || token == "/") {
            // 如果是運算符，處理運算符的優先級
            while (!operatorStack.isEmpty() && operatorStack.getTop(gettopitem) != "(" &&
                precedence[token] <= precedence[operatorStack.getTop(gettopitem)]) {
                postlist.ins(operatorStack.getTop(gettopitem));
                //postfixS += " ";
                operatorStack.pop();
            }
            operatorStack.push(token);
        } 
        
        list.del() ;
    }
	// cout << infixS ;
    // 將運算符堆疊中的所有運算符彈出，添加到後綴表示法中
    while (!operatorStack.isEmpty()) {
        if (operatorStack.getTop(gettopitem) == "(" || operatorStack.getTop(gettopitem) == ")") {
            // 如果還有括號在堆疊中，表示不匹配，返回錯誤
            return false;
        }
        postlist.ins(operatorStack.getTop(gettopitem));
        //postfixS += " ";
        operatorStack.pop();
    }
	infixS = "\0";
	string benson ;
	postlist.getHead(benson);
	cout<<"Postfix expression:"<<benson;
	postlist.del();
	while(!postlist.isEmpty()){
		postlist.getHead(benson) ;
    	cout<<","<<benson;
    	postlist.del();
	}
    return true;
}

bool isOperator(string c) {
    return c == "+" || c == "-" || c == "*" || c == "/";
}

int main (void) {
 int command = 0; 
 
 expLIST<string> list ;
 do {
  
  string postfixS;
  string infixS;
  cout << endl << "* Arithmetic Expression Evaluator *";
  cout << endl << "* 0. QUIT                         ";
  cout << endl << "* 1. Infix2postfix Transformation  ";
  cout << endl << "*******************************";
  cout << endl << "Input a choice(0, 1): ";
  cin >> command; 
  cin.ignore (MAX_LEN, '\n');	//clear the input buffer
  switch (command) {
   case 0: break;
   case 1: cout << endl << "Input an infix expression: ";
   getline (cin, infixS);	//將輸入文本儲存到字符串變數中 
   
   if (isExp(infixS) && isBalanced (infixS) && isLegal(infixS)) {
   	cout<<"It is a legitimate infix expression."<<endl; 
	str2list(infixS,list);
    infix2postfix(infixS ,postfixS,list);
  
   } //end if
   
   break;
   
   default: cout << endl << "Command does not exist!" << endl;
   } // end switch()  
	} while (command != 0);  
  	system ("pause");  
 	return 0;
 } // end main
