//11127247�i�ů� 
#include <iostream>
#include <cstring>
using namespace std;

class Check{
	

	
	public:
		
		string inS;

		int countleft=0; //���A�����ƶq 
	    int countright=0; //�k�A�����ƶq 
	    int i=0;  
	    
	    bool v=true;
		
		bool checkOnP(){ //�P�_�O�_��'+','-','*','/','(',')'�μƦr 
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
		bool checkRule(){ //�P�_�B��Ÿ���Ʀr���e�ᶶ�ǬO�_�X�z 
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
		bool checkAll(string in){ //��X�_�ӧP�_�O���O�X�k���|�h�B�� 
			
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

class aList{ //�s�񤤧����Ǫ�linked list 
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
	   	void p(){ //�L�X 
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

		bool isEmpty(){ //�P�_�s��B��Ÿ���linked list�O�_���� 
		
			if(head==NULL)
				return true;
			
			return false; 
		}
		
		void push(string s){ //���|�B��Ÿ� 
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
		void pop(){ //�R�����|���̤W�� 
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
		string getTop(){ //�^�ǰ��|���̤W������ 
			stack *head2=head;
		    string top;
			
		   	while(head2->next!=NULL)
				head2=head2->next;	
			
			top=head2->value;
			return top;
			
		}


		int setInstack(){ //�]�w�Ÿ��b���|�����B���v 
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
		int setIncoming(string s){ //�]�w�Ÿ��ǳƭn��i�h���|�ɪ��B���v 

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
	
	if(isOk){ //�O�X�k���|�h�B�� 
		cout<<endl<<"Postfix expression: ";
		list.setS(infixS);
		
		for(i==0;i<infixS.length();i++){
			if(infixS[i]=='+'||infixS[i]=='-'||infixS[i]=='*'||infixS[i]=='/'){
		 		
				result.alist(s);
				s=infixS[i];  
				j=list.setIncoming(s); //�U��i���Ÿ��B���v 
				k=list.setInstack(); //�b���|�����Ÿ��B���v 

				if(j>k){ //�n��i���Ÿ��B���v�j����|�̤W�����Ÿ��B���v 
					list.push(s); //���| 
					s.clear();
				}
				else if(j<=k){ //�n��i���Ÿ��B���v�p����|�̤W�����Ÿ��B���v  
					t=s;
					while(j<=k){
						s=list.getTop(); //���o���|�̤W�������� 
						result.alist(s);
						list.pop(); //�R�����|�̤W�������� 
						k=list.setInstack();
					}
					
					list.push(t); //�N�Ÿ���J���| 
					s.clear();
			    }
			}
			else if(infixS[i]=='('){
				s=infixS[i];
				list.push(s);//�N�Ÿ���J���| 
				s.clear();
			}
			else if(infixS[i]==')'){

				result.alist(s);  
				s.clear();
				s=list.getTop();
				
				while(s!="("){ //����Ÿ�����'('����ɡA�q�̤W���@�@�N�B��Ÿ�����Ǧ� 
					result.alist(s);
				 	list.pop();
				 	s=list.getTop();
			 	}
			 	if(s=="(")
			 	 	list.pop();  
				
				s.clear();
			}
			else if(infixS[i]>=48&&infixS[i]<=57) {

			    s=s+infixS[i]; //�r����r�� 
			    
			    
			    if(i==infixS.length()-1||(infixS[i]=='+'||infixS[i]=='-'||infixS[i]=='*'||infixS[i]=='/')){
			    	result.alist(s);
			    	s.clear();							    		
			    }
		    }
		}
		
		while(!list.isEmpty()){ //��r���ˬd�����ɦp�G���|�٦��B��Ÿ��N�q�W��������Ǧ� 
			s=list.getTop();
			result.alist(s);
			list.pop();
			s.clear();
	 	}
		result.p(); //�L�X��Ǧ� 
	}
	
	
	
	
	
	return 0;
} 


