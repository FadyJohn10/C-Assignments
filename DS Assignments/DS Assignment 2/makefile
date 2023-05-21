vfs.out: main.o myvector.o inode.o mystack.o myqueue.o vfs_tree.o
	g++ main.o myvector.o inode.o mystack.o myqueue.o vfs_tree.o -o vfs.out
main.o: main.cpp
	g++ -c main.cpp
vfs_tree.o: vfs_tree.cpp vfs_tree.h
	g++ -c vfs_tree.cpp
myqueue.o: myqueue.cpp myqueue.h
	g++ -c myqueue.cpp
mystack.o: mystack.cpp mystack.h
	g++ -c mystack.cpp
inode.o: inode.cpp inode.h
	g++ -c inode.cpp
myvector.o: myvector.cpp myvector.h
	g++ -c myvector.cpp
clean:
	rm *.o vfs.out