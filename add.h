#ifndef ADD_H
#define ADD_H
#include <dlfcn.h>
#include <stdbool.h>
//сложение
//a_str и b_str - первый и второй операнды, соответственно
//операнды в виде строк
//возвращает true в случае успеха, результат в виде строки в res
bool add(const char* a_str, const char* b_str, char* res_str);
#endif