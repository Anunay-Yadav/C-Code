#include <cstdlib>
#ifndef MANAGER
#include "manager.hpp"
#endif
#include <chrono>
using namespace std::chrono;
#include <unistd.h>
#include <cstring>
#define SIZE 250
void f(std::unique_ptr<int> &count){
    int k = *count;
    // sleep(abs(rand())%10 + 1000*(k == 1));
    std::cout << k << " " << *count << std::endl;
    k++;
    *count = k;
}
int main(){
    for(int i1 = 0; i1 < 1; i1++){
        manager task_handler(16);
        std::cout << sizeof(task_handler) << std::endl;
        std::unique_ptr<int> count(new int(0));
        call_id a1,a2;
        for(int i = 0;i < 500; i++){
            task_handler.push([&]{
                    task_handler.isolate([&]{
                        (*count)++;
                    }, a1);
                    task_handler.isolate([&]{
                        (*count)++;
                    }, a1);
            });
        }
        task_handler.finish();
        task_handler.finalize();
        std::cout << *count <<" value"<< std::endl;
    }
    return 0;
}