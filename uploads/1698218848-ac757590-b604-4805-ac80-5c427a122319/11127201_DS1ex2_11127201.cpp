// 11127201 陳品妤 
#include<iostream> 
#include<string>
#include<cstdlib>

#define MAX_LEN 255  // maximum string length 
using namespace std ;

class Node {
	
	public:
		
		string *stack ;
		string formula = "", error1char = ""  ;
		int num = -1 ;
		int number = 0, plusCount = 0, minusCount = 0, multiplyCount = 0, divideCount = 0;
		int totalbrackets = 0, leftbrackets = 0, rightbrackets = 0 ;
		bool isdigit = false, istogether = false, error3 = false ;
		
		struct SequenceToken {
			string element ;  // 字符元素 
			SequenceToken *next ;
		};
		
		SequenceToken* head = NULL ; // 表達式串列頭 
		SequenceToken* walk = NULL ; // 表達式串列遍歷 
		SequenceToken* tail = NULL ; // 表達式串列尾巴 

		void push( string element ) { // 將次字串接在後序的Link中 		
			if (tail == NULL) { // 是空的情況創建新節點 
            	tail = new SequenceToken;
            	head = tail;
        	} // if 
			else {
           		tail->next = new SequenceToken;  // 在尾巴創建新節點 
            	tail = tail->next; 
        	} // else 
        	
        	tail->next = NULL;
       		tail->element = element;
		} // push()
		
		struct SequenceSybol {
			int Syboljudge = 0 ; // 符號的值 
			string element ; // 符號元素 
			SequenceSybol *next ;  
		};
				
		SequenceSybol* headsy = NULL ; // 符號串列頭 
		SequenceSybol* tailsy = NULL ; // 符號串列尾  
		SequenceSybol* walksy = NULL ; //符號串列遍歷 


		void Sybolpush( string element ) { // 將操作字符的字串接在符號的Link中 
			tailsy->next = new SequenceSybol ;
			tailsy = tailsy->next ;
			tailsy->next = NULL ;
			tailsy->element = element ;  
			tailsy->Syboljudge = Sybol( element ) ; // 定義符號大小  
		} // Sybolpush()
		
		string Sybolpop() { // 拿出Link內最後一個 (取出最後一個操作符) 
			string temp = tailsy->element ; // 紀錄最後一個的符號 
			walksy = headsy ; // 將遍歷設在頭讓他往後跑 
			
			if (walksy != NULL && walksy->next != NULL) { // 防止只有一個元素或為空 
    			while (walksy->next->next != NULL) 
        			walksy = walksy->next; // walk指到tail的前一個 
    
    			delete tailsy; // 刪除最後一個 
    			walksy->next = NULL; // 刪掉那個設為NULL  
    			tailsy = walksy; // tail指到新的Link最後一個
			} // if 		
			
			return temp ;	
		} // Sybolpop()
		
		void Transform() { // 將中序轉為後序
			if ( tailsy == NULL ) { // 符號Link內是空的，先設一個屬性為 0 的字串 
				tailsy = new SequenceSybol ;
				headsy = tailsy;
				walksy = tailsy ;
				tailsy->next = NULL ;
				tailsy->Syboljudge = 0; // 沒有任何符號設0 
				tailsy->element = "" ; // 新節點的元素設置 
			} // if 
			for ( int i = 0 ; i < formula.length() ; i++ ) { // 將一維陣列的值接到Link中 
				if ( stack[i].empty() ) break ; // 當一維陣列碰到空陣列就停下來 
			
				if ( IsSybol( stack[i] ) ||  stack[i] == "(" || stack[i]== ")" ) { // 是符號 

					if ( Sybol( stack[i] ) == 0 ) Sybolpush( stack[i] ) ; // 碰到 "(" 就直接添加符號中當作新的底 
					else if ( Sybol( stack[i] ) == 3 ) { // 碰到 ")" 就拿出符號Link內的東西直到把 "(" 拿出 並且放入後序Link中 
						while ( tailsy->Syboljudge != 0 ) push( Sybolpop() ) ; // 拿出 "("後的所有符號 並且放入後序Link中 
						Sybolpop() ; // 將 "(" 拿出 
					} // else if 
					else if ( Sybol( stack[i] ) > tailsy->Syboljudge ) Sybolpush( stack[i] ) ; // 當符號屬性的數值比前一個大就將其疊上去 
					else { // 符號屬性的數值跟前一個一樣大或比較小就拿出符號內的東西拿到底部為止 並且放入後序Link中 
						while ( ( tailsy->Syboljudge >= Sybol( stack[i] ) - 1 ) && tailsy->Syboljudge != 0 ) push( Sybolpop() ) ; // 拿出底部後的所有符號 並且放入後序Link中 
						Sybolpush( stack[i] ) ; // 將一樣大或比較小的符號丟入符號的Link中 
					} // else 

				} // if 
				else {
					if ( tail == NULL ) { // 當 tail Link中是空的給他新的空間 
						tail = new SequenceToken ;
						head = tail;
						walk = tail ;
						tail->next = NULL ;
						tail->element = stack[i] ;
					} // if 
					else push( stack[i] ) ; // 丟入後序中 
				} // else if 
			} // for  
			
			while ( headsy->next != NULL ) push( Sybolpop() ) ; // 將剩下的符號都放入後序Link中 
		} // Transform()
		
