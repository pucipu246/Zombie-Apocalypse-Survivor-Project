#ifndef HASHTABLE
#define HASHTABLE
#include <iostream>
#include <string>

template<typename T>
struct Hash;

template<>
struct Hash<int>{
    int operator()(int x) const{
        return x;
    }
};

template<>
struct Hash<std::string>
{
    long long operator()(const std::string& s) const{
        long long h = 0;
        for(int i = 0; i < s.size(); ++i){
            h = h * 31 + s[i];
        }
        return h;
    }
};

const int capacity = 101;

template<typename K, typename V>
class HashTable{
private:
    class AVL{
        class Node{
        public:
            K key;
            V val;
            Node *left, *right;
            int height, sz;

            Node(){
                left = nullptr;
                right = nullptr;
                height = 0;
                sz = 1;
            }
            Node(const K& key, const V& val){
                this->key = key;
                this->val = val;
                left = nullptr;
                right = nullptr;
                height = 0;
                sz = 1;
            }

        };

        Node *root;

    private:
        int max(const int& a, const int& b){
            if(a < b) return b;
            return a;
        }

        int getHeight(Node *pRoot){
            if(pRoot == nullptr) return -1;
            return pRoot->height;
        }

        int getSize(Node *pRoot){
            if(pRoot == nullptr) return 0;
            return pRoot->sz;
        }

        int getBalanceFactor(Node *pRoot){
            if(pRoot == nullptr) return 0;
            return getHeight(pRoot->right) - getHeight(pRoot->left);
        }

        void update(Node *&pRoot){
            if(pRoot == nullptr) return;
            pRoot->height = 1 + max(getHeight(pRoot->left), getHeight(pRoot->right));
            pRoot->sz = 1 + getSize(pRoot->left) + getSize(pRoot->right);
        }

        void rotateLL(Node *&pRoot){
            if(pRoot == nullptr) return;

            Node *newRoot = pRoot->left;
            pRoot->left = newRoot->right;
            newRoot->right = pRoot;

            update(pRoot);
            update(newRoot);
            pRoot = newRoot;
        }

        void rotateRR(Node *&pRoot){
            if(pRoot == nullptr) return;

            Node *newRoot = pRoot->right;
            pRoot->right = newRoot->left;
            newRoot->left = pRoot;

            update(pRoot);
            update(newRoot);
            pRoot = newRoot;
        }

        void rotateLR(Node *&pRoot){
            if(pRoot == nullptr) return;

            Node *A = pRoot;
            Node *B = pRoot->left;
            Node *C = B->right;

            B->right = C->left;
            A->left = C->right;
            C->left = B;
            C->right = A;

            update(B);
            update(A);
            update(C);
            pRoot = C;
        }

        void rotateRL(Node *&pRoot){
            if(pRoot == nullptr) return;

            Node *A = pRoot;
            Node *B = pRoot->right;
            Node *C = B->left;

            B->left = C->right;
            A->right = C->left;
            C->right = B;
            C->left = A;

            update(A);
            update(B);
            update(C);
            pRoot = C;
        }

        void rebalance(Node *&pRoot){
            update(pRoot);
            int bf = getBalanceFactor(pRoot);
            if(bf < -1){
                if(getBalanceFactor(pRoot->left) <= 0){
                    rotateLL(pRoot);
                }
                else{
                    rotateLR(pRoot);
                }
            }
            else if(bf > 1){
                if(getBalanceFactor(pRoot->right) >= 0){
                    rotateRR(pRoot);
                }
                else{
                    rotateRL(pRoot);
                }
            }
        }

        Node *insertNode(Node *pRoot, const K& key, const V& val){
            if(pRoot == nullptr){
                return new Node(key, val);
            }
            if(key < pRoot->key){
                pRoot->left = insertNode(pRoot->left, key, val);
            }
            else if(key > pRoot->key){
                pRoot->right = insertNode(pRoot->right, key, val);
            }
            else{
                pRoot->val = val;
                return pRoot;
            }

            rebalance(pRoot);
            return pRoot;
        }

        Node *findMin(Node *pRoot){
            if(pRoot == nullptr) return nullptr;
            while(pRoot->left != nullptr){
                pRoot = pRoot->left;
            }
            return pRoot;
        }

        Node *deleteNode(Node *pRoot, const K& key){
            if(pRoot == nullptr) return nullptr;

            if(key < pRoot->key){
                pRoot->left = deleteNode(pRoot->left, key);
            }
            else if(key > pRoot->key){
                pRoot->right = deleteNode(pRoot->right, key);
            }
            else{
                if(pRoot->left == nullptr){
                    Node *tmp = pRoot->right;
                    delete pRoot;
                    return tmp;
                }
                if(pRoot->right == nullptr){
                    Node *tmp = pRoot->left;
                    delete pRoot;
                    return tmp;
                }

                Node *tmp = findMin(pRoot->right);
                pRoot->val = tmp->val;
                pRoot->key = tmp->key;
                pRoot->right = deleteNode(pRoot->right, tmp->key);
            }

            rebalance(pRoot);
            return pRoot;
        }

        Node *search(Node *pRoot, const K& key){
            if(pRoot == nullptr) return nullptr;

            if(key < pRoot->key){
                return search(pRoot->left, key);
            }
            else if(key > pRoot->key){
                return search(pRoot->right, key);
            }
            return pRoot;
        }

