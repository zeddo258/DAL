// 11127245 薛宏毓
// Dev-C++ 5.11

#include <iostream>
#include <new>
#include <string> // string class
#include <cstdlib> // system, atoi
#include <sstream> // double to string

#define MAX_LEN 255 // maximum string length

using namespace std;

template <class T> // type template for data value in list node

class expLIST {
	
	typedef struct qN {  // structure of each node in list
		T value;
		struct qN *next; // next element
	} listNode;
	
	listNode *head, *tail; // only two data members
	
public:
	expLIST(): head(NULL), tail(NULL) // constructor with initialization
	{ } //end expLIST initializer
	
	bool isEmpty() const {  // decide whether list is empty
		return head == NULL;
	} //end expLIST::isEmpty
	
	void ins(const T inValue) {  // append one value into list
        
		try {
    		listNode *newSymbol = new listNode;
    	    newSymbol->value = inValue;
    	    newSymbol->next  = NULL;
    	    
    	    if (!newSymbol) {  // if the new node cannot be allocated, a std::bad_alloc exception is thrown
                throw std::bad_alloc();  // thrown when the required memory cannot be successfully allocated
            } // if (It is NULL when no space is found.)
    	    
            if (!head) {
                head = tail = newSymbol;
            } else {
                tail->next = newSymbol;
                tail = newSymbol;
            } // end if-else
		} catch (std::bad_alloc& ba) {  // unable to allocate space
		
		    // 'std::cerr'是 C++ 標準庫中的標準錯誤輸出流。它通常用於向控制台或終端輸出錯誤訊息。
		    //            用於錯誤訊息和不應延遲輸出的情況，以確保錯誤訊息及時顯示。
		    // 'ba.what()'返回一個文字串（C++ 字串），該文字串通常包含有關拋出的例外的描述或原因。
			std::cerr << endl << "bad_alloc on stack caught: " << ba.what() << endl;
		} // end catch
		
	} // end expLIST::ins
	
	void getHead(T& outValue) {  // get the head of list without removal
	
	    outValue = head->value;
		
	} // end expLIST::getHead
	
	void getTail(T& outValue) {  // get the tail of list without removal
	
	    outValue = tail->value;
		
	} // end expLIST::getTail
	
	void setTail(T outValue) {  // set the tail of list
	
	    tail->value = outValue;
		
	} // end expLIST::setTail
	
	void del() {  // remove the head of list
	
	    if (head) {
            listNode *temp = head;
            head = head->next;
            delete temp;
        } else {
        	cout << endl << "There is nothing here when you delete head";
        	
		} // end if-else
		
	} // end expLIST::del without output parameter
	
	void del(T& outValue) {  // get the head of stack and remove it
	
		getHead(outValue);
	    if (head) {
            listNode *temp = head;
            head = head->next;
            delete temp;
        } else {
        	cout << endl << "There is nothing here when you delete head";
        	
		} // end if-else
		
	} // end expLIST::del with output parameter
	
	void printAll() {
		
		if (head) {
            listNode *temp = head;
            while (temp != NULL) {
            	if (temp != head)
            		cout << ", ";
	            cout << temp->value;
	            temp = temp->next;
	    	} // while
        } else {
        	cout << endl << "There is nothing here when you print head";
        	
		} // end if-else
		
	} // end expLIST::printAll
	
	~expLIST() {  // destructor
		while (!isEmpty())
			del();
	} // end destructor
	
}; //end expLIST class

template <class T> // type template for data value in stack node

class expSTACK {

	typedef struct sN {// structure of each element in stack
		T value;
		struct sN *next; // next element
	} stackNode;
	
	stackNode *topPtr; // only one data member
	
public:
	expSTACK(): topPtr(NULL) // constructor with initialization
	{ } //end expSTACK initializer
	
	bool isEmpty() const {  // decide whether stack is empty
		return topPtr == NULL;
	} //end expSTACK::isEmpty
	
