LETTER	[A-Za-z]
%%
{LETTER}{2}		{
					printf("%s ", yytext);
				}
. {}
%%
void main() {
	yylex();
}
int yywrap() {
	return 0;
}
