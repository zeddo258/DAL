//11127247張嘉紜 
#include <iostream>
#include <cstring>
using namespace std;

class Check{
	

	
	public:
		
		string inS;

		int countleft=0; //左括號的數量 
	    int countright=0; //右括號的數量 
	    int i=0;  
	    
	    bool v=true;
		
		bool checkOnP(){ //判斷是否為'+','-','*','/','(',')'或數字 
			if((inS[i]>=48&&inS[i]<=57)||inS[i]=='+'||inS[i]=='-'||inS[i]=='*'||inS[i]=='/'||inS[i]=='('||inS[i]==')'){
  				if(inS[i-1]=='/'&&inS[i]=='0'){
			    		
				}
				
				if(inS[i]=='(')
			    	countleft++;
			    else if(inS[i]==')')
			    	countright++;
			    
			    return true;
		    }
		    
		    return false;
		}
		bool checkRule(){ //判斷運算符號跟數字的前後順序是否合理 
			v= true;
			if(i==inS.length()-1){
				if(inS[i]==')'||(inS[i]>=48&&inS[i]<=57))
					return true;
				else
					return false;
			}
			else if(inS[i]>=48&&inS[i]<=57){
				if(inS[i+1]==')'||(inS[i+1]=='+'||inS[i+1]=='-'||inS[i+1]=='*'||inS[i+1]=='/')||(inS[i+1]>=48&&inS[i]<=57))
	 				return true;
				else
					return false;
			}
			if((inS[i]=='+'||inS[i]=='-'||inS[i]=='*'||inS[i]=='/')){
				if(inS[i+1]=='('||(inS[i+1]>=48&&inS[i]<=57))
	 				return true;
				else
					return false;
			}
			else if(inS[i]=='('){
				if(inS[i+1]!='+'||inS[i+1]!='-'||inS[i+1]!='*'||inS[i+1]!='/'||inS[i+1]=='('||(inS[i+1]>=48&&inS[i+1]<=57))
					return true;
				else
					return false;
		    }
		    else if(inS[i]==')'){
				if(inS[i+1]=='+'||inS[i+1]=='-'||inS[i+1]=='*'||inS[i+1]=='/'||inS[i+1]==')')
					return true;
				else
					return false;
		    }
			
		}
		bool checkAll(string in){ //整合起來判斷是不是合法的四則運算 
			
			inS=in;
			for(i = 0; i<inS.length(); i++){
				if(checkOnP()){
					if(!checkRule()){
                        if(inS[i]=='+'||inS[i]=='-'||inS[i]=='*'||inS[i]=='/')
						  cout<<"Error3:there is one extra operator.";
						else
						  cout<<"Error3:there is one extra operand.";
						  
				  		return false;	
					}
				
			    }
      			else{
      				cout<<"Error1:"<<inS[i]<<" is not a legitimate character.";
				    return false;
      				
				} 
		     	
		     	
		     	if(i==inS.length()-1){
		     		
					if(countleft>countright)
						cout<<"Error2:there is one extra open parenthesis.";
					else if (countleft<countright)
						cout<<"Error2:there is one extra close parenthesis.";
					else {
					    cout<<"It is a legitimate infix expression.";
					    return true;
				    }
					return false;
			    }
						

			
			}
			
			
			
			
			 

			    
			    
			      
			  
		}
	
};

class aList{ //存放中序轉後序的linked list 
	public:
		typedef struct Pointer{
		  string value;
		  Pointer *next;
	    }result;
	 
		result *head=NULL;
		
		void alist(string s){
			result *tail;
			result *temp;
			
			if(s.empty())
				return;
 			if(head==NULL){
				head=new result;
				head->value=s;
				head->next=NULL;
			}
			else{
			  	temp=head;
			  	while(temp->next!=NULL)
			  		temp=temp->next;
		   		tail=new result;
		   		tail->value=s;
		   		tail->next=NULL;
		   		temp->next=tail;
		    }
	    }
	   	void p(){ //印出 
	   		result *tail;
		 	result *temp;
			tail=head;
			
			while(tail->next!=NULL){
				cout<<tail->value<<", ";
				tail=tail->next;
			}
			if(tail->next==NULL)
				cout<<tail->value;
		}
		

	
};
class Stack{
	

	
	public:
		typedef struct Pointer{
		  string value;
		  Pointer *next;
	    }stack;
	

		stack *head=NULL;

		int inStack,inComing;
		string s;
		void setS(string inS){
			s=inS;
		}

		bool isEmpty(){ //判斷存放運算符號的linked list是否為空 
		
			if(head==NULL)
				return true;
			
			return false; 
		}
		
