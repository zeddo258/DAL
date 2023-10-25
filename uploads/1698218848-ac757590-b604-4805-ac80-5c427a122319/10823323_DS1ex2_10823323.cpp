// 10823323 ����|�� ���� 

#include "iostream"
#include <string>
#include <regex>

#define MAX_LEN 255
using namespace std;

template<class T>
class JWang_Stack // �w�q�@�ӼҪO���O�A�W�� JWang_Stack 
{
	typedef struct StackNode // �����w�q�@�ӵ��c�A�N����|�����`�I 
	{
		T value; // �`�I�� 
		StackNode *next; // ���V�U�@�Ӹ`�I������ 
	};

	StackNode *topPtr;

public:

	JWang_Stack() : topPtr(NULL) // �w�]�غc�l�A��l�� topPtr �� NULL 
	{}

	bool isEmpty() const // �P�_���|�O�_���šA�p�G topPtr �� NULL�A�h��^ true�A�_�h��^ false 
	{
		return topPtr == NULL;
	}

	void push(T invalue) // �N�ȥ[�J���|���� 
	{
		try
		{
			StackNode* newNode = new StackNode(); // �Ыؤ@�ӷs�`�I 
			newNode->value = invalue;   // �]�w�`�I����
			newNode->next = topPtr; // �N�s�`�I���U�@�Ӹ`�I�]���ثe�����|���� 
			topPtr = newNode;  // ��s���|�������� 
		}
		catch (bad_alloc& ba) // �����ʺA���t�O���饢�Ѫ��ҥ~ 
		{
			cerr << endl << "bad_alloc on stack caught: " << ba.what() << endl;
		}
	}
	T getTop()  // ������|�������ȡA�����q���|������ 
	{
		return topPtr->value;
	}

	T pop() //pop and return
	{
		if (topPtr != nullptr) {
			StackNode* temp = topPtr; // �Ȧs�ثe���|�������`�I 
			topPtr = topPtr->next; // ��s���|�������� 
			T ReturnValue = temp->value;  // ����n��^���� 
			delete temp; // �R���`�I 
			return ReturnValue;
		}
		else {
			std::cout << "Stack is empty." << std::endl; // �p�G���|���šA��X���~���� 
			return T(); // ��^�w�]��
		}
	}
	~JWang_Stack()
	{
		while (!isEmpty())  // ����|�����Ů� 
		{
			pop(); // �q���|������������ 
		}
	}

};

template<class T>
class JWang_List // �w�q�@�ӼҪO���O�A�W�� JWang_List 
{
	typedef struct StackNode // �����w�q�@�ӵ��c�A�N��������`�I 
	{
		T value; // �`�I�� 
		StackNode *next; // ���V�U�@�Ӹ`�I������ 
	};

	StackNode *head , *tail; // ����Y�M������ 

public:
	JWang_List() : head(NULL), tail(NULL)  // �w�]�غc�l�A��l���Y�M�����Ь� NULL 
	{}

	bool isEmpty() const // �ˬd���O�_���� 
	{
		return head == NULL;
	}
	void ins(const T inValue)  // ���J������������ 
	{
		try
		{
			StackNode* newNode = new StackNode(); // �Ыؤ@�ӷs�`�I 
			newNode->value = inValue;  // �]�w�`�I���� 
			newNode->next = nullptr; // ��l�ƤU�@�ӫ��Ь� nullptr 
			if (!head)  // �p�G���O�Ū�
			{
				head = tail = newNode; // �]�w�Y�M�������s�`�I 
			}
			else // �_�h�K�[�s�`�I������ç�s������ 
			{
				tail->next = newNode;
				tail = newNode;
			}

		}
		catch (bad_alloc& ba)
		{
			cerr << endl << "bad_alloc on stack caught: " << ba.what() << endl; // �����ʺA���t�O���饢�Ѫ��ҥ~ 
		}

	}
	void getHead(T& outValue) // �������Y������ 
	{
		if(head)
			outValue =  head->value;
	}
	void del()	//delete head
	{
		if (head)
		{
			StackNode* temp = head; // �Ȧs�Y�`�I
			head = head->next;  // ��s�Y���� 
			delete temp;  // �R���Ȧs���`�I 
		}
	}
	void del(T& outValue)	//delete head and output value
	{
		if (head)
		{
			outValue = head->value; // ����Y�`�I���� 
			StackNode* temp = head;  // �Ȧs�Y�`�I 
			head = head->next; // ��s�Y���� 
			delete temp; // �R���Ȧs���`�I 
		}
	}
	void clearUp() // �M����� 
	{
		while (head)
		{
			StackNode* temp = head; // �Ȧs�Y�`�I 
			head = head->next;  // ��s�Y���� 
			delete temp; // �R���Ȧs���`�I 
		}
		tail = nullptr; // �N�����г]�� nullptr

	}

