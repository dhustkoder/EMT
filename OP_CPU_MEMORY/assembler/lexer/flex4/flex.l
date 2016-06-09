%{
	enum yyTokenType 
	{
		NUMBER = 258, ADD = 259, SUB = 260,
		MUL = 261, DIV = 262, ABS = 263, EOL = 264
	};

	int yylval;
%}


%%

"+"	{ return ADD; }
"-"	{ return SUB; }
"*"	{ return MUL; }
"/"	{ return DIV; }
"|"	{ return ABS; }
[0-9]+	{ yylval = atoi(yytext); return NUMBER; }
\n 	{ return EOL; }
[ \t]	{ /* ignore */ }
.	{ printf("Mystery character %c", *yytext); }

%%

int add(int f, int s) { return f + s; }
int sub(int f, int s) { return f - s; }
int mul(int f, int s) { return f * s; }
int div_(int f, int s) { return f / (s!=0?s:1); }
int abs_(int f, int s) { return f | s; }

int main(int argc, char **argv)
{
	int tok, first, second;
	int* waiting = &first;
	int(*fun)(int,int) = &add;

	while(tok = yylex()) 
	{
		switch(tok)
		{
			case ADD: printf(" + "); fun = add; break;
			case SUB: printf(" - "); fun = sub; break;
			case MUL: printf(" * "); fun = mul; break;
			case DIV: printf(" / "); fun = div_; break;
			case ABS: printf(" | "); fun = abs_; break;

			case NUMBER: 
				printf("%d", yylval);
				*waiting = yylval;
				if(waiting == &first)
					waiting = &second;
				else if(waiting == &second)
					waiting = &first;
				break;
			case EOL:
				printf(" = %d\n", fun(first, second)); 
				break;
		}
	}
}


