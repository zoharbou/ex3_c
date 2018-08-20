CC= gcc
CFLAGS= -c -Wvla -Wall


# All Target
all: ex3


# Object Files

reader.o: reader.c reader.h
	$(CC) $(CFLAGS) reader.c reader.h

calculator.o: calculator.c calculator.h
	$(CC) $(CFLAGS) calculator.c calculator.h


# Exceutables
ex3: reader.o calculator.o
	$(CC) reader.o calculator.o -o ex3.exe


# tar
tar:
	tar -cf reader.c calculator.c Makefile


# Other Targets
clean:
	-rm -f *.o reader calculator ex3.exe

# Things that aren't really build targets
.PHONY: clean
