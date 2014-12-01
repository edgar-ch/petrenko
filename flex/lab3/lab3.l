%START COMMENT COMMENT2

COMM_BEGIN	"/*"
COMM_END	"*/"

COMM1_BEGIN "//"
%%
{COMM1_BEGIN}[^\n]*	{
	/* если комментарий 2 типа, то убираем все до конца строки
	и переходим в состояние COMMENT2 */
	BEGIN COMMENT2;
};

<COMMENT2>[\t\n]* {
	/* убираем оставшиеся символы табуляции и конца строки */
	BEGIN 0;
};

{COMM_BEGIN} {
	/* если комментарий 1 типа, то переходим в состояние COMMENT */
	BEGIN COMMENT;
};

<COMMENT>[^*]*		;
<COMMENT>[^/]		;
<COMMENT>{COMM_END} {
	/* убираем все символы, которые точно не могут обозначать конец
	конец комментария, потом убираем конец комментария */
	BEGIN 0;
};

[^\n] {
	ECHO; /* все остальное выводим на экран */
};
%%
void main()  {
	yylex();
}
int yywrap() {
	return 0;
}
