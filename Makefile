prettylines: prettylines.o
	gcc -Wall -Werror -std=c11 -o prettylines prettylines.o

prettlines.o: prettylines.c
	gcc -Wall -Werror -std=c11 -c prettylines.c

clean:
	rm *.o prettylines
