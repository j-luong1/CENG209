lab03: lab03.o ghutils.o ghcontrol.o
	gcc -g -o lab03 lab03.o ghutils.o ghcontrol.o
lab03.o: lab03.c ghutils.h ghcontrol.h
	gcc -g -c lab03.c
ghutils.o: ghutils.c ghutils.h ghcontrol.h
	gcc -g -c ghutils.c
ghcontrol.o: ghcontrol.c ghcontrol.h
	gcc -g -c ghcontrol.c