    	void Postfix() { // 輸出內容後序 
    		while ( walk != NULL ) {
	    		cout << walk->element ;
	    		if ( walk->next != NULL ) cout << ", " ;
	    		walk = walk->next ;
			} // while
			
			cout << endl << endl ;
		} // Postfix()
		
		void *Setstack () {  // 創建一個動態陣列來做儲存  
			stack = new string[formula.length()] ;  // 儲存表達式得符號跟數字 
		} // Setstack() 

		void GetToken() { // 將輸入的字串切成各個數字和符號 
			for ( int i = 0 ; i < formula.length() ; i++ ) {
				// 遍歷輸入式子的每個符號 
				if ( !formula.substr( i, 1 ).empty() && ( formula.substr( i, 1 ).compare( " " ) != 0 ) ) {
					//檢查當前符號不是空的且不是空格 
					if ( Isdigit(formula.substr(i, 1)) ) isdigit = true ; // 看此格是否為數字 
					else isdigit = false ;  
					
					if ( istogether ) istogether = false ;  // 處理過 
					else if ( !isdigit ) num++ ; // 是符號就要先換因為此格是數字 
					else if ( num == -1 ) num++ ; // 是數字的時候並且數字在第一個要將 -1 變為 0 
					
					stack[num] = stack[num] + formula.substr( i, 1 ) ; //當前字符連結到儲存stack的相對位置   
					if ( !isdigit ) {
						num++;
						istogether = true ; // 當是符號的時候直接換到下個陣列 ，表示已處理 
					} // if 
				} // if 
			} // for
		} // GetToken() 
			
		int Sybol( string element ) { // 看此字串是哪個符號 
 			if (element == "+" || element == "-") return 1; //(+-一起看)
        	if (element == "*" || element == "/") return 2;//(*/一起看)
        	if (element == "(") return 0;
        	if (element == ")") return 3;
		} // Sybol()
		
