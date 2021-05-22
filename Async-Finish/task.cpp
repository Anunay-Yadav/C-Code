
#ifndef TASK
#include "task.hpp"
#endif
#include <thread>
#include <mutex>
#include <queue>
#include <vector>
task::task(void (*func)(void*),void* arguments): heap_f(func),arguments(arguments){
}
task::task(task && a): heap_f(a.heap_f), arguments(a.arguments){
    a.heap_f = nullptr;
    a.arguments = nullptr;
}
task::task(task & a): heap_f(a.heap_f), arguments(a.arguments){}

bool task::execute(){
    try{
        (*heap_f)(arguments);
    }
    catch(char* mess){
        std::cout << "Exception :" << mess << std::endl;
        return 0;
    }
    catch(...){
        std::cout << "Default Exception" << std::endl;
        return 0;
    }
    return 1;
}
void task::operator()(){
    int x = execute();
    if(!x){
        std::cout << "Execution stopped" << std::endl;
    }
}