	~JWang_List()  // �M����� 
	{
		clearUp();
	}

};

// ��ƥΩ��ˬd�r�Ŧꤤ���A���O�_����
// ��^��:
// 0: �A���ǰt���T
// 1: �h�l�����X�A�� ')'
// 2: �h�l���}��A�� '('
int isVlaidParentheses(string expression)	// 0: OK , 1:extra close parentheses , 2 :extra open parentheses
{
	JWang_Stack<char> parentheses;  // �Ыؤ@�Ӧr�Ű��|�Ӧs�x�}��A�� 
	int status = 0;  // �w�]�����A�� 0�A��ܥثe�S�����~ 
	for (char c : expression)
	{
		if (c == '(') // �p�G��e�r�ŬO�}��A�� 
		{
			parentheses.push(c); // �N�����J���| 
		}
		else if (c == ')' ) // �p�G��e�r�ŬO���X�A�� 
		{
			if (parentheses.isEmpty()) // �p�G���|���šA�o�N���ۨS���ǰt���}��A�� 
			{
				status = 1; // �]�m���A��1�A��ܦh�l�����X�A�� 
				//cout << "Error 2 : there is one extra close parentheses" << endl;
				return status; // ������^���G
			}

			// stack is not empty
			char top = parentheses.getTop(); // ������|�������r�� 
			parentheses.pop(); // �q���|�������Ӧr�� 

			if ((c == ')' && top != '(') )  // �ˬd���|�������r�ŬO�_�P��e�����X�A���ǰt 
			{
				status = 1; // �]�m���A��1�A��ܦh�l�����X�A�� 
				//cout << "Error 2 : there is one extra close parentheses" << endl;
				return status;  // ������^���G
			}
		}
	}
	if (!parentheses.isEmpty()) // �ˬd���|�O�_���� 
	{
		status = 2; // �p�G�����šA�o�N���ۦ��h�l���}��A��
	} 
		//cout << "Error 2 : there is one extra open parentheses" << endl;

	return status; // ��^�̲ת��A 
}
int isValidOtherExample(string expression)
//�A���O�_�ǰt
//�O�_�s�b�s�򪺹B���
//��F�����A�����O�_�ŦX�����F�����W�h
//�B��ŬO�_�b�X�A����m
{
	/*
	1. //Parentheses Match
	2. continuous operator
	3. example :  )9
	4. example :  +)
	5. example :  5(
	7.  example : (+
	6. first is operator
	7. empty string -->there is one extra operator

	output:
	status = 0. OK
	status = 1. Error 3 : there is one extra operand
	status = 2. Error 3 : there is one extra operator
	status = 3. Error 3 : It is not infix in the parentheses

	** 1+2() --> It is not infix in the parentheses
	*/
	//JWang_Stack<char> parentheses;
	int status = 0; // ��l�ƪ�^�����A��0�A��ܥثe�S�����~ 
	char lastChar = '\0';  // �Ω�O�s�W�@�Ӧr�Ū��ܶq
	if(expression.length() == 0) return 2; // �ˬd�Ŧr�Ŧ걡�p 
	for (int i = 0; i < expression.length(); ++i) // �M���r�Ŧꤤ���C�Ӧr�� 
	{
		char c = expression[i];
		if (c == '(')
		{
			if (i + 1 < expression.length()) // �ˬd"()"�o�ر��p 
			{
				if (expression[i + 1] == ')')
				{
					status = 3;
					//cout << "Error 3 : It is not infix in the parentheses" << endl;
					return status;
				}
			}
			else if (isdigit(lastChar))	//9(
			{
				status = 1;
				//cout << "Error 3 : there is one extra operand" << endl;
				return status;
			}
			//parentheses.push(c);
		}
		else if (c == ')')
		{
			if (lastChar == '(')
			{
				status = 3;
				//cout << "Error 3 : It is not infix in the parentheses" << endl;
			}
			else if (lastChar == '+' || lastChar == '-' || lastChar == '*' || lastChar == '/') // �ˬd�O�_���s�򪺹B��� 
			{
				status = 2;
				//cout << "Error 3 : there is one extra operator" << endl;
				return status;
			}

		}
		else if (c == '+' || c == '-' || c == '*' || c == '/')
		{
			if (lastChar == '+' || lastChar == '-' || lastChar == '*' || lastChar == '/' || lastChar == '\0' || lastChar == '(') // �ˬd�B��ŬO�_�b���T����m 
			{
				status = 2;
				//cout << "Error 3 : there is one extra operator" << endl;
				return status; 
			}
		}
		else
		{
			//c is a number
			if (lastChar == ')')
			{
				status = 1;
				//cout << "Error 3 : there is one extra operand" << endl;
				return status;
			}
		}
		lastChar = c;
	}
	if(lastChar == '+' || lastChar == '-' || lastChar == '*' || lastChar == '/') // �ˬd�B��ŬO�_�b�r�Ŧꪺ���� 
    {
        status = 2;
    }
	return status;
}

 //�ˬd���w�⦡���O�_�t���X�k�r�Ū���ơA�u���Ʀr�B�|�ذ򥻹B��š]+�B-�B*�B/�^�M�A���](�B)�^�Q�����X�k�r�� 
