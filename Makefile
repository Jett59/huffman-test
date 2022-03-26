CXX:=clang++
CXXFLAGS:=-std=c++17 -g -Wall -Wextra -pedantic

LIB-SRCS:=bitstring.cpp

SRCS:=$(LIB-SRCS) main.cpp
TEST-SRCS:=$(LIB-SRCS) test.cpp

program: $(SRCS)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@
	@echo done

.PHONY: test
test: $(TEST-SRCS)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@
	@./test && echo Passed

clean:
	@rm -f program
