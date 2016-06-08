/* DECLARATIONS */
%{
	int chars = 0, words = 0, lines = 0, comments = 0;
%}


/* PATTERNS AND ACTONS */
%%

[#-a-zA-Z-0-9]+ { ++comments; }
[a-zA-Z]+ { ++words; chars += strlen(yytext); }
\n	  { ++chars; ++lines; }
.         { ++chars; }

%%

/* C CODE */




int main(int argc, char **argv)
{
	yylex();

	printf("CHARS: %8d | LINES: %8d | WORDS: %8d | COMMENTS: 8%d\n", 
               chars, lines, words, comments);

	return 0;
}
