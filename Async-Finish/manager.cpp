
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
    int shutdown;
    int thread_num;
    std::mutex my_mutex;
}
void manager::display(){
    std::cout << "Queueu size ::: " <<  Queue.size() << std::endl;
}
void manager::start(int num){
    shutdown = 0;
    thread_num = num;
    for(int i = 0;i < thread_num; i++){
        all_threads.push_back(std::thread(&manager::thread_fetch_execute));
    }
}
void manager::push(void (*heap_f)(void*), void* args){
    std::lock_guard<std::mutex> guard(my_mutex);
    Queue.push(std::make_unique<task>(heap_f,args));
}

std::unique_ptr<task> manager::pop_execute(){
    std::lock_guard<std::mutex> guard(my_mutex);
    if(Queue.empty()) return std::unique_ptr<task>(nullptr);
    std::unique_ptr<task> k(std::move(Queue.front()));
    Queue.pop();
    return k;
}

void manager::finalize(){
    shutdown = 1;
    for(int i = 0;i < thread_num; i++){
        all_threads[i].join();
    }
    all_threads.clear();
    shutdown = 0;
    thread_num = 0;
}
void manager::finish(){
    while(!Queue.empty()){
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