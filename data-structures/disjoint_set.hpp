
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

    int N;
    int M; // max num of people in a community
    int Q; // num querys

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
             // NOTE- A friend requested is accepted only if the merger of the two communities results in a community not greater than 'm'.
            std::cout<< n1<<n2<< std::endl;


        }

    }

    return 0;
}


