#include "utility.h"
//преобразование строки str в вещественное число двойной точности num
//возвращает true в случае успеха
bool str_to_double(const char* str, double* num)
{
	//проверка, что строка непустая
	if (!strlen(str))
		return false;

	char* stop_str;
	*num = strtod(str, &stop_str);

	//проверка на выход за пределы диапазона double
	if (errno == ERANGE)
	{
		errno = 0;
		return false;
	}

	//проверка, что stop_str указывает на конец str
	if (strlen(stop_str))
		return false;

	//проверка на бесконечность и не число
	if (isnan(*num) || isinf(*num))
		return false;

	return true;
}

//преобразование числа num в строку str
void double_to_str(double num, char* str)
{
	snprintf(str, sizeof(str), "%g", num);
}

//проверка на ошибки при вычислении
//возвращает false, если ошибки не обнаружены
bool check_fe_exceptions(double res)
{
	//проверка установки машинно - зависимые флагов состояний
	if (fetestexcept(FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW))
	{
		//сброс флагов
		feclearexcept(FE_ALL_EXCEPT);
		return true;
	}

	//дополнительная проверка на бесконечность и не число
	if (isnan(res) || isinf(res))
		return true;
	return false;
}