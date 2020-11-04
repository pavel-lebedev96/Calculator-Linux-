#ifndef UTILITY_H
#define UTILITY_H
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <fenv.h>

//преобразование строки str в вещественное число двойной точности num
//возвращает true в случае успеха
bool str_to_double(const char* str, double* num);

//преобразование числа num в строку str
void double_to_str(double num, char* str);

//проверка на ошибки при вычислении
//возвращает true, если ошибки не обнаружены
bool check_fe_exceptions(double res);
#endif