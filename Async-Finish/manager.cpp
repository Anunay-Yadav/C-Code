
#include <functional>
#ifndef MANAGER
    #include "manager.hpp"
#endif



void manager::display(){
    std::cout << "Queueu size ::: " <<  Queue.size() << std::endl;
}
manager::manager(int num){
    shutdown = 0;
    thread_num = num;
    for(int i = 0;i < thread_num; i++){
        all_threads.push_back(std::thread(&manager::thread_fetch_execute,this));
    }
}


std::function<void()> manager::pop_execute(){
    std::lock_guard<std::mutex> guard(my_mutex);
    if(Queue.empty()) return nullptr;
    auto k = Queue.front();
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
        auto k = pop_execute();
        if(k != nullptr){
            k();
        }
    }
}

void manager::thread_fetch_execute(){
    while(shutdown != 1){
        auto k = pop_execute();
        if(k != nullptr){
            k();
        }
    }
}
// void manager::for_async_1d(loop t, void func(void*) , void* arg,  MODE mode){
//     if(mode == RECURSIVE){
        
//     }
//     else if(mode == FLAT){

//     }

// }

// void manager::flat_1d_gen(loop t, void func(void*,int), void* arg ){
//     for(int i = t.start; i < t.end ; i+=t.tile_size){
//         int ind = i;
//         for(int j = 0;j < t.tile_size ;j++){
//             manager::push([](void*) {
                
//             }, arg );
//         }
//     }
// }
