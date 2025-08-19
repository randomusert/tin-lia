CC = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Wextra -O2
OBJS = $(patsubst %.c,%.o,$(wildcard *.c)) \
	   $(patsubst %.c,%.o,$(wildcard io/*.c))

all: libwin.dll libwin.dll.a

libwin.dll libwin.dll.a: $(OBJS) ../liblia/liblia.dll.a
	$(CC) -shared -o libwin.dll $(OBJS) -L../liblia -llia -lws2_32 -Wl,--out-implib,libwin.dll.a -Wl,--enable-auto-import -DWIN32 -lws2_32

clean:
	rm -f *.o libwin.dll libwin.dll.a
