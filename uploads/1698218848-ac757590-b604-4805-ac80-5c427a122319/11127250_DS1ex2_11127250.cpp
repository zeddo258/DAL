// 11127250 陳銘展
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <cstdlib>

using namespace std;

typedef char Str255[255] ;                                                                          // define "string which have max 256 char" is "Str255"  

struct Node {                                                                                       // define a struct name Node
  char ch ;                                                                                         // define every char ( but not have ' ' and '\n' ) of formula name ch
  int type ;                                                                                        // define this ch is what type name type ; a 'number' = 1 ; a 'calculating sign' = 2 ; a '(' = 3 ; a ')' = 4 ; a 'the others' = 5
  Str255 str ;                                                                                      // define every str which is combination to formula name str
  int strtype ;                                                                                     // define this str is which type name strtype ; "number" = 1 ; "+" , "-" = 2 ; "*" , "/" = 3 ; "(" = 4 ; ")" = 5  
  int layer ;                                                                                       // define this str in which layer name layer
  Node * next ;                                                                                     // define a pointer of Node name next
} ;

typedef Node * NodePtr ;                                                                            // define "Node *" is "NodePtr" 
char gchar = '\n' ;                                                                                 // define a '\n' name gchar is global

//--------------------------------------------------------------------------- Mission1 use function ---------------------------------------------------------------------------

/*

CheckIsError1 function is check formula whether is the first type of error 
if true then this formula is the first type of error
if false then this formula is not the first type of error
the first type of error only one case ->
1. Error 1: ? is not a legitimate character.

*/

bool CheckIsError1( NodePtr head ) {
  while ( head != NULL ) {                                                                          // until head point NULL 
    if ( head->type == 5 ) {                                                                        // if head point a node which is not a 'number' , 'calculating sign' , '(' , ')' ; ex: 35^(40+60)
      printf( "Error 1: %c is not a legitimate character.\n", head->ch ) ;  
      return true ;                                                                                 // this formula is error1
    } // if ( head->type == 5 )
    
    head = head->next ;                                                                             // let head point a next node 
  } // while ( head != NULL )
  
  return false ;                                                                                    // this formula is not error1
} // CheckIsError1()

/*

CheckIsError2 function is check formula whether is the second type of error
if true then this formula is the second type of error
if false then this formula is not the second type of error
the second type of error have two case ->
1. Error 2: there is one extra open parenthesis.
2. Error 2: there is one extra close parenthesis.

*/

bool CheckIsError2( NodePtr head ) {
  int open = 0 ;                                                                                    // define '(' num name open , initial value is 0
  int close = 0 ;                                                                                   // define ')' num name close , initial value is 0
  bool firstclose = false ;                                                                         // define whether is a first ')' before a first '(' name firstclose , initial value is false
  while ( head != NULL ) {                                                                          // until head point NULL
    if ( head->type == 3 ) {                                                                        // if head point a node which is a '('
      open = open + 1 ;                                                                             // '(' num + 1
    } // if ( head->type == 3 )
    else if ( head->type == 4 ) {                                                                   // if head point a node which is a ')'
      close = close + 1 ;                                                                           // ')' num + 1
      if ( open == 0 ) {                                                                            // if a first ')' before a first '('  
        firstclose = true ;                                                                         // this formula is a first ')' before a first '(' so firstclose is true
      } // if ( open == 0 ) 
    } // else if ( head->type == 4 )
    
    head = head->next ;                                                                             // let head point a next node
  } // while ( head != NULL )
  
  if ( open < close || firstclose == true ) {                                                       // if '(' num less than ')' num or a first ')' before a first '(' ; ex: (35+40)+60) or 35)+(40+60
    printf( "Error 2: there is one extra close parenthesis.\n" ) ;
    return true ;                                                                                   // this formula is error2
  } // if ( open < close || firstclose == true )
  else if ( open > close ) {                                                                        // if '(' num more than ')' num ; ex: ((35+40)+60 
    printf( "Error 2: there is one extra open parenthesis.\n" ) ;
    return true ;                                                                                   // this formula is error2
  } // else if ( open > close )
  
  return false ;                                                                                    // this formula is not error2
} // CheckIsError2()

/*

CheckIsError3 function is check formula whether is the third type of error
if true then this formula is the third type of error
if false then this formula is not the third type of error
the third type of error have three case ->
1. Error 3: there is one extra operand.
2. Error 3: there is one extra operator.
3. Error 3: it is not infix in the parentheses.

*/

