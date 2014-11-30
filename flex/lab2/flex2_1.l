LETTER	[A-Za-z]
NOLETTER [^A-Za-z]
%%
{LETTER}{NOLETTER} {
						unput(yytext[0]);
					}
{NOLETTER}{LETTER} {
						unput(yytext[1]);
					}
{LETTER}{2}		{
					printf("%s ", yytext);
					yyless(1);
				}
. {}
%%

void main()
{
	yylex();
}
int yywrap() {
	return 0;
}
