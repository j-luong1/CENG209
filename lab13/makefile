##typo in lab13.o compile line
lab13:  lab13.o projectile.o
	gcc -g -o lab13 lab13.o projectile.o -lm

lab13.o: lab13.c projectile.h
	gcc -g -c lab13.c

projectile.o: projectile.c projectile.h
	gcc -g -c projectile.c

clean:
		touch *
		rm *.o
