all: ttar ccat

ttar: ttar.c
	gcc -o ttar ttar.c

ccat: ccat.c
	gcc -o ccat ccat.c