		void push(string s){ //堆疊運算符號 
			stack *temp;
			stack *tail;
				if(head==NULL){
					head=new stack;
					head->value=s;
					head->next=NULL;
				}
				else{
		
					temp=head;

			  		while(temp->next!=NULL)
			  			temp=temp->next;
					
		   			tail=new stack;
		   			tail->value=s;
		   			tail->next=NULL;
		   			temp->next=tail;
		   		
			    }
            
		}
		void pop(){ //刪掉堆疊的最上面 
			stack *head2=head;
            stack *tail;
            if(head2->next==NULL){
            	tail=head;
            	head=NULL;
            	delete head2;
            	head2=NULL;
		 	}
		 	else{
			 
				while(head2->next->next!=NULL)
					head2=head2->next;
				
				tail=head2->next;
				head2->next=NULL;
				delete tail;
				tail=NULL;
				
	    	}
			
		}
		string getTop(){ //回傳堆疊中最上面的值 
			stack *head2=head;
		    string top;
			
		   	while(head2->next!=NULL)
				head2=head2->next;	
			
			top=head2->value;
			return top;
			
		}


		int setInstack(){ //設定符號在堆疊中的運算權 
			string top;

			inStack=0;
			
			if(head==NULL)
				inStack = 0;
	
			else{
				top=getTop();
				if(top=="(")
					inStack=0;
				else if(top==")")
					inStack=-1;
				else if(top=="+"||top=="-")
					inStack=1;
				else
					inStack=2;
			}
			return inStack;
		}
		int setIncoming(string s){ //設定符號準備要放進去堆疊時的運算權 

			if(s=="(")
				inComing=4;
			else if(s==")")
				inComing=-1;
			else if(s=="+"||s=="-")
				inComing=1;
			else
				inComing=2;
			
			return inComing;
		}

	
	
}; 




int main() {
	int command,i,j,k;
	string infixS,s,t;
    Check my;
    Stack list;
    aList result;
    bool isOk;
    
	
	cout<<endl<<"*Arithmetic Expresion Evaluator*";
	cout<<endl<<"*0.QUIT                        *";
	cout<<endl<<"*1.infix2postfix Transfomation *";
	cout<<endl<<"********************************";
	cout<<endl<<"Input a choice(0, 1): ";
	cin>>command;
	cout<<endl<<"Input an infix expression: ";
	if(command==0)
	  return 0;
	cin>>infixS;
	isOk=my.checkAll(infixS);  
	
	if(isOk){ //是合法的四則運算 
		cout<<endl<<"Postfix expression: ";
		list.setS(infixS);
		
		for(i==0;i<infixS.length();i++){
			if(infixS[i]=='+'||infixS[i]=='-'||infixS[i]=='*'||infixS[i]=='/'){
		 		
				result.alist(s);
				s=infixS[i];  
				j=list.setIncoming(s); //愈放進的符號運算權 
				k=list.setInstack(); //在堆疊中的符號運算權 

				if(j>k){ //要放進的符號運算權大於堆疊最上面的符號運算權 
					list.push(s); //堆疊 
					s.clear();
				}
				else if(j<=k){ //要放進的符號運算權小於堆疊最上面的符號運算權  
					t=s;
					while(j<=k){
						s=list.getTop(); //取得堆疊最上面的元素 
						result.alist(s);
						list.pop(); //刪除堆疊最上面的元素 
						k=list.setInstack();
					}
					
					list.push(t); //將符號放入堆疊 
					s.clear();
			    }
			}
			else if(infixS[i]=='('){
				s=infixS[i];
				list.push(s);//將符號放入堆疊 
				s.clear();
			}
			else if(infixS[i]==')'){

				result.alist(s);  
				s.clear();
				s=list.getTop();
				
				while(s!="("){ //直到符號等於'('為止時，從最上面一一將運算符號放到後序式 
					result.alist(s);
				 	list.pop();
				 	s=list.getTop();
			 	}
			 	if(s=="(")
			 	 	list.pop();  
				
				s.clear();
			}
			else if(infixS[i]>=48&&infixS[i]<=57) {

			    s=s+infixS[i]; //字元轉字串 
			    
			    
			    if(i==infixS.length()-1||(infixS[i]=='+'||infixS[i]=='-'||infixS[i]=='*'||infixS[i]=='/')){
			    	result.alist(s);
			    	s.clear();							    		
			    }
		    }
		}
		
		while(!list.isEmpty()){ //當字串檢查完畢時如果堆疊還有運算符號就從上全部放到後序式 
			s=list.getTop();
			result.alist(s);
			list.pop();
			s.clear();
	 	}
		result.p(); //印出後序式 
	}
	
	
	
	
	
	return 0;
} 


