
#include <functional>
#ifndef MANAGER
    #include "manager.hpp"
#endif



void manager::display() const{
    std::cout << "Queueu size ::: " <<  Queue.size() << std::endl;
}
manager::manager(int num){
    shutdown = 0;
    thread_num = num;
    for(int i = 0;i < thread_num; i++){
        all_threads.push_back(std::thread(&manager::thread_fetch_execute,this));
    }
}


void manager::pop_execute(){
    std::lock_guard<std::mutex> guard(my_mutex);
    if(Queue.empty()) return ;
    // manager::display();
    auto k = Queue.front();
    Queue.pop();
    k();
}

void manager::finalize(){
    shutdown = 1;
    for(int i = 0;i < thread_num; i++){
        all_threads[i].join();
    }
    all_threads.clear();
    shutdown = 0;
    thread_num = 0;
    lock.clear();
}
void manager::finish(){
    while(!Queue.empty()){
        pop_execute();
    }
}

void manager::thread_fetch_execute(){
    while(shutdown != 1){
        pop_execute();
    }
}
