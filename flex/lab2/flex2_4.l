LETTER [A-Za-z]
%%
{LETTER}{2} {
	/* если оба символа - буквы, то выводим их на экран */
	printf("%s ", yytext);
	/* в поток второй символ НЕ возвращаем */
}
. { /* Пропускаем все, что не биграмма из букв */ }
%%
void main() {
	yylex();
}
int yywrap() {
	return 0;
}