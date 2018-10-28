CFLAGS:=-Wall

bank:common.o Login.o master.o bank.o
	$(CC) $(CFLAGS) -o $@ $^


main:main.o
	$(CC) $(CFLAGS) -o $@ $^

*.o:*.c

clean:
	$(RM) bank main *.o
