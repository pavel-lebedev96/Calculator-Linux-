#Makefile for Calculator
#Создание объектных модулей для статической библиотеки
object_files_a: add.c substract.c multiply.c divide.c utility.c
	gcc -c add.c substract.c multiply.c divide.c utility.c
#Создание статической библиотеки из объектных модулей
static_library: add.o substract.o multiply.o divide.o utility.o
	ar rs libmath_operations.a add.o substract.o multiply.o divide.o utility.o
#Создание исполняемого модуля, с использованием статической библиотеки
binary_a: source.c libmath_operations.a
	gcc -c source.c
	gcc -o program source.o libmath_operations.a -lm
#Создание объектных модулей для динамической библиотеки
object_files_so: add.c substract.c multiply.c divide.c utility.c
	gcc -Wall -fPIC -c add.c substract.c multiply.c divide.c utility.c
#Создание динамической библиотеки из объектных модулей
shared_library: add.o substract.o multiply.o divide.o utility.o
	gcc -shared -o libmath_operations.so add.o substract.o multiply.o divide.o utility.o
#Создание исполняемого модуля, с использованием динамической библиотеки
binary_so: source.c libmath_operations.so
	gcc -c source.c
	gcc -o program source.o libmath_operations.so -lm
#End Makefile