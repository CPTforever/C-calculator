CC = clang
#CFLAGS = -Wall -Wpedantic -Werror -Wextra
CFLAGS = 
all: calculator

calculator.o: calculator.c  
	$(CC) $(CFLAGS) -c calculator.c 

calculator: calculator.o integrate.o trie.o
	$(CC) -o calc calculator.o integrate.o trie.o -lncurses

integrate.o: integrate.c
	$(CC) $(CFLAGS) -c integrate.c 

trie.o: trie.c
	$(CC) $(CFLAGS) -c trie.c 

clean:
	rm -f calc *.o

format:
	clang-format -i -style=file *.[ch]