bool CheckIsError3( NodePtr head ) {
  NodePtr temp = head ;                                                                             // define a pointer of Node name temp point which head point ; temp is use to point a first node until a last node
  NodePtr prev = head ;                                                                             // define a pointer of Node name prev point which head point ; prev next point is always temp point when head and temp point not a same node  
  while ( temp != NULL ) {                                                                          // until temp point NULL 
    if ( temp->type == 1 ) {                                                                        // if temp point a node which is a 'number'
      if ( temp == head ) {                                                                         // if temp point at a first node
        if ( temp->next->type == 3 ) {                                                              // if temp next point a node which is a '(' ; ex: 3(40+60) 
          printf( "Error 3: there is one extra operand.\n" ) ;
          return true ;                                                                             // this formula is error3
        } // if ( temp->next->type == 3 )
      } // if ( temp == head )
      else if ( temp->next == NULL ) {                                                              // if temp point at a last node
        if ( prev->type == 4 ) {                                                                    // if prev point a node which is a ')' ; ex: (40+60)3
          printf( "Error 3: there is one extra operand.\n" ) ;
          return true ;                                                                             // this formula is error3
        } // if ( prev->type == 4 )
      } // else if ( temp->next == NULL )
      else {                                                                                        // if temp point not at a first and last node  
        if ( prev->type == 4 || temp->next->type == 3 ) {                                           // if prev point a node which is a ')' or temp next point a node which is a '(' ; ex: (35+40)7+60 or 35+7(40+60) 
          printf( "Error 3: there is one extra operand.\n" ) ;
          return true ;                                                                             // this formula is error3
        } // if ( prev->type == 4 and temp->next->type == 3 )
      } // else
    } // if ( temp->type == 1 )
    else if ( temp->type == 2 ) {                                                                   // if temp point a node which is a 'calculating sign' 
      if ( temp == head ) {                                                                         // if temp point at a first node
        if ( temp->type == 2 ) {                                                                    // if temp point a node which is a 'calculating sign' ; ex: +35+(40+60)
          printf( "Error 3: there is one extra operator.\n" ) ;
          return true ;                                                                             // this formula is error3
        } // ( temp->type == 2 )
      } // if ( temp == head )
      else if ( temp->next == NULL ) {                                                              // if temp point at a last node
        if ( temp->type == 2 ) {                                                                    // if temp point a node which is a 'calculating sign' ; ex: 35+(40+60)+
          printf( "Error 3: there is one extra operator.\n" ) ;
          return true ;                                                                             // this formula is error3
        } // ( temp->type == 2 )  
      } // else if ( temp->next == NULL )
      else {                                                                                        // if temp point not at a first and last node 
        if ( prev->type == 2 || temp->next->type == 2 ) {                                           // if prev point a node which is a 'calculating sign' or temp next point a node which is a 'calculating sign' ; ex: 35++(40+60)  
          printf( "Error 3: there is one extra operator.\n" ) ;
          return true ;                                                                             // this formula is error3
        } // if ( prev->type == 2 || temp->next->type == 2 )
        else if ( prev->type == 3 || temp->next->type == 4 ) {                                      // if prev point a node which is a '(' or temp next point a node which is a ')' ; ex: (+35+40)+60 or (35+40+)+60 
          printf( "Error 3: it is not infix in the parentheses.\n" ) ;
          return true ;                                                                             // this formula is error3
        } // else if ( prev->type == 3 || temp->next->type == 4 )
      } // else
    } // else if ( temp->type == 2 )  
    else if ( temp->type == 3 ) {                                                                   // if temp point a node which is a '('  
      if ( temp == head ) {                                                                         // if temp point at a first node
        if ( temp->next->type == 2 || temp->next->type == 4 ) {                                     // if temp next point a node which is a 'calculating sign' or a ')' ; ex: (+35+40)+60 or ()+35+40+60   
          printf( "Error 3: it is not infix in the parentheses.\n" ) ;
          return true ;                                                                             // this formula is error3
        } // if ( temp->next->type == 2 || temp->next->type == 4 )
      } // if ( temp == head )
      else if ( temp->next == NULL ) {                                                              // if temp point at a last node ( no this case because this is error2 )
      } // else if ( temp->next == NULL )
      else {                                                                                        // if temp point not at a first and last node 
        if ( prev->type == 1 ) {                                                                    // if prev point a node which is 'number' ; ex: 35+7(40+60) 
          printf( "Error 3: there is one extra operand.\n" ) ;
          return true ;                                                                             // this formula is error3
        } // if ( prev->type == 1 )
        else if ( temp->next->type == 2 || temp->next->type == 4 ) {                                // if temp next point a node which is a 'calculating sign' or a ')' ; ex: 35+(+40+60) or 35+()+40+60  
          printf( "Error 3: it is not infix in the parentheses.\n" ) ;
          return true ;                                                                             // this formula is error3
        } // else if ( temp->next->type == 2 || temp->next->type == 4 )
      } // else
    } // else if ( temp->type == 3 )
    else if ( temp->type == 4 ) {                                                                   // if temp point a node which is a ')'   
      if ( temp == head ) {                                                                         // if temp point at a first node ( no this case because this is error2 )
      } // if ( temp == head )
      else if ( temp->next == NULL ) {                                                              // if temp point at a last node
        if ( prev->type == 2 || prev->type == 3 ) {                                                 // if prev point a node which is a 'calculating sign' or a '(' ; ex: 35+(40+60+) or 35+40+60+()
          printf( "Error 3: it is not infix in the parentheses.\n" ) ;
          return true ;                                                                             // this formula is error3
        } // if ( prev->type == 2 || prev->type == 3 ) 
      } // else if ( temp->next == NULL )
      else {                                                                                        // if temp point not at a first and last node 
        if ( prev->type == 2 || prev->type == 3 ) {                                                 // if prev point a node which is a 'calculating sign' or a '(' ; ex: (35+40+)+60 or 35+40+()+60  
          printf( "Error 3: it is not infix in the parentheses.\n" ) ;
          return true ;                                                                             // this formula is error3
        } // if ( prev->type == 2 || prev->type == 3 )
        else if ( temp->next->type == 1 ) {                                                         // if temp next point a node which is a 'number' ; ex: (35+40)7+60 
          printf( "Error 3: there is one extra operand.\n" ) ;
          return true ;                                                                             // this formula is error3
        } // else if ( temp->next->type == 1 )
      } // else
    } // else if ( temp->type == 4 ) 
      
    if ( head != temp ) {                                                                           // if temp not point at a first node
      prev = prev->next ;                                                                           // let prev point a next node
    } // if ( head != temp )
  
    temp = temp->next ;                                                                             // let head point a next node
  } // while ( temp != NULL )   
  
  return false ;                                                                                    // this formula is not error3
} // CheckIsError3()

