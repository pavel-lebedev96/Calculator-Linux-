#Makefile for Calculator
#Создание объектных модулей для динамических библиотек
object_files_so: add.c substract.c multiply.c divide.c utility.c
	gcc -Wall -fPIC -c add.c substract.c multiply.c divide.c utility.c
#Создание динамической библиотеки из объектных модулей
shared_libraries: add.o substract.o multiply.o divide.o utility.o
	gcc -shared -o add.so add.o -ldl
	gcc -shared -o substract.so substract.o -ldl
	gcc -shared -o multiply.so multiply.o -ldl
	gcc -shared -o divide.so divide.o -ldl
	gcc -shared -o utility.so utility.o -lm
	rm *.o
#Создание исполняемого модуля, с использованием динамической библиотеки
binary_so: source.c
	gcc -o program source.c -ldl
#End Makefile