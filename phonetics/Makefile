includes = Desktop/Projects/Lang/support_libraries/Expt

header: phonetics.h
	g++ -std=c++11 -o $@.o -iquote $(includes) $^

test: phonetics_test.cpp phonetics.cpp
	g++ -std=c++11 -o $@.o -iquote $(includes) $^ -lgtest -lpthread
	./$@.o

clean:
	rm -f *.o *.gch