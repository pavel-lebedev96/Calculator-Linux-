#ifndef SUBSTRACT_H
#define SUBSTRACT_H
#include <stdbool.h>
#include <dlfcn.h>
//вычитание
//a_str и b_str - первый и второй операнды, соответственно
//операнды в виде строк
//возвращает true в случае успеха, результат в виде строки в res
bool substract(const char* a_str, const char* b_str, char* res_str);
#endif