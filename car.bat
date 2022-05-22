<<<<<<< HEAD

gcc -std=c11 -g src/main.c -o bin/main.exe
=======
cls
set workdir=.
cd workdir
gcc -fdiagnostics-color=always -std=c11 -g %workdir%/src/main.c -o %workdir%/main.exe
main.exe
>>>>>>> 215af91d3033d3e8935b52f152facda9378e6f7f
pause