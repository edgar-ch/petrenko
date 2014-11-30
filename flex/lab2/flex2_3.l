LETTER	[A-Za-z]
%%
{LETTER}{2}		{
					printf("%s ", yytext);
					yyless(1);
				}
. {}
%%
void main() {
	yylex();
}
int yywrap() {
	return 0;
}
