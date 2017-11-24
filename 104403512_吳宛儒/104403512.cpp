#include<iostream>
#include<fstream>
#include <stdlib.h>
using namespace std;
#define MAXLEN 500

typedef struct node * nodePointer;
struct node{
	char data;
	nodePointer link;
};

nodePointer top;

void push(char d)
{
	nodePointer newNode = new node();
	newNode->data = d;
	newNode->link = top;
	top = newNode;
	return;
}

char pop()
{	
	nodePointer temp = top;
	if(!temp)
		return 'N';
	top = top->link;
	char item = temp->data;
	free(temp);
	return item;
}

void clear()
{
	char x = pop();
	while(x!='N')
	{
		x = pop();
	}	
}

int main()
{
	fstream f1,f2;
	f1.open("input.txt",ios::in);
	f2.open("output.txt", ios::out | ios::trunc);
	int i;
	char line[MAXLEN],last;
	// Read each line one time
	while(f1.getline(line,sizeof(line),'\n'))
	{
		// Read each character one time
        for(i=0;i<sizeof(line);i++)
		{
        	if(line[i]=='(')
			{
    			push('(');
			}
			else if(line[i]==')')
			{
				char k = pop();
				if(k=='N')
				{
					// If we meet the')' but the stack is empty
					f2<<"The expression is invalid.\n";
					break;
				}
			}
			else if(line[i]==line[MAXLEN-1])
			{
				// seem as the end of the line
				break;
			}
			// get the last character of the line
			last = line[i];

		}

		char get = pop();
		//if last = '+' or '-' or '*' or '/' means the infix is invalid
		//if g=='N' means the infix is invalid
		if(get=='N' && last != '+' && last != '-' && last != '*' && last != '/')
		{
			// a char array to store postfix
			char postfix[MAXLEN]={};
			// an int to store the index of postfix
			int index = 0;
			
			//Read each line
	        for(int n=0;n<sizeof(line);n++)
			{
	        	// token is the character now we meet
				char token = line[n];
	        	
	        	if(token == line[MAXLEN-1])
	        		break;
	        		
	        	if(token == ')')
				{
					char p = pop();
					while (p != '(' && p !='N')
					{
						postfix[index++] = p;
						p = pop();
					}
				}
				else if(token == '(')
				{
					// if we meet r is '(' , we have to push it back
					push(token);
				}
				else if(token == '+' || token == '-')
				{
					char p = pop();
					while(p=='*' || p=='/' || p=='+' || p=='-')
					{
						postfix[index++] = p;
						p = pop();
					}
					if (p == '(')
					{
						// if we meet r is '(' , we have to push it back
						push(p);
					}
					push(token);
				}
				else if(token == '*' || token == '/')
				{
					char p = pop();
					while(p=='*' || p=='/')
					{
						postfix[index++] = p;
						p = pop();
					}
					if(p =='(' || p=='+' || p=='-')
					{
						// if we meet r is '('or'+'or'-' , we have to push it back
						push(p);
					}
					push(token);
				}
				else
				{
					// if we meet operand
					postfix[index++] = token;
				}
	    	}
	    		// clear the node in the stack
				nodePointer tmp = top;
				while(tmp!=NULL){
					postfix[index++] = tmp->data;
					tmp = tmp->link;
				}			
	    	
			f2 << postfix;
			f2 << "\n";
			clear();
			
			//postfix to its value
	    	for(int i=0;i<sizeof(postfix);i++){
	    		
	    		// token is the character we now meet 
	    		char token = postfix[i];
	    		// declare op1,op2 to store the integer operand
	    		int op1, op2;
	    		 
	    		if(token == postfix[MAXLEN-1])
	        		break;
				// if we meet operator
				if( token =='+' || token =='-' || token =='*' || token =='/')
				{
					op2= pop()-'0';
	        		op1 = pop()-'0';
	        		
	        		switch(token)
					{
		        		case '+': 
							push ((op1+op2)+'0');
		        			break;
		        		case '-': 
							push ((op1-op2)+'0');
		        			break;
		        		case '*': 
							push ((op1*op2)+'0');
		        			break;
		        		case '/':  
							float result = (float)op1/(float)op2 ;
							int num;
							if(op1%op2 != 0)
							{
								num = result + 0.5;
							}
							else
							{
								num = result; 
							}
							push (num +'0');
							
			        		break;
					}
					
				}
				else
				{
					push(token);
					
				}
			}
			//the rest in the stack is our result 
			// pop the result
			f2 << pop()-'0';
			f2 << "\n"; 
		
		}
		else
		{
			f2<<"The expression is invalid.\n";
		}
		//clean the stack when the line is finished
		clear();
	}
	//  Close two files
    f1.close();
 	f2.close();
 	
    system("pause");
    return 0;
}

