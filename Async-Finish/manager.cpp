
#ifndef MANAGER
#include "manager.hpp"
#endif
#include <thread>
#include <mutex>
#include <queue>
#include <vector>
#include <memory>

namespace manager{
    std::queue<std::unique_ptr<task>> Queue;
    std::vector<std::thread> all_threads;
    int size;
    int shutdown;
    int thread_num;
    std::mutex my_push_mutex;
    std::mutex my_pop_mutex;
}

void manager::start(int num){
    size = 0;
    shutdown = 0;
    thread_num = num;
    for(int i = 0;i < thread_num; i++){
        all_threads.push_back(std::thread(&manager::thread_fetch_execute));
    }
}
void manager::push(void (*heap_f)(void*), void* args){
    std::lock_guard<std::mutex> guard(my_push_mutex);
    std::unique_ptr<task> f1 = std::make_unique<task>(heap_f,args);
    Queue.push(std::move(f1));
    size++;
}

std::unique_ptr<task> manager::pop_execute(){
    std::lock_guard<std::mutex> guard(my_pop_mutex);
    if(Queue.size() == 0) return std::unique_ptr<task>(nullptr);
    std::unique_ptr<task> k(std::move(Queue.front()));
    Queue.pop();
    size--;
    return k;
}

void manager::finalize(){
    shutdown = 1;
    for(int i = 0;i < thread_num; i++){
        all_threads[i].join();
    }
}
void manager::finish(){
    while(size != 0){
        std::unique_ptr<task> k(std::move(pop_execute()));
        if(k != nullptr){
            k -> execute();
        }
    }
}

void manager::thread_fetch_execute(){
    while(shutdown != 1){
        std::unique_ptr<task> k(std::move(pop_execute()));
        if(k != nullptr){
            k -> execute();
        }
    }
}