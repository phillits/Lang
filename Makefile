header: expt.h
	g++ -std=c++11 -o $@.o $^

test: expt_test.cpp expt.cpp
	g++ -std=c++11 -o $@.o $^ -lgtest -lpthread
	./$@.o

clean: 
	rm -f *.o *.gch