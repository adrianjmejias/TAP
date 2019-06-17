
#include <memory>
#include <functional>
#include <array>
namespace fibonacci{
    
    template <typename TT>
    class Node{
        private: int grado = 0;
        private: bool isMarked = false;
        public : TT value;
        private: std::shared_ptr<Node<TT> > right;
        private: std::shared_ptr<Node<TT> > left;
        private: std::shared_ptr<Node<TT> > child;
        private: std::shared_ptr<Node<TT> > parent;

        // public: bool ToggleMark(){
        //     return(isMarked=!isMarked);
        // };

        public: bool SetParent(std::shared_ptr<Node<TT> > other){
            this->parent = other;
            isMarked = false;
        }
        public: bool SetLeft(std::shared_ptr<Node<TT> > other){
            this->left = other;
        }
        public: bool SetRight(std::shared_ptr<Node<TT> > other){
            this->right = other;
        }
        public: bool SetChild(std::shared_ptr<Node<TT> > other){
            this->child = other;
        }


        public: void insertRight(const Node<TT> &other){
            // conecto al que estoy insertando
            other->SetRight(this->right);
            other->SetLeft(this);
            
            // redirijo el que estaba a mi derecha para que ahora apunte
            // en su izquierda al que estoy insertando
            this->right->SetLeft(other);
            this->SetRight(other);
        }
    };

    template <typename TT>
    class Heap{
        public: std::shared_ptr<Node<TT> > root;
        private: std::function<int(TT,TT)> comp;
        public: Heap(const std::function<int(TT, TT)> &comp){
            this->comp = comp;
        }
        void Union(const Heap<TT> &other){
            // other.root->family[Node<TT>]

            this->root->insertRight(other.root);

            if(comp(this->root, other.root)){
                
            }
        }
    };

}