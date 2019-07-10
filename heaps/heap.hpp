#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

template <class Elem>
class Heap : public std::vector<Elem> {
    private: size_t n;
    public: Heap();
    public: Heap(const Heap<Elem> &h);
    public: Heap(const std::vector<Elem> &a);
    public: ~Heap();
    public: void insert(const Elem &e);
    public: void remove();
    public: Elem &head(); // retorna referencia
    public: Elem head() const; // retorna copia
    public: static void sort(std::vector< Elem > &A);
    private: static void heapify(std::vector< Elem > &A);
    private: static void sink( std::vector< Elem > &A, int k, int n);// hundir
    private: void swim(int k); 
    private: inline static size_t parent(size_t index){
        return index >> 1;
    }
    private: inline static size_t left(size_t index){
        return index << 1;
    }
    private: inline static size_t right(size_t index){
        return left(index) | 1;
    }
    private: inline static size_t hasLeft(size_t index, size_t n){
        return left(index) <= n;
    }
    private: inline static size_t hasRight(size_t index, size_t n){
        return right(index) <= n;
    }
};


template <class Elem>
Heap<Elem>::Heap(){
    this->push_back(Elem());
    n = 0;
}

template <class Elem>
Heap<Elem>::Heap(const Heap<Elem> &h){

}

template <class Elem>
Heap<Elem>::Heap(const std::vector<Elem> &a){

}

template <class Elem>
Heap<Elem>::~Heap(){

}

template <class Elem>
void Heap<Elem>::insert(const Elem &e){
    this->push_back(e);
    n = this->size() -1;
    this->swim(n);
}

template <class Elem>
void Heap<Elem>::remove(){
    std::swap(this->at(1), this->at(n)); 
    n--;
    this->pop_back();
    sink(*dynamic_cast< std::vector<Elem>* >(this),1,n);
}

template <class Elem>
Elem& Heap<Elem>::head(){
    return this->at(1);
} // retorna referencia

template <class Elem>
Elem Heap<Elem>::head() const{
    return this->at(1);
} // retorna copia

template <class Elem>
void Heap<Elem>::sort(std::vector< Elem > &A){
    heapify(A);
    size_t n = A.size()-1;
    for(int i = n; i > 1; i--) {
        std::swap(A[1], A[i]);
        n--;
        sink(A,1,n);
    }
    A.erase(A.begin());
}

template <class Elem>
void Heap<Elem>::heapify(std::vector< Elem > &A){

    A.insert(A.begin(),0);
    size_t n = A.size()-1;
    for (int i = n/2; i>0; i--)
        sink(A, i, n);

}

template <class Elem>
void Heap<Elem>::sink( std::vector< Elem > &A, int k, int n){
    
    while(left(k) <= n){
        size_t biggerDudeIndex = left(k);
        if(right(k) <= n && A.at(right(k)) > A.at(biggerDudeIndex)){
            biggerDudeIndex = right(k);
        }


        if(A.at(k) > A.at(biggerDudeIndex)){
            // si la condicion de max heap se mantiene
            break;
        }else{
            std::swap(A.at(k), A.at(biggerDudeIndex));
        }
        
        k = biggerDudeIndex;
    }
} // hundir

template <class Elem>
void Heap<Elem>::swim(int k){
    while (k > 1 && this->at(parent(k)) < this->at(k))
    {
        std::swap(this->at(parent(k)), this->at(k));
        k = parent(k);
    }
}