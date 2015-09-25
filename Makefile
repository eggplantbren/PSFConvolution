CFLAGS = -m64 -O3 -flto -march=native -funroll-loops -DNDEBUG -Wall -Wextra -ansi -pedantic
LIBS = -lfftw3
OBJECTS = PSF.o

default:
	g++ -c $(CFLAGS) -c *.cpp
	g++ -o test_PSF test_PSF.o $(OBJECTS) $(LIBS)
	rm -rf *.o

