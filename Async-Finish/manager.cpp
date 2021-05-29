
#include <functional>
#ifndef MANAGER
    #include "manager.hpp"
#endif


bool operator<(const call_id &lhs,const call_id &rhs){
        return lhs.id < rhs.id;  
}

std::set<int> call_id::list_of_id;

call_id::call_id(){
    int k = abs(rand());
    while(call_id::list_of_id.find(k) != call_id::list_of_id.end()){
            k = abs(rand());
    }
    call_id::list_of_id.insert(k);
    id = k;
}

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
    my_mutex.lock();
    if(Queue.empty()) {
        my_mutex.unlock();    
        return ;
    }
    // manager::display();
    auto k = Queue.front();
    Queue.pop();
    my_mutex.unlock();
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
