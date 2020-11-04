#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <stdbool.h>
#define BUFSIZE 1024
extern bool add(const char* a_str, const char* b_str, char* res_str);
extern bool subtract(const char* a_str, const char* b_str, char* res_str);
extern bool multiply(const char* a_str, const char* b_str, char* res_str);
extern bool divide(const char* a_str, const char* b_str, char* res_str);
int main(int argc, char* argv[])
{
	char mode, temp;
	char a_str[BUFSIZE], b_str[BUFSIZE], res_str[BUFSIZE];
	bool (*func)(const char* a_str, const char* b_str, char* res_str) = NULL;
	setlocale(LC_CTYPE, "Russian");
	do
	{
		mode = 'y';
		while (mode != '1' && mode != '2' && mode != '3' && mode != '4' && mode != '5')
		{
			system("clear");
			printf("%s%s", "Нажмите следующие клавиши, для соответсвующих действий:",
				"\n1 - сложение,\n2 - вычитание,\n3 - умножение,\n4 - деление,\n5 - выход\n");
			while ((temp = getchar()) != EOF)
				mode = temp;
		}		
		switch (mode)
		{
		case '1':
			func = add;
			break;
		case '2':
			func = subtract;
			break;
		case '3':
			func = multiply;
			break;
		case '4':
			func = divide;
			break;
		case '5':
			mode = 'n';
			goto skip;
		}
		system("clear");
		printf("а:\n");
		scanf("%s", a_str);

		printf("b:\n");
		scanf("%s", b_str);
		if (func(a_str, b_str, res_str))
			printf("Результат операции: %s\n", res_str);
		else
			printf("Ошибка!\n");

		while (getchar() != EOF) {};
		skip:;
		
	} while (mode != 'n');
	return 0;
}