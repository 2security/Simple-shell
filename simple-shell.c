#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<setjmp.h>
#define add 111
#define sub 222
#define mul 333
#define div 444
#define ERR 0
char *tok_ptr;
char *t;
jmp_buf jmpbuffer;
int get_token(char *line)
	{
	t=strtok(line," ");
	if(strcmp("add",t)==0)
		return add;
	else if(strcmp("sub",t)==0)
		return sub;
	else if(strcmp("mul",t)==0)
		return mul;
	else if(strcmp("div",t)==0)
		return div;
	else 
		return atoi(t);
	}
void cmd_division()
	{
	float a,b;
	a=get_token(tok_ptr);
	b=get_token(tok_ptr);
	if (a <= 0 || b <= 0)		
		longjmp(jmpbuffer, 1);
	printf("%.3f\n",a/b);
	}
void cmd_product()
	{
	int a,b;
	a=get_token(tok_ptr);
	b=get_token(tok_ptr);
	if (a <= 0 || b <= 0)		
		longjmp(jmpbuffer, 1);
	printf("%d\n",a*b);
	}
void cmd_add()
	{
	int a,b;
	a=get_token(tok_ptr);
	b=get_token(tok_ptr);
	if (a <= 0 || b <= 0)		
		longjmp(jmpbuffer, 1);
	printf("%d\n",a+b);
	}
void cmd_sub()
	{
	int a,b;
	a=get_token(tok_ptr);
	b=get_token(tok_ptr);
	if (a <= 0 || b <= 0)		
		longjmp(jmpbuffer, 1);
	else if(a<b)
		longjmp(jmpbuffer, 1);
	printf("%d\n",a-b);
	}
void do_line(char *p)
	{
	int op;
	op=get_token(p);
	switch (op)
		{
		case add:
			 cmd_add();
			 break;
		case sub:
			 cmd_sub();
			 break;
		case mul:
			 cmd_product();
			 break;
		case div:
			 cmd_division();
			 break;
		case ERR:
			printf("OOPS! invalid operation name, try again...\n");
			break;
		}
	}
int main()
	{
	char line[100];
	if (setjmp(jmpbuffer) != 0)
		printf("OPPS! invalid arguments, try again...\n");
	while(fgets(line,20,stdin) != NULL)
		{
		if(strncmp(line,"bye",3)==0)
			exit(0);
		else
			do_line(line);
		}
	return 0;
	}

