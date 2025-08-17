# --- toolchain per platform ---
ifeq ($(PLATFORM),win)
  CC      = x86_64-w64-mingw32-gcc
  CFLAGS  = -Wall -Wextra -O2
  OBJDIR  = obj-win
  TARGETS = liblia.dll liblia.dll.a
else
  CC      = gcc
  CFLAGS  = -Wall -Wextra -O2 -fPIC
  OBJDIR  = obj-linux
  TARGETS = liblia.a liblia.so
endif

SRCS    = $(wildcard *.c)
OBJS    = $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

.PHONY: all clean
all: $(TARGETS)

# make sure obj dir exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# per-file compile into platform-specific objdir
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Windows outputs (DLL + import lib) ---
ifeq ($(PLATFORM),win)
liblia.dll liblia.dll.a: $(OBJS)
	$(CC) -shared -o liblia.dll $(OBJS) \
		-Wl,--out-implib,liblia.dll.a -Wl,--enable-auto-import
endif

# --- Linux outputs (static + shared) ---
ifeq ($(PLATFORM),)
# (nothing)
else ifeq ($(PLATFORM),linux)
liblia.a: $(OBJS)
	ar rcs $@ $(OBJS)

liblia.so: $(OBJS)
	$(CC) -shared -o $@ $(OBJS)
endif

clean:
	rm -rf obj-linux obj-win liblia.a liblia.so liblia.dll liblia.dll.a
