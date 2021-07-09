all: project

project: main.o istack.o list.o functions.o
	gcc -Wall -o project main.o istack.o list.o functions.o

functions.o: functions.c list.h functions.h
	gcc -c -Wall functions.c 
main.o: main.c istack.h functions.h
	gcc -c -Wall main.c
istack.o: istack.c istack.h
	gcc -c -Wall istack.c
list.o: list.c list.h
	gcc -c -Wall list.c