#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>

template <typename T>
struct Node{
    T data;
    Node<T> *next;
    Node(){
        next = nullptr;
    }
    Node(const T& x){
        data = x;
        next = nullptr;
    }
};

template <typename T>
struct LinkedList
{
    Node<T> *head;
    Node<T> *tail;
    int length;

    //khởi tạo
    LinkedList();

    //hủy
    ~LinkedList();

    //chèn đầu
    void insertFront(const T& x);

    //chèn cuối
    void insertBack(const T& x);

    //chèn tại vị trí
    void insertAt(int index, const T& x);

    //xóa node đầu tiên có giá trị bằng val
    void remove(const T& value);

    //xóa tại vị trí
    void removeAt(int index);

    //tìm node đầu tiên có giá trị bằng value
    Node<T> *find(const T& value);

    //duyệt và in ra List
    void print(bool reverse = false);

    //trả về kích thước List
    int size();

    //xóa List
    void clear();
};

template <typename T>
LinkedList<T>::LinkedList(){
    head = nullptr;
    tail = nullptr;
    length = 0;
}

template <typename T>
void LinkedList<T>::insertFront(const T& x){
    Node<T> *newNode = new Node<T>(x);
    if(head == nullptr){
        head = newNode;
        tail = newNode;
        ++length;
        return;
    }
    newNode->next = head;
    head = newNode;
    ++length;
}

template <typename T>
void LinkedList<T>::insertBack(const T& x){
    Node<T> *newNode = new Node<T>(x);
    if(head == nullptr){
        head = newNode;
        tail = newNode;
        ++length;
        return;
    }
    tail->next = newNode;
    tail = newNode;
    ++length;
}

template <typename T>
void LinkedList<T>::insertAt(int index, const T& x){
    if(index < 0 || index > length) return;

    if(index == 0){
        insertFront(x);
        return;
    }

    if(index == length){
        insertBack(x);
        return;
    }

    Node<T> *newNode = new Node<T>(x);

    Node<T> *cur = head;
    for(int i = 0; i < index - 1; ++i){
        cur = cur->next;
    }
    newNode->next = cur->next;
    cur->next = newNode;
    ++length;
}

template <typename T>
void LinkedList<T>::remove(const T& value){
    Node<T> *dummy = new Node<T>();
    dummy->next = head;
    Node<T> *cur = dummy;
    while(cur->next != nullptr){
        if(cur->next->data == value){
            Node<T> *del = cur->next;
            if(del == tail) tail = (cur == dummy ? nullptr : cur);
            cur->next = del->next;
            delete del;
            del = nullptr;
            --length;
            break;
        }
        cur = cur->next;
    }
    head = dummy->next;
    delete dummy;
    dummy = nullptr;
}

template <typename T>
void LinkedList<T>::removeAt(int index){
    if(index < 0 || index >= length) return;

    if(head == nullptr) return;

    if(index == 0){
        Node<T> *del = head;
        head = head->next;
        delete del;
        del = nullptr;
        if(head == nullptr){
            tail = nullptr;
        }
        --length;
        return;
    }

    Node<T> *cur = head;

    for(int i = 0; i < index - 1; ++i){
        cur = cur->next;
    }

    Node<T> *del = cur->next;
    if(del == tail) tail = cur;
    cur->next = del->next;
    delete del;
    del = nullptr;
    --length;
}

template <typename T>
Node<T>* LinkedList<T>::find(const T& value){
    Node<T> *cur = head;
    while(cur != nullptr){
        if(cur->data == value) return cur;
        cur = cur->next;
    }
    return nullptr;
}

template <typename T>
void printReverse(Node<T> *node){
    if(node == nullptr) return;
    printReverse(node->next);
    std::cout << node->data << " ";
}

template <typename T>
void LinkedList<T>::print(bool reverse){
    if(reverse){
        printReverse(head);
        std::cout << "\n";
        return;
    }
    Node<T> *cur = head;
    while(cur != nullptr){
        std::cout << cur->data << " ";
        cur = cur->next;
    }
    std::cout << "\n";
}

template <typename T>
int LinkedList<T>::size(){
    return length;
}

template <typename T>
void LinkedList<T>::clear(){
    while(head != nullptr){
        Node<T> *del = head;
        head = head->next;
        delete del;
        del = nullptr;
    }
    tail = nullptr;
    length = 0;
}

template <typename T>
LinkedList<T>::~LinkedList(){
    clear();
}

#endif // LINKEDLIST_HPP
