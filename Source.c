#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <dlfcn.h>
#define BUFSIZE 1024
#define TABLE_OP_SIZE 4

//информация об операции
typedef struct
{
	//handle для разделяемой библиотеки
	void* handle;
	//указатель на функцию
	bool (*funcp)(const char* a_str, const char* b_str, char* res_str);
	//название операции
	char name[20];
	//номер действия в пункте меню
	char key;
} OperationInfo;

//таблица операций
typedef struct
{
	//таблица для операций
	OperationInfo table[TABLE_OP_SIZE];
	//текущий размер таблицы
	size_t size;
} TableOperations;

//добавление элемента op_info в таблицу operations
bool addItemInTable(OperationInfo* op_info, TableOperations* operations)
{
	if (operations->size == TABLE_OP_SIZE)
		return false;
	operations->table[operations->size].handle = op_info->handle;
	operations->table[operations->size].funcp = op_info->funcp;
	strcpy(operations->table[operations->size].name, op_info->name);
	operations->table[operations->size].key = operations->size + '0' + 1;
	operations->size++;
	return true;
}

//добавление операции с именем op_name в таблицу operations
bool addOperation(const char* op_name, TableOperations* operations)
{
	OperationInfo op_info;
	strcpy(op_info.name, op_name);

	/*имя библиотеки в текущей директории в формате
	"/имя библиотеки.so"*/
	char libname[40] = "./";
	strcat(libname, op_name);
	strcat(libname, ".so");

	//открытие библиотеки
	op_info.handle = dlopen(libname, RTLD_LAZY);
	if (!op_info.handle)
		return false;

	//поиск функции
	op_info.funcp = (bool (*)
		(const char*, const char*, char*)) dlsym(op_info.handle, op_name);
	if (!op_info.funcp)
	{
		dlclose(op_info.handle);
		return false;
	}
	
	return addItemInTable(&op_info, operations);
}

//загрузка операций
void load(TableOperations* operations)
{
	operations->size = 0;
	char names[TABLE_OP_SIZE][20] = { "add", "substract", "multiply", "divide" };
	for (int i = 0; i < TABLE_OP_SIZE; i++)
		addOperation(names[i], operations);
}

//закрытие библиотек
void close(TableOperations* operations)
{
	for (int i = 0; i < operations->size; i++)
		dlclose(operations->table[i].handle);
	operations->size = 0;
}

int main(int argc, char* argv[])
{
	char mode, temp;
	char a_str[BUFSIZE], b_str[BUFSIZE], res_str[BUFSIZE];
	bool (*func)(const char* a_str, const char* b_str, char* res_str) = NULL;
	bool flag;
	TableOperations operations;
	load(&operations);
	if (operations.size == 0)
	{
		printf("There is no operations to show\n");
		getchar();
		return 0;
	}
	do
	{
		mode = 'y';
		flag = false;
		while (!flag)
		{
			system("clear");
			for (int i = 0; i < operations.size; i++)
				printf("%c - %s\n", operations.table[i].key, operations.table[i].name);
			printf("q - exit\n");
			while ((temp = getchar()) != EOF)
				mode = temp;
			if (mode == 'q')
				goto skip;
			for (int i = 0; i < operations.size; i++)
				if (mode == operations.table[i].key)
				{
					func = operations.table[i].funcp;
					flag = true;
				}
		}
		system("clear");
		printf("а:\n");
		scanf("%s", a_str);

		printf("b:\n");
		scanf("%s", b_str);
		if (func(a_str, b_str, res_str))
			printf("Result: %s\n", res_str);
		else
			printf("Error!\n");

		while (getchar() != EOF) {};
	skip:;

	} while (mode != 'q');
	close(&operations);
	return 0;
}