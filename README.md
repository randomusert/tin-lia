# tin-lia
tin-lia is a linux in a app project made in C.

## notes
- this is for educational use
- please don't mess with the platform spesific libraries
- this is in early development
- there is no documentation

## building
after build infrasturcture change from writing makefiles by hand to gnu autotools

to build, run 
```bash
# Everything can be now built by a custom tool called tin-forge
python tools/tin-forge/forge.py
```

To configure a platform manually, pass the value with `=`:
```bash
./configure --with-platform=linux
```

Autoconf treats a value passed as a separate argument (`--with-platform linux`)
as a positional configuration name, which causes the `config.sub` error.

The libraries are managed through libtool. To build without static library
archives, use:
```bash
./configure --with-platform=win --disable-static --prefix=/tmp/tin-lia-install
make
make install
```

For a Windows shared build, distribute these files from the install `bin`
directory together:
```text
tin-lia.exe
liblia-0.dll
libwin-0.dll
```

The dependency chain is `tin-lia.exe` -> `liblia-0.dll` ->
`libwin-0.dll`; `libwin` is not embedded in the executable. Inspect the
installed executable (or `src/.libs/tin-lia.exe`), not an executable left
over from an earlier static build:
```text
dumpbin /dependents tin-lia.exe
```
## running
to run it, just launch the binary

## found bugs?
if you found bugs please report them on the issues tab