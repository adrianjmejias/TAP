
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <time.h>
using namespace std;

//Strassen 
class Strassen{
    public:
        int splitLimit = 16;
    
    public:
        Strassen(){};

        void commonMxM(vector<vector<int>> A, vector<vector<int>> B, vector<vector<int>> &C, int n)
        {
            for (int i = 0; i < n; i++)
            {
                for (int k = 0; k < n; k++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }

        void StrassenRecursive(vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C, int tam)
        {
            if (tam <= splitLimit)
            {
                commonMxM(A, B, C, tam);
                return;
            }

            // other cases are treated here:
            else
            {
                int newTam = tam / 2;
                vector<int> rows(newTam);
                vector<vector<int>>
                    a11(newTam, rows), a12(newTam, rows), a21(newTam, rows), a22(newTam, rows),
                    b11(newTam, rows), b12(newTam, rows), b21(newTam, rows), b22(newTam, rows),
                    c11(newTam, rows), c12(newTam, rows), c21(newTam, rows), c22(newTam, rows),
                    p1(newTam, rows), p2(newTam, rows), p3(newTam, rows), p4(newTam, rows),
                    p5(newTam, rows), p6(newTam, rows), p7(newTam, rows),
                    aResult(newTam, rows), bResult(newTam, rows);

                int i, j;

                //dividing the matrices in 4 sub-matrices:
                for (i = 0; i < newTam; i++)
                {
                    for (j = 0; j < newTam; j++)
                    {
                        a11[i][j] = A[i][j];
                        a12[i][j] = A[i][j + newTam];
                        a21[i][j] = A[i + newTam][j];
                        a22[i][j] = A[i + newTam][j + newTam];

                        b11[i][j] = B[i][j];
                        b12[i][j] = B[i][j + newTam];
                        b21[i][j] = B[i + newTam][j];
                        b22[i][j] = B[i + newTam][j + newTam];
                    }
                }

                // Calculating p1 to p7:

                matPlusMat(a11, a22, aResult, newTam);          // a11 + a22
                matPlusMat(b11, b22, bResult, newTam);          // b11 + b22
                StrassenRecursive(aResult, bResult, p1, newTam); // p1 = (a11+a22) * (b11+b22)

                matPlusMat(a21, a22, aResult, newTam);      // a21 + a22
                StrassenRecursive(aResult, b11, p2, newTam); // p2 = (a21+a22) * (b11)

                matMinusMat(b12, b22, bResult, newTam); // b12 - b22
                StrassenRecursive(a11, bResult, p3, newTam); // p3 = (a11) * (b12 - b22)

                matMinusMat(b21, b11, bResult, newTam); // b21 - b11
                StrassenRecursive(a22, bResult, p4, newTam); // p4 = (a22) * (b21 - b11)

                matPlusMat(a11, a12, aResult, newTam);      // a11 + a12
                StrassenRecursive(aResult, b22, p5, newTam); // p5 = (a11+a12) * (b22)

                matMinusMat(a21, a11, aResult, newTam);     // a21 - a11
                matPlusMat(b11, b12, bResult, newTam);          // b11 + b12
                StrassenRecursive(aResult, bResult, p6, newTam); // p6 = (a21-a11) * (b11+b12)

                matMinusMat(a12, a22, aResult, newTam);     // a12 - a22
                matPlusMat(b21, b22, bResult, newTam);          // b21 + b22
                StrassenRecursive(aResult, bResult, p7, newTam); // p7 = (a12-a22) * (b21+b22)

                // calculating c21, c21, c11 e c22:

                matPlusMat(p3, p5, c12, newTam); // c12 = p3 + p5
                matPlusMat(p2, p4, c21, newTam); // c21 = p2 + p4

                matPlusMat(p1, p4, aResult, newTam);       // p1 + p4
                matPlusMat(aResult, p7, bResult, newTam);  // p1 + p4 + p7
                matMinusMat(bResult, p5, c11, newTam); // c11 = p1 + p4 - p5 + p7

                matPlusMat(p1, p3, aResult, newTam);       // p1 + p3
                matPlusMat(aResult, p6, bResult, newTam);  // p1 + p3 + p6
                matMinusMat(bResult, p2, c22, newTam); // c22 = p1 + p3 - p2 + p6

                // Grouping the results obtained in a single matrix:
                for (i = 0; i < newTam; i++)
                {
                    for (j = 0; j < newTam; j++)
                    {
                        C[i][j] = c11[i][j];
                        C[i][j + newTam] = c12[i][j];
                        C[i + newTam][j] = c21[i][j];
                        C[i + newTam][j + newTam] = c22[i][j];
                    }
                }
            }
        }

        unsigned int nextPow(int n)
        {
            return pow(2, int(ceil(log2(n))));
        }

        void strassen(vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C, unsigned int n)
        {
            //unsigned int n = tam;
            unsigned int m = nextPow(n);
            vector<int> rows(m);
            vector<vector<int>> A_aux(m, rows), B_aux(m, rows), C_aux(m, rows);

            for (unsigned int i = 0; i < n; i++)
            {
                for (unsigned int j = 0; j < n; j++)
                {
                    A_aux[i][j] = A[i][j];
                    B_aux[i][j] = B[i][j];
                }
            }

            StrassenRecursive(A_aux, B_aux, C_aux, m);
            for (unsigned int i = 0; i < n; i++)
            {
                for (unsigned int j = 0; j < n; j++)
                {
                    C[i][j] = C_aux[i][j];
                }
            }
        }

        void matPlusMat(vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C, int tam)
        {
            int i, j;

            for (i = 0; i < tam; i++)
            {
                for (j = 0; j < tam; j++)
                {
                    C[i][j] = A[i][j] + B[i][j];
                }
            }
        }

        void matMinusMat(vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C, int tam)
        {
            int i, j;

            for (i = 0; i < tam; i++)
            {
                for (j = 0; j < tam; j++)
                {
                    C[i][j] = A[i][j] - B[i][j];
                }
            }
        }

        void print(vector<vector<int>> matrix, int n)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (j != 0)
                    {
                        cout << "\t";
                    }
                    cout << matrix[i][j];
                }
                cout << endl;
            }
        }
};

//Modo Cubico
void orden3(vector<vector<int>> A, vector<vector<int>> B, vector<vector<int>> &C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            for (int j = 0; j < n; j++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    srand (time(NULL));
    clock_t start, end;
    Strassen *strAlgr = new Strassen();
    for(int n = 16; n <=2048; n=n+n)
    {
        vector<int> rows(n);
        vector<vector<int>> A(n, rows), B(n, rows), C(n, rows);

        //Initializing matrixes
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                A[i][j] = rand() % n;
                B[i][j] = rand() % n;
                C[i][j] = 0;
            }
            
        }
        

        cout << "*************************************************************" << endl;
        start = clock();
        strAlgr->strassen(A, B, C, n);
        end = clock();
        cout << "El tiempo promedio de Multiplicacion de matrices de tamaño " << n << ", por Strassen es: " << ((float)(end - start) / CLOCKS_PER_SEC) << "s" << endl;

        start = clock();
        orden3(A, B, C, n);
        end = clock();
        cout << "El tiempo promedio de Multiplicacion de matrices de tamaño " << n << ", por Cubico es: " << ((float)(end - start) / CLOCKS_PER_SEC) << "s" << endl;
        cout << "*************************************************************" << endl;

        //strAlgr->print(C, n);
    }

    return 0;
}