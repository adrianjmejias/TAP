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

class DisjointSet : public unordered_map<string, string>{


public:

    void add(string a, string b)
    {

    }
};


int main()
{

    // Input Specification
    // The first line of input contains one integer T (T<=10) specifying the number of test cases to follow.
    // Each test case begins with a line containing an integer N (N<=100000), the number of new relations.
    // Each of the following N lines contains couple of strings denoting the names of two people who have just formed relation,
    // separated by a space. Names will have no more than 20 characters.
    
    int test;

    std::cin >> test;

    while(test--)
    {
        int N;
        std::cin >> N;
        
        DisjointSet crc;

        for(string a,b; N > 0 ; N--)
        {
            crc.add(a,b);

            // cout << crc.colony_size(a) << endl;
        }
        
    }

    return 0;
}