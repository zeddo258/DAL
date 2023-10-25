// 11127213	 ­â¹©°a 

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// Macros
# define EXPRESSION_SIZE 200                                  // input string maximum size
# define IsDigit( ch )  ( ch >= '0' && ch <= '9' )            // if the character is a number
# define IsOperator( ch )  ( ch == '+' || ch == '-' ||  \
                             ch == '*' || ch == '/' )         // it is operator or not
# define IsBracket( ch )  ( ch == '(' || ch == ')' )          // is parentheses or not


int GetNumber( const char* str, int* i );                     // This function will be
                                                              // elaborated later
                                                              
int stringToInt( char* str );

typedef struct Node Node;
typedef Node* NodePtr;
typedef struct StackItem StackItem;
typedef StackItem* StackItemPtr;


enum Type {             // This will distinguish the content of the node.
	
	OPERAND = 0,
	OPERATOR = 1,
	PAREN = 2           // brackets
	
};

enum Precedence {       // Put it in the stack to check for precedence
	
	// LPAREN has the hightest precedence, MULTIPLY and DIVISION came second, and the last ones,
    // PLUS and MINUS. Following arithmetic rules.
	
	PLUS = 0,
	MINUS = 0,
	MULTIPLY = 1,
	DIVISION = 1,
	LPAREN = 2
	
};

enum Operators {       // Used for copying Node's data to the postfix node
	
	plus = 10,
	minus = 20,
	multiply = 30,
	division = 40,
	lparen = 50
	
};

struct Node {
	
	Type type;
	char* data;
	struct Node* next;
	
};

void InitialNode( Node* node )  {            // Initialize the Node
	
	node -> type = OPERAND;
	node -> next = NULL;
	node -> data = NULL;
	
}

void PrintList( Node* head );               // print the linked list

struct StackItem  {
	
	Precedence priority;            // Determine the precedence of operator in the stack
	Operators ops;                  // What is the operator
	float number;
	struct StackItem* next;  
	
};

StackItem* CreateStack()  {        // Create a stack item
	
	StackItem* head = ( StackItem* )calloc( 1, sizeof( StackItem ) );
	head -> ops = plus;
	head -> next = NULL;
	head -> number = 0;
	return head;
	
}

void setItem( StackItem* item, Precedence priority )  {        // Set the stack item's priority
	
	item -> priority = priority;
	
}

void pushItem( StackItemPtr* head, StackItem* item )  {        // Push
	
	item -> next = ( *head );
	*head = item;
	
}

bool IsEmpty( StackItem* head )  {                             // If the stack is empty, return true
	                                                           // else return false
	if ( !head )   return true;
	return false;
	
}

StackItem* popItem( StackItemPtr* head )  {                    // Pop
	
	if ( IsEmpty( *head ) )  {
	
	    printf( "Error! Stack is empty!\n" );
	    return NULL;
	    
    }
	    
	StackItem* temp = *head;
	( *head ) = ( *head ) -> next;
	temp -> next = NULL;
	
	return temp;
	
}

// setNode function copy the corresponding node information onto stack item
// node, the initialized node
// str_len, the length of the data
// str, the data that copied to node -> data

void setNode( Node* node, size_t str_len, const char* str )  { 
	
	node -> data = ( char* )calloc( str_len + 1, sizeof( char ) );
	memcpy( node -> data, str, str_len );
	node -> data[str_len] = '\0';
	node -> next = NULL;
	
}

void labelStack( Node* node, StackItem* top )  {          // copy the corresponding node data to the stack item
	
	top -> number = 0;
	
	if ( strcmp( node -> data, "+" ) == 0 )  {    // if the data is "+" 
	
	    top -> priority = PLUS;          // stack priority set to PLUS
	    top -> ops = plus;               // the exact operator is "+". ( Later use for creating the node )
	    
    }
	    
	else if ( strcmp( node -> data, "-" ) == 0 )  {
	
	    top -> priority = MINUS;
	    top -> ops = minus;
	    
    }
	    
	else if ( strcmp( node -> data, "*" ) == 0 )  {

	    top -> priority = MULTIPLY;
	    top -> ops = multiply;
	    
    }
	    
	else if ( strcmp( node -> data, "/" ) == 0 )  {
	
	    top -> priority = DIVISION;
	    top -> ops = division;
	    
    }
	    
	else if ( strcmp( node -> data, "(" ) == 0 )  {
	
	    top -> priority = LPAREN;
	    top -> ops = lparen;
	
    }
	    
    else
        top -> number = stringToInt( node -> data );
	
}

