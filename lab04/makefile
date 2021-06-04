lab04: lab04.o ghutils.o ghcontrol.o
	gcc -g -o lab04 lab04.o ghutils.o ghcontrol.o
lab04.o: lab04.c ghutils.h ghcontrol.h
	gcc -g -c lab04.c
ghutils.o: ghutils.c ghutils.h ghcontrol.h
	gcc -g -c ghutils.c
ghcontrol.o: ghcontrol.c ghcontrol.h
	gcc -g -c ghcontrol.c
