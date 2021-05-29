#ifndef MANAGER
#include "manager.hpp"
#endif
#include <chrono>
using namespace std::chrono;
#include <unistd.h>
#include <cstring>
#define SIZE 250

int main(){
    for(int i1 = 0; i1 < 100; i1++){
        manager task_handler(8);
        std::unique_ptr<int> count (new int(0));
        for(int i = 0;i < 1000; i++){
            task_handler.push([&]{
                for(int j = 0;j < 500; j++){
                    task_handler.isolate([&]{
                        (*count)++;
                    }, 1);
                }
            });
        }
        task_handler.finish();
        task_handler.finalize();
        std::cout << *count <<" value"<< std::endl;
    }
    return 0;
}