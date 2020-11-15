#ifndef ADD_H
#define ADD_H
//сложение
//a_str и b_str - первый и второй операнды, соответственно
//операнды в виде строк
//возвращает true в случае успеха, результат в виде строки в res
bool add(const char* a_str, const char* b_str, char* res_str);

//вспомогательные функции (utility.h)
extern bool str_to_double(const char* str, double* num);
extern void double_to_str(double num, char* str);
extern bool check_fe_exceptions(double res);
#endif