/*

CheckIsError function is check formula whether is one of three type error
if true then this formula is illegal
if false then this formula is legal

*/

bool CheckIsError( NodePtr head ) {
  if ( !CheckIsError1( head ) ) {                                                                   // go to the function of CheckIsError1 with head , if not then go to the function of CheckIsError2 with head
    if ( !CheckIsError2( head ) ) {                                                                 // go to the function of CheckIsError2 with head , if not then go to the function of CheckIsError3 with head
      if ( !CheckIsError3( head ) ) {                                                               // go to the function of CheckIsError3 with head , if not then this formula is no error  
        printf( "It is a legitimate infix expression.\n" ) ; 
        return false ;                                                                              // this formula is legal
      } // if ( !CheckIsError3( head ) )
    } // if ( !CheckIsError2( head ) )
  } // if ( !CheckIsError1( head ) ) 
  
  return true ;                                                                                     // this formula is illegal
} // CheckIsError()

/*

SkipSpace function is use to skip 'the char of space'
if ch is 'the char of space' then get next ch
until find ch not is 'the char of space'

*/

void SkipSpace( char &ch ) {
  while ( ch == ' ' ) {                                                                             // until ch not a space 
    scanf( "%c", &ch ) ;                                                                            // get a ch
  } // while ( ch == ' ' )     
} // SkipSpace()

/*

ToNode function is let every char of this formula but not include 'space' and '\n' char
store to the struct of Node and decide is which type
this can be a dynamic array which store ch and type then head point a first node 
 
*/

