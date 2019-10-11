// 5. Escriba un código en c++ para calcular la cápsula convexa dados n puntos p0, p1, ... pn-1, basado en el siguiente
// principio: partiendo del conjunto de n puntos, tomar tres puntos de ellos a la vez, y eliminar del conjunto todos los
// puntos dentro de ese triángulo. Repetir este procedimiento hasta que no haya un triángulo que contenga uno o más
// puntos dentro del mismo. Note que en cada paso el tamaño del conjunto podría ser reducido, por lo que la cantidad
// de triángulos remanentes podría reducirse también. Haga la mejor implementación dentro de sus posibilidades con

// este enfoque. Luego implemente el algoritmo de Graham, y haga una comparación en tiempo variando n con al menos los siguientes valores {100, 200, 500, 1000, 2000}. Para cada uno de los valores de n, haga 30 corridas, generando n puntos aleatorios dentro de un cuadrado de 100x100, para tener un mejor estimado del tiempo promedio para ese valor de n. Favor hacer una tabla con los resultados obtenidos, graficar los resultados y discutir. (9 puntos).
#include <vector>
#include <chrono>
#include <functional>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <array>
#include <iostream>
#include <math.h>

template <typename TT>
std::vector<TT> GenerateRandom(size_t size, std::function<TT()> generator)
{
    std::vector<TT> randVec;
    for (int ii = 0; ii < size; ii++)
    {
        randVec.push_back(generator());
    }
    return randVec;
}


template <typename durationType>
durationType measureTime(std::function<void()> f)
{
    auto start = std::chrono::system_clock::now();

    f();

    auto end = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}


template <typename DataType>
struct _Vec2
{
    DataType x, y;
    DataType &operator[] (int a)
    {
        return (&x) + sizeof(DataType) * a; 
    }
    void Normalize()
    {
        
    }
};

struct Vec2 : public _Vec2<float>{

    float angle;
    Vec2(float _x = 0, float _y = 0)
    {
        x = _x;
        y = _y;
    }

    bool operator<(const Vec2 &p2)
    {
        if(y < p2.y)
        {
            return true;
        }
        else if(y == p2.y)
        {
            if(x < p2.x)
            {
                return true;
            }
        }

        return false;
    }
    Vec2 operator-(const Vec2 &p2)
    {
        Vec2 res;
        res.x = x- p2.x;
        res.y = y - p2.y;
        return res;
    }
};
Vec2 angleVector;
std::ostream& operator<<(std::ostream& os, const Vec2& dt)
{
    os << "(" << dt.x << ',' << dt.y << ")";
    return os;
}



float Distance(const Vec2 &a, const Vec2 &b)
{
    float l = a.x - b.x;
    float r = a.y - b.y;

    l = l*l;
    r = r*r;

    return sqrt( l + r );
}

Vec2 Normalize(Vec2 v)
{
    float mag = sqrt(v.x*v.x + v.y*v.y);
    v.x /= mag;
    v.y /=mag;
    return v;
}

float Dot(const Vec2 &a, const Vec2 &b)
{
    return (a.x * b.x) + (a.y * b.y);
}

using RetVal = std::vector<Vec2>;
Vec2 *pp;

struct Vec2Comparator {
    bool operator() (const Vec2& a, const Vec2& b) const{
        return a.angle < b.angle ;
    }
};

inline bool fequal(float a, float b)
{
    return a == b;   
}

// http://www.dcs.gla.ac.uk/~pat/52233/slides/Geometry1x1.pdf
int ccw(Vec2 p1, Vec2 p2, Vec2 p3) 
{ 
    float d12 = (p2.y - p1.y)/(p2.x - p1.x);
    float d23 = (p3.y - p2.y)/(p3.x - p2.x);
    std::cout<<"ccw  "<< p1<< " "<<p2<< " "<<p3 << std::endl;
    std::cout <<"d12 "<<d12 <<"  d23 "<<d23<<std::endl;
    
    if(d12 == d23) return 0;

    if(d12 > d23)
    {
    //ccw 
        return 1;
    }
    else
    {
    //cw 
        return -1;
    }
    

} 
// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(Vec2 p, Vec2 q, Vec2 r) 
{ 
    int val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y); 
  
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 

void FilterQueue(std::priority_queue<Vec2, std::vector<Vec2>, Vec2Comparator> &q)
{
    std::vector<Vec2> aux;
    while(!q.empty())
    {
        aux.push_back(q.top());
        q.pop();
    }

    // std::cout << "FilterQueue BEGIN" << std::endl;
    // for(int ii = aux.size()-1; ii >= 0; ii--)
    // {
    //     std::cout<< aux[ii] <<"   angle   "<< aux[ii].angle<< std::endl;
    // }



    // asumimos que está ordenado por angulo
    for(int ii = aux.size()-1, next; ii >= 0; ii--)
    {
        float dist = Distance(aux[ii], (*pp));
        int farthest = ii;


        // vemos el más lejos que tenga el mismo angulo
        while( ( next = ii-1) >=0 && fequal(aux[ii].angle, aux[next].angle))
        {
            // std::cout<< aux[ii] <<"   angle   "<< aux[ii].angle<< std::endl;

            float nDist = Distance(aux[next], *(pp));

            if(nDist > dist)
            {
                dist = nDist;
                farthest = next;
            }
            ii--;
        }

        // std::cout<<"farthest "<< aux[ii] <<"   angle   "<< aux[ii].angle<< std::endl;

        q.push(aux[farthest]);
    }
}


