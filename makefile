all: menu.o system.o
	gcc -o menu menu.o
	gcc -o system system.o

menu.o: menu.c menu.h
	gcc -c menu.c

system.o: system.c system.h
	gcc -c system.c

clean:
	rm *.o
	rm system menu
	rm menu_p system_p