void ToNode( NodePtr &head ) {
  NodePtr temp = NULL ;                                                                             // define a pointer of Node name temp point NULL ; temp is use to point a first node until a last node
  NodePtr prev = NULL ;                                                                             // define a pointer of Node name prev point NULL ; prev next point is always temp point when head and temp point not a same node
  head = new Node ;                                                                                 // create a new struct of Node and head point this  
  head->next = NULL ;                                                                               // let head next point NULL
  temp = head ;                                                                                     // let temp point which head point
  prev = head ;                                                                                     // let prev point which head point
  char ch = '\0' ;                                                                                  // define every char of formula name ch and initial value is '\0' 
  scanf( "%c", &ch ) ;                                                                              // get a ch
  while ( ch != gchar ) {                                                                           // until ch is '\n' mean until this formula end
    if ( ch == ' ' ) {                                                                              // if ch is a space
      SkipSpace( ch ) ;                                                                             // go to the function of SkipSpace with ch
    } // if ( ch == ' ' )
  
    if ( ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' ||                           // if ch is a 'number' 
         ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9' ) {                                                                              
      temp->type = 1 ;                                                                              // type of the node is 1 which temp point  
    } // if           
    else if ( ch == '+' || ch == '-' || ch == '*' || ch == '/' ) {                                  // if ch is a 'calculating sign'   
      temp->type = 2 ;                                                                              // type of the node is 2 which temp point  
    } // else if ( ch == '+' || ch == '-' || ch == '*' || ch == '/' )
    else if ( ch == '(' ) {                                                                         // if ch is a '(' 
      temp->type = 3 ;                                                                              // type of the node is 3 which temp point
    } // else if ( ch == '(' ) 
    else if ( ch == ')' ) {                                                                         // if ch is a ')'
      temp->type = 4 ;                                                                              // type of the node is 4 which temp point
    } // else if ( ch == ')' )
    else {                                                                                          // ch is not a 'number' , 'calculating sign' , '(' , ')'
      temp->type = 5 ;                                                                              // type of the node is 5 which temp point
    } // else
    
    temp->ch = ch ;                                                                                 // store ch to the node which temp point
    scanf( "%c", &ch ) ;                                                                            // get a ch
    if ( ch != gchar ) {                                                                            // if ch is '\n' mean this formula is end     
      if ( head != temp ) {                                                                         // if temp not point at a first node
        prev = prev->next ;                                                                         // let prev point a next node
      } // if ( head != temp )
  
      temp->next = new Node ;                                                                       // create a new struct of Node and temp next point this
      temp = temp->next ;                                                                           // let temp point a next node
      temp->next = NULL ;                                                                           // let temp next point NULL
    } // if ( ch != '\n' )    
  } // while ( ch != '\n' )  
} // ToNode()

//--------------------------------------------------------------------------- Mission2 use function ---------------------------------------------------------------------------

/*

ChangeToStr function is let every 'char' which store in dynamic array change to "string" 
'number' need to change int number then add up this int number of different digit , 
finally , let int number change to "string" and store in node
'calculating sign' , '(' , ')' just change from 'char' to "string" and store in node
this can be a new dynamic array which store string then head point a first node 
ex: (30+40)-5
old head point node: '(' -> '3' -> '0' -> '+' -> '4' -> '0' -> ')' -> '-' -> '5'
new head point node: "(" -> "30" -> "+" -> "40" -> ")" -> "-" -> "5"

*/

