CC = gcc
CFLAGS = -Wall -Wextra -O2 -fPIC
OBJS = $(patsubst %.c,%.o,$(wildcard *.c))

all: liblinux.a liblinux.so

liblinux.a: $(OBJS)
	ar rcs liblinux.a $(OBJS)

liblinux.so: $(OBJS)
	$(CC) -shared -o liblinux.so $(OBJS)

clean:
	rm -f *.o liblinux.a liblinux.so
