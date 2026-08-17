#ifndef QUEUE_HPP
#define QUEUE_HPP

static const int QUEUE_CAPACITY = 100;

template<typename T>
class Queue{
private:
    T a[QUEUE_CAPACITY];
    int rear, frontIndex, count;

public:
    Queue();

    //thêm phần tử vào queue
    void enqueue(const T& x);

    //xóa phần tử khỏi queue
    void dequeue();

    //kiểm tra queue rỗng
    bool empty();

    //kích thước
    int size();

    //giá trị đầu hàng đợi
    const T& front();

    //cuối hàng đợi
    const T& back();

    //xóa queue
    void clear();
};

template<typename T>
Queue<T>::Queue(){
    rear = -1;
    frontIndex = count = 0;
}

template<typename T>
void Queue<T>::enqueue(const T& x){
    if(count == QUEUE_CAPACITY) return;
    rear = (rear + 1) % QUEUE_CAPACITY;
    a[rear] = x;
    ++count;
}

template<typename T>
void Queue<T>::dequeue(){
    if(count == 0) return;
    frontIndex = (frontIndex + 1) % QUEUE_CAPACITY;
    --count;
}

template<typename T>
bool Queue<T>::empty(){
    return count == 0;
}

template<typename T>
int Queue<T>::size(){
    return count;
}

template<typename T>
const T& Queue<T>::front(){
    return a[frontIndex];
}

template<typename T>
const T& Queue<T>::back(){
    return a[rear];
}

template<typename T>
void Queue<T>::clear(){
    rear = -1;
    frontIndex = count = 0;
}

#endif // QUEUE_HPP
