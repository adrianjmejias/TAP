
typedef unsigned long long timeUnit;
template <typename durationType>
durationType measureTime(std::function<void()> f)
{
      auto start = std::chrono::system_clock::now();

      f();

      auto end = std::chrono::system_clock::now();
      return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

std::vector<unsigned int> GenerateRandVector(){

}







int main(){

    std::vector<timeUnit> testCases;

    testCases.push_back(1000);
    testCases.push_back(100000);
    testCases.push_back(1000000);
    testCases.push_back(10000000);
    testCases.push_back(100000000);


    for(auto a : testCases){


    }

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 10000000); // distribution in range [1, 6]




    return 0;
}