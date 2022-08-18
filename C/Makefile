CC=gcc
CFLAGS="-Wall"

debug:clean
	$(CC) $(CFLAGS) -shared -fPIC -liio -o libpluto.so libpluto.c
stable:clean
	$(CC) $(CFLAGS) -shared -fPIC -liio -o libpluto.so libpluto.c
install:stable
	cp libpluto.so /usr/lib64/
	# cp cp libpluto.so /usr/lib/		# use for 32bit system
clean:
	rm -vfr *~ libpluto.so
