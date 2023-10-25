// 11127203 ���O�p 
#include <iostream>
#include <cstdlib> // system, atoi
#include <string> // string class

#define MAX_LEN 255 // maximum string length

using namespace std ;

class ListNode {
public:
    string value ;  // �Ψ��x�s�`�I����
    ListNode* next ; // ���V�U�@�Ӹ`�I������
    ListNode( const string& val ) : value( val ), next( nullptr ) {} // ��l�Ƹ`�I�A�Nnext���Ъ�l�Ƭ�nullptr�A��ܥ��O���|�����̤W���@�Ӹ`�I 
};

class expLIST {
private:
    ListNode* head ;
    ListNode* tail ;
    // ���V����Y�`�I�M���`�I

public:
    expLIST() : head( nullptr ), tail( nullptr ) {} // �غc�l�A��l�����O������A�ð���@�Ǫ�l�]�w�ާ@ 

    bool isEmpty() { // �ˬd�C��O�_���šA�Y�`�I�O�_�� nullptr 
        return head == nullptr ;
    } // bool isEmpty()
 
    void ins( const string val ) { // �b�C�������J�㦳�S�w�Ȫ��s�`�I
        ListNode* newNode = new ListNode( val ) ;
        if ( tail == nullptr ) {
            head = tail = newNode ; // �s�`�I�]��head�Mtail
        } // if ( tail == nullptr )
        else {
            tail->next = newNode ; // �s�`�I�s����ثe��tail�`�I���᭱
            tail = newNode ; // �Ntail���w��s���s�`�I
        }
    }
    
    void deleteHead() { // �R���C���Y�`�I�C����O���� 
        if ( !isEmpty() ) {
            ListNode* temp = head ; // �Ыؤ@�ӫ��V�Y�`�I������
            head = head->next ; // ��shead���ХH���V�C���U�@�Ӹ`�I
            delete temp ; // ���񤧫e���Y�`�I���O����A�H����s���|
        } // if ( !isEmpty() )
        
    } // void deleteHead()

    void clear() { // �M����ӦC�� 
        while ( !isEmpty() ) {
            deleteHead() ;
        } // while ( !isEmpty() )
    } // void clear()
    
	void getpostfix() { // �L�X��ǹB�⦡
    	ListNode* current = head ;
    	string separator = "" ;
    	while ( current != nullptr ) {
        	cout << separator << current->value ;
        	separator = ", " ;
        	current = current->next ;
    	} // while ( current != nullptr )
    	
	} // void getpostfix()


    ~expLIST() { // �Ѻc�l�A�b����ͩR�g�������ɶi��M�z�M����귽���ާ@
        clear() ;
    }
};

class expSTACK {
private:
    ListNode* topPtr ; //���V���|�������`�I�C�Ω���@���|�����c�A�������J�]push�^�M�u�X�]pop�^�ާ@ 

public:
    expSTACK() : topPtr( nullptr ) {} // �غc�l�A��l�����O������A�ð���@�Ǫ�l�]�w�ާ@ 

    bool isEmpty() { // �ˬd���|�O�_���� 
        return topPtr == nullptr ;
    } // bool isEmpty()

    void push( char val ) { // �N�S�w��(val)���J���| 
        ListNode* newNode = new ListNode( string( 1, val ) ) ; // �Ыؤ@�ӷs��stackNode�`�I newNode�A�ñN�� val ��l�Ƭ��o�Ӹ`�I����
        newNode->next = topPtr ; // ���V��e���|�������`�I�A�����|���̤W���@�Ӹ`�I
        topPtr = newNode ; // �N topPtr ���V�s���J���`�I newNode�A�Ϩ䦨���s�����|����
    } // void push( char val )  

    char getTop() { // ���o���|��������
        if ( !isEmpty() ) {
            return topPtr->value[0] ;
        } // if ( !isEmpty() )
        return '\0';
    } // char getTop()

