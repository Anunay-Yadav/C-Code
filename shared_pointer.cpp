#include<iostream>
#include<memory>
template<typename data_type>
class shared_pointer{
 private:
    data_type* data;
    int* count;
 public:

    explicit shared_pointer(data_type old_data): data(new data_type(old_data)), count(new int(1)){}
    shared_pointer(const shared_pointer &old): data(old.get_data()), count(old.get_count){
        ++(*count);
    }
    shared_pointer(shared_pointer &&old): data(old.get_data()), count(old.get_count){
        old.set_data(nullptr);
        old.set_cnt(new int(1));
        ++(*count);
    }
    
    data_type operator*(){
        return (*data);
    }
    data_type* operator->(){
        return data;
    }
    shared_pointer& operator=(shared_pointer &&old){
        data = old.get_data();
        count = old.get_count();
        ++(*count);
    }
    
    
    data_type* get_data(){
        return data;
    }
    void set_data(data_type &x){
        *data = x;
    }
    void set_data(data_type* x){
        *data = *x;
    }
    int* get_count(){
        return count;
    }
    void set_count(int cnt){
        *count = cnt;
    }
    void set_count(int* cnt){
        count = cnt;
    }
    ~shared_pointer(){
        --(*count);

        if((*count) == 0){

            std :: cout << data << std :: endl;
            delete data;
        }
    }
}; 
class Data{
    public : 
    int a = 10;
    int b;
};
void f(Data x){
    x.a = 11;
}
int main(){
    int* a = new int(10);
    std :: shared_ptr<int> ptr_a(a);
    std :: shared_ptr<int> ptr_d(a);
    std :: cout << *ptr_a << " : " << *ptr_d << std ::  endl;
    
    *a = 20;

    std :: cout << *ptr_a << " : " << *ptr_d << std :: endl;


}