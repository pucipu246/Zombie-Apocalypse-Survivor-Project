#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP
#include <functional>
#include <utility>

template<typename T, typename Comp = std::less<T>>
void bubbleSort(T *arr, int n, Comp cmp = Comp()){
    for(int i = 0; i < n - 1; ++i){
        for(int j = 0; j < n - i - 1; ++j){
            if(cmp(arr[j + 1], arr[j])){
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

template<typename T, typename Comp = std::less<T>>
void selectionSort(T *arr, int n, Comp cmp = Comp()){
    for(int i = 0; i < n - 1; ++i){
        int id = i;
        for(int j = i + 1; j < n; ++j){
            if(cmp(arr[j], arr[id])) id = j;
        }
        std::swap(arr[i], arr[id]);
    }
}

template<typename T, typename Comp = std::less<T>>
void insertionSort(T *arr, int n, Comp cmp = Comp()){
    for(int i = 1; i < n; ++i){
        int j = i;
        while(j > 0 && cmp(arr[j], arr[j - 1])){
            std::swap(arr[j], arr[j - 1]);
            --j;
        }
    }
}

template<typename T, typename Comp>
void heapify(T *arr, int i, int n, Comp cmp){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if(l < n && cmp(arr[largest], arr[l])) largest = l;
    if(r < n && cmp(arr[largest], arr[r])) largest = r;

    if(largest != i){
        std::swap(arr[i], arr[largest]);
        heapify(arr, largest, n, cmp);
    }
}

template<typename T, typename Comp = std::less<T>>
void heapSort(T *arr, int n, Comp cmp = Comp()){
    for(int i = n / 2 - 1; i >= 0; --i){
        heapify(arr, i, n, cmp);
    }

    for(int i = n - 1; i > 0; --i){
        std::swap(arr[0], arr[i]);
        heapify(arr, 0, i, cmp);
    }
}

template<typename T, typename Comp>
int partition(T *arr, int l, int r, Comp cmp){
    int m = l + (r - l) / 2;
    if(cmp(arr[m], arr[l])) std::swap(arr[l], arr[m]);
    if(cmp(arr[r], arr[l])) std::swap(arr[l], arr[r]);
    if(cmp(arr[r], arr[m])) std::swap(arr[m], arr[r]);

    std::swap(arr[m], arr[r - 1]);

    T pivot = arr[r - 1];
    int i = l, j = r - 1;
    while(true){
        do
        {
            ++i;
        }while(cmp(arr[i], pivot));

        do
        {
            --j;
        }while(cmp(pivot, arr[j]));

        if(i >= j) break;
        std::swap(arr[i], arr[j]);
    }
    std::swap(arr[i], arr[r - 1]);
    return i;
}

template<typename T, typename Comp = std::less<T>>
void quickSort(T *arr, int lo, int hi, Comp cmp = Comp()){
    if(lo >= hi) return;

    int p = partition(arr, lo, hi, cmp);
    quickSort(arr, lo, p - 1, cmp);
    quickSort(arr, p + 1, hi, cmp);
}

template<typename T, typename Comp>
void mergeSort(T *arr, int l, int r, Comp cmp){
    if(l >= r) return;

    int m = l + (r - l) / 2;
    mergeSort(arr, l, m, cmp);
    mergeSort(arr, m + 1, r, cmp);

    int n1 = m - l + 1;
    int n2 = r - m;

    T *L = new T[n1];
    T *R = new T[n2];

    for(int i = 0; i < n1; ++i){
        L[i] = arr[l + i];
    }

    for(int i = 0; i < n2; ++i){
        R[i] = arr[m + 1 + i];
    }

    int i = 0, j = 0, k = l;
    while(i < n1 && j < n2){
        if(cmp(R[j], L[i])) arr[k++] = R[j++];
        else arr[k++] = L[i++];
    }

    while(i < n1){
        arr[k++] = L[i++];
    }

    while(j < n2){
        arr[k++] = R[j++];
    }

    delete[] L;
    delete[] R;
}

template<typename T, typename Comp = std::less<T>>
void mergeSort(T *arr, int n, Comp cmp = Comp()){
    mergeSort(arr, 0, n - 1, cmp);
}

template<typename T>
bool linearSearch(T *arr, int n, const T& key){
    for(int i = 0; i < n; ++i){
        if(arr[i] == key) return true;
    }

    return false;
}

template<typename T, typename Comp = std::less<T>>
bool binarySearch(T *arr, int n, const T& key, Comp cmp = Comp()){
    int l = 0, r = n - 1;
    while(l <= r){
        int m = l + (r - l) / 2;
        if(!cmp(arr[m], key) && !cmp(key, arr[m])) return true;
        else if(cmp(arr[m], key)){
            l = m + 1;
        }
        else r = m - 1;
    }
    return false;
}

#endif // ALGORITHM_HPP