    void pop() {
        if ( !isEmpty() ) {
            ListNode* temp = topPtr ; // �Ыؤ@�ӫ��V�����`�I���{�ɫ��� temp
            topPtr = topPtr->next ; // ��s topPtr�A�Ϩ���V��e�����`�I���U�@�Ӹ`�I
            delete temp ; // ���� temp�A�Y�R����Ӫ������`�I�A�H����s���|
        } // if ( !isEmpty() )
    } // void pop()

    ~expSTACK() { // �Ѻc�l�A�b����ͩR�g�������ɶi��M�z�M����귽���ާ@ 
        while ( !isEmpty() ) {
            pop() ; // while ( !isEmpty() )
        } // while ( !isEmpty() ) {
    } // ~ExpStack()
};

bool isOperator( char c ) { // �禡�H�ˬd�r�ŬO�_���B��� 
    return ( c  == '+' || c == '-' || c == '*' || c == '/' ) ;
} // bool isOperator( char c )  

int getPrecedence( char c ) { // �禡�H����B��Ū��u������ 
    if ( c == '+' || c == '-' ) {
        return 1 ;
    } // if ( c == '+' || c == '-' )
	
	else if ( c == '*' || c == '/' ) {
        return 2 ;
    } // else if ( c == '*' || c == '/' )
    
    return 0;
} // int getPrecedence( char c )

void infix2Postfix( const string infix ) {  // �禡�H�N���Ǫ�ܪk�ഫ���e�Ǫ�ܪk
    expSTACK stack ;
    expLIST postfix ;

    for ( int i = 0 ; i < infix.length() ; i++ ) { // �M�����Ǫ�F�� infix
        char c = infix[i] ;
        if ( c == ' ' ) { // ���L�Ů�r�šA�~��U�@���`��
            continue ;
        } // if ( c == ' ' )
		
		else if ( c >= '0' && c <= '9' ) { // �p�G��e�r�ŬO�Ʀr�]'0' �� '9' �������r�š^�A�h�B�z�Ʀr
            string number ;               // �`��Ū���s�򪺼Ʀr�r�šA�N���̫������@�ӧ��㪺�Ʀr
            number += c ;
            while ( i + 1 < infix.size() && infix[i + 1] >= '0' && infix[i + 1] <= '9' ) {
                i++ ;
                number += infix[i] ;
            } // while ( i + 1 < infix.size() && infix[i + 1] >= '0' && infix[i + 1] <= '9' )
            
            postfix.ins( number ) ; // �N�ӼƦr�K�[�� postfix ����A��ܫ�Ǫ�F�����@����
        } // else if ( c >= '0' && c <= '9' )
		
		else if ( isOperator( c ) ) {
            while ( !stack.isEmpty() ) {
                char top = stack.getTop();
                if ( isOperator( top ) && getPrecedence( top ) >= getPrecedence( c ) ) { // �P�_���u���šA ���|�������B��Ū��u���Ťj��ε����e�B��šA
                    postfix.ins( string( 1, top ) ) ;                                   // �N�N���|�������B��żu�X�òK�[�� postfix��
                    stack.pop() ;
                } // if ( isOperator( top ) && getPrecedence( top ) >= getPrecedence( c ) ) 
				
				else {
                    break;
                } // else
                
            } // while ( !stack.isEmpty() )
            
            stack.push( c ) ;
        } // else if ( isOperator( c ) )
		
		else if ( c == '(' ) { // ���J 
            stack.push( c ) ;
        } // else if ( c == '(' )
        
		else if ( c == ')' ) {
            while (!stack.isEmpty() && stack.getTop() != '(' ) { //�u�X 
                postfix.ins(string( 1, stack.getTop() ) ) ;
                stack.pop() ;
            } // while (!stack.isEmpty() && stack.getTop() != '(')
            
            if ( !stack.isEmpty() && stack.getTop() == '(' ) { //�u�X 
                stack.pop() ;
            } // if (!stack.isEmpty() && stack.getTop() == '(')
            
        } // else if ( c == ')' )
        
    } // for ( int i = 0 ; i < infix.length() ; i++ )

    while ( !stack.isEmpty() ) {
        postfix.ins( string( 1, stack.getTop() ) ) ; // �����B������J 
        stack.pop() ;
    } //while ( !stack.isEmpty() )

    postfix.getpostfix() ;  // �L�X��ǹB�⦡
    postfix.clear() ;
} // void infix2Postfix( const string infix )


