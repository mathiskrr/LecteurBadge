# top-level rule to create the program.
all: Main

# compiling the source file.
Main.o: Main.cpp
	g++ -g -Wall -c Main.cpp

# compiling the source file.
LSAByte.o: LSAByte.cpp
	g++ -g -Wall -c LSAByte.cpp

# compiling the source file.
LecteurRFID.o: LecteurRFID.cpp
	g++ -g -Wall -c LecteurRFID.cpp

# compiling the source file.
VerifBDD.o: VerifBDD.cpp
	g++ -g -Wall -c VerifBDD.cpp
	
# linking the program.
Main: Main.o LSAByte.o LecteurRFID.o VerifBDD.o
	g++ -g Main.o LSAByte.o LecteurRFID.o VerifBDD.o -o Main -lmysqlcppconn

# cleaning everything that can be automatically recreated with "make".
clean:
	/bin/rm -f Main *.o



