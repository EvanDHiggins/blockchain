

all: *.cpp
	clang++ -std=c++14 -o out $^