// https://www.youtube.com/watch?v=ZFxFKABnXN0
RetVal GrahamAlgorithm(RetVal points)
{


    // este es el de wikipedia
    // let points be the list of points
    // let stack = empty_stack()

    // find the lowest y-coordinate and leftmost point, called P0
    // sort points by polar angle with P0, if several points have the same polar angle then only keep the farthest

    // for point in points:
    //     # pop the last point from the stack if we turn clockwise to reach this point
    //     while count stack > 1 and ccw(next_to_top(stack), top(stack), point) < 0:
    //         pop stack
    //     push point to stack
    // end


    //https://iq.opengenus.org/graham-scan-convex-hull/



    RetVal convexHull;
    std::vector<Vec2> stack;
    std::priority_queue<Vec2, std::vector<Vec2>, Vec2Comparator> q;
    int p = 0;

    // find the lowest y-coordinate and leftmost point, called P0
    for(int ii= 0; ii < points.size() ; ii++)
    {
        if(points[ii] < points[p]) // overloaded
        {
            p = ii;
        }
    };

    
    std::cout << "minimun at "<< p << std::endl;
    std::swap(points[0], points[p]); // pa que sea menos ladilla hacer todo
    p = 0;
    pp = &points[p];
    pp->angle = 1;

    // float yDisp = 0;//pp->y;
    // for (size_t ii = 0; ii < points.size(); ii++)
    // {
    //     points[ii].y-= yDisp;
    // }
    
    angleVector.x = 1;
    angleVector.y = 0;

    // sort points by polar angle with P0, if several points have the same polar angle then only keep the farthest
    for(int ii= 1; ii< points.size(); ii++)
    {
        Vec2 dir = Normalize(points[ii] -(*pp));
        // std::cout << "Point "<< points[ii]<< "   dir "<< dir<<std::endl;
        points[ii].angle = Dot( angleVector,  dir);
    }


    for(int ii=1; ii< points.size(); ii++)
    {
        q.push(points[ii]);
    }

    // filter points with the same angle, keeping the farthest
    FilterQueue(q);

    q.push(points[0]);


    if(q.size() < 3)
    {
        std::cout << " hull not possible "<< std::endl;
        return {};
    }



    // for point in points:
    //     # pop the last point from the stack if we turn clockwise to reach this point
    //     while count stack > 1 and ccw(next_to_top(stack), top(stack), point) < 0:
    //         pop stack
    //     push point to stack
    // end
    stack.push_back(q.top()); q.pop();
    stack.push_back(q.top()); q.pop();
    stack.push_back(q.top()); q.pop();

    while(!q.empty())
    {
        Vec2 point = q.top();
        q.pop();

        // pop the last point from the stack if we turn clockwise to reach this point
        int sz;

        // The code below uses a function ccw: ccw > 0 if three points make a counter-clockwise turn, 
        // clockwise if ccw < 0, and collinear if ccw = 0. (In real applications, 
        // if the coordinates are arbitrary real numbers, the function requires exact comparison of floating-point numbers,
        // and one has to beware of numeric singularities for "nearly" collinear points.)
        while((sz = stack.size()) > 1 && orientation(stack[sz-2], stack[sz-1], point) == 1)
        {
            std::cout << "stack.pop_back--------------- " << stack[sz-1]<<std::endl;
            stack.pop_back();
        }
        std::cout << "stack.push_back*********** " << point<<std::endl;
        stack.push_back(point);
    }


    for (auto &&i : stack)
    {
        std::cout << "i "<<i<< std::endl;
    }
    return stack;
}

class Eliminable
{
    protected:

    public:
    bool isActive = true;
    bool IsActive()
    {
        return isActive;
    }
};

struct Triangle : public Eliminable
{
    std::array<int, 3> vertexIndices;
    void Eliminate()
    {
        isActive = false;
    }
};

struct TrianglePoint : public Vec2, Eliminable{
    std::vector<int> trianglesAssociated;

    void Eliminate(std::vector<Triangle>& triangles)
    {
        if (IsActive())
        {
            for (int tIndex : trianglesAssociated)
            {
                triangles[tIndex].Eliminate();
            }
        }
        
    }

    void Add(int tIndex)
    {
        trianglesAssociated.push_back(tIndex);
    }
};



RetVal DummyAlgorithm(RetVal points)
{
    RetVal convexHull;
    std::vector<TrianglePoint> activePoints;
    std::vector< Triangle > triangles;


    return convexHull;
}


