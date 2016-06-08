%%





"#".+    { printf("COMMENT\n"); }
"+"	{ printf("PLUS\n"); }
"-"	{ printf("MINUS\n"); }
"*"	{ printf("TIMES\n"); }
"/"	{ printf("DIVIDE\n"); }
[0-9]+	{ printf("NUMBER %s\n", yytext); }
\n	{ printf("NEW LINE\n"); }
[ \t]   {	}
.	{ printf("Mystery character %s\n", yytext); }



%%