int IsVaildChar(string expression)	//-1: OK , other: wierd charater position
{
	// ��J�G�@�Ӧr�Ŧ��F��
   // ��X�G�p�G�Ҧ��r�ų��X�k�A��^-1�A�_�h��^�D�k�r�Ū���m
	for (int i = 0; i < expression.length(); ++i)
	{
		char c = expression[i];
		if (isdigit(c)) // �p�G�r�ŬO�Ʀr�A�h�~�� 
			continue;
		else if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/')  // �p�G�r�ŬO�A���Υ|�ذ򥻹B��Ť��@�A�h�~�� 
			continue;
		else // �p�G�r�ŬO�D�k�� 
		{
			//cout << c << " is not a  legitimate character.";
			return i; // ��^�D�k�r�Ū���m 
		}
	} // �Ҧ��r�ų��w�g�ˬd�åB���O�X�k��
	return -1; // ��^-1���OK 
}

bool IsValidExpression(string expression)
{
	//1. check if weird character
	int tmp = IsVaildChar(expression);
	if (tmp != -1) // �p�GIsVaildChar��^�����O-1�A�h��ܦ��D�k�r�� 
	{
		cout << expression[tmp] << " is not a  legitimate character.";
		return false; // ��^��F�����X�k 
	}
	//2. check if parentheses match or continuous operator
	tmp = isVlaidParentheses(expression);
	if (tmp == 1 || tmp == 2)  // �ھ�isVaildParentheses����^�ȶi���ˬd 
	{
		if (tmp == 1) // ��X���������~�H�� 
			cout << "Error 2 : there is one extra close parentheses" << endl;
		else
			cout << "Error 2 : there is one extra open parentheses" << endl;
		return false; // ��^��F�����X�k 
	}

	//3. other example
	tmp = isValidOtherExample(expression);  
	if (tmp != 0) // �p�GisValidOtherExample��^�����O0�A�h��ܦ���L���������~  
	{
		// �ھڪ�^�ȿ�X���������~�H��
		if (tmp == 1)
			cout << "Error 3 : there is one extra operand" << endl;
		else if (tmp == 2)
			cout << "Error 3 : there is one extra operator" << endl;
		else if (tmp == 3)
			cout << "Error 3 : It is not infix in the parentheses" << endl;
		return false; // ��^��F�����X�k 
	}

	return true; // �p�G�Ҧ��ˬd���q�L�A��^true��ܪ�F���O�X�k��


}


int getPrecedence(char op) //��������[�� 
{
	int weight = 0; // ��l�ƹB��Ū��u�����v����0 
	switch (op)  // �ھڿ�J���B��ų]�w�v�� 
	{
	case '+': // �p�G�O�[�k 
	case '-': // �Ϊ̬O��k 
		weight = 1; // �]�m�v����1 
		break;
	case '*': // �p�G�O���k 
	case '/': // �Ϊ̬O���k 
		weight = 2; // �]�m�v����2
		break; 
		break;
	}
	return weight;
}

