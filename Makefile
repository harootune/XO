generate: xo.c
	gcc -O1 -o xo xo.c xo_backend.c


generate_debug: xo.c
	gcc -g -Og -o xo xo.c xo_backend.c


