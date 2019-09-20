
#include <vector>
#include <iostream>

// https://www.spoj.com/problems/SOCNETC/
namespace BoletaDS
{

    
    template <typename TT>
    class DisjointSet
    {
        struct Element
        {
            int parent;
            TT data;
        }
        using DataContainer = std::vector<Element>;
        DataContainer elements;



        static bool belongs(DisjointSet a, DisjointSet b, Element ea, Element eb)
        {

            // int ii = ea

        }


        void Union(DisjointSet other){

        }

        int _Find(int e)
        {
            while(e > 0) 
            {
                e= elements[e].parent;
            }
        }

    };
} // namespace BoletaDS

int main()
{
    // You need to build an ADD friend feature. if 'x' sends a friend request to 'y',he may accept it or deny it.
    
    // .When two people 'x' and 'y' becomes friends,the communities of two are merged together.
    // (If 'x' has no friends,it's community consist of only himself,size-1)
    
    // Since,your friend is low on funds,the data center he uses has a restriction-the MAXIMUM size of any community cannot exceed 'm'.


    // You need to work on following three types of queries-


    
    // NOTE- A friend requested is accepted only if the merger of the two communities results in a community not greater than 'm'.


    // The first line of input consists of two positive integers - n and m(n is the number of registered users and m is the maximum size of any community).
    // Next line consist of a positive integer q(number of queries).

    // q lines follows(Each line consist of a query as described in the problem statement).

    // The queries follows 1-indexing.

    int N, M, Q;

    // std::cin >> N >> M >> Q;
    scanf("%d %d\n", &N, &M);
    scanf("%d\n", &Q);

    while(Q--)
    {
        int n1, n2;


        if(scanf("S %d", n1) == 3)
        {
            // S x - prints the size of the community 'x' belongs to.
            std::cout<< n1<< std::endl;
            

        }
        if(scanf("E %d %d", n1, n2) == 3)
        {
            // E x y - check whether x and y are present in same community(print 'Yes' or 'No')
            std::cout<< n1<<n2<< std::endl;
            

        }
        if(scanf("A %d %d", n1, n2) == 3)
        {
            // A x y - x sends a friend request to y
            std::cout<< n1<<n2<< std::endl;


        }

    }

    return 0;
}


