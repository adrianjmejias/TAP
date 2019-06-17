// #include <iostream>
// #include <chrono>
// #include <ctime>

// int fibonacci(int n)
// {
//     if (n < 3) return 1;
//     return fibonacci(n-1) + fibonacci(n-2);
// }

// int main()
// {
//     std::chrono::time_point<std::chrono::system_clock> start, end;
//     start = std::chrono::system_clock::now();

//     end = std::chrono::system_clock::now();

//     int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
//                              (end-start).count();
//     std::time_t end_time = std::chrono::system_clock::to_time_t(end);

//     std::cout << "Cálculo terminado  " << std::ctime(&end_time)
//               << "tiempo transcurrido: " << elapsed_seconds << "s\n";

//     return 0;
// }





void permute(int step, int A[], int n)
{
    if (step == n)
        print(A, n); // (0,A[0]), (1,A[1]), (2,A[2]), ..., (n-1, A[n-1])
    else
        for (int i = step; i < n; i++)
        {
            bool valid = true;
            for (int k = 0; k < step; k++)

                if (sameDiagonal(k, A[k], step, A[i]))
                {

                    valid = false;
                    break;
                }
            if (valid)
            {

                std::swap(A[step], A[i]);
                permute(step + 1, A, n);
                std::swap(A[step], A[i]);
            }
        }
}