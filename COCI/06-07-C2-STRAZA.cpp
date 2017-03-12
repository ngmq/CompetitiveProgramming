//// ngmq
//// COCI #2, 2006/2007, task STRAZA
//// AC on http://wcipeg.com/problem/coci062p6
//// Execution Results
//// Test case #1: AC [0.003s, 2892K] (10/10)
//// Test case #2: AC [0.003s, 2892K] (10/10)
//// Test case #3: AC [0.003s, 2892K] (10/10)
//// Test case #4: AC [0.003s, 2892K] (10/10)
//// Test case #5: AC [0.003s, 2892K] (10/10)
//// Test case #6: AC [0.003s, 2892K] (10/10)
//// Test case #7: AC [0.000s, 2892K] (10/10)
//// Test case #8: AC [0.003s, 2892K] (10/10)
//// Test case #9: AC [0.003s, 2892K] (10/10)
//// Test case #10: AC [0.003s, 2892K] (10/10)
////
//// Final score: 100/100
//// The tricky part is the normalize of Line equation: usally the case a = 0 and b < 0 is overlooked
//// That leads to the situation when Line(0, 1, -20) and Line(0, -1, 20) are seen as two different lines => incorrect

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <cstdlib>
// #include <climits>
// #include <functional>
// #include <ctime>
#include <cmath>
#include <bitset>
// #include <utility>
#include <complex>
#include<fstream>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define inf (1e9 + 1e9)
#define linf 1e18
#define BASE 1000000
#define EPS 1e-10
#define PI acos(-1)
#define pii pair<int,int>
#define vi vector<int>
#define fi first
#define se second
#define ALL(x) (x).begin(), (x).end()
#define ms(x,val) memset(x, val, sizeof(x))
#define pb(x) push_back(x)
#define make_unique(x) sort(ALL(x)) ; x.erase( unique(ALL(x)), x.end()) ;
#define dbg(x) do { cout << #x << " = " << x << endl; } while(0)
#define mp(x, y) make_pair(x, y)

/*** IMPLEMENTATION ***/
bool exitInput = false;
int ntest = 1, itest = 1 ;

const int dx[4] =
{
    1, 0, -1, 0
};
const int dy[4] =
{
    0, 1, 0, -1
};
// const int dx[8] = {-2, -1, -1, +0, +0, +1, +1, +2};
// const int dy[8] = {+0, -1, +1, -2, +2, -1, +1, +0};

/** Knight Move **/
// const int dx[8] = {+1, +2, +2, +1, -1, -2, -2, -1};
// const int dy[8] = {+2, +1, -1, -2, -2, -1, +1, +2};

const char * directions[4] =
{
    "NE", "SE", "Sw", "Nw"
};

const ll Mod = 1000000007LL;
const int maxn = 300 + 5;
const int maxv = 5000 + 5;
const int maxe = 1000011 + 5;

struct Point
{
    int x, y;
    Point()
    {

    }
    Point(int _x, int _y) : x(_x), y(_y)
    {

    }
    bool operator <(const Point& other) const
    {
        if(x != other.x)
            return x < other.x;
        return y < other.y;
    }
    bool operator !=(const Point& other) const
    {
        if(x != other.x || y != other.y)
            return true;
        return false;
    }
    void display()
    {
        printf("************");
        printf("(x, y) = (%d, %d)\n", x, y);
    }
};

struct DPoint
{
    double x, y;
    DPoint()
    {

    }
    DPoint(Point p)
    {
        x = p.x;
        y = p.y;
    }
    DPoint(int _x, int _y) : x(_x), y(_y)
    {

    }
    DPoint(double _x, double _y): x(_x), y(_y)
    {

    }
    void display()
    {
        printf("************");
        printf("(x, y) = (%.6lf, %.6lf)\n", x, y);
    }
};

bool isInOrder(const DPoint& p1, const DPoint& p2, const DPoint &p3)
{
    double k;
    if(p1.x < p3.x)
    {
        k = (0.0 + p2.x - p1.x) / (0.0 + p3.x - p1.x);
    }
    else
    {
        k = (0.0 + p2.y - p1.y) / (0.0 + p3.y - p1.y);
    }
    if( abs(k) < EPS || abs(k - 1) < EPS || (k > 0 && k < 1) )
    {
        return true;
    }
    return false;
}

struct Line{
    int a, b, c;
    Line()
    {

    }
    Line(int _a, int _b, int _c)
    {
        a = _a;
        b = _b;
        c = _c;
        normalize();
    }
    Line(Point p1, Point p2)
    {
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        // a * x + b * y + c = 0
        // (p1.y - p2.y) * x + (p2.x - p1.x) * y + c = 0
        // x = p1.x, y = p1.y => (p1.y - p2.y) * p1.x + (p2.x - p1.x) * p1.y + c = 0
        // -p2.y * p1.x + p2.x * p1.y + c = 0
        // c = p1.x * p2.y - p1.y * p2.x
        c = p1.x * p2.y - p1.y * p2.x;
        normalize();
    }
    void normalize()
    {
        if(a < 0)
        {
            a = -a;
            b = -b;
            c = -c;
        }
        else if(a == 0 && b < 0)
        {
            b = -b;
            c = -c;
        }
        int k = __gcd(__gcd(a, b), c);
        if(k < 0)
            k = -k;
        a /= k;
        b /= k;
        c /= k;
    }
    bool operator ==(const Line& other) const
    {
        if(a != other.a)
            return false;
        if(b != other.b)
            return false;
        return c == other.c;
    }
    bool isParallel(const Line& other) const
    {
        return a * other.b == b * other.a;
    }
    int positionPoint(const Point& p) const
    {
        int k = a * p.x + b * p.y + c;
        if(k == 0)
            return 0;
        if(k < 0)
            return -1;
        return 1;
    }
    DPoint intersect(const Line& other) const
    {
        double x = -(0.0 + c * other.b - other.c * b) / (0.0 + a * other.b - other.a * b);
        double y = -(0.0 + c * other.a - other.c * a) / (0.0 + b * other.a - other.b * a);
        return DPoint(x, y);
    }
    void display() const
    {
        printf("-----------------");
        printf("(a, b, c) = %d, %d, %d\n", a, b, c);
    }
};

