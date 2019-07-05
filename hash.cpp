

#include <vector>
#include <random>

#include <map>
#include <iostream>
#include <unordered_map>

std::vector<int> GenerateRandom(size_t size, std::function<int()> generator)
{
    std::vector<int> randVec;
    for (int ii = 0; ii < size; ii++)
    {
        randVec.push_back(generator());
    }
    return randVec;
}

typedef unsigned long long timeUnit;
template <typename durationType>
durationType measureTime(std::function<void()> f)
{
    auto start = std::chrono::system_clock::now();

    f();

    auto end = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int main()
{

    std::vector<int> testCases;

    testCases.push_back(1000);
    testCases.push_back(5000);
    testCases.push_back(10000);
    testCases.push_back(50000);
    testCases.push_back(100000);
    testCases.push_back(500000);
    testCases.push_back(1000000);
    testCases.push_back(5000000);
    testCases.push_back(10000000);
    testCases.push_back(50000000);
    testCases.push_back(100000000);

    std::unordered_map<int, int> _umap;
    std::map<int, int> _map;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 10000000); // distribution in range [1, 6]

    std::function<int()> randGenerator = [&]() {
        return dist(rng);
    };

    std::vector<unsigned long long> v[3];
    unsigned long long uSumInsert[4], uSumDelete[4];
    unsigned long long SumInsert[4], SumDelete[4];

    uSumInsert[3] = 0;
    uSumDelete[3] = 0;
    SumInsert[3] = 0;
    SumDelete[3] = 0;

    for (int jj = 0; jj < 3; jj++)
    {

        for (auto test : testCases)
        {
            std::cout << "testing " << test << std::endl;
            auto vectorTest = GenerateRandom(test, randGenerator);


            uSumInsert[jj] = (measureTime<unsigned long long>([&]() {
                for (auto b : vectorTest)
                {
                    _umap[b] = b;
                }
            }));

            uSumDelete[jj] = (measureTime<unsigned long long>([&]() {
                for (auto b : vectorTest)
                {
                    _umap.erase(b);
                }
            }));

            SumInsert[jj] = (measureTime<unsigned long long>([&]() {
                for (auto b : vectorTest)
                {
                    _map[b] = b;
                }
            }));

            SumDelete[jj] = (measureTime<unsigned long long>([&]() {
                for (auto b : vectorTest)
                {
                    _map.erase(b);
                }
            }));

            std::cout << test << " uSumInsert " << uSumInsert[jj] << std::endl;
            std::cout << test << " uSumDelete " << uSumDelete[jj] << std::endl;
            std::cout << test << " SumInsert " << SumInsert[jj] << std::endl;
            std::cout << test << " SumDelete " << SumDelete[jj] << std::endl;

            uSumInsert[3] += uSumInsert[jj] / test;
            uSumDelete[3] += uSumDelete[jj] / test;
            SumInsert[3] += SumInsert[jj] / test;
            SumDelete[3] += SumDelete[jj] / test;
        }
    }
    std::cout << "Promedio inserciones unordered " << uSumInsert[3] << std::endl;
    std::cout << "Promedio inserciones " << SumInsert[3] << std::endl;
    std::cout << "Promedio borrar unordered " << uSumDelete[3] << std::endl;
    std::cout << "Promedio borrar " << SumDelete[3] << std::endl;

    return 0;
}
