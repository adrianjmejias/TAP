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
#include <numeric>
#include <deque>
#include <array>
#include <set>
#include <iostream>
#include <unordered_set>
#include <math.h>
#include <cstdlib>
#include <ctime>

template <typename TT>
inline std::vector<TT> GenerateRandom(size_t size, std::function<TT()> generator)
{
    std::vector<TT> randVec;
    for (int ii = 0; ii < size; ii++)
    {
        randVec.push_back(generator());
    }
    return randVec;
}


template <typename durationType>
inline durationType measureTime(std::function<void()> f)
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

inline Vec2 Normalize(Vec2 v)
{
    float mag = sqrt(v.x*v.x + v.y*v.y);
    v.x /= mag;
    v.y /=mag;
    return v;
}

inline float Dot(const Vec2 &a, const Vec2 &b)
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

inline void FilterQueue(std::priority_queue<Vec2, std::vector<Vec2>, Vec2Comparator> &q)
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

    
    // std::cout << "minimun at "<< p << std::endl;
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
            // std::cout << "stack.pop_back--------------- " << stack[sz-1]<<std::endl;
            stack.pop_back();
        }
        // std::cout << "stack.push_back*********** " << point<<std::endl;
        stack.push_back(point);
    }


    for (auto &&i : stack)
    {
        // std::cout << "i "<<i<< std::endl;
    }
    return stack;
}
inline float sign (Vec2 p1, Vec2 p2, Vec2 p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

inline bool PointInTriangle (Vec2 pt, Vec2 v1, Vec2 v2, Vec2 v3)
{
    float d1, d2, d3;
    bool has_neg, has_pos;

    d1 = sign(pt, v1, v2);
    d2 = sign(pt, v2, v3);
    d3 = sign(pt, v3, v1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
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
    bool Eliminate();
    Triangle(int x, int y, int z)
    {
        SetVertices(x,y,z);
    }

    bool HasIndex(int idx) const 
    {  
        for (size_t ii = 0; ii < 3; ii++)
        {
            if(this->vertexIndices[ii] == idx)
            {
                return true;
            }
        }
        return false;
    }

    bool operator==(const Triangle &t) const 
    {  
        for (size_t ii = 0; ii < 3; ii++)
        {
            if(this->vertexIndices[ii] != t.vertexIndices[ii])
            {
                return false;
            }
        }
        return true;
    }

    // with this we can assume a triangle has it's vertices ordered
    // this is usefull to check combination of triangles
    void SetVertices(int x, int y, int z)
    {
        vertexIndices[0] = x;
        vertexIndices[1] = y;
        vertexIndices[2] = z;

        std::make_heap(vertexIndices.begin(), vertexIndices.end());
    }


    int operator[](int a) const 
    {
        return vertexIndices[a];
    }


    protected:
    std::array<int, 3> vertexIndices;
};
std::ostream& operator<<(std::ostream& os, const Triangle& t)
{
    os << "(" << t[0] << ','<< t[1]<<"," << t[2] << ")";
    return os;
}

bool Triangle::Eliminate()
    {
        if(IsActive())
        {
            // std::cout << "killing triangle "<< *this<< std::endl;
            isActive = false;
            return true;
        }
        return false;
    }


struct TrianglePoint : public Vec2, Eliminable{
    std::vector<int> trianglesAssociated;

    TrianglePoint(const Vec2 &p)
    {
        x = p.x;
        y = p.y;
    }


    inline void Eliminate(std::vector<Triangle>& triangles)
    {
        if (IsActive())
        {           
            isActive = false;
            // std::cout << "Eliminating point "<< *this<< std::endl;

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

inline void comb(int N, int K, std::vector< Triangle > &triangles)
{
    std::string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's

    // print integers and permute bitmask
    do {
        std::vector<int> acum;
        for (int i = 0; i < N; ++i) // [0..N-1] integers
        {
            if (bitmask[i]) acum.push_back(i);
        }

        triangles.emplace_back(acum[0],acum[1], acum[2]);
        // std::cout << std::endl;
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
}
    // std::unordered_set<Triangle> trianglesBuilt;
    // std::vector<TrianglePoint> points;


    inline bool EliminateInnerPoints(const Triangle& t, std::vector<Triangle> &triangles, std::vector<TrianglePoint> &points)
    {
        // std::cout << "Checking Triangle "<< t<<" -> "<<points[t[0]]<<points[t[1]]<<points[t[2]]<< std::endl;
        for (int ii = 0; ii< points.size(); ii++)
        {
            TrianglePoint &p = points[ii];
            if(p.IsActive())
            {
                if(!t.HasIndex(ii))
                {
                    if(PointInTriangle(p, points[t[0]], points[t[1]], points[t[2]]))
                    {
                        // std::cout << "Checking point inside "<< p<<" -> "<<points[t[0]]<<points[t[1]]<<points[t[2]]<< std::endl;


                        p.Eliminate(triangles);
                    }                
                }
            }
        }
        return false;
    }

    // Escriba un c ́odigo en c++ para calcular la c ́apsula convexa dados n puntos p0, p1, ...  pn-1, basado en el siguiente principio:
    // partiendo  del  conjunto  de  n  puntos,  tomar  tres  puntos  de  ellos  a  la  vez
    // eliminar  del  conjunto  todos  los  puntos  dentrode  ese  tri ́angulo.   
    // Repetir  este  procedimiento  hasta  que  no  haya  un  tri ́angulo  que  contenga  uno  o  m ́as  puntos  dentro  delmismo.  
    
    // generar triangulo
    // eliminar puntos dentro de el 
    // while 

    // Note que en cada paso el tama ̃no del conjunto podr ́ıa ser reducido, por lo que la cantidad de tri ́angulos remanentespodr ́ıa reducirse tambi ́en.  Haga la mejor implementaci ́on dentro de sus posibilidades con este enfoque.
    RetVal DummyAlgorithm(RetVal points)
    {
        RetVal convexHull;
        std::vector<TrianglePoint> activePoints;
        std::vector< Triangle > triangles;
        comb(points.size(), 3, triangles);


        for (auto &&ii : points)
        {
            TrianglePoint t = TrianglePoint(ii);
            activePoints.push_back(t);
        }

        for(int ii =0; ii < triangles.size(); ii++)
        {
            const Triangle &t = triangles[ii];
            activePoints[t[0]].Add(ii);
            activePoints[t[1]].Add(ii);
            activePoints[t[2]].Add(ii);
        }
        
        // std::cout << " before"<<std::endl;
        // for (auto &&jj : triangles)
        // {
        //     std::cout << jj << std::endl;
        // }

        for (auto ii = triangles.rbegin(); ii != triangles.rend(); ii++)
        {
            Triangle &t = *ii;
            if(t.IsActive())
            {
                if(EliminateInnerPoints(t, triangles, activePoints))
                {
                    // ii = triangles.rend()-1;
                }
            }
        }
        

        // pa transformar los triangulos pa hulk
        std::set<int> convertion;

        // std::cout << " after"<<std::endl;
        for (auto &&jj : triangles)
        {
            if(jj.IsActive())
            {
                // std::cout << jj << std::endl;
                convertion.insert(jj[0]);
                convertion.insert(jj[1]);
                convertion.insert(jj[2]);

                // std::cout << "with points " <<points[jj[0]]<<points[jj[1]]<<points[jj[2]]<<std::endl;
            }
        }

        for (auto &&i : convertion)
        {
            convexHull.push_back(points[i]);
        }
        

        // for (auto &&ii : convexHull)
        // {

        //     // std::cout <<"   "<< ii <<std::endl;

            
        // }
        


        
        return convexHull;
    }
    


int random_sign()
{
    return (rand()%100 <50)? -1 : 1;
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

    

    std::vector<int> a;
    

    // std::cout << PointInTriangle( Vec2(-1.5,1), Vec2(-5,0), Vec2(0,5), Vec2(0,0));
    // std::cout << PointInTriangle( Vec2(-1.5,-1), Vec2(-5,0), Vec2(0,5), Vec2(0,0));
    // std::cout << PointInTriangle( Vec2(-5,-1), Vec2(-5,0), Vec2(0,5), Vec2(0,0));
    // std::cout << PointInTriangle( Vec2(1.5,1), Vec2(-5,0), Vec2(0,5), Vec2(0,0));
    // std::cout<< PointInTriangle(Vec2(3,0),Vec2(0,5),Vec2(0,-5),Vec2(-5,0))<<std::endl;;

    srand((int)time(0));
    const int nTests = 30;
    std::vector<int> nCases{100, 200};
    std::vector<unsigned long long> timesDummy{0,0,0,0,0};
    std::vector<unsigned long long> timesGraham{0,0,0,0,0};

    for (size_t jj = 0; jj < nCases.size(); jj++)
    {
        auto geo = GenerateRandom<Vec2>(nCases[jj], []() -> Vec2 {
            float l  = random_sign() *  rand() % 100;
            float r  = random_sign() *  rand() % 100;
            return Vec2(l, r);
        });

        for (size_t ii = 0; ii < nTests; ii++)
        {
            timesDummy[jj] += measureTime<unsigned long long>([&](){
                DummyAlgorithm(geo);
            });

            timesGraham[jj] += measureTime<unsigned long long>([&](){
                GrahamAlgorithm(geo);
            });
            std::cout<< "Case "<< nCases[jj] <<": "<< ii/float(nTests-1)<< std::endl; 
        }
    }
    
    for (size_t jj = 0; jj < nCases.size(); jj++)
    {
        std::cout<< "promedio normal "<<nCases[jj]<<": "<< std::accumulate(timesDummy.begin(), timesDummy.end(), 0.0f)/float(nTests) <<std::endl;
        std::cout<< "promedio Graham "<<nCases[jj]<<": "<< std::accumulate(timesDummy.begin(), timesDummy.end(), 0.0f)/float(nTests) <<std::endl;
    }




    // std::cout<<"ccw "<<ccw(Vec2(0,-1), Vec2(1,0),Vec2(0,1))<<std::endl;
    // std::cout<<"cw "<<ccw(Vec2(0,1),Vec2(1,0), Vec2(0,-1))<<std::endl;
    // std::cout<<"co "<<ccw(Vec2(0,1),Vec2(0,0), Vec2(0,-1))<<std::endl;
    return 0;
}
