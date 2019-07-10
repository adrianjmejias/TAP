#include <list>
#include <iostream>

using std::cout;
using std::endl;
using std::list;
using std::ostream;


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

template <typename TT>
class heap
{
public:
    heap<TT> *left;
    heap<TT> *right;
    TT& data;

    heap(TT& _data) : data(_data){}
    heap() {}

    friend ostream &operator<<(ostream &out, const heap<TT> &h)
    {
        for (size_t ii = 0, iiEnd = h.size(); ii < iiEnd; ii++)
        {
            out << h.data;
        }
        return out;
    }
};

template <typename TT>
class heap_fibonnacci : protected list<heap<TT> *>
{
public:
    heap<TT> *min;

    heap_fibonnacci(){}

    void Push(TT data)
    {
        
        this->push_back(new heap<TT>(data));
    }

    void Print()
    {
        for (auto ii = this->begin(); ii != this->end(); ii++)
        {

            cout << "new Heap" << endl;
            cout << (*ii)->data;
        }
    }
};

int main(int argc, char const *argv[])
{
    heap_fibonnacci<Person> fib;
    fib.Push(Person(0,10));
    fib.Push(Person(1,9));

    fib.Print();
    return 0;
}
