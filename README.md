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
./configure --with-platform=linux --disable-static
make
make install
```
## running
to run it, just launch the binary

## found bugs?
if you found bugs please report them on the issues tab