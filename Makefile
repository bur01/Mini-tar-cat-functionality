all: tinytar wc

tinytar: tinytar.c
	gcc -o tinytar tinytar.c

wc: wc.c
	gcc -o wc wc.c
