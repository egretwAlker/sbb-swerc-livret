all: pbds.out lct.out poly_mod.out

test_pbds: pbds.out
	./pbds.out

test_lct: lct.out
	./lct.out

test_fft_mod: poly_mod.out
	./poly_mod.out

%.out: %.cpp
	g++-12 -Wconversion -Wall -Wextra -pedantic -fno-common -fno-builtin -O2 -g -o $@ $^

clean:
	rm -f *.out