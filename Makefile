CXXFLAGS:=-std=c++17 -g -Wall -Wextra -pedantic

SRCS:=huffman.cpp

program: $(SRCS)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@
	@echo done

clean:
	@rm -f program