		bool IsSybol( string element ) { // 看此是不是符號號 
 			if (element == "+" || element == "-" || element == "*" || element == "/" ) return true;
			else return false ;
		} // IsSybol()
		
		
		int CountSybol() { // 紀錄每個符號和數字數量 傳送錯誤訊息 
			bool stop = false ;
			bool special = false ;
            for ( int i = 0 ; i < formula.length() ; i++ ) {
                if ( stack[i].empty() ) break ; // 式子是空的 
                
                if ( Isdigit( stack[i] ) ) number++ ; // 是數字 
                else if ( stack[i] == "+"  ) plusCount++ ;  // 是加號 
                else if ( stack[i] == "-"  ) minusCount++ ; // 是減號 
                else if ( stack[i] ==  "*" ) multiplyCount++ ; //是乘號 
                else if ( stack[i] ==  "/" ) divideCount++ ; //是除號 
                else if ( stack[i] == "("  ) { 
                    leftbrackets++;//是左括弧 
					totalbrackets++ ; // 括號總數量 
					special = true ; /// 有左括弧 
                    if ( i != formula.length() - 1 ) {
                    	// 檢查左括號後面合法嗎 
                        if (  IsSybol( stack[i+1] )  || stack[i+1] == ")")
							  	error3 = true ; //括號後不能是運算符號或者右括號  像是()或(-3) 
                    } // if 
                } // else if
                else if ( stack[i] ==  ")"  ) {
                	if ( !special ) return 3; // 是)3(的狀況 
                	
                    rightbrackets++; // 是右括弧 
					totalbrackets-- ; // 左邊加右邊減 
                    
                    if ( i != 0 ) {
                    	// 檢查右括號後面合法嗎 
                        if (  IsSybol( stack[i-1] ) || stack[i-1] == "(" ) 
							error3 = true ; //括號後不能是運算符號或者右括號 像是(11-)
                    } // if
                
                } // else if 
                else if ( !stop ){
                    // 既不是數字也不是運算符號 
					error1char = stack[i]; // 錯誤符號 
					stop = true ;  // 停止檢查 
				} // else if 
            } // for
            
            
       		if ( error1char[0] != '\0' ) return 1; // 看有沒有不是運算符號的東西 
         	else if (leftbrackets > rightbrackets) return 2; // 看左括號有沒有大於右括號  
        	else if (leftbrackets < rightbrackets ) return 3;// 看右括號有沒有大於左括號  
        	else if (error3) return 4;  
        	else if (number - 1 < (plusCount + minusCount + multiplyCount + divideCount)) return 5; // 如果操作的數少於運算符號數-1  運算符號比數字多   
        	else if (number - 1 > (plusCount + minusCount + multiplyCount + divideCount)) return 6; // 如果運算符號少於操作的數字-1  數字比運算符號多 
 			else return 7; // 正確的 
        } // CountSybol()
        
        
        void Output( int errorCode ) { // 輸出 
            switch (errorCode) {
            case 1: // 存在不合法字符 
                cout << "Error 1: " << error1char << " is not a legitimate character." << endl ;
                break;
            case 2: // 存在多餘左括號 
                cout << "Error 2: There is one extra open parenthesis." << endl ;
                break;
            case 3: // 存在多餘右括號  
                cout << "Error 2: There is one extra close parenthesis." << endl ;
                break;
            case 4: // 括弧內不合法 
                cout << "Error 3: It is not infix in the parentheses." << endl;
                break;
            case 5: // 存在多餘運算符號 
                cout << "Error 3: There is one extra operator." << endl ;
                break;
            case 6:  // 存在多餘操作數的數字 
                cout << "Error 3: There is one extra operand." << endl ;
                break;
            case 7: // 都正確印出來 
                cout << "It is a legitimate infix expression." << endl;
            	cout << "Postfix expression: ";
                Postfix(); // 印出後序 
                break;
        	} // switch
        } // Output()
        
        void Reset() { // 初始化 
            num = -1 ;
            number = 0, plusCount = 0, minusCount = 0, multiplyCount = 0, divideCount = 0;
			totalbrackets = 0, leftbrackets = 0, rightbrackets = 0;
            isdigit = false, istogether = false, error3 = false ;
            formula = "", error1char = "" ;
            
            // 釋放動態分配內存 
            delete[] stack; 
            stack = NULL ;
            
            // 釋放節點 
            while (head != NULL) {
        		SequenceToken* temp = head;
        		head = head->next;
        		delete temp;
   	 		} //while
   	 		
   	 		head = NULL, walk = NULL, tail = NULL;
    		headsy = NULL, tailsy = NULL, walksy = NULL;
        } // Reset()
		
		bool Isdigit( string num ) { // 判斷數字 
        	int length = num.length();
        	for (int i = 0; i < length; i++) {
            	if (num[i] < '0' || num[i] > '9') {
                	return false;
           	 	} // if 
        	} // for
        	
       		return true;
		} //  Isdigit
		
		void Operate() { // 當輸入值為 1 
			getline( cin, formula ) ; // 讀式子 
			Setstack() ; // 創建一個動態陣列來做儲存 
			GetToken() ; // 將輸入的字串切成各個數字和符號
			int errorCode = CountSybol(); // 切割看有錯誤與否 
			if (  errorCode == 7 ) Transform(); // 轉換成後序 
			Output( errorCode ) ; 
			Reset() ; // 重置 
		} // operate()
};


int main(void) {
	Node node ;
	int command = 0 ; // user command
	string infixS ;
 	do {
		cout << endl << "*Arithmetic Expression Evaluator *" ;
		cout << endl << "*0. QUIT                         *" ;
		cout << endl << "*1. Infix2postfix Transformation *" ;
		cout << endl << "**********************************" ;
		cout << endl << "Input a choice(0, 1):" ;
		cin >> command;  // get the command(獲得指令)
		
		cin.ignore( MAX_LEN, '\n' ) ; // clear the input buffer
		
		switch ( command ) {
			case 0:break;
			case 1:
					cout << endl << "Input an infix expression:" ;
            		node.Operate() ;									   
					break ;
			default: cout << endl << "Command dose not exist!" 	<< endl;								
		} // end switch
	} while( command != 0 ) ;
	
	node.stack = NULL ;
	system( "pause" ) ; // pause the execution 暫停執行 ( system 執行操作命令，pause 用於暫停執行等輸入，執行會顯示案下任意鍵繼續 )
	return 0 ;
} // end main