Node* CreateNode( StackItem* temp )  {                  // Create a node that based on the popped item
	
	Node* node = ( Node* )calloc( 1, sizeof( Node ) );  // allocate a node
	InitialNode( node );   // Initialize it
	
	if ( temp -> ops == plus )    // set the node -> data to "+", if the temp -> ops is "+"
	    setNode( node, 1, "+" );
	else if ( temp -> ops == minus )
	    setNode( node, 1, "-" );
	else if ( temp -> ops == multiply )
	    setNode( node, 1, "*" );
	else if ( temp -> ops == division )
	    setNode( node, 1, "/" );
	else 
	    setNode( node, 1, "(" );
	    
	return node;
	    
}

char* intToString( int number )  {
	
	int digitCount = 0, saveNumber = number;
	
	for( digitCount = 0 ; number / 10 ; number /= 10 )
	    digitCount++;
	    
	char* str_num = ( char* )calloc( digitCount + 2, sizeof( char ) );
	sprintf( str_num, "%d", saveNumber );
	
	return str_num;
	
}

void freeStackItem( StackItem* item )  {
	    
	free( item );

}

void FreeStack( StackItem* top )  {
	
	StackItem* temp;
	
    while ( !IsEmpty( top ) )  {
    	
    	temp = popItem( &top );
    	// if ( temp -> number )  free( temp -> number );
    	free( temp );
    	
	}
	
}

bool calculatePostfix( Node* head )  {
	
	// printf( "Enter calculatePostfix function\n" );
	
	head = head -> next;
	StackItem* top = NULL;
	StackItem* temp, *temp1, *temp2;
	float operand1, operand2, result;
	
	for ( head = head ; head ; head = head -> next )  {
		
		temp = CreateStack();
		
		// printf( "head type : %d\n", head -> type );	
		
		if ( head -> type == OPERAND )
		    labelStack( head, temp );
			
		else  {
			
			// printf( "The node type is OPERATOR\n" );
			temp1 = popItem( &top );
			temp2 = popItem( &top );
			
			// printf( "Items popped\n" );
			
			operand1 = temp1 -> number;
			operand2 = temp2 -> number;
			
			// printf( "stringToInt convert success\n" );
			// printf( "operand1 : %d\n", operand1 );
			// printf( "operand2 : %d\n", operand2 );
			
			if ( !strcmp( head -> data, "+" ) )
			    result = operand2 + operand1;
			else if ( !strcmp( head -> data, "-" ) )
			    result = operand2 - operand1;
			else if ( !strcmp( head -> data, "*" ) )
			    result = operand2 * operand1;
			else if ( !strcmp( head -> data, "/" ) ) {
				
				if ( !operand1 )  {
				
				    printf( "Error 3: division by zero\n" );
			        freeStackItem( temp1 );
			        freeStackItem( temp2 );
                    FreeStack( top );
				    return false;
				
			    }
			    
			    result = operand2 / operand1;
				
			}
			
            // printf( "result : %d\n", result );
			temp -> number = result;
			freeStackItem( temp1 );
			freeStackItem( temp2 );
			
		}
		
		pushItem( &top, temp );
 
	}
	
	return true;
	
}


Node* reverseList( Node* head )  {

    if ( !head || !( head -> next ) )	
		return head;
			
	Node* reverse_head = reverseList( head -> next );
	head -> next -> next  = head;
	head -> next = NULL;
	return reverse_head;
	
}

