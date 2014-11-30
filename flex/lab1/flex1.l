NODELIM [^" "\t\n]
%{
	int l, w, c;
	l = 0;
	w = 0;
	c = 0;
%}
%%
{NODELIM}+	{
				w++;
				c += yyleng;
			}
\n 	{
		l++;
	}
.	{
		c++;
	}
%%

void main() 
{
	yylex();
}
int yywrap()
{
	printf("Lines - %d Words - %d Chars - %d\n", l, w, c);
	return 1;
}