bool isExp( string& infixS ) {   
	char invalid = '\0' ;
	for ( char check : infixS ) {
		if ( check != '+' && check != '-' && check != '*' && check != '/' && check != '(' && check != ')' && !isdigit( check ) && check != ' ' ) {
			invalid = check ;
			cout << "Error 1: " << invalid << " is not a legitimate character." << endl ;
			return false ;
		}
	} // for ( char check : infixS )
	
	return true ;
} // isExp( string& infixS )  // �ˬd�C�ӲŸ������ĩ�

bool isBalanced( const string infixS ) { // 'const'��ܤ��i�ܪ��r�Ŧ�
    int count = 0 ;
    char first =  infixS[0] ;
    if ( first == ')' ) { // �P�_�Ĥ@�Ӧr�ŬO�_��'(' 
    	cout << "Error 2: there is one extra open parenthesis." << endl ;
		return false ;
	} // if ( first == ')' )
	
	for ( char check : infixS ) {
		if ( check == '(' ) {
			count++ ;
		} // if ( check == '(' )
		
		else if ( check == ')' ) {
			count++ ;
		} // else if ( check == ')' )
		
	} // for ( char check : infixS )
	
	if ( count % 2 != 0 ) {
		cout << "Error 2: there is one extra open parenthesis." << endl ;
		return false ;
	}
	
	return true ;
	
} // isBalanced( const string infixS ) �ˬd�A���O�_���Ŧ���



bool isLegalInfix( const string infixS ) { // �O�_�ŦX���ǹB�⦡ 
    int parenContentLength = 0 ;  //�p��A���������e������( �B��Ÿ��P�Ʀr ) 
    int count = 0 ; // �p��A���ƶq 
    bool pcount = true ; // �A���O�_���s 
    bool inParenthesis = false ; // �O�_�b�A���� 
    bool prevIsDigit = false ;  // �e�@�Ӧr�ŬO�_�O�Ʀr 
    bool prevIsOperator = false ; // �e�@�Ӧr�ŬO�_�O�B���
	bool newDigit = false ;  // �O�_�J��F�s�@�A�����Ʀr

    for ( char c : infixS ) {
        if ( c == '(' ) {
            inParenthesis = true ;
            prevIsOperator = false ;
            count++ ;
        } // if ( c == '(' )
        
        else if ( c == ')' ) {
            inParenthesis = false ;
            if ( !prevIsDigit ) {
                return false ; 
                count++ ;
            } // if ( !prevIsDigit ) 

            prevIsDigit = true ;
            prevIsOperator = false ;
            newDigit = false ;
        } // else if ( c == ')' )
        
        else if ( inParenthesis ) {
            if ( isdigit( c ) ) {
            	newDigit = true ;
                prevIsDigit = true ;
                prevIsOperator = false ;
            } // if ( isdigit( c ) )
			
			else if ( c == '+' || c == '-' || c == '*' || c == '/' ) {
                if ( prevIsOperator ) {
                    return false ;  
                } // if ( prevIsOperator )
                
                else if ( !newDigit ) { // �A���᪽�����Ÿ� 
                	return false ;
				} // else if ( !newDigit )
                
                prevIsDigit = false ;
                prevIsOperator = true ;
            } // else if ( c == '+' || c == '-' || c == '*' || c == '/' )
            
			else {
                return false ; 
            } // else
            
        } // else if ( inParenthesis )
        
    } // for ( char c : infixS )
    
    if ( count == 0 ) {
    	pcount = false ;
	} // if ( count == 0 )

    if ( ( prevIsOperator || !prevIsDigit ) && pcount ) {
        return false ;  
    } // if ( prevIsOperator || !prevIsDigit && count!= 0 )

    return true ;
} // bool isLegalInfix( const string infixS )




