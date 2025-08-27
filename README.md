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
./prepdirs # prepare build folders
./bootstrap # create configure script
cd build-win # for windows build
cd build-linux # for linux build
../configure --with-platform=win # for windows build
../configure ---with-platform=linux # for linux build
make # for both, linux and windows builds
```
## running
to run it, just launch the binary

## found bugs?
if you found bugs please report them on the issues tab