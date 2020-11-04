#include "substract.h"
//вычитание
//a_str и b_str - первый и второй операнды, соответственно
//операнды в виде строк
//возвращает true в случае успеха, результат в виде строки в res
bool subtract(const char* a_str, const char* b_str, char* res_str)
{
	double a, b, res;
	if (!str_to_double(a_str, &a) || !str_to_double(b_str, &b))
		return false;
	res = a - b;
	if (check_fe_exceptions(res))
		return false;
	double_to_str(res, res_str);
	return true;
}