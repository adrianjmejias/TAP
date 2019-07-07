#include <vector>
#include <deque>
#include <queue>
#include <memory>
#include <iostream>

using std::cout;
using std::deque;
using std::endl;
using std::ostream;
using std::queue;
using std::vector;

template <typename TT>
class binomial_tree;

template <typename TT>
class binomial_heap;

class Person
{
public:
    unsigned int age;
    unsigned int id;

    Person(unsigned int id, unsigned int age)
    {
        this->age = age;
        this->id = id;
    }

    bool operator<(const Person &other)
    {
        return age < other.age;
    }
    bool operator<=(const Person &other)
    {
        return age <= other.age;
    }
    bool operator>(const Person &other)
    {
        return age > other.age;
    }
    bool operator>=(const Person &other)
    {
        return age >= other.age;
    }
    bool operator==(const Person &other)
    {
        return age == other.age;
    }
    friend ostream &operator<<(ostream &out, const Person &p)
    {
        out << "(" << p.id << ", " << p.age << ")" << endl;
        return out;
    }
};

// bin tree de grado k props
// el root tiene k hijos  (esto es el grado lol)
// el arbol tiene 2^k
// el arbol tiene altura k
// los hijos del arbol son hijos de grado k-1, k-2 ...
template <typename TT>
class binomial_tree : private deque<binomial_tree<TT&>*>
{
public:
    size_t key;
    TT& data;

    binomial_tree(TT &_data) : data(_data)
    {

    }

    static binomial_tree& Merge(binomial_tree<TT> &a, binomial_tree<TT> &ii)
    {
        if (a.size() != ii.size())
        {
            cout << "not equal baby" << endl;
        }

        binomial_tree &min = (ii.data < a.data) ? ii : a;
        binomial_tree &max = (ii.data >= a.data) ? a : ii;

        min.emplace_front(max);
        return min;
    }
    void Print()
    {
        queue<binomial_tree<TT&> *> q;
        q.push(this);

        while (!q.empty())
        {
            binomial_tree<TT&> &act = q.front();
            q.pop();

            ASSERT(act == nullptr);

            cout << act->data << endl;
        }
    }
    TT Pop()
    {
    }

    bool Sink()
    {
    }

    bool Float()
    {
    }

    void ModifyKey()
    {
    }
};

// binomial_heap
// colleccion de binomial_trees
// cada binomial_tree es un heap
// al menos 1 arbol de cada grado
// el arbol más grande es de grado floor logn
// y hay al menos  floor (logn) +1 arboles en total
template <typename TT>
class binomial_heap : vector<binomial_tree<TT> *>
{
public:
    size_t nNodes = 0;
    size_t maxGrade = 0;
    TT data;
    binomial_heap()
    {
    }
    ~binomial_heap()
    {
    }

    void Print()
    {
        for (size_t ii = 0; ii < this->size(); ii++)
        {
            cout<< "Grado "<< ii<< "==========================="<<endl;
            this->at(ii)->Print();
            cout<< "Grado "<< ii<< "---------------------------"<<endl;
        }
    }

    void Push(TT data)
    {
        push_back(new binomial_tree<TT>(data));
    }

    TT pop()
    {
    }
};

int main()
{
    Person a(0,10);
    Person b(1,9);
    binomial_tree<Person> treeA(a);
    binomial_tree<Person> treeB(b);



    
    treeA.Print();

    cout<< "--------------"<<endl;
    treeB.Print();

    cout<< "--------------X"<<endl;

    treeA.Merge(treeA, treeB);
    treeA.Print();
    cout<< "--------------"<<endl;
    treeB.Print();
    
    return 0;
}