// 11127217 陳彥汝 
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node
{ string item; 
  Node *next;
};

class Stack //堆疊 
{
private:
    vector<string> arr; //存放運算子 
public:
    bool isEmpty(); //確認陣列中有沒有存放東西 
    string gettop(); //取出最上面的運算子 
    void rmtop(); //刪除最上面的運算子 
    void push( string test ); //將新運算子放到最上面 
    int size(); // 目前存放的數量 
};

bool Havenum ( Node *list ); //確認括弧中由無數字 
bool Error1( Node *list ); //判斷第一類錯誤  
bool Error2( Node *list ); //判斷第二類錯誤
bool Error3( Node *list ); //判斷第三類錯誤
void Write( Node *list ); //輸出後序式 

int main() {
	char test;
	int command; 
	string test2;
	Node *head, *now, *last, *posthead, *postnow;
	Stack tsum;
	while ( command != 0 ){
		cout << "* Arithmetic Expression Evaluator *" << endl;
		cout << "* 0. QUIT                         *" << endl;
		cout << "* 1. Infix2postfix Transformation *" << endl;
		cout << "***********************************" << endl;
		cout << "Input a choice(0, 1): "; 
		cin >> command;
		cout << endl;
		if ( command == 0){ //指令0就結束程式 
			return 0;
		}
		else if ( command!= 1){ //指令錯誤 
			cout << "Command does not exist!" << endl<<endl;; 
		}
		else {
			cout << "Input an infix expression: ";
			head = new Node();
			now = head;
			cin >> test;
			//cin.get(test);
			while ( test != '\n') { //用鏈結串列存算式 
				if ( test == ' ' || test == '\t'){ //輸入中有空白就忽略 
					cin.get(test);
				}
				else if ( test < '0' || test > '9'){ // 輸入為數字以外的字直接存成一個節點 
					test2.push_back(test);
					now->item = test2;
					last = now;
					now->next = new Node();
					now = now->next;
					test2 = "";
					cin.get(test);
				}
				else{ // 輸入為數字 
					while ( (test >= '0' && test <= '9' ) || test == ' ' || test == '\t'){
						while( test == ' ' || test == '\t' ) //碰到空白就忽略 
							cin.get(test);
						if ( test >= '0' && test <= '9' ){ //只要是數字就串起來 
							test2.push_back(test);
							cin.get(test);
						}
					}
					now->item = test2;
					last = now;
					now->next = new Node();
					now = now->next;
					test2 = "";
				}	

			}
			now = last;
			now->next = NULL;
			if ( Error1(head) || Error2(head) || Error3(head) ){ //出現錯誤一錯誤二錯誤三就結束 
				cout << endl;
				now = head;
				while ( now != NULL){ //釋放空間 
					last = now;
					now = now->next;
					delete last;
				}
				delete now;
			}
			else{ //為合格中序式 
				cout << "It is a legitimate infix expression." << endl; 
				posthead = new Node(); //存取後序式 
				postnow = posthead;
				for( now = head ; now != NULL ; now = now->next ){
					if ( now->item[0] >= '0' && now->item[0] <= '9' ){ //當此結點為數字直接放出 
						postnow->item = now->item;
						last = postnow;
						postnow->next = new Node();
						postnow = postnow->next;
					}
					else if ( now->item == "*" || now->item == "/" ){ //當結點為*或/ 
						if ( tsum.size() == 0 || tsum.gettop() == "(" || tsum.gettop() == "+" || tsum.gettop() == "-" ){ //如果暫存空間目前沒東西或是最上面是(或+或-就直接疊上去 
							tsum.push( now->item );
						}
						else{ //如果最上面是*或/就輸出目前最上面的運算子並把自己放進去 
							postnow->item = tsum.gettop();
							last = postnow;
							postnow->next = new Node();
							postnow = postnow->next;
							tsum.rmtop();
							tsum.push(now->item);
						}
					}
					else if ( now->item == "+" || now->item == "-" ){ //當結點為+或- 
						if ( tsum.size() == 0 || tsum.gettop() == "(" ){ //如果暫存空間目前沒東西或是最上面是(就直接疊上去 
							tsum.push( now->item );
						}
						else{
							while ( tsum.size() != 0 && tsum.gettop() != "(" ){//如果最上面是*或/或+或-就輸出目前最上面的運算子並把自己放進去 
								postnow->item = tsum.gettop();
								last = postnow;
								postnow->next = new Node();
								postnow = postnow->next;
								tsum.rmtop();
							}
							tsum.push(now->item);
						}
					}
					else if ( now->item == "(" ){ //當結點為(就直接疊到最上面 
						tsum.push( now->item );
					}
					else{ //當結點為)就一直取出最上面直到碰到( 
						while( tsum.gettop() != "(" ){
							postnow->item = tsum.gettop();
							last = postnow;
							postnow->next = new Node();
							postnow = postnow->next;
							tsum.rmtop();
						}
						tsum.rmtop();
					}
				}
	
				while ( tsum.size() != 0 ) { //將暫存空間中所有的運算子由最上開始輸出直到全部輸完 
					postnow->item = tsum.gettop();
					last = postnow;
					postnow->next = new Node();
					postnow = postnow->next;
					tsum.rmtop();
				}
				postnow = last;
				postnow->next = NULL;
				Write(posthead);
			
				now = head;
				while ( now != NULL){ //釋放空間 
					last = now;
					now = now->next;
					delete last;
				}
				delete now;
		
				now = posthead;
				while ( now != NULL){ // 釋放空間 
					last = now;
					now = now->next;
					delete last;
				}
				delete now;

			}
		}	
	}
}

