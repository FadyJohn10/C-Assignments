wizard.out: main.o mylist.o maxheap.o dochashtable.o
	g++ main.o mylist.o maxheap.o dochashtable.o -o wizard.out
main.o: main.cpp
	g++ -c main.cpp
dochashtable.o: dochashtable.cpp dochashtable.h
	g++ -c dochashtable.cpp
maxheap.o: maxheap.cpp maxheap.h
	g++ -c maxheap.cpp
mylist.o: mylist.cpp mylist.h
	g++ -c mylist.cpp
clean:
	rm *.o wizard.out