void ChangeToStr( NodePtr &head ) {
  NodePtr temp = head ;                                                                             // define a pointer of Node name temp point which head point ; temp is use to point a first node until a last node
  NodePtr prev = head ;                                                                             // define a pointer of Node name prev point which head point ; prev next point is always temp point when head and temp point not a same node 
  NodePtr first = NULL ;                                                                            // define a pointer of Node name first point NULL ; first is a first pointer of region   
  NodePtr after = NULL ;                                                                            // define a pointer of Node name after point NULL ; after is a last pointer of region
  NodePtr last = NULL ;                                                                             // define a pointer of Node name last point NULL ; last is a pointer of region which next point is always after point when first and after point not a same node 
  int n = 0 ;                                                                                       // define a int name n , initial value is 0 ; n is use to calculate digit
  int m = 1 ;                                                                                       // define a int name m , initial value is 1 ; m is use to calculate number
  int k = 1 ;                                                                                       // define a int name k , initial value is 1 ; k is use to calculate number
  int num = 0 ;                                                                                     // define a int name num , initial value is 0 ; num is use to calculate number
  while ( temp != NULL ) {                                                                          // until temp point NULL 
    if ( temp->type == 1 ) {                                                                        // if temp point a node which is a 'number' , this mean let n 'number' change to "number"
      first = temp ;                                                                                // let first point which temp point
      after = first ;                                                                               // let after point which first point
      last = first ;                                                                                // let last point which first point
      while ( after->type == 1 && after->next != NULL ) {                                           // until after point a node which is a 'calculating sign' , ')' or after next point NULL  
        if ( first != after ) {                                                                     // if after not point at a first node of region
          last = last->next ;                                                                       // let last point a next node
        } // if ( first != after )
  
        after = after->next ;                                                                       // let after point a next node
        n = n + 1 ;
      } // while ( after->type == 1 && after->next != NULL )
      
      temp = new Node ;                                                                             // create a new struct of Node and temp point this
      if ( head == prev && head->type != 3 ) {                                                      // if head point which prev point and head point a node which is a 'number' ; ex: 35+40
        head = temp ;                                                                               // let head point which temp point
        prev = temp ;                                                                               // let prev point which temp point
      } // if ( head == prev && head->type != 3 )
      else {
        prev->next = temp ;                                                                         // let prev next point which temp point
      } // else
      
      if ( after->type != 4 &&  after->next == NULL ) {                                              // if after next point NULL and after point a node which is a 'number' ; ex: 35+40  
        n = n + 1 ;   
        temp->next = NULL ;                                                                         // let temp next point NULL
      } // if ( after->next == NULL && after->type != 4 )     
      else {                                                                                        
        temp->next = after ;                                                                        // let temp next point which after point
        last->next = NULL ;                                                                         // let last next point NULL 
      } // else
      
      while ( first != NULL ) {                                                                     // until first point NULL 
        while ( m < n ) {                                                                           // until m is same as n
          k = k * 10 ;
          m = m + 1 ;
        } // while ( m < n )
        
        num = num + ( int(first->ch) - 48 ) * k ;                                                   // add from low digit to high digit
        n = n - 1 ;
        m = 1 ;
        k = 1 ;
        first = first->next ;                                                                       // let first point a next node
      } // while ( first != NULL )
      
      sprintf( temp->str, "%d", num ) ;                                                             // let int num change to string and store to the node which temp point
      n = 0 ;                                                                                   
      num = 0 ;
      delete first ;                                                                                // delete node which first point because not need to use
      first = NULL ;                                                                                // let first point NULL
    } // if ( temp->type == 1 )
    else {                                                                                          // if temp point a node which is a 'calculating sign' , '(' , ')'
      sprintf( temp->str, "%c", temp->ch ) ;                                                        // let char ch change to string and store to the node which temp point
    } // else 
    
    
    if ( head != temp ) {                                                                           // if temp not point at a first node
      prev = prev->next ;                                                                           // let prev point a next node   
    } // if ( head != temp )
    
    temp = temp->next ;                                                                             // let temp point a next node
  } // while ( temp != NULL )
} // ChangeToStr()

/*

ChangeToStrtype function is let every type which store in dynamic array change to strtype
then decide this string is in which layer and record the most layer of this formula
meet "(" need add 1 layer
meet ")" next need reduce 1 layer
and layer is start from 1  
ex: 30+(40-20)*10 
layer = 1 -> "30" , "+" , "*" , "10"
layer = 2 -> "(" , "40" , "-" , "20" , ")"
maxlayer = 2

*/

void ChangeToStrtype( NodePtr head, int &maxlayer ) {
  int layer = 1 ;                                                                                   // define a int name layer , initial value is 1 ; when go to next () then layer + 1 , leave () then layer - 1 
  while ( head != NULL ) {                                                                          // until head point NULL
    if ( strcmp( head->str, "+" ) == 0 || strcmp( head->str, "-" ) == 0 ) {                         // if head point a node which is a "+" or "-" 
      head->strtype = 2 ;                                                                           // strtype of the node is 2 which head point  
    } // if ( strcmp( head->str, "+" ) == 0 || strcmp( head->str, "-" ) == 0 )
    else if ( strcmp( head->str, "*" ) == 0 || strcmp( head->str, "/" ) == 0 ) {                    // if head point a node which is a "*" or "/"     
      head->strtype = 3 ;                                                                           // strtype of the node is 3 which head point
    } // else if ( strcmp( head->str, "*" ) == 0 || strcmp( head->str, "/" ) == 0 )
    else if ( strcmp( head->str, "(" ) == 0 ) {                                                     // if head point a node which is a "("  
      head->strtype = 4 ;                                                                           // strtype of the node is 4 which head point
      layer = layer + 1 ;                                                                           // meet "(" so layer + 1
      if ( layer > maxlayer ) {                                                                     // record the most layer of this formula 
        maxlayer = layer ;  
      } // if ( layer > maxlayer )
    } // else if ( strcmp( head->str, "(" ) == 0 )
    else if ( strcmp( head->str, ")" ) == 0 ) {                                                     // if head point a node which is a ")" 
      head->strtype = 5 ;                                                                           // strtype of the node is 5 which head point
    } // else if ( strcmp( head->str, ")" ) == 0 )
    else {                                                                                          // if head point a node which is a "number"
      head->strtype = 1 ;                                                                           // strtype of the node is 1 which head point
    } // else 
    
    head->layer = layer ;                                                                           // store layer to the node which head point
    if ( strcmp( head->str, ")" ) == 0 ) {                                                          // if head point a node which is a ")"
      layer = layer - 1 ;                                                                           // because before meet ")" so next layer of the node - 1   
    } // if ( strcmp( head->str, ")" ) == 0 )
    
    head = head->next ;                                                                             // let head point a next node
  } // while ( head != NULL )  
} // ChangeToStrtype()