void prefixPreprocess( Node* reverse_head )  {
	
	while ( reverse_head -> next -> next )  {
		
		if ( !strcmp( reverse_head -> data, "(" ) )
		    strcpy( reverse_head -> data, ")" );
		    
		else if ( !strcmp( reverse_head -> data, ")" ) )
		    strcpy( reverse_head -> data, "(" );
		    
		reverse_head = reverse_head -> next;
		
	}
	
	Node* temp = reverse_head -> next;
	reverse_head -> next = NULL;
	free( temp );
	
}

Node* ToPrefix( Node* head )  {
	
	Node* prefix_head = ( Node* )calloc( 1, sizeof( Node ) );   // create head
	Node* prefix_traverse = prefix_head;                       // used to traverse postfix linked list
	InitialNode( prefix_traverse );
	StackItem* top = NULL;
	StackItem* item;
	StackItem* temp;
	
	for ( head = head ; head ; head = head -> next )  {    // traverse through the infix's nodes
		
		if ( head -> type == OPERAND )  {    // If the node is a number
			
			prefix_traverse -> next = ( Node* )calloc( 1, sizeof( Node ) );  // create a node
			prefix_traverse = prefix_traverse -> next;
			setNode( prefix_traverse, strlen( head -> data ), head -> data ); // and copy it to postfix node
			prefix_traverse -> type = OPERAND;
			
		} 
		
		else if ( head -> type == OPERATOR )  {    // If the node contains a operator
			
			item = CreateStack();          // create a stack item
			labelStack( head, item );      // label the stack item
			 
			if ( IsEmpty( top ) )          // If empty, just push it
			    pushItem( &top, item );
				
			// If the precedence of the top is less than the current item, push onto the stack
				
			else if ( top -> priority <= item -> priority )
			    pushItem( &top, item );
		    
		    // If the precedence of the top is greater or equal to the current item, pop it
		    // until this condition is not met
		    
		    else if ( top -> priority > item -> priority )  {
		    	
		    	while ( !IsEmpty( top ) && top -> priority > item -> priority &&
				        top -> ops != lparen )  {
		    		
		    		temp = popItem( &top );
		    		prefix_traverse -> next = CreateNode( temp );
		    		prefix_traverse = prefix_traverse -> next;
		    		prefix_traverse -> type = OPERATOR;
		    		free( temp );
		    		
				}
				
				pushItem( &top, item );  // push the current item
		    	
			}
			
		}
		
		else if ( head -> type == PAREN )  {               // left parentheses
				
			// If the node is right parentheses, keep popping until ecountered left parentheses	
			
			if ( strcmp( head -> data, ")" ) == 0 )  {     
				
			    while ( !IsEmpty( top ) && top -> ops != lparen )  {
				 	
				    temp = popItem( &top );
		    	    prefix_traverse -> next = CreateNode( temp );
		    	    prefix_traverse = prefix_traverse -> next;
		    		prefix_traverse -> type = PAREN;
		    	    free( temp );
										
			    }
				
			    temp = popItem( &top );   // pop the left parentheses from the stack
			    free( temp );
			    
		    }
		    
		    else  {              // left parentheses, just push it
                
                item = CreateStack();
                labelStack( head, item );
		        pushItem( &top, item );
		        
		    }
				
		}	
			
	}
	
	// Clear out the stack when finishing traverse the infix list
	
	while ( top )  {
		
		temp = popItem( &top );
	    prefix_traverse -> next = CreateNode( temp );
	    prefix_traverse = prefix_traverse -> next;
	    prefix_traverse -> type = OPERATOR;
	    free( temp );
		
	}
	
	return prefix_head;    // return the postfix head	
	
}

