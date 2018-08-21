CC= gcc
CFLAGS= -c -Wvla -Wall
CODEFILES = reader.c calculator.c Makefile

# All Target
all: ex3


# Object Files

reader.o: reader.c calculator.c calculator.h heat_eqn.c heat_eqn.h
	$(CC) $(CFLAGS) reader.c calculator.c heat_eqn.c

calculator.o: calculator.c calculator.h
	$(CC) $(CFLAGS) calculator.c

heat_eqn.o: heat_eqn.c heat_eqn.h
	$(CC) $(CFLAGS) heat_eqn.c


# Exceutables
ex3: reader.o calculator.o
	$(CC) reader.o calculator.o heat_eqn.o -o ex3


# tar
tar:
	tar -cf ex3.tar $(CODEFILES)


# Other Targets
clean:
	-rm -f *.o reader calculator heat_eqn ex3

# Things that aren't really build targets
.PHONY: clean
