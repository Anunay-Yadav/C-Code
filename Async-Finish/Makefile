default: test1 test2 

test1:
	g++ -g -std=c++17 -fsanitize=address -Wall -pthread test.cpp task.cpp manager.cpp 
	./a.out
test2:
	g++ -std=c++17 -fsanitize=address -Wall -pthread test2.cpp task.cpp manager.cpp 
	./a.out