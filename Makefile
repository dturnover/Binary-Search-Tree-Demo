#linking
bst: bst.o
	g++ -o bst bst.o

#compilation
bst.o: bst.cpp bst.o
	g++ -c bst.cpp -g -Iincludes

.PHONY: archive
archive:
	tar -cvzf $(USER)_bst.tar.gz bst.cpp BinarySearchTree.h dsexceptions.h sample.txt README.txt bst.out Makefile
