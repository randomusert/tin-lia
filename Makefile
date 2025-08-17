CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lm
LIBDIRS =
LIBNAMES =
EXT =

# -------------------
# Platform detection
# -------------------
ifeq ($(PLATFORM),win)
	CC = x86_64-w64-mingw32-gcc
	CFLAGS += -DWIN32
	LDFLAGS += -lws2_32
	LIBDIRS = src/liblia src/libwin
	LIBNAMES = lia win
	EXT = .exe
else
	CFLAGS += -static
	PLATFORM = linux
	LIBDIRS = src/liblia src/liblinux
	LIBNAMES = lia linux
	EXT =
endif

.PHONY: all build clean

all: build

build:
	@echo "Building platform: $(PLATFORM)"
	# Build libraries
	$(MAKE) -C src/liblia PLATFORM=$(PLATFORM)
ifeq ($(PLATFORM),win)
	$(MAKE) -C src/libwin PLATFORM=$(PLATFORM)
else
	$(MAKE) -C src/liblinux PLATFORM=$(PLATFORM)
endif
	# Build main executable
	$(CC) -o tin-lia$(EXT) src/main.c $(addprefix -I,$(LIBDIRS)) $(addprefix -L,$(LIBDIRS)) $(addprefix -l,$(LIBNAMES)) $(CFLAGS) $(LDFLAGS)
ifeq ($(PLATFORM),win)
	# Copy DLLs next to exe
	cp src/liblia/liblia.dll .
	cp src/libwin/libwin.dll .
endif

clean:
	$(MAKE) -C src/liblia clean
	$(MAKE) -C src/liblinux clean
	$(MAKE) -C src/libwin clean
	rm -f tin-lia tin-lia.exe liblia.dll libwin.dll
