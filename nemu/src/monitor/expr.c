#include "nemu.h"
#include "cpu/reg.h"
#include "memory/memory.h"

#include <stdlib.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum
{
	NOTYPE = 256,
	EQ=1,//???
	NUM=128,
	NUM_H=2,
	REG=64,
	SYMB=32,
	MIN=16,
	DEREF=8,
	OPR=4//operation
	/* TODO: Add more token types */

};

static struct rule
{
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +", NOTYPE}, // white space
	{"\\+", '+'},
	{"\\-",'-'},
	{"\\*",'*'},
	{"\\*",'*'},
	{"/",'/'},
	{"\\(",'('},
	{"\\)",')'},

	{"[0-9]{1,10}", NUM}, // dec
	{"0[xX][0-9a-fA-F]{1,8}",NUM_H},//hex
	//{"[0-1]{1,32}",NUM},//bin
	{"$e[a-d]x",REG},
	{"$e[bs]p",REG},
	{"$e[ds]i",REG},
	{"[a-zA-Z][a-zA-Z0-9_]",SYMB}
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]))

static regex_t re[NR_REGEX];

/* Rules are used for more times.
 * Therefore we compile them only once before any usage.
 */
void init_regex()
{
	int i;
	char error_msg[128];
	int ret;

	for (i = 0; i < NR_REGEX; i++)
	{
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if (ret != 0)
		{
			regerror(ret, &re[i], error_msg, 128);
			assert(ret != 0);
		}
	}
}

typedef struct token
{
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e)
{
	int position = 0;
	int i;
	regmatch_t pmatch;

	nr_token = 0;

	while (e[position] != '\0')
	{
		/* Try all rules one by one. */
		for (i = 0; i < NR_REGEX; i++)
		{
			if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0)
			{
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				printf("match regex[%d] at position %d with len %d: %.*s", i, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. 
				 * Add codes to perform some actions with this token.
				 */

				switch (rules[i].token_type)
				{
				case NUM:
					strncpy(tokens[nr_token].str,substr_start,substr_len+1);
					tokens[nr_token].type=NUM;
					break;
				case REG:
					;//
				case SYMB:
					;//
				case MIN:
					;//
				case DEREF:
					;//
				case OPR:
					;//
				default:
					tokens[nr_token].type = rules[i].token_type;
					nr_token++;
				}

				break;
			}
		}

		if (i == NR_REGEX)
		{
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true;
}

bool check_parentheses(int p,int q)
{
	if(tokens[p].type!='('||tokens[q].type!=')')
		return false;
	int top=1;
	for(int i=p+1;i<q-1;i++)
	{
		if(!top)
			return false;
		if(tokens[i].type=='(')
			top++;
		else if(tokens[i].type==')')
			top--;
	}
	if(top==1)
		return true;
	else return false;

}

int domi_oper(int p,int q)
{
	int flag1=1,flag2=0;
	for(int i=p;i<=q;i++)
	{
		if(tokens[i].type=='+'||tokens[i].type=='-')
		{
			flag2=1;
			break;
		}
	}
	for(int i=q;i>=p;i--)
	{
		if(tokens[i].type==')')
			flag1=1;
		else if(tokens[i].type=='(')
			flag1=0;
		if(flag1)
		{
			if(flag2)
			{	
				if(tokens[i].type=='+'||tokens[i].type=='-')
					return i;
			}
			else
			{
				if(tokens[i].type=='*'||tokens[i].type=='/')
					return i;
			}
		
		}
	}
	return p;//??
}

uint32_t eval (int p , int q , bool *success)
{
	if(p > q) {
	/* Bad expression*/
		*success=false;
		return 0;
	}
	else if(p == q) {
	/* Single
	* For now this token should be a number.
	* Return the value of the number
	*/
		*success=true;
		uint32_t val=0;
		int i=0;
		int temp=0;
		//
		if(tokens[p].type==NUM_H)
			temp=16;
		else if(tokens[p].type==NUM)
			temp=10;
		else
		{
			*success=false;
			return 0;
		}

		while(tokens[p].str[i]!='\0')
		{
			val=temp*val+tokens[p].str[i]-'0';
			i++;
		}
		return val;
	}
	else if(check_parentheses(p, q) == true) {
	/* The expression is surrounded by a matched pair of parentheses.
	* If that is the case, just throw away the parentheses*/
		return eval(p + 1, q-1,success);
	}
	else {
		int op = domi_oper(p,q);
		int val1 = eval(p, op - 1,success);
		int val2 = eval(op + 1, q,success);
		int op_type=tokens[op].type;
		switch(op_type) {
			case '+': return val1 + val2;
			case '-': return val1-val2;
			case '*': return val1*val2;
			case '/': return val1/val2;
			default: assert(0);
		}
	}
}

uint32_t expr(char *e, bool *success)
{
	if (!make_token(e))
	{
		*success = false;
		return 0;
	}

	//printf("\nPlease implement expr at expr.c\n");
	//assert(0);
	for(int i = 0; i < nr_token; i ++) {
		if(tokens[i].type == '*' && (i == 0 || tokens[i-1].type == SYMB) ) {
			tokens[i].type = DEREF;
		}
		else if(tokens[i].type=='-'&&(i==0||tokens[i-1].type==SYMB))
		{
			tokens[i].type=MIN;
		}
	}

	return eval(0,nr_token,success);	
}
