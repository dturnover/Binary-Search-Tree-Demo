#linking
lab8: lab8.o
	g++ -o lab8 lab8.o

#compilation
lab8.o: lab8.cpp lab8.o
	g++ -c lab8.cpp -g -Iincludes

.PHONY: archive
archive:
	tar -cvzf $(USER)_lab8.tar.gz lab8.cpp BinarySearchTree.h dsexceptions.h sample.txt README.txt l8.out Makefile
