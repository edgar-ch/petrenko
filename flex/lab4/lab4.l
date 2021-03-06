%START JCB
DIG [0-9]
%%
4{DIG}{15}|4{DIG}{12} {
	/* если начинается на 4 и имеет длину 16 или 13 цифр, то VISA */
	printf("VISA");
}
5[1-5]{1}{DIG}{14} {
	/* если первые 2 цифры от 51 до 55 и длина 16, то Master Card */
	printf("Master Card");
}
(34|37){1}{DIG}{13} {
	/* если начинается на 34 или 37 и длина 15, то American Express */
	printf("American Express");
}
(30[0-5]|309){DIG}{11}|(36|38|39){DIG}{12} {
	/* если начинается на 300-305 или 309 и имеет длину 14 ИЛИ
	начинается на 36, 38, 39 и имеет длину 14, то Diners Club */
	printf("Diners Club");
}
6011{DIG}{12}|65{DIG}{14} {
	/* если начинается на 6011 или 65 и имеет длину 16,
	то Discover Card */
	printf("Discover Card");
}
35 {
	/* если начинается на 35, то переходим в состояние JCB для
	дальнейшего распознавания */
	BEGIN JCB;
}

<JCB>(2[8-9]|[3-8][0-9]){DIG}{12} {
	/* если следущие цифры 28, 29, от 30 до 89 и в конце 12 цифр
	(общая длина 16), то JCB */
	printf("JCB");
	BEGIN 0;
}
%%
void main() {
	yylex();
}
int yywrap() {
	return 0;
}
