ghglg: ghglgmain.o ghutils.o ghcontrol.o hshbme280.o
	gcc -L/usr/local/glg/lib -L. -o ghglg ghglgmain.o ghutils.o ghcontrol.o hshbme280.o \
            -lwiringPi -lglg_int -lglg -lglg_map_stub -lXm -lXt -lX11 -lXmu -lXft \
            -lXext -lXp -lz -ljpeg -lpng -lfreetype -lfontconfig -lm -ldl -lpthread
ghglgmain.o : ghglgmain.c ghglgmain.h ghutils.h ghcontrol.h hshbme280.h
	gcc -c -g -I/usr/local/glg/include ghglgmain.c
ghutils.o: ghutils.c ghutils.h ghcontrol.h
	gcc -g -c ghutils.c
ghcontrol.o: ghcontrol.c ghcontrol.h
	gcc -g -c ghcontrol.c
hshbme280.o: hshbme280.c hshbme280.h

clean:
	touch *
	rm *.o
