// 11127217 ���ۦ� 
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node
{ string item; 
  Node *next;
};

class Stack //���| 
{
private:
    vector<string> arr; //�s��B��l 
public:
    bool isEmpty(); //�T�{�}�C�����S���s��F�� 
    string gettop(); //���X�̤W�����B��l 
    void rmtop(); //�R���̤W�����B��l 
    void push( string test ); //�N�s�B��l���̤W�� 
    int size(); // �ثe�s�񪺼ƶq 
};

bool Havenum ( Node *list ); //�T�{�A�����ѵL�Ʀr 
bool Error1( Node *list ); //�P�_�Ĥ@�����~  
bool Error2( Node *list ); //�P�_�ĤG�����~
bool Error3( Node *list ); //�P�_�ĤT�����~
void Write( Node *list ); //��X��Ǧ� 

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
		if ( command == 0){ //���O0�N�����{�� 
			return 0;
		}
		else if ( command!= 1){ //���O���~ 
			cout << "Command does not exist!" << endl<<endl;; 
		}
		else {
			cout << "Input an infix expression: ";
			head = new Node();
			now = head;
			cin >> test;
			//cin.get(test);
			while ( test != '\n') { //���쵲��C�s�⦡ 
				if ( test == ' ' || test == '\t'){ //��J�����ťմN���� 
					cin.get(test);
				}
				else if ( test < '0' || test > '9'){ // ��J���Ʀr�H�~���r�����s���@�Ӹ`�I 
					test2.push_back(test);
					now->item = test2;
					last = now;
					now->next = new Node();
					now = now->next;
					test2 = "";
					cin.get(test);
				}
				else{ // ��J���Ʀr 
					while ( (test >= '0' && test <= '9' ) || test == ' ' || test == '\t'){
						while( test == ' ' || test == '\t' ) //�I��ťմN���� 
							cin.get(test);
						if ( test >= '0' && test <= '9' ){ //�u�n�O�Ʀr�N��_�� 
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
			if ( Error1(head) || Error2(head) || Error3(head) ){ //�X�{���~�@���~�G���~�T�N���� 
				cout << endl;
				now = head;
				while ( now != NULL){ //����Ŷ� 
					last = now;
					now = now->next;
					delete last;
				}
				delete now;
			}
			else{ //���X�椤�Ǧ� 
				cout << "It is a legitimate infix expression." << endl; 
				posthead = new Node(); //�s����Ǧ� 
				postnow = posthead;
				for( now = head ; now != NULL ; now = now->next ){
					if ( now->item[0] >= '0' && now->item[0] <= '9' ){ //�����I���Ʀr������X 
						postnow->item = now->item;
						last = postnow;
						postnow->next = new Node();
						postnow = postnow->next;
					}
					else if ( now->item == "*" || now->item == "/" ){ //���I��*��/ 
						if ( tsum.size() == 0 || tsum.gettop() == "(" || tsum.gettop() == "+" || tsum.gettop() == "-" ){ //�p�G�Ȧs�Ŷ��ثe�S�F��άO�̤W���O(��+��-�N�����|�W�h 
							tsum.push( now->item );
						}
						else{ //�p�G�̤W���O*��/�N��X�ثe�̤W�����B��l�ç�ۤv��i�h 
							postnow->item = tsum.gettop();
							last = postnow;
							postnow->next = new Node();
							postnow = postnow->next;
							tsum.rmtop();
							tsum.push(now->item);
						}
					}
					else if ( now->item == "+" || now->item == "-" ){ //���I��+��- 
						if ( tsum.size() == 0 || tsum.gettop() == "(" ){ //�p�G�Ȧs�Ŷ��ثe�S�F��άO�̤W���O(�N�����|�W�h 
							tsum.push( now->item );
						}
						else{
							while ( tsum.size() != 0 && tsum.gettop() != "(" ){//�p�G�̤W���O*��/��+��-�N��X�ثe�̤W�����B��l�ç�ۤv��i�h 
								postnow->item = tsum.gettop();
								last = postnow;
								postnow->next = new Node();
								postnow = postnow->next;
								tsum.rmtop();
							}
							tsum.push(now->item);
						}
					}
					else if ( now->item == "(" ){ //���I��(�N�����|��̤W�� 
						tsum.push( now->item );
					}
					else{ //���I��)�N�@�����X�̤W������I��( 
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
	
				while ( tsum.size() != 0 ) { //�N�Ȧs�Ŷ����Ҧ����B��l�ѳ̤W�}�l��X��������駹 
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
				while ( now != NULL){ //����Ŷ� 
					last = now;
					now = now->next;
					delete last;
				}
				delete now;
		
				now = posthead;
				while ( now != NULL){ // ����Ŷ� 
					last = now;
					now = now->next;
					delete last;
				}
				delete now;

			}
		}	
	}
}

bool Havenum ( Node *list ) {//�b�I��)�e�J��Ʀr�N�^��true �_�h�Nfalse 
	for ( Node *current = list; current->item != ")" ; current = current->next ) {
		if ( current->item[0] >= '0' && current->item[0] <= '9'){ 
			return true;
		}
	}
	
	return false;
} 

bool Error1( Node *list ){ //�I��Ʀr,+,-,*,/,(,)�H�~�����I�N��Xtrue 
	for ( Node *current = list; current != NULL ; current = current->next){
		if ( (current->item[0] < '0' || current->item[0] > '9') && current->item[0] != '+' && current->item[0] != '-' &&
		current->item[0] != '*' && current->item[0] != '/' && current->item[0] != '(' && current->item[0] != ')'){
			cout << "Error 1: " << current->item << " is not a legitimate character." << endl;
			return true;
		}
	}	
	return false;
}

bool Error2( Node *list ){ //�T�{�A���ƶq 
	int open = 0, close = 0, final = 0;
	for ( Node *current = list; current != NULL ; current = current->next){
		if ( current->item == "(" ) //�I��e�A���ƶq�[�@ 
			final++;
		if ( current->item == ")" ) //�I���A���ƶq��@ 
			final--;
		if ( final < 0 ) { //��A�����h  
			cout << "Error 2: there is one extra close parenthesis." << endl;
			return true;
		}
	}
	
	if ( final == 0 ) //�e��A���ƶq�ۦP 
		return false;
	else if ( final < 0 ){ //�e�A�����h 
		cout << "Error 2: there is one extra close parenthesis." << endl;
		return true;
	}
	else{ //��A�����h 
		cout << "Error 2: there is one extra open parenthesis." << endl;
		return true;
	}
}

bool Error3( Node *list ){

	if ( list->item[0] == '+' || list->item[0] == '-' || list->item[0] == '*' || list->item[0] == '/' ){ //�}�Y���O�Ʀr��( 
		cout << "Error 3: there is one extra operator." << endl;
		return true;
	}
	
	for ( Node *current = list; current != NULL ; current = current->next){
		if ( current->item[0] == '+' || current->item[0] == '-' || current->item[0] == '*' || current->item[0] == '/'){ // +-*/�᭱���O�Ʀr�άO�A�� 
			if ( current->next->item == "+" || current->next->item == "-" || current->next->item == "*" || 
			current->next->item == "/" || current->next == NULL ){
				cout << "Error 3: there is one extra operator." << endl;
				return true;
			}
		}
		else if ( current->item[0] >= '0' && current->item[0] <= '9' ){ //�Ʀr�᭱���O�Ū��Τ��O+-*/ 
			if ( current->next != NULL && current->next->item == "(" ) {
				cout << "Error 3: there is one extra operand." << endl;
				return true;
			}
		}
		else if ( current->item == "(" ){ //�I��A���ݽT�{�������L�Ʀr 
			if ( ! Havenum(current) ){
				cout << "Error 3: it is not infix in the parentheses." << endl;
				return true;
			}
		}
		else if ( current->item == ")" ){ //�p�G��A���᭱���Ʀr�N���~ 
			if ( current->next != NULL && current->next->item != ")" && current->next->item != "+" && current->next->item != "-" && current->next->item != "*" && current->next->item != "/"){
				cout << "Error 3: there is one extra operand." << endl;
				return true;
			}
		}
	}
	
	return false;
}

void Write( Node *list ){ //��X��Ǧ� 
	Node *current = list;
	cout << "Postfix expression: " << current->item;
	for ( current = list->next ; current != NULL ; current = current->next){
		cout << "," << current->item;
	}
	cout << endl << endl; 
}

bool Stack::isEmpty() //�Ȧs�Ŷ����S���F�� 
{
    if( arr.size() == 0 )
        return true;
    else
        return false;
}

string Stack::gettop(){ //�^�ǳ̤W������ 
	return arr[arr.size()-1];
}

void Stack::rmtop(){ //�R���̤W������ 
	arr.pop_back();
}

void Stack::push( string test ) //��test���̤W�� 
{
    arr.push_back( test );
    	
}

int Stack::size() //�^�ǼȦs�Ŷ��{�b���h�֪F�� 
{
    int i = arr.size();
        return i;
}