int main()
{
    const RetVal geometry{
        // Vec2(1,1),
        // Vec2(2,1),
        // Vec2(3,1),
        // Vec2(0,0),
        // Vec2(2.0,0.85),
        // Vec2(-3,1),

        // Vec2(0,0),
        // Vec2(0.8f,0.7f),
        // Vec2(1,0),
        // Vec2(1,1),
        // // Vec2(0.4f,0.5f),
        // Vec2(0,1),
        // Vec2(0.5f,0.5f),


        // Vec2(-1,0),
        // Vec2(1,0),
        // Vec2(0,1),
        // Vec2(0,-1),
        // Vec2(0,0)




        // Vec2(-2.5,0.8660254037844386),
        // Vec2(-2.2,1.4696938456699067),
        // Vec2(-1.9000000000000004,1.8411952639521965),
        // Vec2(-1.6000000000000005,2.107130750570547),
        // Vec2(-1.3000000000000007,2.304343724360582),
        // Vec2(-1.0000000000000009,2.449489742783178),
        // Vec2(-0.7000000000000011,2.5514701644346145),
        // Vec2(-0.40000000000000124,2.6153393661244038),
        // Vec2(-0.10000000000000142,2.643860813280457),
        // Vec2(0.1999999999999984,2.638181191654584),
        // Vec2(0.4999999999999982,2.5980762113533165),
        // Vec2(0.799999999999998,2.521904042583699),
        // Vec2(1.0999999999999979,2.4062418831031938),
        // Vec2(1.3999999999999977,2.244994432064366),
        // Vec2(1.6999999999999975,2.0273134932713313),
        // Vec2(1.9999999999999973,1.7320508075688803),
        // Vec2(2.299999999999997,1.3076696830622072),
        // Vec2(2.599999999999997,0.48989794855665125),
        // Vec2(-2.5, -0.8660254037844386),
        // Vec2(-2.2, -1.4696938456699067),
        // Vec2(-1.9000000000000004, -1.8411952639521965),
        // Vec2(-1.6000000000000005, -2.107130750570547),
        // Vec2(-1.3000000000000007, -2.304343724360582),
        // Vec2(-1.0000000000000009, -2.449489742783178),
        // Vec2(-0.7000000000000011, -2.5514701644346145),
        // Vec2(-0.40000000000000124, -2.6153393661244038),
        // Vec2(-0.10000000000000142, -2.643860813280457),
        // Vec2(0.1999999999999984, -2.638181191654584),
        // Vec2(0.4999999999999982, -2.5980762113533165),
        // Vec2(0.799999999999998, -2.521904042583699),
        // Vec2(1.0999999999999979, -2.4062418831031938),
        // Vec2(1.3999999999999977, -2.244994432064366),
        // Vec2(1.6999999999999975, -2.0273134932713313),
        // Vec2(1.9999999999999973, -1.7320508075688803),
        // Vec2(2.299999999999997, -1.3076696830622072),
        // Vec2(2.599999999999997, -0.48989794855665125),
        // Vec2(-1.5, 1.3228756555322954),
        // Vec2(-1.2, 1.6),
        // Vec2(-0.8999999999999999, 1.7860571099491753),
        // Vec2(-0.5999999999999999, 1.9078784028338913),
        // Vec2(-0.2999999999999998, 1.977371993328519),
        // Vec2(2.220446049250313e-16, 2.0),
        // Vec2(0.30000000000000027, 1.9773719933285188),
        // Vec2(0.6000000000000005, 1.907878402833891),
        // Vec2(0.9000000000000004, 1.786057109949175),
        // Vec2(1.2000000000000002, 1.5999999999999999),
        // Vec2(1.5000000000000004, 1.3228756555322947),
        // Vec2(-1.2, -1.6),
        // Vec2(-0.8999999999999999, -1.7860571099491753),
        // Vec2(-0.5999999999999999, -1.9078784028338913),
        // Vec2(-0.2999999999999998, -1.977371993328519),
        // Vec2(2.220446049250313e-16, -2.0),
        // Vec2(0.30000000000000027, -1.9773719933285188),
        // Vec2(0.6000000000000005, -1.907878402833891),
        // Vec2(0.9000000000000004, -1.786057109949175),
        // Vec2(1.2000000000000002, -1.5999999999999999),
        // Vec2(1.5000000000000004, -1.3228756555322947),



        Vec2(3,0),
        Vec2(-3,0),
        Vec2(0,-3),
        Vec2(0,3),

        Vec2(5,0),
        Vec2(-5,0),
        Vec2(0,-5),
        Vec2(0,5),
    };

    DummyAlgorithm(geometry);
    GrahamAlgorithm(geometry);

    // std::cout<<"ccw "<<ccw(Vec2(0,-1), Vec2(1,0),Vec2(0,1))<<std::endl;
    // std::cout<<"cw "<<ccw(Vec2(0,1),Vec2(1,0), Vec2(0,-1))<<std::endl;
    // std::cout<<"co "<<ccw(Vec2(0,1),Vec2(0,0), Vec2(0,-1))<<std::endl;
    return 0;
}