struct Segment
{
    Point p1, p2;
    Line L;
    Segment()
    {

    }
    Segment(Point _p1, Point _p2)
    {
        p1 = _p1;
        p2 = _p2;
        L = Line(p1, p2);
    }
    Segment(int _x, int _y, int __x, int __y)
    {
        p1 = Point(_x, _y);
        p2 = Point(__x, __y);
        L = Line(p1, p2);
        normalize();
    }
    void normalize()
    {
        if(p2 < p1)
            swap(p1, p2);
    }
    bool operator <(const Segment& other) const
    {
        if(p1 != other.p1)
            return p1 < other.p1;
        return p2 < other.p2;
    }
    bool isParallel(const Segment& other) const
    {
        return L.isParallel(other.L);
    }
    bool isConverge(const Segment& s1, const Segment& s2) const
    {
        if( isParallel(s1) || isParallel(s2) || s1.isParallel(s2) )
            return false;
        DPoint p = s1.L.intersect(s2.L);
        double x = p.x;
        double y = p.y;
        double k = L.a * x + L.b * y + L.c;

        return abs(k) < EPS;
    }
    bool isTriangle(const Segment& s1, const Segment& s2) const
    {
        if( isParallel(s1) || isParallel(s2) || s1.isParallel(s2) || isConverge(s1, s2) )
            return false;

        DPoint p = s1.L.intersect(s2.L);
//        s1.L.display();
//        s2.L.display();
//        p.display();
        if ( !isInOrder(s1.p1, p, s1.p2) || !isInOrder(s2.p1, p, s2.p2) )
            return false;

        p = L.intersect(s1.L);

        if ( !isInOrder(p1, p, p2) || !isInOrder(s1.p1, p, s1.p2) )
            return false;

        p = L.intersect(s2.L);

        if ( !isInOrder(p1, p, p2) || !isInOrder(s2.p1, p, s2.p2) )
            return false;

        return true;
    }
    bool isSameLine(const Segment& other)
    {
        return L == other.L;
    }
    bool merge(const Segment& other)
    {
        if( isSameLine(other) )
        {
            if( isInOrder(p1, other.p1, p2) )
            {
                if(p2 < other.p2)
                    p2 = other.p2;
                return true;
            }
        }
        return false;
    }
};

int n;
Segment a[22];
bool isActive[22];

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int i, j, k;

    //scanf("%d", &ntest);

    for(itest = 1; itest <= ntest; ++itest)
    {
        scanf("%d", &n);
        int tx, ty, gx, gy;
        for(i = 0; i < n; ++i)
        {
            scanf("%d %d %d %d", &tx, &ty, &gx, &gy);
            a[i] = Segment(tx, ty, gx, gy);
            isActive[i] = true;
        }
        sort(a, a + n);
//        for(i = 0; i < n; ++i)
//        {
//            printf("i = %d, Segment = \n", i);
//            a[i].p1.display();
//            a[i].p2.display();
//            a[i].L.display();
//        }
        for(i = 0; i < n; ++i)
        {
            for(j = i + 1; j < n; ++j)
            {
                if( isActive[j] )
                {
                    if( a[i].merge(a[j]) )
                    {
                        //printf("%d merged to %d\n", j, i);
                        isActive[j] = false;
                    }
                }
            }
        }
//         for(i = 0; i < n; ++i)
//        {
//            if(isActive[i])
//            {
//                printf("i = %d, Segment = \n", i);
//            a[i].p1.display();
//            a[i].p2.display();
//            a[i].L.display();
//            }
//
//        }
//        a[0].p1.display();
//        a[0].p2.display();
//
//        bool test = a[0].isTriangle(a[1], a[2]);
//        printf("test = %d\n", test);

        int res = 0;
        for(i = 0; i < n; ++i)
        //i = 0;
        {
            if( isActive[i] )
            {
                for(j = i + 1; j < n; ++j)
                //j = 1;
                {
                    if( isActive[j] )
                    {
                        for(k = j + 1; k < n; ++k)
                        //k = 2;
                        {
                            if( isActive[k] )
                            {
//                                a[i].L.display();
//                                a[j].L.display();
//                                a[k].L.display();
                                if( a[i].isTriangle(a[j], a[k]) )
                                {
                                    //printf("Triangle: (%d, %d, %d)\n", i, j, k);
                                    ++res;
                                }
                            }
                        }
                    }
                }
            }
        }
        printf("%d\n", res);
    }

    return 0;
}

