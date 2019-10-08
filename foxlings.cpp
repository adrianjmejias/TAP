#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>


using ull = int;

std::unordered_map<ull, ull> foxlings;


// •Implementar la clasede conjuntos disjuntos. Incluir constructor, find y union-pertenece.



void print(std::vector<ull> a)
{
    std::cout<< std::endl;

    for (int ii = 0; ii < a.size(); ii++)
    {
        std::cout << a[ii] <<", ";

    }
    std::cout<< std::endl;
    
    for (int ii = 0; ii < a.size(); ii++)
    {
        std::cout << ii <<", ";

    }

    std::cout<< std::endl;
}



class DisjointSet 
{
    public:
    std::vector<ull> data;

    DisjointSet(ull size)
    {
        data.reserve(size);
        std::fill_n(std::back_inserter(data), size, -1);
    }


    // Find(x): devuelve la raíz del árbol al cual
    // pertenece x
    ull find(ull index)
    {
        while(index != data[index]) index = data[index];
        return index;
    }

    // Unión-pertenencia: la operación de
    // pertenencia busca la raíz de los árboles en
    // donde están ambos elementos. Si la raíz
    // coincide retorna verdad. En caso contrario
    // falso. El parámetro unión indica si los
    // conjuntos deben unirse.
    bool union_belong(int x, int y, bool doUnion)
    {
        ull rx = find(x);
        ull ry = find(y);

        
        // std::cout<< "x "<< x <<" rx "<< rx <<std::endl;
        // std::cout<< "y "<< y <<" ry "<< ry <<std::endl;
        bool were_joined = rx == ry;

        if(!were_joined && doUnion)
        {
            while(y != ry)
            {
                data[y] = data[data[y]];
                y = data[y];
            }

            while(x != rx)
            {
                data[x] = data[data[x]];
                x = data[x];
            }

            data[rx] = ry;
            were_joined=true;
            // std::cout<<"joined " << rx << " to "<< ry<<std::endl;
        }
        // print(data);
        

        return were_joined;
    }

    void add(ull toInsert)
    {
        // while(toInsert >= data.size()) data.push_back(-1);
        bool isNew = data[toInsert] < 0;
        // std::cout<< toInsert <<" isNew "<< isNew << std::endl;

        if(isNew)
        {
            data[toInsert] = toInsert;
        }

    }
};

int main()
{
    ull res =0, n, m;

    std::cin >> n >> m;

    DisjointSet foxies(n+2);


    res = n;
    while(m--)
    {
        ull a, b;

        std::cin >> a >> b;

        foxies.add(a);
        foxies.add(b);

        if(foxies.union_belong(a,b, true))
        {
            // std::cout<<"res--"<<std::endl;
            res--;
        }

    }

    // print(foxies.data);
    std::cout << res << std::endl;

    return 0;
}
