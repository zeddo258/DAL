// 11127230 鍾帛勳
#include <iostream>
#include <string>
using namespace std;

class dll {
	struct Node {
		string str;
		int num;
		Node* next;
		Node* back;
	};
	
public:
	typedef Node* nodeptr;
	nodeptr head;
	nodeptr tail;
	nodeptr temp;
	
	void addnode(nodeptr & h, nodeptr & t, string s, int num) {
		nodeptr temp = new Node;
		temp->str = s;
		temp->next = NULL;
		temp->back = NULL;
		temp->num = num;
		if (h == NULL) {
			h = temp;
			t = temp;
		}
		else {
			t->next = temp;
			t->next->back = t;
			t = t->next;
		}
	}
	
	void deletelast(nodeptr & h, nodeptr & t) {
		nodeptr temp = t;
		if (t->back != NULL) {
			t = t->back;
		}
		else {
			h = NULL;
			t = NULL;
		}
		delete temp;
	}
};

dll in;
dll post;
dll s;
string input;
bool islegal;

bool isoperator(char a) {
	return a == '+' || a == '-' || a == '*' || a == '/';
}

void printall(dll h) {
	dll t = h;
	cout << "Postfix expression: ";
	cout << t.head->str;
	for (t.temp=t.head->next; t.temp != NULL; t.temp = t.temp->next) {
		cout << ", " << t.temp->str ;
	}
	cout << endl;
}

void printallback(dll h) {
	dll t = h;
	cout << "Postfix expression: ";
	cout << t.tail->str;
	for (t.temp=t.tail->back; t.temp != NULL; t.temp = t.temp->back) {
		cout << ", " << t.temp->str ;
	}
	cout << endl;
}

bool expbalance() {
	int i;
	int scope = 0;
	for (i = 0; i < input.size(); i++) {
		for (;input[i] == ' ' && i < input.size(); i++); // skip space
		// return false if there exist a illegal character 
		if (input[i] != '(' && input[i] != ')' && (input[i] < '0' || input[i] > '9') && !isoperator(input[i])) { 
			cout << "Error 1: " << input[i] << " is not a legitimate character." << endl << endl;
			return false;
		}

		if (input[i] == '(') {
			scope++;
		}
		else if (input[i] == ')') {
			scope--;
		}
		
		if (scope < 0) {
			cout << "Error 2: there is one extra close parenthesis." << endl << endl;
			return false;
		}
	}
	if (scope > 0) {
		cout << "Error 2: there is one extra open parenthesis." << endl << endl;
		return false;
	}
	return true;
}

