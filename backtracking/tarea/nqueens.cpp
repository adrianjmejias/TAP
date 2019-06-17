#include <vector>
#include <array>
#include <algorithm>
#include <iostream>
#include <random>

#include <sstream>
#include <chrono>
typedef int timeUnit;

namespace TapAdrix
{
template <typename durationType>
durationType measureTime(std::function<void()> f)
{
    auto start = std::chrono::system_clock::now();

    f();

    auto end = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

class NQueens : public std::vector<int>
{
public:
    enum class SolveType
    {
        RANDOM,
        NORMAL,
    };

    int solve(SolveType type = SolveType::NORMAL, float percentage = 1.0f)
    {
        if (percentage < 0 || percentage > 1)
        {
            throw std::invalid_argument("Percentage of taken solutions must be within 0 and 1");
        }

        m_numRand = static_cast<int>(round((m_size - 1) * percentage));

        if (m_numRand == 0)
        {
            throw std::invalid_argument("Percentage is too little");
        }

        m_sType = type;
        m_nSol = 0;
        m_solve();
        return m_nSol;
    }

    NQueens(int size)
    {
        setSize(size);
    }

    int setSize(int n)
    {
        if (n <= 3)
        {
            std::string out_string;
            std::stringstream ss;
            ss << n;
            throw std::invalid_argument("Invalid size " + ss.str());
        }
        m_size = n;
        this->reserve(m_size);
        m_positions.reserve(m_size);
        for (int ii = 0; ii < m_size; ii++)
        {
            m_positions.push_back(ii);
        }
        return n;
    }

    ~NQueens(){
        m_positions.clear();
        clear();
    }

private:
    int m_size;
    std::vector<int> m_positions;
    int m_nSol;
    SolveType m_sType;
    int m_numRand;

    bool m_survives(int col) const
    {
        bool isAlive = true;
        const int fil = size(); // fila que ocupara la reina

        for (int oFil = 0; isAlive && oFil < fil; oFil++)
        {
            const int oCol = at(oFil);
                // si comparten fila, col o diag.
            isAlive = !((oFil == fil) || (oCol == col) || (abs(oFil - fil) == abs(oCol - col)));
        }
        return isAlive;
    };

    void m_print() const
    {
        for (int ii = 0; ii < size(); ii++)
        {
            std::cout<< ii << " " << at(ii) << std::endl;
        }
        std::cout<< "---------" << std::endl;
    }

    void m_solve()
    {
        if(m_nSol > 0){
            return ;
        }
        if (this->size() == m_size)
        {
            m_nSol++;
            // if (m_sType == SolveType::RANDOM)
            //     m_print();
        }
        else
        {
            if (m_sType == SolveType::RANDOM)
            {
                // std::cout << "random" << std::endl;
                std::random_device rd;
                std::mt19937 g(rd());
                std::shuffle(m_positions.begin(), m_positions.end(), g);

                for (int ii = 0; ii < m_numRand; ii++)
                {
                    const int pos = m_positions[ii];
                    if (m_survives(pos))
                    {
                        push_back(pos);
                        m_solve();
                        if(m_nSol > 0) return;
                        pop_back();
                    }
                }
            }
            else
            {   
                for (const int pos : m_positions)
                {
                    if (m_survives(pos))
                    {
                        push_back(pos);
                        m_solve();
                        if(m_nSol > 0) return;

                        pop_back();
                    }
                }
            }
        }
    }
};
} // namespace TapAdrix
int main(int argc, char **argv)
{
    using namespace TapAdrix;

    const int numRepeat = 3;
    auto testCases = { 20,21,22,23,24,25,26,27,28,29,30,31,32};
    std::array<timeUnit, 12> countRandTime({0});
    std::array<unsigned long long, 12> countRandSol({0});
    std::array<timeUnit, 12> countNormalTime({0});
    std::array<unsigned long long, 12> countNormalSol({0});


    double acumNormal{0};
    double acumRand{0};

    int nSolNormal = 0;
    int nSolRand = 0;
    for (int ii = 0; ii < numRepeat; ii++)
    {
        std::cout<<"Caso "<<ii<<std::endl;
        for (const int ii : testCases)
        {
            timeUnit timeNormal;
            timeUnit timeRand;
            int isRandSolved;
            int isNormalSolved;

            timeNormal = measureTime<timeUnit>([ii, &isNormalSolved]() {
                NQueens problem(ii);
                isNormalSolved = problem.solve(NQueens::SolveType::NORMAL, 1);
            });

            timeRand = measureTime<timeUnit>([ii, &isRandSolved]() {    
                NQueens problem(ii);
                isRandSolved = problem.solve(NQueens::SolveType::RANDOM, 0.3f);
            });
            
            nSolRand += isRandSolved;
            nSolNormal += isNormalSolved;

            std::cout << "For n=" << ii << std::endl;
            std::cout << "Normal consigue " << isNormalSolved << " y tarda " << timeNormal << " milisegundos" << std::endl;
            std::cout << "Random consigue " << isRandSolved << " y tarda " << timeRand << " milisegundos" << std::endl;

            countRandTime[ii] += timeRand;
            countRandSol[ii] += nSolRand;

            countNormalTime[ii] += timeNormal;
            countNormalSol[ii] += nSolNormal;
            
            acumRand += countRandTime[ii]/float(numRepeat);
            acumNormal += countNormalTime[ii]/float(numRepeat);
        }
    }

    std::cout << "En " << numRepeat << " pruebas" << std::endl;
    std::cout << "Random tomó "<< acumRand <<" milisegundos y encontró "<<nSolRand << std::endl;
    std::cout << "Normal tomó "<< acumNormal <<" milisegundos y encontró "<<nSolNormal << std::endl;

    return 0;
}



// El problema esta encapsulado
// la creas pasandole el tamaño
// se puede cambiar con el setSize
// y despues llamas a .solve pasandole como paramétro los enums 
// como está establecido en el código que indican cual método
// es usado para resolver el problema

// El problema en si está modelado como un vector donde el indice para acceder es el número
// de fila y el valor es el número de columna

// para verificar si 2 reinas se comen entre si se hace la siguiente formula 
// isAlive = !((oFil == fil) || (oCol == col) || (abs(oFil - fil) == abs(oCol - col)));


// cuando se resuelve de manera normal 
// se itera sobre todos los valores posibles para las columnas y se agregan al arreglo.
// (0, 0) (0,1) ... (0, n-1) son generados 
// se verifica para cada uno de esos pares si alguna reina ya colocada está amenazando esa casilla
// si la casilla está amenazada se descarta esa posición y se busca otra 
// sino se coloca dentro de la solucion parcial
// y se llama recursivamente para analizar la siguiente fila

// Esta verificacion sobre la casilla asegura que siempre el tablero está en un estado consistente
// donde ninguna reina mata a ninguna otra reina

// el caso base o resolucion del problema viene cuando todas las reinas están colocadas


// para el modo random, se toma solo p porciento de las soluciones posibles.
// se procede igual que en el caso normal pero con la variacion de que las columnas posibles 
// se shufflean por cada vez que se llama recursivamente la funcion y que solo queremos 
// n * p de las soluciones ( si n = 10, p = 0.3f, entonces 3)


// Comparación 

// Corridas

// auto testCases = { 4,5,6,10,20,21,22,23,24,25};
// En 30 pruebas el promedio de tiempo fue
// Random tomó 4.63673e+07 milisegundos // 100%
// Normal tomó 115832 milisegundos

// auto testCases = { 20,21,22,23,24,25,26,27,28,29,30,31,32};
// En 3 pruebas el promedio de tiempo fue
// Random tomó -8.98212e+08 milisegundos // hizo overflow a pesar de que el algoritmo es time1/n + time2/n en vez de (time1 + time2)/n
// Normal tomó 1.85497e+06 milisegundos //100%

// veamos esta corrida 
// For n=29
// Normal consigue 1 y tarda 8238 milisegundos
// Random consigue 1 y tarda 1 milisegundos
// For n=30
// Normal consigue 1 y tarda 311813 milisegundos
// Random consigue 1 y tarda 31 milisegundos
// For n=31
// Normal consigue 1 y tarda 79632 milisegundos
// Random consigue 1 y tarda 7 milisegundos


// pero también tenemos que 
// For n=20
// Normal consigue 1 y tarda 530 milisegundos
// Random consigue 0 y tarda 4292 milisegundos // 30%
// For n=22
// Normal consigue 1 y tarda 5505 milisegundos
// Random consigue 0 y tarda 9677 milisegundos // 30%

// en la primera corrida mostrada tenemos que el random es excelente
// en la segunda tenemos que no consigue solución y que tarda mucho más que el normal

// por lo que tenemos una disyuntiva.

// veamos esta corrida detallada para ver mejor ciertos aspectos

// auto testCases = { 20,21,22,23,24,25,26,27,28,29,30,31,32};
// En 3 pruebas
// Random tomó -8.56497e+08 milisegundos y encontró 36
// Normal tomó 1.86118e+06 milisegundos y encontró 39

// detallandola tenemos que perdemos 3/39 soluciones

// por lo que tenemos que el random puede no encontrar una solución y tardarse más que el normal
// así como puede encontrarlo en las primeras corridas

// es evidente que el random puede causar variaciones en la velocidad alarmante

// esto se debe a que. cómo el backtracking es un algoritmo de fuerza
// bruta va a evaluar todo el espacio de posibles soluciones.

// planteemos el problema encontrar un valor dentro de
// un arreglo de N elementos y accedemos a ellos de manera lineal.
// tenemos que ver N elementos en el peor caso.

// ahora digamos que hacemos la busqueda de manera aleatoria
// osea que accedemos a los elementos de manera aleatoria
// tenemos el chance de conseguir el elemento que estamos buscando en
// el primer intento, o en el segundo, o en el .....
// se apuesta a la suerte para tratar de conseguir un resultado más rápido
// y en casos dónde los espacios de solución son tan grandes tiene sentido 
// tratar de usarlos para evaluar su rendimiento
// como en este problema de N reinas