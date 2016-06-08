
%{
	int chars = 0, words = 0, lines = 0;
%}

%%

[a-zA-Z]+ { ++words; chars += strlen(yytext); }
\n	  { ++chars; ++lines; }
.         { ++chars; }


%%





int main(int argc, char **argv)
{
	yylex();
	printf("CHARS: %8d | LINES: %8d | WORDS: %8d\n", chars, lines, words);
	return 0;
}
