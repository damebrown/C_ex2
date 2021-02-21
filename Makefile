CC= gcc
CFLAGS= -c -Wvla -Wall

# generating ex2.exe file
ex2: battleships.o battleships_game.o
	$(CC) battleships.o battleships_game.o -o ex2

# generating battleships file
battleships.o: battleships.c battleships.h
	$(CC) $(CFLAGS) battleships.c

# generating battleships_game file
battleships_game.o: battleships_game.c battleships.h battleships.c
	$(CC) $(CFLAGS) battleships_game.c

# clean
clean:
	-rm -f *.o  ex2

.PHONY: clean