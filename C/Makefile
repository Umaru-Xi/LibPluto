CC=gcc
CFLAGS="-Wall"

debug:clean
	$(CC) $(CFLAGS) -shared -fPIC -liio -o libpluto.so libpluto.c
stable:clean
	$(CC) $(CFLAGS) -shared -o libpluto.so libpluto.c
clean:
	rm -vfr *~ libpluto.so
