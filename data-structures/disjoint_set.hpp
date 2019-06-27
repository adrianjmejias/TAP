
#include <vector>

namespace BoletaDS
{
    template <typename TT>
    class disjoint_set{
        class node{
            TT data;
            ID parent;

        };

        size_t size;
        
        std::vector<node<TT> > nodes;


        


        TT data;



    };
} // namespace BoletaDS




