default: test1 test2 test3

test1:
	g++ -g -std=c++17 -fsanitize=address -Wall -pthread src/test.cpp src/task.cpp src/manager.cpp 
	./a.out
test2:
	g++ -g -std=c++17 -fsanitize=address -Wall -pthread src/test2.cpp src/task.cpp src/manager.cpp
	./a.out
test3:
	g++ -g -std=c++17 -fsanitize=address -Wall -pthread src/test3.cpp src/task.cpp src/manager.cpp
	./a.out
