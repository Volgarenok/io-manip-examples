CXXFLAGS += -std=c++14 -Wall -Wextra

lab-io: main.cpp stream_guard.cpp
	$(CXX) -o $@ $^

run-io: lab-io
	@./lab-io
