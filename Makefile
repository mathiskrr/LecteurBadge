# top-level rule to create the program.
all: Main

# compiling the source file.
Main.o: Main.cpp
	g++ -g -Wall -c Main.cpp

# compiling the source file.
LSAByte.o: LSAByte.cpp
	g++ -g -Wall -c LSAByte.cpp

# compiling the source file.
CLecteurRFID.o: CLecteurRFID.cpp
	g++ -g -Wall -c CLecteurRFID.cpp

# compiling the source file.
CBDD.o: CBDD.cpp
	g++ -g -Wall -c CBDD.cpp

# compiling the source file.
INIReader.o: INIReader.cpp
	g++ -g -Wall -c INIReader.cpp

# compiling the source file.
ini.o: ini.cpp
	g++ -g -Wall -c ini.cpp

# compiling the source file.
CPorte.o: CPorte.cpp
	g++ -g -Wall -c CPorte.cpp
	
# linking the program.
Main: Main.o LSAByte.o CLecteurRFID.o CBDD.o INIReader.o CPorte.o ini.o
	g++ -g Main.o LSAByte.o CLecteurRFID.o CBDD.o INIReader.o ini.o CPorte.o -o Main -lmysqlcppconn

# cleaning everything that can be automatically recreated with "make".
clean:
	/bin/rm -f Main *.o



