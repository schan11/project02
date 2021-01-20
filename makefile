all: menu.o system.o order.o
	gcc -o menu menu.o
	gcc -o system system.o order.o

menu.o: menu.c menu.h
	gcc -c menu.c

system.o: system.c system.h
	gcc -c system.c

order.o: order.c order.h
	gcc -c order.c

clean:
	rm *.o
	rm system menu
	rm menu_p system_p
