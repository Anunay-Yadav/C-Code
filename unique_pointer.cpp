#include <iostream>
#include <memory>

template<typename data_type>
class unique_pointer{
    public:
    data_type* data;
    explicit unique_pointer(data_type copy_data){
        data = new data_type(copy_data);
    }
    explicit unique_pointer(data_type* copy_data){
        data = copy_data;
    }
    explicit unique_pointer(unique_pointer& copy_data){
        data = copy_data.data;
        copy_data.data = nullptr;
    }
    explicit unique_pointer(unique_pointer&& copy_data){
        data = copy_data.data;
        copy_data.data = nullptr;
    }
    unique_pointer& operator=(unique_pointer &&right)=delete;
    unique_pointer& operator=(unique_pointer &right)=delete;
    
    data_type* operator->(){
        return data;
    }
    data_type operator*(){
        return (*data);
    }
    ~unique_pointer(){
        if(data == nullptr)
            return;
        if(data != nullptr)
            std :: cout << data << std :: endl;
        delete data;
    }
    data_type* release(){
        data_type* new_t = nullptr;
        new_t = data;
        data = nullptr;
        return new_t;
    }
};
int test1()
{
    unique_pointer<int> sp1(new int(5));
    unique_pointer<int> sp2(sp1);  // copy construction

    if(sp1.data == nullptr){
        std :: cout << "Correct test1" << std :: endl;
    }
    else{
        std :: cout << "wrong test1" << std :: endl;
    }
             // Here the compiler generated copy constructor
             // kicks in and does a member wise copy of sp1
             // into sp2. That in itself is not a problem.
}
int test2()
{
    unique_pointer<int>  sp1(new int(5));
    unique_pointer<int>  sp2(new int(6));

    // sp2 = sp1; // Assignment operation.

             // Here the compiler generated assignment
             // operator kicks in and does a member wise
             // assignment of sp1 into sp2.
             //
             // The main problem with the assignment here
             // is that we have lost the original pointer
             // that sp2 was holding.
    if(sp1.data == nullptr){
        std :: cout << "Correct test1" << std :: endl;
    }
    else{
        std :: cout << "wrong test1" << std :: endl;
    }
}
void takeOwner1(unique_pointer<int> x)
{}
void takeOwner2(unique_pointer<int> const& x)
{}
void takeOwner3(unique_pointer<int>&& x)
{}
int main()
{
    int*  data = new int(7);


    test1();
    test2();
}
