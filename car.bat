cls
set workdir=.
cd workdir
gcc -fdiagnostics-color=always -std=c11 -g %workdir%/src/main.c -o %workdir%/main.exe
main.exe
pause