all: pbds.out lct.out

test_pbds: pbds.out
	./pbds.out

%.out: %.cpp
	g++-12 -Wall -O2 -o $@ $^