

#include <iostream>
#include <algorithm>
#include <deque>
#include <exception>

namespace Fib
{

#define DONE
#define ASSERT(x)                               \
    if (!x)                                      \
    {                                           \
        cout << "Assert failed" << endl;        \
        cout << #x << endl;                     \
        cout << "Line " << __LINE__ << endl;   \
        cout << "Archivo " << __FILE__ << endl; \
    }                                           \

    class fib;
    class node;

    using DataType = int;
    using ptrType = node* ;
    class node{
        friend class fib;
        DataType _data;

        node(DataType data) : _data(data){}

        int _key;
        ptrType _lBro = nullptr;
        ptrType _rBro = nullptr;
        ptrType _parent = nullptr;
        std::deque<ptrType> _children;

        DONE void insertLeft(ptrType other)
        {
            ASSERT(other != nullptr);

            ptrType lNode = _lBro;

            if(lNode){
                lNode->_rBro = other;
                other->_lBro = lNode;
            }

            _lBro = other;
            other->_rBro = this;


            other->_parent = _parent;
        }
    };

    class fib
    {
        ptrType min;
        ptrType leftest;
        size_t size = 0;

        ptrType push(DataType t, int key){
            size++;
            
            ptrType newNode = new node(t);
            newNode->_key = key;

            leftest = newNode;

            if(!min){
                min = newNode;
                return min;
            }
            
            min->insertLeft(newNode);

            if(newNode->_key < min->_key){
                min = newNode;
            }

        }

        DataType pop()
        {
            if(size == 0)
            {
                throw std::exception("Can't pop an empty queue");
            }
            size--;

            ptrType popped = min;
            ptrType lBro = popped->_lBro;
            ptrType rBro = popped->_rBro;
            ASSERT(min != nullptr);


            size_t nChild = popped->_children.size();
            if(nChild <= 0){
                // lBro = rBro;
                // rBro = lBro;
            }
            else
            {
                ptrType poppedLChild = popped->_children[0];
                ptrType poppedRChild = popped->_children[nChild -1]; 
                

                poppedLChild->_lBro = popped->_lBro;
                popped->_lBro->
            }

            min = leftest;
            for(ptrType aux = leftest; aux; aux = aux->_rBro)
            {
                if(aux->_key < min->_key){
                    min = aux;
                }
            }

            return popped->_data;
        }


        void reOrder(){

        }
    };
    
}

int main(int argc, const char** argv) {
    return 0;
}
