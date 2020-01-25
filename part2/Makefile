.PHONY: clean

headers = \
		  object.h \
		  string.h \
		  list.h \
		  map.h

main: test.cpp $(headers)
	g++ -g -Wall -o test test.cpp

clean:
	rm test
