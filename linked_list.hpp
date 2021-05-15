template<typename T>
class Node{
    public:
        T data;
        Node* next;
        Node(T data){
            this -> data = data;
        }
};

template<typename T>
class LinkedList{
    public:
        Node<T>* head;
        void push_back(Node<T>* new_obj){
            if(head == nullptr){
                head = new_obj;
                return;
            }
            Node<T>* curr = head;
            while(curr -> next != nullptr){
                curr = curr -> next;
            }
            curr -> next = new_obj;
        }
        void push_mid(Node<T>* new_obj, const T& key){
            if(head == nullptr){
                head = new_obj;
                return;
            }
            Node<T>* curr = head;
            while(curr -> data != key && curr -> next != nullptr){
                curr = curr -> next;
            }
            new_obj -> next = curr -> next;
            curr -> next = new_obj;
        }
        void delete_mid(const T& key){
            if(head == nullptr){
                return;
            }
            Node<T>* curr = head;
            if(curr -> data == key){
                head = head -> next;
                delete curr;
                return;
            }
            Node<T>* prev = head;
            curr = curr -> next;
            while(curr != nullptr && curr -> data != key ){
                prev = curr;
                curr = curr -> next;
            }
            if(curr -> data == key){
                prev -> next = curr -> next;
                delete curr;
            }
        }
};