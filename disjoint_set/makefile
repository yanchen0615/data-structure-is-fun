all:
	g++ idisjointset.h array_disjointset.h array_disjointset_test.cc -std=c++11 -o array_disjointset_test -Wall -lgtest -lgtest_main -pthread
	g++ simple_disjointset.cc -Wall -lgtest -lgtest_main -pthread -o simple_disjointset -std=c++11
clean:
	rm array_disjointset_test simple_disjointset
