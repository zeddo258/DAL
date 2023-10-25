// 10823323 機械四丙 王婕 

#include "iostream"
#include <string>
#include <regex>

#define MAX_LEN 255
using namespace std;

template<class T>
class JWang_Stack // 定義一個模板類別，名為 JWang_Stack 
{
	typedef struct StackNode // 內部定義一個結構，代表堆疊中的節點 
	{
		T value; // 節點值 
		StackNode *next; // 指向下一個節點的指標 
	};

	StackNode *topPtr;

public:

	JWang_Stack() : topPtr(NULL) // 預設建構子，初始化 topPtr 為 NULL 
	{}

	bool isEmpty() const // 判斷堆疊是否為空，如果 topPtr 為 NULL，則返回 true，否則返回 false 
	{
		return topPtr == NULL;
	}

	void push(T invalue) // 將值加入堆疊頂部 
	{
		try
		{
			StackNode* newNode = new StackNode(); // 創建一個新節點 
			newNode->value = invalue;   // 設定節點的值
			newNode->next = topPtr; // 將新節點的下一個節點設為目前的堆疊頂部 
			topPtr = newNode;  // 更新堆疊頂部指標 
		}
		catch (bad_alloc& ba) // 捕捉動態分配記憶體失敗的例外 
		{
			cerr << endl << "bad_alloc on stack caught: " << ba.what() << endl;
		}
	}
	T getTop()  // 獲取堆疊頂部的值，但不從堆疊中移除 
	{
		return topPtr->value;
	}

	T pop() //pop and return
	{
		if (topPtr != nullptr) {
			StackNode* temp = topPtr; // 暫存目前堆疊頂部的節點 
			topPtr = topPtr->next; // 更新堆疊頂部指標 
			T ReturnValue = temp->value;  // 獲取要返回的值 
			delete temp; // 刪除節點 
			return ReturnValue;
		}
		else {
			std::cout << "Stack is empty." << std::endl; // 如果堆疊為空，輸出錯誤消息 
			return T(); // 返回預設值
		}
	}
	~JWang_Stack()
	{
		while (!isEmpty())  // 當堆疊不為空時 
		{
			pop(); // 從堆疊頂部移除元素 
		}
	}

};

template<class T>
class JWang_List // 定義一個模板類別，名為 JWang_List 
{
	typedef struct StackNode // 內部定義一個結構，代表鏈表中的節點 
	{
		T value; // 節點值 
		StackNode *next; // 指向下一個節點的指標 
	};

	StackNode *head , *tail; // 鏈表的頭和尾指標 

public:
	JWang_List() : head(NULL), tail(NULL)  // 預設建構子，初始化頭和尾指標為 NULL 
	{}

	bool isEmpty() const // 檢查鏈表是否為空 
	{
		return head == NULL;
	}
	void ins(const T inValue)  // 插入元素到鏈表尾部 
	{
		try
		{
			StackNode* newNode = new StackNode(); // 創建一個新節點 
			newNode->value = inValue;  // 設定節點的值 
			newNode->next = nullptr; // 初始化下一個指標為 nullptr 
			if (!head)  // 如果鏈表是空的
			{
				head = tail = newNode; // 設定頭和尾都為新節點 
			}
			else // 否則添加新節點到尾部並更新尾指標 
			{
				tail->next = newNode;
				tail = newNode;
			}

		}
		catch (bad_alloc& ba)
		{
			cerr << endl << "bad_alloc on stack caught: " << ba.what() << endl; // 捕捉動態分配記憶體失敗的例外 
		}

	}
	void getHead(T& outValue) // 獲取鏈表頭部的值 
	{
		if(head)
			outValue =  head->value;
	}
	void del()	//delete head
	{
		if (head)
		{
			StackNode* temp = head; // 暫存頭節點
			head = head->next;  // 更新頭指標 
			delete temp;  // 刪除暫存的節點 
		}
	}
	void del(T& outValue)	//delete head and output value
	{
		if (head)
		{
			outValue = head->value; // 獲取頭節點的值 
			StackNode* temp = head;  // 暫存頭節點 
			head = head->next; // 更新頭指標 
			delete temp; // 刪除暫存的節點 
		}
	}
	void clearUp() // 清空鏈表 
	{
		while (head)
		{
			StackNode* temp = head; // 暫存頭節點 
			head = head->next;  // 更新頭指標 
			delete temp; // 刪除暫存的節點 
		}
		tail = nullptr; // 將尾指標設為 nullptr

	}

	~JWang_List()  // 清空鏈表 
	{
		clearUp();
	}

};