void infixToPostfix(string infix, JWang_List<char>& answer) // �N�����F���ഫ������F���A���ݭn�A���Ӫ�ܹB�⪺���� 
{

	JWang_Stack<char> operatorStack; // �ŧi�@�Ӱ��|�Ӧs�x�B���
    int IsLastdigit = 0;  // �ܶq�Ω�l�ܫe�@�r�ŬO�_���Ʀr�A��l�Ƭ�0
	for (int i = 0; i < infix.length(); ++i)
	{
	    char c = infix[i];
		if (isdigit(c)) // �p�G��e�r�ŬO�Ʀr 
		{
		    answer.ins(c); // �N�ӼƦr�K�[���X�C�� 
		    while(i+1 < infix.length())
            {
                char nextc = infix[i+1];
                if(isdigit(nextc)) // �p�G�U�@�Ӧr�Ť]�O�Ʀr 
                {
                    answer.ins(c);
                    i++;
                    continue;
                }
                else
                {
                    break; // ���O�Ʀr�A���X�j�� 
                }

            }
            answer.ins(','); // ���J���j�šA�Ω���j�Ʀr�M�B��� 

		}
		else if (c == '(') // �p�G�O���A�� 
		{
		    IsLastdigit = 0;
			operatorStack.push(c);
		}
		else if (c == ')') // �p�G�O�k�A�� 
		{
		    IsLastdigit = 0;
			while (!operatorStack.isEmpty() && operatorStack.getTop() != '(')
			{
				answer.ins(operatorStack.getTop());
				answer.ins(',');
				operatorStack.pop();
			}
			if (!operatorStack.isEmpty() && operatorStack.getTop() == '(') // �������A�� 
			{
				operatorStack.pop(); 
			}
			else
			{
				// ��F���L�ġA�]���ʤ֥��A��
			}


		}
		else // �p�G�O�B��� 
		{
		    IsLastdigit = 0; // ����|�����šA�B���|�������B����u���Ťj��ε����e�B��Ů� 
			while (!operatorStack.isEmpty() && operatorStack.getTop() != '(' &&
				getPrecedence(c) <= getPrecedence(operatorStack.getTop()))
			{
				answer.ins(operatorStack.getTop());
				answer.ins(',');
				operatorStack.pop(); // �N��e�B��ű��J���| 
			}
			operatorStack.push(c);
		}
	}

	while (!operatorStack.isEmpty()) // �N���|���Ѿl���Ҧ��B��ŲK�[���X�C�� 
	{
		if (operatorStack.getTop() == '(')
		{
			// ��F���L�ġA�]���ʤ֥k�A��
		}
		answer.ins(operatorStack.getTop());
		answer.ins(',');
		operatorStack.pop();
	}


}



int main()
{

	while (true)
	{

		string expression;
		int command = -1;
		cout << endl << "*********************************";
		cout << endl << "*Arithmetic Expression Evaluator*";
		cout << endl << "0.Quit";
		cout << endl << "1. Infix2Postifix Transformation";
		cout << endl <<"*********************************";
		cout << endl << "Input a choice (0 , 1)";

		cin >> command;
		cin.ignore(MAX_LEN, '\n');
		if (command == 0)  // �p�G��ܰh�X
			break;
		else if (command == 1) // �p�G��ܱN�����ഫ����� 
		{
			cout << endl << "Input an infix expression: ";
			getline(cin, expression);
			expression.erase(remove_if(expression.begin(), expression.end(), ::isspace), expression.end()); // �����r�Ŧꤤ���Ҧ��Ů�
			//Mission : Detect is Valid
			if (IsValidExpression(expression)) // �ˬd��J����N��F���O�_�X�k 
			{
				cout <<endl<< "It is a legitimate infix expression" ;
				JWang_List<char> answer;
				infixToPostfix(expression, answer);	// �N�X�k�������F���ഫ�����Φ�
				cout << endl << "Posfix expression: "; // �L�X����F�� 
				string ans="";
				while (!answer.isEmpty())	//print
				{
					char tmp = 0;
					answer.del(tmp);
					ans+=tmp;
					//cout << tmp;
					//if (!answer.isEmpty())
						//cout << ",";
				}
				for(int i=0; i<ans.length()-1; i++)
                {
                    cout << ans[i];
                }
				cout << endl;
			}

		}

		

	}
	system("pause");
	return 0;
}

