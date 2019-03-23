compile:
	g++ -Wall -c Graph.cpp
	ar crs Graph.a Graph.o
	g++ -o circuit.out circuit.cpp -L . Graph.a
run:
	./circuit.out
clean:
	rm -rf *.o *.out *.a