void target1() {
	int cur = 0;
	int kind = -1; // 0 num, 1 scope, 2 calculator
	int temp;
	// expbalance can output the error 1 and error 2 co that the sequence of error would be correct
	if (!expbalance()) return; 
	for ( ; input[cur] == ' ' && cur < input.size(); cur++);
	if (input[cur] >= '0' && input[cur] <= '9') {
		kind = 0;
	}
	else if (input[cur] == '(' || input[cur] == ')') {
		kind = 1;
	}
	else if (isoperator(input[cur])) { // it illegal that infix start from operator
		cout << "Error 3: there is one extra operator." << endl << endl;
		return;
	}
	int i;
	for (; cur < input.size();) {
		if (kind == 0) {
			temp = 0;
			for (; cur < input.size();) { // find the number save in temp
				if (input[cur] >= '0' && input[cur] <= '9') { 
					temp*=10;
					temp+=input[cur] - '0';
				}
				else {
					break;
				}

				cur++;
				for ( ; input[cur] == ' ' && cur < input.size(); cur++);
				if (cur == input.size()) break;
			}
			in.addnode(in.head, in.tail, to_string(temp), 0);
			if (cur == input.size()) {
				break;
			}
				
			if (isoperator(input[cur])) {  // find next character kind
				kind = 2;
			}
			else if (input[cur] == ')') {
				kind = 1;
			}
			else {
				if (input[cur] == '(') { // number can't connect with '(' so find the error kind
					cur++;
					for ( ; input[cur] == ' ' && cur < input.size(); cur++);
					if (cur == input.size()) {
						cout << "Error 2: there is one extra open parenthesis." << endl << endl;
					}
					else if (input[cur] >= '0' && input[cur] <= '9') {
						cout << "Error 3: there is one extra operand." << endl << endl;
					}
					else if (input[cur] >= ')') {
						cout << "Error 3: it is not infix in the parentheses." << endl << endl;
					}
					
					return ;
				}
				
				kind = -1;
			}
		}
		else if (kind == 1) {
			char lorr; // save the current bracket kind
			if (input[cur] == '(') { 
				lorr = '(';
			}
			else {
				lorr = ')';
				
				// left bracket cannot connect with right bracket or operator
				if (in.tail != NULL && (in.tail->str == "(" || isoperator(in.tail->str[0]))) {
					cout << "Error 3: it is not infix in the parentheses." << endl << endl;
					return ;
				}
			}

			in.addnode(in.head, in.tail, string(1, input[cur]), 0);
			cur++;
			for ( ; input[cur] == ' ' && cur < input.size(); cur++);
			if (cur == input.size()) {
				break;
			}
			
			// exhaustive the next character 
			if (lorr == '(' && input[cur] >= '0' && input[cur] <= '9') {
				kind = 0;
			}
			else if (lorr == '(' && input[cur] == '(') {
				kind = 1;
			}
			else if (lorr == ')' && isoperator(input[cur])) {
				kind = 2;
			}
			else if (lorr == ')' && input[cur] == ')') {
				kind = 1;
			}
			else if (lorr == ')' && input[cur] >= '0' && input[cur] <= '9') {
				cout << "Error 3: there is one extra operand." << endl << endl;
				return;
			}
		}
		else if (kind == 2) {
			// operator can add into infix without any edit
			in.addnode(in.head, in.tail, string(1, input[cur]), 0);

			cur++;
			for ( ; input[cur] == ' ' && cur < input.size(); cur++);
			if (cur == input.size()) {
				cout << "Error 3: there is one extra operator." << endl << endl;
				return ;
			}

			// exhaustive the next character
			if (input[cur] == '(') {
				kind = 1;
			}
			else if (input[cur] >= '0' && input[cur] <= '9') {
				kind = 0;
			}
			else if (isoperator(input[cur])) {
				cout << "Error 3: there is one extra operator." << endl << endl;
				return ;
			}
			else {
				if (input[cur] == ')') {
					cout << "Error 3: it is not infix in the parentheses." << endl << endl;
				}
				return ;
			}
		}
		else {
			cout << "Error 1: " << input[cur] << " is not a legitimate character." << endl << endl;
			return ;
		}
	}
	
	islegal = true;
}

int seq(char a) {
	if (a == '*' || a == '/') {
		return 1;
	}
	else if (a == '+' || a == '-') {
		return 2;
	}

	return -1;
}

void target2() {
	dll temp = in;
	temp.temp = in.head;
	for (; temp.temp != NULL; temp.temp = temp.temp->next) {
		if (temp.temp->str[0] >= '0' && temp.temp->str[0] <= '9') { // put number into postfix
			post.addnode(post.head, post.tail, temp.temp->str, 0);
		}
		else if (temp.temp->str == "(") { // put '(' into stack
			s.addnode(s.head, s.tail, temp.temp->str, 0);
		}
		else if (temp.temp->str == ")") { // if encounter ')' pop all operator unitl '('
			while (s.tail->str != "(") {
				post.addnode(post.head, post.tail, s.tail->str, 0);
				s.deletelast(s.head, s.tail);
			}
			s.deletelast(s.head, s.tail);
		}
		else if (seq(temp.temp->str[0]) == 1) { // if current operator is '*' or '/'

			if (s.tail != NULL && seq(s.tail->str[0]) == 1) { // if last operator is the same priority
				post.addnode(post.head, post.tail, s.tail->str, 0); // add last operator of stack into postfix
				s.tail->str = temp.temp->str; // change last operator of stack
			}
			else {
				s.addnode(s.head, s.tail, temp.temp->str, 0);
			}
		}
		else if (seq(temp.temp->str[0]) == 2) { // if current operator is '+' or '-'
			if (s.tail != NULL && seq(s.tail->str[0]) == 2) { // if last operator is the same priority
				post.addnode(post.head, post.tail, s.tail->str, 0);
				s.tail->str = temp.temp->str;
			}
			else if (s.tail != NULL && seq(s.tail->str[0]) == 1) { // if last operator of stack has bigger priorty
				post.addnode(post.head, post.tail, s.tail->str, 0); // push last operator of stack into postfix
				s.deletelast(s.head, s.tail); 

				if (s.tail != NULL && seq(s.tail->str[0]) == 2) { // if last operator has same priority
					post.addnode(post.head, post.tail, s.tail->str, 0); 
					s.deletelast(s.head, s.tail);
				}
				s.addnode(s.head, s.tail, temp.temp->str, 0);

			}
			else {
				s.addnode(s.head, s.tail, temp.temp->str, 0);
			}
		}
		else {cout << "error" << endl;}
	}

	for (;s.tail!=NULL; s.tail=s.tail->back) { // push all the operator in stack 
		post.addnode(post.head, post.tail, s.tail->str, 0);
	}
}

