.PHONY: clean

headers = \
		  object.h \
		  string.h \
		  list.h \
		  map.h

main: test-map.cpp $(headers)
	g++ -g -Wall -o test test-map.cpp

clean:
	rm test
