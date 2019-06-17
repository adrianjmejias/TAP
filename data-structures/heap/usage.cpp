#include "heap.hpp"
#include <initializer_list>
#include <functional>
#include <random>
#include <iostream>
typedef unsigned long long timeUnit;
template <typename durationType>
durationType measureTime(std::function<void()> f)
{
      auto start = std::chrono::system_clock::now();

      f();

      auto end = std::chrono::system_clock::now();
      return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

// Función para dividir el array y hacer los intercambios
int divide(std::vector<int> &array, int start, int end)
{
      int left;
      int right;
      int pivot;
      int temp;

      pivot = array[start];
      left = start;
      right = end;

      // Mientras no se cruzen los índices
      while (left < right)
      {
            while (array[right] > pivot)
            {
                  right--;
            }

            while ((left < right) && (array[left] <= pivot))
            {
                  left++;
            }

            // Si todavía no se cruzan los indices seguimos intercambiando
            if (left < right)
            {
                  temp = array[left];
                  array[left] = array[right];
                  array[right] = temp;
            }
      }

      // Los índices ya se han cruzado, ponemos el pivot en el lugar que le corresponde
      temp = array[right];
      array[right] = array[start];
      array[start] = temp;

      // La nueva posición del pivot
      return right;
}

// Función recursiva para hacer el ordenamiento
void quicksort(std::vector<int> &array, int start, int end)
{
      int pivot;

      if (start < end)
      {
            pivot = divide(array, start, end);

            // Ordeno la lista de los menores
            quicksort(array, start, pivot - 1);

            // Ordeno la lista de los mayores
            quicksort(array, pivot + 1, end);
      }
}
int main()
{
      // std::unique_ptr<Heap<int>> heap(new Heap<int>());

      // std::vector<int> arr;

      std::vector<timeUnit> timeQuick;
      std::vector<timeUnit> timeHeap;
      std::vector<timeUnit> testCases;

      testCases.push_back(1000);
      testCases.push_back(100000);
      testCases.push_back(1000000);
      testCases.push_back(10000000);
      testCases.push_back(100000000);

      std::random_device dev;
      std::mt19937 rng(dev());
      std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 10000000); // distribution in range [1, 6]
      int ii=0;
      for (auto a : testCases)
      {
            std::vector<int> randomQuick;
            std::vector<int> randomHeap;

            randomQuick.reserve(a);
            randomHeap.reserve(a);

            for (int ii = 0; ii < a; ii++)
            {
                  int r = dist6(rng);
                  randomQuick.push_back(r);
                  randomHeap.push_back(r);
            }

            timeUnit time;

            time = measureTime<timeUnit>([&]() {
                  quicksort(randomQuick, 0, randomQuick.size());
            });
            timeHeap.push_back(time);

            time = measureTime<timeUnit>([&]() {
                  Heap<int>::sort(randomHeap);
            });
            timeQuick.push_back(time);

            randomQuick.clear();
            randomHeap.clear();

            std::cout << timeQuick[ii] << std::endl;
            std::cout << timeHeap[ii] << std::endl;
            std::cout << std::endl;
            ii++;
      }

      for (int ii = 0; ii < timeQuick.size(); ii++)
      {
            std::cout << timeQuick[ii] << std::endl;
            std::cout << timeHeap[ii] << std::endl;
            std::cout << std::endl;
      }

      return 0;
}