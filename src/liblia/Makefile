ifeq ($(PLATFORM),win)
	CC = x86_64-w64-mingw32-gcc
	CFLAGS = -Wall -Wextra -O2
else
	CC = gcc
	CFLAGS = -Wall -Wextra -O2 -fPIC
endif

OBJS = $(patsubst %.c,%.o,$(wildcard *.c))

ifeq ($(PLATFORM),win)
all: liblia.dll liblia.dll.a

liblia.dll liblia.dll.a: $(OBJS)
	$(CC) -shared -o liblia.dll $(OBJS) -Wl,--out-implib,liblia.dll.a -Wl,--enable-auto-import

clean:
	rm -f *.o liblia.dll liblia.dll.a
else
all: liblia.a liblia.so

liblia.a: $(OBJS)
	ar rcs liblia.a $(OBJS)

liblia.so: $(OBJS)
	$(CC) -shared -o liblia.so $(OBJS)

clean:
	rm -f *.o liblia.a liblia.so
endif