	void push(const T inValue) {  // add one element into stack
	
		try {
    		stackNode *newSymbol = new stackNode;
    	    newSymbol->value = inValue;
    	    newSymbol->next  = NULL;
    	    
    	    if (!newSymbol) {  // if the new node cannot be allocated, a std::bad_alloc exception is thrown
                throw std::bad_alloc();  // thrown when the required memory cannot be successfully allocated
            } // if (It is NULL when no space is found.)
    	    
            if (!topPtr) {
                topPtr = newSymbol;
            } else {
                newSymbol->next = topPtr;
                topPtr = newSymbol;
            } // end if-else
		} catch (std::bad_alloc& ba) {  // unable to allocate space
		
		    // 'std::cerr'是 C++ 標準庫中的標準錯誤輸出流。它通常用於向控制台或終端輸出錯誤訊息。
		    //            用於錯誤訊息和不應延遲輸出的情況，以確保錯誤訊息及時顯示。
		    // 'ba.what()'返回一個文字串（C++ 字串），該文字串通常包含有關拋出的例外的描述或原因。
			std::cerr << endl << "bad_alloc on stack caught: " << ba.what() << endl;
		} // end catch
	} // end expSTACK::push
	
	void getTop() {  // get the top of stack without removal
		
		return topPtr->value;
		
	} // end expSTACK::getTop
	
	void getTop(T& outValue) {  // get the top of stack without removal
		
		outValue = topPtr->value;
		
	} // end expSTACK::getTop
	
	void pop() {  // remove the top of stack 
		
		if (topPtr) {
            stackNode *temp = topPtr;
            topPtr = topPtr->next;
            delete temp;
            
        } else {
        	cout << endl << "There is nothing here when you delete head";
        	
		} // end if-else
		
	} // end expSTACK::pop without output parameter
	
	void pop(T& outValue) {  // get the top of stack and remove it
	
		getTop(outValue);
		if (topPtr) {
            stackNode *temp = topPtr;
            topPtr = topPtr->next;
            delete temp;
        } else {
        	cout << endl << "There is nothing here when you delete head";
        	
		} // end if-else
	} // end expSTACK::pop with output parameter
	
	~expSTACK() {  // destructor
		while (!isEmpty())
			pop();
	} // end destructor
}; //end expSTACK class

string noSpaceStr(string formula); // delete all space about input fomula

bool isExp(const string infixS); // check the validity of each symbol

bool isBalanced(const string infixS); // check the validity of balanced parentheses

bool isLegal(const string infixS, char preChar, int position); // check whether it is a legal expression

void str2list(expLIST<string> &infix_list, const string infixS); // parse a string into a linked list

int level(string operation);  // first * or /, then other 

bool infix2postfix(expLIST<string> &infix_list, expLIST<string> &postfix_list); // transform infix into postfix

bool check_divided_zero(expLIST<string> &postfix_list); // Check if this calculation divides by 0

int main(void) {
	int command = 0; // user command
	
	do {
		string infixS;
		
 		cout << endl << "* Arithmetic Expression Evaluator *";
 		cout << endl << "* 0. QUIT *";
 		cout << endl << "* 1. Infix2postfix Transformation *";
 		cout << endl << "***********************************";
		cout << endl << "Input a choice(0, 1): ";
		cin >> command; // get a command
		cin.ignore(MAX_LEN, '\n'); // clear the input buffer
		
		switch (command) {
			case 0: break;
			
			case 1: cout << endl << "Input an infix expression: ";
					
					getline(cin, infixS);
					infixS = noSpaceStr(infixS);
					
					if (isExp(infixS) &&           // check each symbol & remove useless ones
						isBalanced(infixS) &&      // check the validity of balanced parentheses
						isLegal(infixS, ' ', 0)) { // check whether it is a legal expression
						
					    cout << "It is a legitimate infix expression.";
					    
					    expLIST<string> infix_List;
				 		str2list(infix_List, infixS); // parse a string into a linked list
				 		
				 		// infix_List.printAll();
				 		expLIST<string> postfix_List;
				 		if(infix2postfix(infix_List, postfix_List)) { // transform infixS into postfixS
							cout << endl << "Postfix expression: ";
							postfix_List.printAll();
						} else {
							cout << endl << "fail";
							
						} // end if-else
						
						if (check_divided_zero(postfix_List)) {
							cout << endl << "########## This calculation involves dividing by 0 ##########";
						}
						
				 	} // end if
				 	
		 			break;
		 	
		 	default: cout << endl << "Command does not exist!" << endl;
		} // end switch
		 	
		cout << endl;
	} while (command != 0); // '0': stop the program
	
	system("pause"); // pause the display
	return 0;
} // end main

