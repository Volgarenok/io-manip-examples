CXXFLAGS += -std=c++14 -Wall -Wextra

lab-io: main.cpp
	$(CXX) -o $@ $^

run-io: lab-io
	@./lab-io
