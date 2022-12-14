all: pbds.out lct.out

test_pbds: pbds.out
	./pbds.out

test_lct: lct.out
	./lct.out

%.out: %.cpp
	g++-12 -Wall -O2 -g -o $@ $^

clean:
	rm -f *.out