// 函數用於檢查字符串中的括號是否有效
// 返回值:
// 0: 括號匹配正確
// 1: 多餘的閉合括號 ')'
// 2: 多餘的開放括號 '('
int isVlaidParentheses(string expression)	// 0: OK , 1:extra close parentheses , 2 :extra open parentheses
{
	JWang_Stack<char> parentheses;  // 創建一個字符堆疊來存儲開放括號 
	int status = 0;  // 預設的狀態為 0，表示目前沒有錯誤 
	for (char c : expression)
	{
		if (c == '(') // 如果當前字符是開放括號 
		{
			parentheses.push(c); // 將它推入堆疊 
		}
		else if (c == ')' ) // 如果當前字符是閉合括號 
		{
			if (parentheses.isEmpty()) // 如果堆疊為空，這意味著沒有匹配的開放括號 
			{
				status = 1; // 設置狀態為1，表示多餘的閉合括號 
				//cout << "Error 2 : there is one extra close parentheses" << endl;
				return status; // 直接返回結果
			}

			// stack is not empty
			char top = parentheses.getTop(); // 獲取堆疊頂部的字符 
			parentheses.pop(); // 從堆疊中移除該字符 

			if ((c == ')' && top != '(') )  // 檢查堆疊頂部的字符是否與當前的閉合括號匹配 
			{
				status = 1; // 設置狀態為1，表示多餘的閉合括號 
				//cout << "Error 2 : there is one extra close parentheses" << endl;
				return status;  // 直接返回結果
			}
		}
	}
	if (!parentheses.isEmpty()) // 檢查堆疊是否為空 
	{
		status = 2; // 如果不為空，這意味著有多餘的開放括號
	} 
		//cout << "Error 2 : there is one extra open parentheses" << endl;

	return status; // 返回最終狀態 
}
int isValidOtherExample(string expression)
//括號是否匹配
//是否存在連續的運算符
//表達式中括號內是否符合中綴表達式的規則
//運算符是否在合適的位置
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
	int status = 0; // 初始化返回的狀態為0，表示目前沒有錯誤 
	char lastChar = '\0';  // 用於保存上一個字符的變量
	if(expression.length() == 0) return 2; // 檢查空字符串情況 
	for (int i = 0; i < expression.length(); ++i) // 遍歷字符串中的每個字符 
	{
		char c = expression[i];
		if (c == '(')
		{
			if (i + 1 < expression.length()) // 檢查"()"這種情況 
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
			else if (lastChar == '+' || lastChar == '-' || lastChar == '*' || lastChar == '/') // 檢查是否有連續的運算符 
			{
				status = 2;
				//cout << "Error 3 : there is one extra operator" << endl;
				return status;
			}

		}
		else if (c == '+' || c == '-' || c == '*' || c == '/')
		{
			if (lastChar == '+' || lastChar == '-' || lastChar == '*' || lastChar == '/' || lastChar == '\0' || lastChar == '(') // 檢查運算符是否在正確的位置 
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
	if(lastChar == '+' || lastChar == '-' || lastChar == '*' || lastChar == '/') // 檢查運算符是否在字符串的末尾 
    {
        status = 2;
    }
	return status;
}

 //檢查給定算式中是否含有合法字符的函數，只有數字、四種基本運算符（+、-、*、/）和括號（(、)）被視為合法字符 
int IsVaildChar(string expression)	//-1: OK , other: wierd charater position
{
	// 輸入：一個字符串表達式
   // 輸出：如果所有字符都合法，返回-1，否則返回非法字符的位置
	for (int i = 0; i < expression.length(); ++i)
	{
		char c = expression[i];
		if (isdigit(c)) // 如果字符是數字，則繼續 
			continue;
		else if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/')  // 如果字符是括號或四種基本運算符之一，則繼續 
			continue;
		else // 如果字符是非法的 
		{
			//cout << c << " is not a  legitimate character.";
			return i; // 返回非法字符的位置 
		}
	} // 所有字符都已經檢查並且都是合法的
	return -1; // 返回-1表示OK 
}

bool IsValidExpression(string expression)
{
	//1. check if weird character
	int tmp = IsVaildChar(expression);
	if (tmp != -1) // 如果IsVaildChar返回的不是-1，則表示有非法字符 
	{
		cout << expression[tmp] << " is not a  legitimate character.";
		return false; // 返回表達式不合法 
	}
	//2. check if parentheses match or continuous operator
	tmp = isVlaidParentheses(expression);
	if (tmp == 1 || tmp == 2)  // 根據isVaildParentheses的返回值進行檢查 
	{
		if (tmp == 1) // 輸出相應的錯誤信息 
			cout << "Error 2 : there is one extra close parentheses" << endl;
		else
			cout << "Error 2 : there is one extra open parentheses" << endl;
		return false; // 返回表達式不合法 
	}

	//3. other example
	tmp = isValidOtherExample(expression);  
	if (tmp != 0) // 如果isValidOtherExample返回的不是0，則表示有其他類型的錯誤  
	{
		// 根據返回值輸出相應的錯誤信息
		if (tmp == 1)
			cout << "Error 3 : there is one extra operand" << endl;
		else if (tmp == 2)
			cout << "Error 3 : there is one extra operator" << endl;
		else if (tmp == 3)
			cout << "Error 3 : It is not infix in the parentheses" << endl;
		return false; // 返回表達式不合法 
	}

	return true; // 如果所有檢查都通過，返回true表示表達式是合法的


}


int getPrecedence(char op) //先乘除後加減 
{
	int weight = 0; // 初始化運算符的優先級權重為0 
	switch (op)  // 根據輸入的運算符設定權重 
	{
	case '+': // 如果是加法 
	case '-': // 或者是減法 
		weight = 1; // 設置權重為1 
		break;
	case '*': // 如果是乘法 
	case '/': // 或者是除法 
		weight = 2; // 設置權重為2
		break; 
		break;
	}
	return weight;
}

void infixToPostfix(string infix, JWang_List<char>& answer) // 將中綴表達式轉換為後綴表達式，不需要括號來表示運算的順序 
{

	JWang_Stack<char> operatorStack; // 宣告一個堆疊來存儲運算符
    int IsLastdigit = 0;  // 變量用於追蹤前一字符是否為數字，初始化為0
	for (int i = 0; i < infix.length(); ++i)
	{
	    char c = infix[i];
		if (isdigit(c)) // 如果當前字符是數字 
		{
		    answer.ins(c); // 將該數字添加到輸出列表中 
		    while(i+1 < infix.length())
            {
                char nextc = infix[i+1];
                if(isdigit(nextc)) // 如果下一個字符也是數字 
                {
                    answer.ins(c);
                    i++;
                    continue;
                }
                else
                {
                    break; // 不是數字，跳出迴圈 
                }

            }
            answer.ins(','); // 插入分隔符，用於分隔數字和運算符 

		}
		else if (c == '(') // 如果是左括號 
		{
		    IsLastdigit = 0;
			operatorStack.push(c);
		}
		else if (c == ')') // 如果是右括號 
		{
		    IsLastdigit = 0;
			while (!operatorStack.isEmpty() && operatorStack.getTop() != '(')
			{
				answer.ins(operatorStack.getTop());
				answer.ins(',');
				operatorStack.pop();
			}
			if (!operatorStack.isEmpty() && operatorStack.getTop() == '(') // 移除左括號 
			{
				operatorStack.pop(); 
			}
			else
			{
				// 表達式無效，因為缺少左括號
			}


		}
		else // 如果是運算符 
		{
		    IsLastdigit = 0; // 當堆疊不為空，且堆疊頂部的運算符優先級大於或等於當前運算符時 
			while (!operatorStack.isEmpty() && operatorStack.getTop() != '(' &&
				getPrecedence(c) <= getPrecedence(operatorStack.getTop()))
			{
				answer.ins(operatorStack.getTop());
				answer.ins(',');
				operatorStack.pop(); // 將當前運算符推入堆疊 
			}
			operatorStack.push(c);
		}
	}

	while (!operatorStack.isEmpty()) // 將堆疊中剩餘的所有運算符添加到輸出列表中 
	{
		if (operatorStack.getTop() == '(')
		{
			// 表達式無效，因為缺少右括號
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
		if (command == 0)  // 如果選擇退出
			break;
		else if (command == 1) // 如果選擇將中綴轉換為後綴 
		{
			cout << endl << "Input an infix expression: ";
			getline(cin, expression);
			expression.erase(remove_if(expression.begin(), expression.end(), ::isspace), expression.end()); // 移除字符串中的所有空格
			//Mission : Detect is Valid
			if (IsValidExpression(expression)) // 檢查輸入的算術表達式是否合法 
			{
				cout <<endl<< "It is a legitimate infix expression" ;
				JWang_List<char> answer;
				infixToPostfix(expression, answer);	// 將合法的中綴表達式轉換為後綴形式
				cout << endl << "Posfix expression: "; // 印出後綴表達式 
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