Node* ToPostfix( Node* head )  {                          // Convert the infix linked list to postfix
	
	Node* postfix_head = ( Node* )calloc( 1, sizeof( Node ) );   // create head
	Node* postfix_traverse = postfix_head;                       // used to traverse postfix linked list
	InitialNode( postfix_traverse );
	StackItem* top = NULL;
	StackItem* item;
	StackItem* temp;
	
	for ( head = head -> next; head ; head = head -> next )  {    // traverse through the infix's nodes
		
		if ( head -> type == OPERAND )  {    // If the node is a number
			
			postfix_traverse -> next = ( Node* )calloc( 1, sizeof( Node ) );  // create a node
			postfix_traverse = postfix_traverse -> next;
			setNode( postfix_traverse, strlen( head -> data ), head -> data ); // and copy it to postfix node
		    postfix_traverse -> type = OPERAND;
			
		} 
		
		else if ( head -> type == OPERATOR )  {    // If the node contains a operator
			
			item = CreateStack();          // create a stack item
			labelStack( head, item );      // label the stack item
			 
			if ( IsEmpty( top ) )          // If empty, just push it
			    pushItem( &top, item );
				
			// If the precedence of the top is less than the current item, push onto the stack
				
			else if ( top -> priority < item -> priority )
			    pushItem( &top, item );
		    
		    // If the precedence of the top is greater or equal to the current item, pop it
		    // until this condition is not met
		    
		    else if ( top -> priority >= item -> priority )  {
		    	
		    	while ( !IsEmpty( top ) && top -> priority >= item -> priority &&
				        top -> ops != lparen )  {
		    		
		    		temp = popItem( &top );
		    		postfix_traverse -> next = CreateNode( temp );
		    		postfix_traverse = postfix_traverse -> next;
					postfix_traverse -> type = OPERATOR;
		    		free( temp );
		    		
				}
				
				pushItem( &top, item );  // push the current item
		    	
			}
			
		}
		
		else if ( head -> type == PAREN )  {               // left parentheses
				
			// If the node is right parentheses, keep popping until ecountered left parentheses	
			
			if ( strcmp( head -> data, ")" ) == 0 )  {     
				
			    while ( !IsEmpty( top ) && top -> ops != lparen )  {
				 	
				    temp = popItem( &top );
		    	    postfix_traverse -> next = CreateNode( temp );
		    	    postfix_traverse = postfix_traverse -> next;
					postfix_traverse -> type = OPERATOR;
		    	    free( temp );
										
			    }
				
			    temp = popItem( &top );   // pop the left parentheses from the stack
			    free( temp );
			    
		    }
		    
		    else  {              // left parentheses, just push it
                
                item = CreateStack();
                labelStack( head, item );
		        pushItem( &top, item );
		        
		    }
				
		}	
			
	}
	
	// Clear out the stack when finishing traverse the infix list
	
	while ( top )  {
		
		temp = popItem( &top );
	    postfix_traverse -> next = CreateNode( temp );
	    postfix_traverse = postfix_traverse -> next;
	    postfix_traverse -> type = OPERATOR;
	    free( temp );
		
	}
	
	return postfix_head;    // return the postfix head
	
}

NodePtr makeList( const char* str )  {    //  convert a valid infix into a linked list
	
	Node* head = ( Node* )malloc( 1 * sizeof( Node ) );
	Node* traverse = head;
	InitialNode( traverse );
	
	int i, j;
	int saveI, len;
	
	for ( i = 0 ; i < strlen( str ) ; i++ )  {      // loop through by characters
		
		traverse -> next = ( Node* )malloc( 1 * sizeof( Node ) );   // create the node 
		traverse = traverse -> next;
		InitialNode( traverse );    // initialize it
		
		if ( IsDigit( str[i] ) )  {   // if the character is a digit
			
			saveI = i;     // save the current position of i
			
			len = GetNumber( str, &i );  // The result of GetNumber include the NULL-terminator
			
			i = saveI;
			traverse -> data = ( char* )calloc( len, sizeof( char ) );   // get the number length and malloc it
			traverse -> type = OPERAND;   // the type is number ( operand )
			
		    for ( j = i ; ( j < strlen( str ) && IsDigit( str[j] ) ) ; j++ )
		    	strncat( traverse -> data, &str[j], 1 );   // adding the digits to data
		    
		    i = j - 1;   // j will stop at non-digit, so need to minus one
			
		}
		
		else if ( IsOperator( str[i] ) )  {    // if the character is operator
			
			traverse -> data = ( char* )calloc( 1, sizeof( char ) );
			traverse -> type = OPERATOR;
			strncat( traverse -> data, &str[i], 1 );
			
		}
		
		else {    // parenthese
			
			traverse -> data = ( char* )calloc( 1, sizeof( char ) );
			traverse -> type = PAREN;
			strncat( traverse -> data, &str[i], 1 );			
			
		}
		
		traverse -> next = NULL;

	}
	
	return head;    //  return the infix head
	
}

