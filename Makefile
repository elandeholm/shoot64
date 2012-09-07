CC=gcc
CC-FLAGS=-Wall -std=c99
CC-DFLAGS=$(CC-FLAGS) -g -DSHOOT64_DEBUG
CC-OFLAGS=$(CC-FLAGS) -O2 -march=native
LD-FLAGS=-lglut
RM=rm -f

clean:
	$(RM) *~ *.o shoot64 shoot64debug

color.o:	color.c color.h config.h debug.h
	$(CC) $(CC-FLAGS) $(CC-OPTFLAGS) -o color.o -c smet64.c

_debug_color.o:	color.c color.h config.h debug.h
	$(CC) $(CC-DLAGS) $(CC-OPTFLAGS) -o color.o -c smet64.c

shoot64.o: shoot64.c color.h config.h debug.h
	$(CC) $(CC-FLAGS) -o shoot64_test.o -c shoot64.c

_debug_shoot64.o: shoot64.c color.h config.h debug.h
	$(CC) $(CC-DFLAGS) -o _debug_shoot64.o -c shoot64.c

shoot64: shoot64.o color.o
	$(CC) $(LD-FLAGS) -o shoot64 shoot64.o color.o

shoot64debug: _debug_shoot64.o _debug_color.o
	$(CC) $(LD-FLAGS) -o shoot64debug _debug_shoot64.o _debug_color.o