/*

ToStrNode function is let every 'char' which store in dynamic array change to "string" 
and let every type which store in dynamic array change to strtype
then decide this string is in which layer and record the most layer of this formula
this can be a new dynamic array which store string , strtype then head point a first node 

*/

void ToStrNode( NodePtr &head, int &maxlayer ) {
  ChangeToStr( head ) ;                                                                             // go to the function of ChangeToStr with head
  ChangeToStrtype( head, maxlayer ) ;                                                               // go to the function of ChangeToStrtype with head and maxlayer
} // ToStrNode()

/*

ChangeMulAndDiv function is when meet "*" or "/" how to swap
"*" and "/" is swap with 
1. next number  
2. next the content in parenthesis include parenthesis
--------------- ex: 30 / ( 50 + 60 * 70 ) + 20
when layer = 2 then 30 / ( 50 + 60 70 * ) + 20 -> case 1: * swap with 70 
when layer = 1 then 30 ( 50 + 60 70 * ) / + 20 -> case 2: / swap with ( 50 + 60 70 * )

*/

void ChangeMulAndDiv( NodePtr head, int layer ) { 
  NodePtr temp = head ;                                                                             // define a pointer of Node name temp point which head point ; temp is use to point a first node until a last node
  NodePtr prev = head ;                                                                             // define a pointer of Node name prev point which head point ; prev next point is always temp point when head and temp point not a same node 
  NodePtr first = NULL ;                                                                            // define a pointer of Node name first point NULL ; first is a first pointer of region   
  NodePtr after = NULL ;                                                                            // define a pointer of Node name after point NULL ; after is a last pointer of region
  while ( temp != NULL ) {                                                                          // until temp point NULL
    if ( temp->strtype == 3 && temp->layer == layer ) {                                             // if temp point a node which is a "*" , "/" and temp point a node which layer is same as the value which brought in by the function
      first = temp->next ;                                                                          // let first point which temp next point
      after = first ;                                                                               // let after point which first point
      if ( after->strtype == 4 ) {                                                                  // if after point a node which is a "(" 
        while ( after->strtype != 5 || after->layer != layer + 1 ) {                                // until after point a node which is a ")" and after point a node which layer is same as the value which brought in by the function + 1 
          after = after->next ;                                                                     // after point a next node
        } // while ( after->strtype != 5 || after->layer != layer + 1 )
      } // if ( after->strtype == 4 )
      
      temp->next = after->next ;                                                                    // let temp next point which after next point
      prev->next = first ;                                                                          // let prev next point which first point 
      after->next = temp ;                                                                          // let after next point which temp point 
      prev = after ;                                                                                // let prev point which after point 
    } // if ( temp->strtype == 3 && temp->layer == layer )
    
    if ( head != temp ) {                                                                           // if temp not point at a first node
      prev = prev->next ;                                                                           // prev point a next node   
    } // if ( head != temp )
    
    temp = temp->next ;                                                                             // temp point a next node
  } // while ( temp != NULL )
} // ChangeMulAndDiv()

/*

ChangeAddAndSub function is when meet "+" or "-" how to swap
"+" and "-" is swap with 
1. the content which between "+" or "-" and the next the same layer of "+" or "-" 
2. the content which is afetr "+" or "-" if after no the same layer of "+" or "-" , when layer = 1
3. the content which is afetr "+" or "-" if after no the same layer of "+" or "-" , when layer > 1
--------------- ex: 30 - ( 40 + 50 )  
when layer = 2 then 30 - ( 40 50 + ) -> case 3: + swap with 50 
when layer = 1 then 30 ( 40 50 + ) - -> case 2: - swap with ( 40 50 + )
--------------- ex: 30 + 50 - 60 
when layer = 1 then 30 50 + 60 - -> case 1: + swap with 50 and case 2: - swap with 60

*/

