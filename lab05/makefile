lab05: lab05.o ghutils.o ghcontrol.o
	gcc -g -o lab05 lab05.o ghutils.o ghcontrol.o -lwiringPi
lab05.o: lab05.c ghutils.h ghcontrol.h
	gcc -g -c lab05.c
ghutils.o: ghutils.c ghutils.h ghcontrol.h
	gcc -g -c ghutils.c
ghcontrol.o: ghcontrol.c ghcontrol.h
	gcc -g -c ghcontrol.c
