reverse.out: Server.o Client.o
	gcc Server.o Client.o -o reverse.out

Server.o: Server.c Header.h
	gcc -c Server.c

Client.o: Client.c Header.h
	gcc -c Client.c

clean:
	rm -rf *.o
	rm -rf *.out
	rm -rf reverse