bool isLegal( const string infixS ) { // 'const'��ܤ��i�ܪ��r�Ŧ�
	int OperCount = 0 ; // �p��B��� 
	int NumCount = 0 ; // �p��Ʀr 
	bool isinfix = isLegalInfix( infixS ) ; // �O�_�����ǹB�⦡ 
	bool isoperator = false ; // �B��ſ��~ 
	bool isnum = false ; // �Ʀr���~ 

    char prevC = ' ' ;
	
	for ( int i = 0 ; i < infixS.length() ; ++i ) {
		if ( isdigit( infixS[i] ) ) {
			NumCount++ ;
			while ( i < infixS.length() && isdigit( infixS[i] ) ) {
				i++ ;
			} // while ( i < infixS.length() && isdigit( infixS[i] ) )
			
			i-- ;
		} // if ( isdigit( infixS[i] ) )
		
		else if ( infixS[i] == '+' || infixS[i] == '-' || infixS[i] == '*' || infixS[i] == '/' ) {
			OperCount++ ;
		} // else if ( infixS[i] == '+' || infixS[i] == '-' || infixS[i] == '*' || infixS[i] == '/')
		
	} // for ( int i = 0 ; i < infixS.length() ; ++i )
	
	if ( ( NumCount <= OperCount || NumCount != OperCount + 1  ) ) {
		if ( NumCount <= OperCount ) {
			isoperator = true ;
		} // if ( NumCount <= OperCount )
		
		else if ( NumCount != OperCount + 1 ) {
			isnum = true ;
		} // else if ( NumCount != OperCount + 1 )
		
	} // if ( NumCount <= OperCount || NumCount != OperCount + 1 )
	
	
	if ( !isinfix && !isoperator && !isnum ) {
		cout << "Error 3: it is not infix in the parenthesis." << endl ;
		return false ;
	} // if ( !isinfix && !isoperator && !isnum )
	
	if ( isoperator ) {
		if ( !isinfix ) 
			cout << "Error 3: it is not infix in the parenthesis." << endl ;
		else
			cout << "Error 3: there is one extra operator." << endl ;
			return false ;
	} // if ( NumCount <= OperCount )
		
	else if ( isnum ) {
		cout << "Error 3: there is one extra operand." << endl ;
		return false ;
	} // else if ( isnum )
	

	return true ;
} // isLegal( const string infixS ) �ˬd�O�_�O���Ī�F


int main() {
	int command = 0 ;
	do {
		string infixS ;
		
		cout << "\n" ;
		cout << "* Arithmetic Expression Evaluator *\n" ;
		cout << "* 0. QUIT                         *\n" ;
		cout << "* 1. Infix2postfix Transformation *\n" ;
		cout << "***********************************\n" ;
		cout << "Input a choice(0, 1): " ;
		cin >> command ;
		cin.ignore( MAX_LEN, '\n' ) ; // �M���w�İϤ�������š]'\n'�^�Ψ�L�i�ण�ݭn���r��
		switch (command) {
			case 0:
			 	break;
			case 1:
				cout << endl << "Input an infix expression: " ;
				getline( cin, infixS ) ;
				if ( isExp( infixS ) && isBalanced( infixS )  && isLegal( infixS ) ) {
					cout << "It is a legitimate infix expression." << endl ; 
					cout << "Postfix expression: ";
					infix2Postfix( infixS ) ;
					cout << "\n" ;				
				} // if ( isExp( infixS ) && isBalanced( infixS )  && isLegal( infixS ) )
				  // �ˬd�C�ӲŸ��F�ˬd�A���O�_���Ŧ��ġF�ˬd�O�_�O���Ī�F  

				break ;
				
			default: cout << endl << "Command does not exist!" << endl ;

		} // swith( command ) 
	} while ( command != 0 ) ;
	
	system("pause") ; // �Ȱ��{�ǰ���A���ݫ��UEnter��
	return 0 ;
} // main()


