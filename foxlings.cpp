#include <unordered_map>
#include <iostream>

using ull = unsigned long long;

std::unordered_map<ull, ull> foxlings;

ull root(ull kid)
{
    if(!foxlings[kid])
    {
        foxlings[kid] = kid;
    }

	while(kid != foxlings[kid])
    {
        foxlings[kid] = foxlings[foxlings[kid]];
        kid = foxlings[kid];
    }

    return kid;
}

int main()
{
    ull res =0, n, m;



    std::cin >> n >> m;

    res = n;
    while(m--)
    {
        ull a, b;

        std::cin >> a >> b;

        ull pa = root(a);
        ull pb = root(b);

        if( pa != pb)
        {
            res--;
            foxlings[pb]= pa;
        }

    }


    std::cout << res<< std::endl;

    return 0;
}
