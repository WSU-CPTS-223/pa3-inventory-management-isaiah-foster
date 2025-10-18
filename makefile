CXX = g++
CXXFLAGS = -Wall -std=c++11
OBJ = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

all: a.out

a.out: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) a.out