bool Havenum ( Node *list ) {//在碰到)前遇到數字就回傳true 否則就false 
	for ( Node *current = list; current->item != ")" ; current = current->next ) {
		if ( current->item[0] >= '0' && current->item[0] <= '9'){ 
			return true;
		}
	}
	
	return false;
} 

bool Error1( Node *list ){ //碰到數字,+,-,*,/,(,)以外的結點就輸出true 
	for ( Node *current = list; current != NULL ; current = current->next){
		if ( (current->item[0] < '0' || current->item[0] > '9') && current->item[0] != '+' && current->item[0] != '-' &&
		current->item[0] != '*' && current->item[0] != '/' && current->item[0] != '(' && current->item[0] != ')'){
			cout << "Error 1: " << current->item << " is not a legitimate character." << endl;
			return true;
		}
	}	
	return false;
}

bool Error2( Node *list ){ //確認括號數量 
	int open = 0, close = 0, final = 0;
	for ( Node *current = list; current != NULL ; current = current->next){
		if ( current->item == "(" ) //碰到前括弧數量加一 
			final++;
		if ( current->item == ")" ) //碰到後括弧數量減一 
			final--;
		if ( final < 0 ) { //後括號較多  
			cout << "Error 2: there is one extra close parenthesis." << endl;
			return true;
		}
	}
	
	if ( final == 0 ) //前後括號數量相同 
		return false;
	else if ( final < 0 ){ //前括號較多 
		cout << "Error 2: there is one extra close parenthesis." << endl;
		return true;
	}
	else{ //後括號較多 
		cout << "Error 2: there is one extra open parenthesis." << endl;
		return true;
	}
}

bool Error3( Node *list ){

	if ( list->item[0] == '+' || list->item[0] == '-' || list->item[0] == '*' || list->item[0] == '/' ){ //開頭不是數字或( 
		cout << "Error 3: there is one extra operator." << endl;
		return true;
	}
	
	for ( Node *current = list; current != NULL ; current = current->next){
		if ( current->item[0] == '+' || current->item[0] == '-' || current->item[0] == '*' || current->item[0] == '/'){ // +-*/後面不是數字或是括號 
			if ( current->next->item == "+" || current->next->item == "-" || current->next->item == "*" || 
			current->next->item == "/" || current->next == NULL ){
				cout << "Error 3: there is one extra operator." << endl;
				return true;
			}
		}
		else if ( current->item[0] >= '0' && current->item[0] <= '9' ){ //數字後面不是空的或不是+-*/ 
			if ( current->next != NULL && current->next->item == "(" ) {
				cout << "Error 3: there is one extra operand." << endl;
				return true;
			}
		}
		else if ( current->item == "(" ){ //碰到括號需確認中間有無數字 
			if ( ! Havenum(current) ){
				cout << "Error 3: it is not infix in the parentheses." << endl;
				return true;
			}
		}
		else if ( current->item == ")" ){ //如果後括弧後面有數字就錯誤 
			if ( current->next != NULL && current->next->item != ")" && current->next->item != "+" && current->next->item != "-" && current->next->item != "*" && current->next->item != "/"){
				cout << "Error 3: there is one extra operand." << endl;
				return true;
			}
		}
	}
	
	return false;
}

void Write( Node *list ){ //輸出後序式 
	Node *current = list;
	cout << "Postfix expression: " << current->item;
	for ( current = list->next ; current != NULL ; current = current->next){
		cout << "," << current->item;
	}
	cout << endl << endl; 
}

bool Stack::isEmpty() //暫存空間有沒有東西 
{
    if( arr.size() == 0 )
        return true;
    else
        return false;
}

string Stack::gettop(){ //回傳最上面的值 
	return arr[arr.size()-1];
}

void Stack::rmtop(){ //刪除最上面的值 
	arr.pop_back();
}

void Stack::push( string test ) //把test放到最上面 
{
    arr.push_back( test );
    	
}

int Stack::size() //回傳暫存空間現在有多少東西 
{
    int i = arr.size();
        return i;
}