int stringToInt( char* str )  {    //  turn string to int, used for detecting division by zero error
	
	int i = 0, result = 0;
	
	for ( i = 0 ; i < strlen( str ) ; i++ ) 
	    result = result * 10 + ( str[i] - '0' );
	    
	return result;
	
}

void PrintList( Node* head )  {     // print the linked list
	
	head = head -> next;
	
	printf( "Postfix expression: %s", head -> data );
	
	while ( head )  {
		
		if ( head -> next )
		    printf( "," );
		    
		head = head -> next;
		
		if ( head )
		    printf( " %s", head -> data );
		
	}
	
	printf( "\n" );
	
}

void PrintPrefixList( Node* head )  {
	
	printf( "Prefix expression: %s", head -> data );
	
	while ( head -> next -> next )  {
		
		if ( head -> next )
		    printf( "," );
		    
		head = head -> next;
		
		if ( head )
		    printf( " %s", head -> data );
		
	}
	
	printf( "\n" );	
	
}

void FreeList( Node* head )  {    // free the list
	
	Node* temp;
	
	while ( head )  {
		
		temp = head;
		head = head -> next;
		if ( temp -> data ) free( temp -> data );
		free( temp );
		
	}
	
}

bool InTable( char ch )  {    // if the character is valid
	
	bool result = false;
	
	if ( IsDigit( ch ) || IsOperator( ch ) ||
	     IsBracket( ch ) || ch == ' ' )  result = true;
	
	return result;
	
}

bool validString( const char* str )  {     // check the whole string if containing invalid character
	
	int i = 0;
	
	for ( i = 0 ; i < strlen( str ) ; i++ )  {

	    if ( !InTable( str[i] ) )  {
	    	
	    	printf( "Error 1: %c is not a legitimate character.\n", str[i] );
	    	return false;
	    	
		}
		
    }

    return true;
	
}

bool bracketInPair( const char* str )  {       // check if the parentheses are in pairs
	
	int i = 0, count = 0;
	
	for ( i = 0 ; i < strlen( str ) ; i++ )  {
	
	    if ( str[i] == '(' )  count++;
	    
	    else if ( str[i] == ')' )  count--;
	    
	    if ( count < 0 )  break;            // close parentheses appear without any open parentheses
	    
    }
	    
    if ( count != 0 ) {
    	
    	if ( count > 0 )
    	    printf( "Error 2: there is one extra open parenthesis.\n" );
    	
    	else
    	    printf( "Error 2: there is one extra close parenthesis.\n" );
    	    
    	return false;
    	  
	}
	
	return true;
	
}

int GetNumber( const char* str, int* i )  {      // This function will return the length of number
	
	if ( IsBracket( str[*i] ) || IsOperator( str[*i] ) || str[*i] == '\0' )  return 1;
		
	( *i )++;
	return 1 + GetNumber( str, i );	

	
}