string noSpaceStr(string formula) {  // delete all space about input fomula
	
	int    stringLength = formula.length();
	string tempString;
	
	for (int i = 0 ; i < stringLength ; i++) {
		if (formula[i] == ' ') {
			// do nothing
		} else {
			tempString = tempString + formula[i];
		} // end if-else
	} // end for
		
	return formula = tempString;
} // noSpaceStr()

bool isExp(const string infixS) {  // check the validity of each symbol
	
	int stringLength = infixS.length();
	
	for (int i = 0 ; i < stringLength ; i++) {
		if (infixS[i] == '*' || infixS[i] == '/' ||
			infixS[i] == '+' || infixS[i] == '-' ||
			infixS[i] == ')' || infixS[i] == '(') {  //  is leglegitimate character *, /, +, -, (, )
		    
		} else if (isdigit(infixS[i])) {             // is leglegitimate number
		
		} else {                                     // is illegitimate
			cout << "Error 1: ";
			cout << infixS[i] << " is not a legitimate character.";
			return false;
		} // end if-else
	} // end for 
	
	return true;
} // end isExp()

bool isBalanced(const string infixS) {  // check the validity of balanced parentheses
	
	int stringLength     = infixS.length();
	int right_parenthesis = 0;
	int left_parenthesis  = 0;
	
	for (int i = 0 ; i < stringLength ; i++) {
		if (infixS[i] == '(') {
			left_parenthesis+=1;
			
		} else if (infixS[i] == ')')  {
			right_parenthesis+=1;
			
			if (right_parenthesis > left_parenthesis) {  // avoid )(
				cout << "Error 2: there is one extra close parenthesis.";
				return false;
			} // end if
		} // end if-else
	} // end for
	
	if (left_parenthesis == right_parenthesis) {
		return true;
		
	} else {  // avoid ()) or (()
		cout << "Error 2: there is one extra close parenthesis.";
		return false;
	} // end if-else
	
} // end isBalanced()

bool isLegal(const string infixS, char preChar, int position) {  // check whether it is a legal expression
	int len_infixS = infixS.length();
	
	if (position == len_infixS) {  // avoid last symbol is (, *, /, +, -
		if (preChar == '(') {
			cout << "Error 3: there is one extra operand.";
			return false;
		} else if (preChar == '*' || preChar == '/' ||
				   preChar == '+' || preChar == '-')  {
			cout << "Error 3: there is one extra operator.";
			return false;
		} else {
			return true;
			
		} // end if-else
	} // end if
	
	if (position == 0) {  // avoid first symbol is ), *, /, +, -
		if (infixS[position] == '*' || infixS[position] == '/' ||
			infixS[position] == '+' || infixS[position] == '-')  {
			cout << "Error 3: there is one extra operator.";
			return false;
		} else {
			preChar = infixS[position];
			return isLegal(infixS, preChar, position+1);
		} // end if-else
	} // end if
	
	if (isdigit(infixS[position])) {
		if (preChar == ')') {  // avoid ...)1
			cout << "Error 3: there is one extra operand.";
			return false;
		} // end if
	} else if (infixS[position] == '*' || infixS[position] == '/' ||
			   infixS[position] == '+' || infixS[position] == '-')  {
		if (preChar == '(') {  // avoid ...(+
			cout << "Error 3: it is not infix in the parentheses.";
			return false;
		} else if (preChar == '*' || preChar == '/' ||
				   preChar == '+' || preChar == '-')  {  // avoid ...++
			cout << "Error 3: there is one extra operator.";
			return false;
		} // end if-else if
	} else if (infixS[position] == '(') {
		if (preChar == ')') {  // avoid (...)(...)
			cout << "Error 3: there is one extra operand.";
			return false;
		} else if (isdigit(preChar)) {  // avoid ...1(
			cout << "Error 3: there is one extra operand.";
			return false;
		} // end if-else if
	} else if (infixS[position] == ')') {
		if (preChar == '(') {  // avoid ...()
			cout << "Error 3: it is not infix in the parentheses.";
			return false;
		} else if (preChar == '*' || preChar == '/' ||
				   preChar == '+' || preChar == '-')  {  // avoid ...+)
			cout << "Error 3: it is not infix in the parentheses.";
			return false;
		} // end if-else if
	} // end if-else if
	
	preChar = infixS[position];
	return isLegal(infixS, preChar, position+1);
} // end isLegal()

