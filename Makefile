# top-level rule to create the program.
all: LectureBadge

# compiling the source file.
LectureBadge.o: LectureBadge.cpp
	g++ -g -Wall -c LectureBadge.cpp

# compiling the source file.
LSAByte.o: LSAByte.cpp
	g++ -g -Wall -c LSAByte.cpp

# compiling the source file.
LectureBadgeRFID.o: LectureBadgeRFID.cpp
	g++ -g -Wall -c LectureBadgeRFID.cpp
	
# linking the program.
LectureBadge: LectureBadge.o LSAByte.o LectureBadgeRFID.o
	g++ -g LectureBadge.o LSAByte.o LectureBadgeRFID.o -o LectureBadge

# cleaning everything that can be automatically recreated with "make".
clean:
	/bin/rm -f LectureBadge *.o



