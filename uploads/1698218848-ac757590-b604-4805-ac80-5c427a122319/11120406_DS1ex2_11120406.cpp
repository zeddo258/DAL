#include<iostream>
#include<new>
#include <map>
#include <string>  // string class 
#include <cstdlib>  // system, atoi 
#define MAX_LEN 255  // maximum string length

using namespace std;

void Dspace(string &infixS){	//�ٲ��ť� 
	string temp;
	for(int i=0;i<infixS.length();i++){
		if(infixS[i] != ' '){
			temp += infixS[i];
		}
	}
	infixS = temp;
}

bool isExp(string &infixS){	//���Τ�Ʀr�Ÿ�  
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

bool isBalanced(const string infixS){	//�A���O�_����	
	int flag1 = 0, flag2 = 0;
	for(int i=0;i<infixS.length();i++){
		if(infixS[i] == '('){
			flag1++;
		}else if(infixS[i] == ')'){
			flag2++;
		}
	
		if(flag2 > flag1 ){		//)(�~�A�����D 
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

bool isLegal(const string infixS){	//�X�k���ǹB�⦡ 
	for(int i=0;i<infixS.length();i++){
		if(infixS[i] == '+' || infixS[i] == '-' || infixS[i] == '*' || infixS[i] == '/'){	//���୫�Ʊ��B��l 
		 	if(infixS[i+1] == '+' || infixS[i+1] == '-' || infixS[i+1] == '*' || infixS[i+1] == '/'){
		 		cout<<"Error 3: there is one extra operator."<< endl;
		 		return false;
			 }
		}
		if(infixS[i] == '('){	//���A�ᤣ�౵�B��r 
			if(infixS[i+1] == '+' || infixS[i+1] == '-' || infixS[i+1] == '*' || infixS[i+1] == '/'){
				cout<<"Error 3: it is not infix in the parentheses."<< endl;
		 		return false;
			}
		}
		if(infixS[i] == ')'){	//�k�A�e���౵�B��r 
			if(infixS[i-1] == '+' || infixS[i-1] == '-' || infixS[i-1] == '*' || infixS[i-1] == '/'){
				cout<<"Error 3: it is not infix in the parentheses."<< endl;
		 		return false;
			}
		}
		if(infixS[i] == '('){	//���A���e���౵�Ʀr 
			if(int(infixS[i-1]) >= 48 && int(infixS[i-1] <= 57)){
				cout<<"Error 3: there is one extra operand."<< endl;
		 		return false;
			}
		}
		if(infixS[i] == ')'){	//�k�A���ᤣ�౵�Ʀr 
			if(int(infixS[i+1]) >= 48 && int(infixS[i+1] <= 57)){
				cout<<"Error 3: there is one extra operand."<< endl;
		 		return false;
			}
		}
		if(infixS[0] == '+' || infixS[0] == '-' || infixS[0] == '*' || infixS[0] == '/'){	//�Ĥ@�Ӧ�l����O�B��l 
			cout<<"Error 3: there is one extra operator."<< endl;
		 	return false;
		}
		if(infixS[infixS.length()-1] == '+' || infixS[infixS.length()-1] == '-' || infixS[infixS.length()-1] == '*' || infixS[infixS.length()-1] == '/'){	//�̫�@�Ӧ�l����O�B��l 
			cout<<"Error 3: there is one extra operator."<< endl;
		 	return false;
		}
		
		if(infixS[i] == '('){	//�A�����S�F�� 
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
            	// �p�G�쵲���šA�N�s�`�I�]�m���Y�M��
            	head = newNode;
            	tail = newNode;
        	} 
			else{
            	// �_�h�N�s�`�I�K�[���쵲������
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
        	delete temp; // ������Y�`�I�����s
    	} 
		else {
			isEmpty();
    	}
    }   // end expLIST::del outout parameter

    void del(T& outValue)   // get the head of stack and remove it
    {
        if (head != NULL) {
        	outValue = head->value; // �N�Y�`�I�����x�s�b outValue ��
        	listNode* temp = head;
        	head = head->next;
        	delete temp; // ������Y�`�I�����s
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
        	delete temp; // ����`�I�����s
    	}
    	// �b�`��������A�쵲�����Ҧ��`�I���w�Q�R���Ahead ���V NULL
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
        	newNode->next = topPtr;  // �s�`�I���U�@�Ӹ`�I�O�ثe�����|����

        	topPtr = newNode;  // ��s���|�������s�`�I
        } // end try
        catch(std::bad_alloc& ba)
        {   
			std::cerr << endl << "bad_alloc on stack caught:"<< ba.what() << endl;
        } //end catch
    } // end expSTACK::push

    string getTop(T& outValue)	//������|�������� 
    {
          if(!isEmpty()){
          	outValue = topPtr->value;
          	return outValue;
		  }
		  else{
		  	isEmpty();
		  }
    } //end expSTACK::getTop

    void pop()	//�R�����|�������`�I	
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

    void pop(T& outValue)	//������|�������ȨçR��
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
            // �p�G��e�r�ŬO�Ʀr�A�h�N�s�򪺼Ʀr�r�ŦX�֦��@�Ӧh��Ʀr
            while (i < infixS.length() && isdigit(infixS[i])) {
                token += infixS[i];
                i++;
            }
        } else {
            // �p�G��e�r�Ť��O�Ʀr�A�����N���@���@�ӳ�r�Ū��r�Ŧ�
            token = infixS[i];
            i++;
        }

        // �N token �K�[���쵲 
        list.ins(token);
    }
    
}

bool infix2postfix( string& infixS, string& postfixS, expLIST<string> & list ) {
    // �w�q�B��Ū��u����
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
            // �p�G�Ʀr�A�����K�[�����ܪk��
            postlist.ins(token);
            //postlist += " ";
        } else if (token == "(") {
            // �p�G�O���A���A�N�����J�B��Ű��|
            operatorStack.push(token);
        } else if (token == ")") {
            // �p�G�O�k�A���A�N�B��Ű��|�����B��żu�X�A����J�쥪�A��
            while (!operatorStack.isEmpty() && operatorStack.getTop(gettopitem) != "(" ) {
            	postlist.ins(operatorStack.getTop(gettopitem));
                //postfixS += " ";
                operatorStack.pop();
            }
            if (!operatorStack.isEmpty() && operatorStack.getTop(gettopitem) == "(" ){
                operatorStack.pop(); // �u�X���A��
            } else {
                // �A�����ǰt�A��^���~
                return false;
            }
        } else if (token == "+" || token == "-" || token == "*" || token == "/") {
            // �p�G�O�B��šA�B�z�B��Ū��u����
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
    // �N�B��Ű��|�����Ҧ��B��żu�X�A�K�[�����ܪk��
    while (!operatorStack.isEmpty()) {
        if (operatorStack.getTop(gettopitem) == "(" || operatorStack.getTop(gettopitem) == ")") {
            // �p�G�٦��A���b���|���A��ܤ��ǰt�A��^���~
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
   getline (cin, infixS);	//�N��J�奻�x�s��r�Ŧ��ܼƤ� 
   
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
