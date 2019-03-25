compile:
	g++ -Wall -c Graph.cpp
	ar crs Graph.a Graph.o
	g++ -Wall -o circuit.out circuit.cpp -L . Graph.a -larmadillo

debug:
	g++ -g -Wall -o debug.out circuit.cpp -L . Graph.a -larmadillo
run:
	./circuit.out
clean:
	rm -rf *.o *.out *.a