void target3() {
	dll temp = in;
	temp.temp = in.tail;
	for (; temp.temp != NULL; temp.temp = temp.temp->back) {
		if (temp.temp->str[0] >= '0' && temp.temp->str[0] <= '9') { // put number into postfix
			post.addnode(post.head, post.tail, temp.temp->str, 0);
		}
		else if (temp.temp->str == ")") { // put '(' into stack
			s.addnode(s.head, s.tail, temp.temp->str, 0);
		}
		else if (temp.temp->str == "(") { // if encounter ')' pop all operator unitl '('
			while (s.tail->str != ")") {
				post.addnode(post.head, post.tail, s.tail->str, 0);
				s.deletelast(s.head, s.tail);
			}
			s.deletelast(s.head, s.tail);
		}
		else if (seq(temp.temp->str[0]) == 1) { // if current operator is '*' or '/'
			s.addnode(s.head, s.tail, temp.temp->str, 0);
			
		}
		else if (seq(temp.temp->str[0]) == 2) { // if current operator is '+' or '-'
			if (s.tail != NULL && seq(s.tail->str[0]) == 2) { // if last operator is the same priority
				post.addnode(post.head, post.tail, s.tail->str, 0);
				s.tail->str = temp.temp->str;
			}
			else if (s.tail != NULL && seq(s.tail->str[0]) == 1) { // if last operator of stack has bigger priorty
				post.addnode(post.head, post.tail, s.tail->str, 0); // push last operator of stack into postfix
				s.deletelast(s.head, s.tail); 
				s.addnode(s.head, s.tail, temp.temp->str, 0);

			}
			else {
				s.addnode(s.head, s.tail, temp.temp->str, 0);
			}
		}
		else {cout << "error" << endl;}
	}

	for (;s.tail!=NULL; s.tail=s.tail->back) { // push all the operator in stack 
		post.addnode(post.head, post.tail, s.tail->str, 0);
	}
}

int getint(string a) {
	int i;
	int out = 0;
	for (i = 0; i < a.size(); i++) {
		out *= 10;
		out += a[i] - '0'; 
	}
	return out;
}

// bool calculate() {
	// nodeptr pt = posthead;
	// for (;pt != NULL; pt = pt->next) {
		// if (pt->str[0] >= '0' && pt->str[0] <= '9') {
			// addnode(shead, stail, "", getint(pt->str));
		// }
		// else {
			// if (pt->str == "+") {
				// stail->back->num += stail->num;
			// }
			// else if (pt->str == "-") {
				// stail->back->num -= stail->num;
			// }
			// else if (pt->str == "*") {
				// stail->back->num *= stail->num;
			// }
			// else if (pt->str == "/") {
				// if (stail->num == 0) {
					// cout << "error / zero" << endl << endl;
					// return false;
				// }
				// stail->back->num /= stail->num;
			// }
			// deletelast(shead, stail); 
		// }
	// }
	// // if (shead != NULL) {
		// // cout << shead->num << endl;
	// // }
	// // else {
		// // cout << "head NULL" << endl;
	// // }
	// return true;
// }

int main() {
	int i;
	int com;
	while (true) {
		cout << "* Arithmetic Expression Evaluator *" << endl;
		cout << "* 0. QUIT                         *" << endl;
		cout << "* 1. Infix2postfix Transformation *" << endl;
		cout << "***********************************" << endl;
		cout << "Input a choice(0, 1): ";
		cin >> com;
		cout << endl;
		if (com == 0) {
			break;
		}
		else if (com != 1) {
			cout << "Command does not exist!" << endl;
			continue;
		}
		cout << "Input an infix expression: ";
		getline(cin, input);
		getline(cin, input);
		// reset
		for(;in.head != NULL; in.deletelast(in.head, in.tail));
		for(;post.head != NULL; post.deletelast(post.head, post.head));
		for(;s.head != NULL; s.deletelast(s.head, s.head));
		islegal = false;
		target1();
		if (islegal == true) {
			if (com == 1) {
				target2();
				printall(post);
			}
			else {
				target3();
				printallback(post);
			}
		
			cout << endl;
		}
	}
	return 0;
}

// (29+101)*33/25
// 24*7770/(55+30*2)
// (90+(70*(68-55/10)))
// 69/3+30*5-24/8
