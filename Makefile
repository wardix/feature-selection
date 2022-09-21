fselection: main.o parsefile.o
	g++ -Wall main.o parsefile.o -o fselection

main.o: main.cpp parsefile.hpp
	g++ -std=c++11 -Wall -c main.cpp

parsefile.o: parsefile.cpp parsefile.hpp
	g++ -std=c++11 -Wall -c parsefile.cpp 

clean:
	rm -f *.o fselection
