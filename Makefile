esh: esh.c
	$(CC) esh.c -o esh -g -lreadline -Wall -Wextra -pedantic -std=c99
test: test.c
	$(CC) test.c -o test -Wall -Wextra -pedantic -std=c99