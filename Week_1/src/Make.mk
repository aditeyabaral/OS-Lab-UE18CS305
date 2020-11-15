reverse.out: server.o client.o
	gcc server.o client.o -o reverse.out

server.o: server.c header.h
	gcc -c server.c

client.o: client.c header.h
	gcc -c client.c

clean:
	rm -rf *.o
	rm -rf *.out
