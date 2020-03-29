heapsort: heapsort.cc heapsort.h build-test
	g++ heapsort.cc  -o heapsort -g

build-test: heapsort-test.cc heapsort.h
	g++ heapsort-test.cc -o heapsort-test -g

clean:
	rm heapsort heapsort-test

test:
	./heapsort-test < testdata.txt