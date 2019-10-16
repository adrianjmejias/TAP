// https://www.spoj.com/problems/FRNDCIRC/



// Lucy has made too many friends but she does not know how many friends are in her circle. 
// Assume that every relation is mutual. If Lucy is Patty's friend, then Patty is also Lucy's friend. 
// Your task is to help Lucy in keeping track of each person's circle size.


#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

using std::unordered_map;
using std::endl;
using std::cout;
using std::cin;
using std::string;


#define tcout(x) 



template <typename TKey>
class DisjointSet : protected unordered_map<TKey, TKey>{

    public:

        bool union_belong(TKey a, TKey b, bool shouldUnion)
        {
            TKey pa = find(a);
            TKey pb = find(b);

            tcout( << "pa " << pa<<"   a   " << a << endl);
            tcout( << "pb " << pb<<"   b   " << b << endl);

            bool belong = pa == pb;
            if(!belong && shouldUnion)
            {
                (*this)[pb] = pa;
                belong = true;
            }

            return belong;
        }

        void add(TKey a)
        {
            (*this)[a] = a;
        }


        TKey find(TKey child)
        {

            tcout( << "find  " << child <<endl);
            if(child == (*this)[child])
            {
                tcout( << "return " << child<< endl);

                return child;
            }

            TKey parent = find((*this)[child]);
            (*this)[child] = parent;
            tcout( << "return " << parent<< endl);
            return parent;
        }
};


int main()
{

    // Input Specification
    // The first line of input contains one integer T (T<=10) specifying the number of test cases to follow.
    // Each test case begins with a line containing an integer N (N<=100000), the number of new relations.
    // Each of the following N lines contains couple of strings denoting the names of two people who have just formed relation,
    // separated by a space. Names will have no more than 20 characters.
    


    // DisjointSet<string> test;


    int test;

    cin >> test;

    while(test--)
    {
        int N;
        cin >> N;
        
        DisjointSet<string> crc;
        unordered_map<string, int> qt;
        for(string a,b; N > 0 ; N--)
        {
            cin >> a >> b;


            if(!qt[a])
            {
                qt[a] = 1;
                crc.add(a);
            }

            if(!qt[b])
            {
                qt[b] = 1;
                crc.add(b);
            }


            string pa;
            string pb;
            pa = crc.find(a);
            pb = crc.find(b);

            if(crc.union_belong(a,b, true))
            {
                qt[pa] = qt[pa] + qt[pb];
            }

            cout << qt[pa] << endl;
        }
        
    }

    return 0;
}