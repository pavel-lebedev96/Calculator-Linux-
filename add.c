#include "add.h"
//сложение
//a_str и b_str - первый и второй операнды, соответственно
//операнды в виде строк
//возвращает true в случае успеха, результат в виде строки в res
bool add(const char* a_str, const char* b_str, char* res_str)
{
	double a, b, res;
	//вспомогательные функции (utility.h)
	bool (*str_to_double)(const char* str, double* num);
	void (*double_to_str)(double num, char* str);
	bool (*check_fe_exceptions)(double res);
	
	//открытие библиотеки
	void* handle;
	handle = dlopen("./utility.so", RTLD_NOW);
	if (!handle)
		return false;

	//поиск функций
	str_to_double = (bool (*)
		(const char*, double*)) dlsym(handle, "str_to_double");
	double_to_str = (void (*)
		(double, char*)) dlsym(handle, "double_to_str");
	check_fe_exceptions = (bool (*)
		(double)) dlsym(handle, "check_fe_exceptions");	
	if (!str_to_double || !double_to_str || !check_fe_exceptions)
		return false;

	if (!str_to_double(a_str, &a) || !str_to_double(b_str, &b))
		return false;
	res = a + b;
	if (check_fe_exceptions(res))
		return false;
	double_to_str(res, res_str);
	dlclose(handle);
	return true;
}