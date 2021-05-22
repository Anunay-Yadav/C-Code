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
    
    unique_pointer(unique_pointer&& copy_data){
        data = copy_data.data;
        copy_data.data = nullptr;
    }

    unique_pointer& operator=(unique_pointer &&right){
        data = right.data;
        right.data = nullptr;
    };

    unique_pointer(unique_pointer* copy_data)=delete;
    unique_pointer(const unique_pointer& copy_data)=delete;
    unique_pointer& operator=(const unique_pointer &right)=delete;
    
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
    unique_pointer<int> sp2(std::move(sp1));  // copy construction

    if(sp1.data == nullptr){
        std :: cout << "Correct test1" << std :: endl;
    }
    else{
        std :: cout << "wrong test1" << std :: endl;
    }
}
int test2()
{
    unique_pointer<int>  sp1(new int(5));
    unique_pointer<int>  sp2(new int(6));

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
