all: pbds.out lct.out poly_mod.out fft.out

test_pbds: pbds.out
	./pbds.out

test_lct: lct.out
	./lct.out

test_poly_mod: poly_mod.out
	./poly_mod.out

test_poly: poly.out
	./poly.out

%.out: %.cpp
	g++-12 -Wconversion -Wall -Wextra -pedantic -fno-common -fno-builtin -O2 -g -o $@ $^

clean:
	rm -f *.out