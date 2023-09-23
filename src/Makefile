CXX= g++
CXXFLAGS= -std=c++17 -g -Wall -Werror -Wextra
SRC= main.cc model/**.cc **.h

all:
	$(CXX) $(SRC) $(CXXFLAGS)
	./a.out

clean:
	rm -rf a.out **.gch a.out.dSYM

style:
	cd ..
	clang-format -i $(SRC)
