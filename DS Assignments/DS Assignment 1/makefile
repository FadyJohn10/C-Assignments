a.out: main.o linkedmatrix.o matcomp.o
	g++ main.o linkedmatrix.o matcomp.o -o a.out
main.o: main.cpp
	g++ -c main.cpp
matcomp.o: matcomp.cpp matcomp.h
	g++ -c matcomp.cpp
linkedmatrix.o: linkedmatrix.cpp linkedmatrix.h
	g++ -c linkedmatrix.cpp
clean:
	rm *.o a.out