        void NLR(Node *pRoot){
            if(pRoot == nullptr) return;

            std::cout << "(" << pRoot->key << ", " << pRoot->val << ") ";
            NLR(pRoot->left);
            NLR(pRoot->right);
        }

        void LRN(Node *pRoot){
            if(pRoot == nullptr) return;

            LRN(pRoot->left);
            LRN(pRoot->right);
            std::cout << "(" << pRoot->key << ", " << pRoot->val << ") ";
        }

        void LNR(Node *pRoot){
            if(pRoot == nullptr) return;

            LNR(pRoot->left);
            std::cout << "(" << pRoot->key << ", " << pRoot->val << ") ";
            LNR(pRoot->right);
        }

        void removeTree(Node *pRoot){
            if(pRoot == nullptr) return;
            removeTree(pRoot->left);
            removeTree(pRoot->right);
            delete pRoot;
        }

    public:
        AVL();

        ~AVL();

        //thêm phần tử vào cây
        void insert(const K& key, const V& val);

        //xóa phần tử có khóa key
        void remove(const K& key);

        //kiểm tra khóa key có trong cây khong
        bool contains(const K& key);

        //tìm và trả về con trỏ giá trị val nếu tìm được, tìm không thấy trả về nullptr
        V *find(const K& key);

        //xóa cây
        void clear();

        //kích thước cây
        int size();

        //kiểm tra rỗng
        bool empty();

        //in theo thứ tự tăng dần
        void print();
    };

    //HashTable
    int sz;
    AVL bucket[capacity];
    Hash<K> hasher;

public:
    HashTable();

    ~HashTable();

    //hash function
    int hash(const K& key);

    //thêm phần tử vào table
    void insert(const K& key, const V& val);

    //xóa phần tử có khóa key trong table
    void remove(const K& key);

    //kiểm tra table rỗng
    bool contains(const K& key);

    //tìm phần tử có khóa key trong table và trả về con trỏ của giá trị val nếu tìm được, tìm không thấy trả về nullptr
    V *find(const K& key);

    //dùng [] để trích xuất giá trị của khóa key, VD: t[key]
    V& operator[](const K& key);

    //kích thước table
    int size();

    //xóa table
    void clear();

    //in ra giá trị
    void print();
};

//AVL
template<typename K, typename V>
HashTable<K, V>::AVL::AVL(){
    root = nullptr;
}

template<typename K, typename V>
HashTable<K, V>::AVL::~AVL(){
    clear();
}

template<typename K, typename V>
void HashTable<K, V>::AVL::insert(const K& key, const V& val){
    root = insertNode(root, key, val);
}

template<typename K, typename V>
void HashTable<K, V>::AVL::remove(const K& key){
    root = deleteNode(root, key);
}

template<typename K, typename V>
bool HashTable<K, V>::AVL::contains(const K& key){
    return search(root, key) != nullptr;
}

template<typename K, typename V>
V* HashTable<K, V>::AVL::find(const K& key){
    Node *tmp = search(root, key);
    if(tmp == nullptr) return nullptr;
    return &(tmp->val);
}

template<typename K, typename V>
void HashTable<K, V>::AVL::clear(){
    removeTree(root);
    root = nullptr;
}

template<typename K, typename V>
int HashTable<K, V>::AVL::size(){
    return getSize(root);
}

template<typename K, typename V>
bool HashTable<K, V>::AVL::empty(){
    return root == nullptr;
}

template<typename K, typename V>
void HashTable<K, V>::AVL::print(){
    LNR(root);
}

//HashTable
template<typename K, typename V>
HashTable<K, V>::HashTable(){
    sz = 0;
}

template<typename K, typename V>
HashTable<K, V>::~HashTable(){
    clear();
}

template<typename K, typename V>
int HashTable<K, V>::hash(const K& key){
    long long x = hasher(key);
    if(x < 0) x = -x;
    return x % capacity;
}

template<typename K, typename V>
void HashTable<K, V>::insert(const K& key, const V& val){
    int idx = hash(key);
    if(!bucket[idx].contains(key)){
        ++sz;
    }
    bucket[idx].insert(key, val);
}

template<typename K, typename V>
void HashTable<K, V>::remove(const K& key){
    int idx = hash(key);
    if(bucket[idx].contains(key)) --sz;
    bucket[idx].remove(key);
}

template<typename K, typename V>
bool HashTable<K, V>::contains(const K& key){
    int idx = hash(key);
    return bucket[idx].contains(key);
}

template<typename K, typename V>
V* HashTable<K, V>::find(const K& key){
    int idx = hash(key);
    return bucket[idx].find(key);
}

template<typename K, typename V>
V& HashTable<K, V>::operator[](const K& key){
    V *k = find(key);
    if(k==nullptr){ insert(key, V()); k=find(key);} return *k;
}

template<typename K, typename V>
int HashTable<K, V>::size(){
    return sz;
}

template<typename K, typename V>
void HashTable<K, V>::clear(){
    for(int i = 0; i < capacity; ++i){
        bucket[i].clear();
    }
    sz = 0;
}

template<typename K, typename V>
void HashTable<K, V>::print(){
    for(int i = 0; i < capacity; ++i){
        if(!bucket[i].empty()){
            bucket[i].print();
            std::cout << "\n";
        }
    }
}

#endif // HASHTABLE
