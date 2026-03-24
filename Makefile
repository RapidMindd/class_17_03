CXXFLAGS += -Wall -Wextra -std=c++14 -MMD

main: main.cpp
	$(CXX) $^ -o $@

-include main.d

clean:
	@$(RM) main.d main.o main