void str2list(expLIST<string> &infix_list, const string infixS) {
    
    infix_list.ins(string(1, infixS[0])); // save the first symbol
    
    for (int i = 1 ; i < infixS.length() ; i++) {
    	if (isdigit(infixS[i]) && isdigit(infixS[i-1])) {
    		// Only one number can be stored per location, so multiple numbers need to be retrieved from multiple locations.
    		string tempCurrent = string(1, infixS[i]);  // transform string form
            string tempPrevious;
            infix_list.getTail(tempPrevious);
            infix_list.setTail(tempPrevious + tempCurrent);  // ex: 10 + 1 => 101
		} else {
			infix_list.ins(string(1, infixS[i]));
			
		} // end if-else
	} // end for
    
} // end str2list()

int level(const string op) {
	if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0; // 如果不是已知運算符，返回0作為默認值
} // end level() 

bool infix2postfix(expLIST<string> &infix_list, expLIST<string> &postfix_list) {
    
    expSTACK<string> stackTemp;  // A stack that stores arithmetic symbols
    string temp;
    
    while (!infix_list.isEmpty()) {  // Check if there are any unsorted
    	infix_list.del(temp);        // Delete and save data
    	
    	if (isdigit(temp[0])) {      // If it is a number, it is added directly to postfix.
    		postfix_list.ins(temp);
    		
		} else if (temp == "(") {
			// Whenever '(' is encountered, a new legal function is entered to judge
			// '(' represents the beginning of a subexpression
			if (!infix2postfix(infix_list, postfix_list)) {
				return false;
				
			} // end if
		} else if (level(temp) >= 1) {   // is calculating signs
			if (!stackTemp.isEmpty()) {  // Check if there is an arithmetic symbol on the stack
				string tempOperation;
				stackTemp.getTop(tempOperation);  // Store previous operation symbols
				
				while (!stackTemp.isEmpty() && level(temp) <= level(tempOperation)) {
					// 1. There are also unprocessed arithmetic symbols in the stack
					// 2. Compare operation priority
					stackTemp.pop(tempOperation);      // Get, delete
					postfix_list.ins(tempOperation);   // and add 
					
					if (!stackTemp.isEmpty())  // There are also unprocessed arithmetic symbols in the stack
						stackTemp.getTop(tempOperation);
				} // end while
				
				stackTemp.push(temp);
			} else { 
				// Arithmetic symbols are stored directly on the stack
				stackTemp.push(temp);
			} // end if-else
			
		} else if (temp == ")") {
			// '(' represents the Endding of a subexpression
			// Remove all operators from the stack and arrange them
			while (!stackTemp.isEmpty()) {
				string tempOperation;
				stackTemp.pop(tempOperation);
				postfix_list.ins(tempOperation);
			} // end while
			
			return true;
		} // end if-else if 
    	
	} // end while
	
	while (!stackTemp.isEmpty()) {  // Remove all operators from the stack and arrange them
		stackTemp.pop(temp);
		postfix_list.ins(temp);
	} // end while
	
	return true;
    
} // end infix2postfix()

bool check_divided_zero(expLIST<string> &postfix_list) {
    expSTACK<string> stackTemp;
    std::stringstream ss;
    double numberTwo, numberOne;
    string numberStr;

    while (!postfix_list.isEmpty()) {  // 將所有後續排列拿出來運算，直到沒有 
        string temp;
        postfix_list.del(temp);

        if (temp == "*" || temp == "/" || temp == "+" || temp == "-") {
            stackTemp.pop(numberStr);
            numberTwo = atoi(numberStr.c_str());  // 提出第一個為被算數 
            stackTemp.pop(numberStr);
            numberOne = atoi(numberStr.c_str());  // 提出第一個為算數 
            
            // 做運算 
            if (temp == "*") {
                ss << numberOne * numberTwo;
            } else if (temp == "+") {
                ss << numberOne + numberTwo;
            } else if (temp == "-") {
                ss << numberOne - numberTwo;
            } else if (temp == "/") {
                if (numberTwo == 0)
                    return true;  // 存在除零情況 
                
                ss << numberOne / numberTwo;
            } // end if-else
            
            stackTemp.push(ss.str());
            ss.str("");  // 重置 stringstream
        } else {
            stackTemp.push(temp);
        } // end if-else
    } // end while

    return false;  // 不存在除零情況 
} // end check_divided_zero()





