# liblia Makefile - cross-platform build

# --- platform selection ---
ifeq ($(PLATFORM),win)
  CC      = x86_64-w64-mingw32-gcc
  CFLAGS  = -Wall -Wextra -O2 -DWIN32
  OBJDIR  = obj-win
  TARGETS = liblia.dll liblia.dll.a
  PLAT_OBJ = $(OBJDIR)/libwin.o
else
  CC      = gcc
  CFLAGS  = -Wall -Wextra -O2 -fPIC
  OBJDIR  = obj-linux
  TARGETS = liblia.a liblia.so
  PLAT_OBJ = $(OBJDIR)/liblinux.o
endif

# --- common sources ---
COMMON_SRCS = $(wildcard *.c) $(wildcard commands/*.c)

# --- object files ---
COMMON_OBJS = liblia.o commands/client.o commands/server.o commands/test.o
OBJS = $(COMMON_OBJS) $(PLAT_OBJ)

.PHONY: all clean

# --- main target ---
all: $(OBJDIR) $(TARGETS)

# --- ensure object directory exists ---
$(OBJDIR):
	mkdir -p $(OBJDIR)

# --- compile local sources ---
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# --- compile platform-specific source ---
$(OBJDIR)/libwin.o: ../libwin/libwin.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/liblinux.o: ../liblinux/liblinux.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Windows DLL ---
ifeq ($(PLATFORM),win)
liblia.dll liblia.dll.a: $(OBJS)
	$(CC) -shared -o liblia.dll $(OBJS) \
		-Wl,--out-implib,liblia.dll.a -Wl,--enable-auto-import -lws2_32
endif


# --- Linux static and shared libraries ---
ifeq ($(PLATFORM),linux)
liblia.a: $(OBJS)
	ar rcs $@ $(OBJS)

liblia.so: $(OBJS)
	$(CC) -shared -o $@ $(OBJS)
endif

# --- clean ---
clean:
	rm -rf $(OBJDIR) *.a *.so *.dll *.dll.a
