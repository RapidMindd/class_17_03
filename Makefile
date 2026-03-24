CXXFLAGS += -Wall -Wextra -std=c++14 -MMD

main: main.cpp
	g++ $^ -o $@

-include main.d