bool IsInfix( const char* str, int i )  {       // check if the string is a valid infix
	
	bool operandNext = true;           // valid infix must follow <operand> <operator> <operand>
	bool haveNumber = false;
	bool paren_problem = false;        // indicate the cases of number + '('
	int parenCount = 0;                // check if the error is in the parentheses or not
 
 	
	for ( i = 0 ; i < strlen( str ) ; i++ )  {
		
	    if ( str[i] == '(' )  {
			
			if ( !operandNext )        // if "number + (" , eg. 12 ( 5 + 6 )
                paren_problem = true;  // turn this error on
			
			haveNumber = false;     // check for empty parenthese, ()
			operandNext = true;     // after open parentheses, must be a operand
            parenCount++;           // add the paren counter, this means one layer of parenthese
		
	    }
		
		else if ( str[i] == ')' )  {  
			
			parenCount--;    // minus the counter
			
			if ( operandNext )  {    // eg. 1 + ( 5 + )
				
				printf( "Error 3: it is not infix in the parentheses.\n" );
				return false;
				 
			}
			
		}
		
		else if ( operandNext )  {    // the number should be expected
			
			if ( str[i] == '(' )   continue;
			
			else if ( IsDigit( str[i] ) && paren_problem )  {    // this means after open parenthese, there is a operand
				
				printf( "Error 3: there is one extra operand.\n" );
				return false;
				
			}

            else if ( IsDigit( str[i] ) )  { 
        	
        	    GetNumber( str, &i );    // read all the remainging digits
        	    i--;
        	    haveNumber = true;      // used for parentheses
        	    operandNext = false;    // operator next
        	
	        }
	        
	        else  {
	            
	            if ( !haveNumber && parenCount )     // ()
	                printf( "Error 3: it is not infix in the parentheses.\n" );
	                
	            else
	                printf( "Error 3: there is one extra operator.\n" );  
					          
	        	return false;
	        	
			}
	    
	    }
	    
	    else if ( !operandNext )  {    // if the next should be operator
	    	
	    	if ( !IsOperator( str[i] ) ) {   
	    	
	    		printf( "Error 3: there is one extra operand.\n" );
	    		return false;
	    		
			}
			
			operandNext = true;
	     	
		}
	 	
	}
	
	if ( operandNext ) {     // if the last endded with operator
		
		printf( "Error 3: there is one extra operator.\n" ); 
		return false;
		
	}
	
	return true;
	
}

bool IsValidInfix( const char* str )  {
	
	int i = 0, error = 0;
	
	if ( validString( str ) && bracketInPair( str ) && IsInfix( str, i ) )
	    return true;
	  
	return false;
	
}

int main()  {

    int command = 0, i = 0;
    char ch = 'A';
	char trash;
	char* str = ( char* )malloc( EXPRESSION_SIZE );
	
	do  {
	
	    printf( "\n* Arithmetic Expression Evaluator *" );
        printf( "\n* 0. QUIT                         *" );
        printf( "\n* 1. Infix2postfix Transformation *" );
        printf( "\n***********************************" );
	
	    printf( "\nInput a choice(0, 1): " );
	    scanf( "%d", &command );
	
	    if ( command == 0 || command == 1 )  {
	    	
	    	if ( !command )  break;
	
	        else  {

                i = 0;
                printf( "\nInput an infix expression: " );
                scanf( "%c %c", &trash, &ch );
 
	            while ( ch != '\n' )  {     // keep reading until newline character
	    	
	    	        if ( ch != ' ' )    // skip the whitespace
	        	        str[i++] = ch;
	    	    
	        	    scanf( "%c", &ch );
	    	
		        }
		
		        str[i] = '\0';
		
	            if ( IsValidInfix( str ) )  {    // if it is a valid infix expression
				
	                Node* head = makeList( str );   // make an infix linked list
	                
	                if ( command == 1 ) {  // if there are not division by zero

	                    Node* postfix_head = ToPostfix( head );   // create a postfix linked list
	                    if ( calculatePostfix( postfix_head ) )
	                        printf( "It is a legitimate infix expression.\n" );
	                    PrintList( postfix_head );   // print the list
	                    FreeList( postfix_head );   // free it
	                        
	                }
	                
	                FreeList( head );
	                
	            }
	    
	            memset( str, 0, sizeof( str ) );   //  reset the string
	    
            }
    
        }
        
        else printf( "\nCommand does not exist!\n" );
        
    } while ( command );
    
    free( str );
	
}