void ChangeAddAndSub( NodePtr head, int layer ) { 
  NodePtr temp = head ;                                                                             // define a pointer of Node name temp point which head point ; temp is use to point a first node until a last node
  NodePtr prev = head ;                                                                             // define a pointer of Node name prev point which head point ; prev next point is always temp point when head and temp point not a same node 
  NodePtr first = NULL ;                                                                            // define a pointer of Node name first point NULL ; first is a first pointer of region   
  NodePtr after = NULL ;                                                                            // define a pointer of Node name after point NULL ; after is a last pointer of region
  NodePtr last = NULL ;                                                                             // define a pointer of Node name last point NULL ; last is a pointer of region which next point is always after point when first and after point not a same node
  while ( temp != NULL ) {                                                                          // until temp point NULL
    if ( temp->strtype == 2 && temp->layer == layer ) {                                             // if temp point a node which is a "+" , "-" and temp point a node which layer is same as the value which brought in by the function
      first = temp->next ;                                                                          // let first point which temp next point
      after = first ;                                                                               // let after point which first point
      last = first ;                                                                                // let last point which first point
      while ( ( after->strtype != 2 || after->layer != layer ) &&                                   // until after point a node which is a "+" , "-" and after point a node which layer is same as the value which brought in by the function 
              ( after->strtype != 5 || after->layer != layer ) &&                                   // or after point a node which is a ")" and after point a node which layer is same as the value which brought in by the function 
              ( after->next != NULL ) ) {                                                           // or after next point NULL 
        if ( first != after ) {                                                                     // if after not point at a first node of region
          last = last->next ;                                                                       // let last point a next node                                                                
        } // if ( first != after )  
  
        after = after->next ;                                                                       // let after point a next node
      } // while   
    
      if ( ( after->strtype == 5 && after->layer == layer && after->next == NULL ) ||               // if after point a node which is a ")" and after point a node which layer is same as the value which brought in by the function and after next point NULL ; ex: (35+40) 
           ( after->next != NULL ) ) {                                                              // or after next not point NULL ; ex: 35+40
        after = last ;                                                                              // let after point which last point
      } // if
      
      temp->next = after->next ;                                                                    // let temp next point which after next point
      prev->next = first ;                                                                          // let prev next point which first point
      after->next = temp ;                                                                          // let after next point which temp point
      prev = after ;                                                                                // let prev point which after point
    } // if ( temp->strtype == 2 && temp->layer == layer )
    
    if ( head != temp ) {                                                                           // if temp not point at a first node
      prev = prev->next ;                                                                           // let prev point a next node   
    } // if ( head != temp )
    
    temp = temp->next ;                                                                             // let temp point a next node
  } // while ( temp != NULL )
} // ChangeAddAndSub()

/*

DeleteOAndC function is let old dynamic array which is swap delete "(" and ")" of the node 
first create a new dynamic array , if char of the node in old dynamic array is "(" or ")"
then no store in new dynamic array , otherwise , the other need store in new dynamic array
--ex: ( 30 + 50 ) / 20
swap: ( 30 50 + ) 20 /
-new: 30 50 + 20 /

*/

void DeleteOAndC( NodePtr &head ) {
  NodePtr temp = head ;                                                                             // define a pointer of Node name temp point which head point ; temp is use to point a first node until a last node                                         
  NodePtr retemp = NULL ;                                                                           // define a pointer of Node name retemp point NULL ; retemp is use to point a new first node until a new last node
  head = NULL ;                                                                                     // let head point NULL
  bool firstone = false ;                                                                           // define whether is find a first "number" , "calculating signs" in this dynamic array name firstone , initial value is false
  while ( temp != NULL ) {                                                                          // until temp point NULL
    if ( temp->strtype == 1 || temp->strtype == 2 || temp->strtype == 3 ) {                         // if temp point a node which is a "number" , "calculating signs"
      if ( firstone == false ) {                                                                    // if not find a first "number" , "calculating signs" in this dynamic array 
        retemp = new Node ;                                                                         // create a new struct of Node and retemp point this 
        head = retemp ;                                                                             // let head point which retemp point
        firstone = true ;                                                                           // find a first "number" , "calculating signs" in this dynamic array so firstone is true
      } // if ( firstone == false )
      else {                                                                                        // if find a first "number" , "calculating signs" in this dynamic array 
        retemp->next = new Node ;                                                                   // create a new struct of Node and retemp next point this
        retemp = retemp->next ;                                                                     // let retemp point a next node
      } // else
      
      retemp->next = NULL ;                                                                         // let retemp next point NULL
      strcpy( retemp->str, temp->str ) ;                                                            // store string from old dynamic array to new dynamic array   
    } // if ( temp->strtype == 1 || temp->strtype == 2 || temp->strtype == 3 )
    
    temp = temp->next ;                                                                             // let temp point a next node
  } // while ( temp != NULL )
} // DeleteOAndC()

/*

PrintPostfix function is print the postfix of this formula
follow the new dynamic array and print in order

*/

