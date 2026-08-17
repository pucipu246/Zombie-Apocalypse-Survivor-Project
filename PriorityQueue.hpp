#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP
#include <functional>

template<typename T, typename Comp = std::less<T>>
class PriorityQueue{
private:
    T *a;
    int capacity;
    int sz;
    Comp cmp;

public:
    //khởi tạo
    PriorityQueue(int capacity = 100);

    //hủy
    ~PriorityQueue();

    //heapify tại đỉnh i
    void heapify(int i);

    //resize priority queue khi đầy size == capacit
    void resize();

    //thêm vào phần tử
    void insert(const T& x);

    //xóa phần tử ra khỏi priority queue
    void pop();

    //lấy giá của top và pop
    T extract();

    //xem giá trị của top
    const T& peek();

    //kiểm tra priority rỗng
    bool empty();

    //kích thước của priority queue
    int size();
};

template<typename T, typename Comp>
PriorityQueue<T, Comp>::PriorityQueue(int capacity){
    if(capacity == 0) capacity = 1;
    this->capacity = capacity;
    a = new T[capacity];
    sz = 0;
}

template<typename T, typename Comp>
PriorityQueue<T, Comp>::~PriorityQueue(){
    delete[] a;
    a = nullptr;
    capacity = 0;
    sz = 0;
}

template<typename T, typename Comp>
void PriorityQueue<T, Comp>::heapify(int i){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if(l < sz && cmp(a[largest], a[l])) largest = l;
    if(r < sz && cmp(a[largest], a[r])) largest = r;

    if(largest != i){
        std::swap(a[largest], a[i]);
        heapify(largest);
    }
}

template<typename T, typename Comp>
void PriorityQueue<T, Comp>::resize(){
    if(sz < capacity) return;
    capacity *= 2;
    T *newArr = new T[capacity];
    for(int i = 0; i < sz; ++i){
        newArr[i] = a[i];
    }
    delete[] a;
    a = newArr;
}

template<typename T, typename Comp>
void PriorityQueue<T, Comp>::insert(const T& x){
    resize();

    a[sz++] = x;

    int i = sz - 1;
    while(i > 0){
        int par = (i - 1) / 2;
        if(cmp(a[i], a[par])) break;
        std::swap(a[i], a[par]);
        i = par;
    }
}

template<typename T, typename Comp>
void PriorityQueue<T, Comp>::pop(){
    if(sz == 0) return;
    std::swap(a[0], a[sz - 1]);
    --sz;
    heapify(0);
}

template<typename T, typename Comp>
T PriorityQueue<T, Comp>::extract(){
    T top = a[0];
    pop();
    return top;
}

template<typename T, typename Comp>
const T& PriorityQueue<T, Comp>::peek(){
    return a[0];
}

template<typename T, typename Comp>
bool PriorityQueue<T, Comp>::empty(){
    return sz == 0;
}

template<typename T, typename Comp>
int PriorityQueue<T, Comp>::size(){
    return sz;
}

#endif // PRIORITY_QUEUE_HPP
