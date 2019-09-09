randwriter: randwriter.o list.o
	g++ -o randwriter randwriter.o list.o

randwriter.o: list.h randwriter.cc
	g++ -c randwriter.cc

list.o: list.cc list.h
	g++ -c list.cc

clean:
	rm -rf randwriter randwriter.o list.o