void PrintPostfix( NodePtr head ) {                                                                 
  printf( "Postfix expression:" ) ;
  while ( head != NULL ) {                                                                          // until head point NULL
    if ( head->next != NULL ) {                                                                     // if head next not point NULL
      printf( " %s,", head->str ) ;
    } // if ( head->next != NULL )
    else {                                                                                          // if head next point NULL
      printf( " %s", head->str ) ;    
    } // else
    
    head = head->next ;                                                                             // let head point a next node
  } // while ( head != NULL )
  
  printf( "%c", gchar ) ;
} // PrintPostfix()

//--------------------------------------------------------------------------- Mission1 , Mission2 and main function ---------------------------------------------------------------------------

/*

Mission2 function is let the infix of this formula change to postfix
first , let 'char' change to "string" and type change to strtype ,
store every "string" is in which layer and record the most layer of this formula
second , from the most layer begin swap , "*" and "/" swap then "+" and "-" swap
until layer = 1 also swap , then this postfix of formula almost done 
thrid , delete "(" and ")" of the node in old dynamic array and
store the other string to new dynamic array
last , print the postfix of this formula 

*/

void Mission2( NodePtr head ) {
  int maxlayer = 1 ;                                                                                // define this formula has how many layer at most name maxlayer , initial value is 1
  ToStrNode( head, maxlayer ) ;                                                                     // go to the function of ToStrNode with head and maxlayer
  while ( maxlayer > 0 ) {                                                                          // until maxlayer is 0
    ChangeMulAndDiv( head, maxlayer ) ;                                                             // go to the function of ChangeMulAndDiv with head and maxlayer
    ChangeAddAndSub( head, maxlayer ) ;                                                             // go to the function of ChangeAddAndSub with head and maxlayer
    maxlayer = maxlayer - 1 ;
  } // while ( maxlayer > 0 )
  
  DeleteOAndC( head ) ;                                                                             // go to the function of DeleteOAndC with head
  PrintPostfix( head ) ;                                                                            // go to the function of PrintPostfix with head
} // Mission2()

/*

Mission1 function is check this formula whether is legal infix 
first , store every char of this formula not include ' ' and '\n' and store is which type ,
second , check this formula is which type of illegal infix or legal infix
if true then this formula is one type of illegal infix
in false then this formula is legal infix and this formula have postfix 
last , need to delete pointer head to free memory 

*/

void Mission1() {
  NodePtr head = NULL ;                                                                             // define a pointer of Node name head point NULL ; head is a pointer which is always point a first node  
  head = new Node ;                                                                                 // create a new struct of Node and head point this    
  head->next = NULL ;                                                                               // let head next point NULL 
  ToNode( head ) ;                                                                                  // go to the function of ToNode with head
  if ( !CheckIsError( head ) ) {                                                                    // go to the function of CheckIsError with head , if not then this formula is legal
    Mission2( head ) ;                                                                              // go to the function of Mission2 with head
  } // if ( !CheckIsError( head ) )   
  
  delete head ;                                                                                     // delete node which head point because mission is over and not need to use
  head = NULL ;                                                                                     // head point NULL 
} // Mission1()

/*

main function is let user use command 

*/

int main(void) {
  int command = 0 ;                                                                                 // define a user command name command , initial value is 0
  do {
    Str255 str ;                                                                                    // define a formula name str
    printf( "%c", gchar ) ;
    printf( "* Arithmetic Expression Evaluator *\n" ) ;
    printf( "* 0. QUIT                         *\n" ) ;
    printf( "* 1. Infix2postfix Transformation *\n" ) ;
    printf( "***********************************\n" ) ;
    printf( "Input a choice(0, 1): " ) ;
    scanf( "%d%c", &command, &gchar ) ;                                                             // get a command and '\n'
    if ( command == 0 ) {                                                                           // if command is 0 , then stop the program
      break ;                                                                                       // skip this while    
    } // if
    else if ( command == 1 ) {                                                                      // if command is 1 , then check error of this formula and get postfix of this formula if no error 
      printf( "%c", gchar ) ;
      printf( "Input an infix expression: " ) ; 
      Mission1() ;                                                                                  // go to the function of Mission1 with head
    } // else if
    else {                                                                                          // if command is not 0 or 1 , then continue the program   
      printf( "%c", gchar ) ;
      printf( "Command does not exist!\n" ) ;     
    } // else
  } while ( command != 0 ) ;                                                                        // until command is 0
  
  system( "pause" ) ;                                                                               // pause the display
  return 0 ;
} // main()
