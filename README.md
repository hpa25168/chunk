NAME of Program: chunk.c

---------------------------------------------------------------------
This program takes in a File and breaks it up into many little files based words ,characters,or lines.
---------------------------------------------------------------------

CODER: Het Patel
CREDIT/Contributions:


How to compile:
    gcc -Wall -g chunkFunctions.c chunk.c  -o chunk
or
make -f Makefile

How to run:
./chunk [-l,-w,-c] -f filename.txt [-p prefix] [-s suffix] or chunk [-l,-w,c] [-p prefix] < filename.txt
