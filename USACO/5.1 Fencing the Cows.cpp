// main.cpp
/*
ID: tiendao1
LANG: C++
TASK: fc
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
//#include <deque>
//#include <queue>
//#include <stack>
#include <cstdlib>
// #include <climits>
// #include <functional>
// #include <ctime>
#include <cmath>
//#include <bitset>
// #include <utility>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define inf 1e9 + 1
#define linf 1e18
#define BASE 1000000
#define EPS 1e-10
#define PI acos(-1)
#define pii pair<int,int>
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
    0, 0, -1, 1
};
const int dy[4] =
{
    1, -1, 0, 0
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
const int maxn = 100000 + 5;
const int maxv = 100000 + 5;
const int maxe = 100000 + 5;
//const int root = 1;

const int root = 1;

struct Point
{
    double x, y;
    Point()
    {
        x = y = 0;
    }
    Point(double _x, double _y)
    {
        x = _x;
        y = _y;
    }
    double size() const
    {
        return sqrt(x * x + y * y);
    }
};
typedef Point Vect;
int n;
Point p[maxn];

#define CCW 1
#define CW -1
#define CL 0

double dist(const Vect& a, const Vect& b)
{
    Vect c(a.x - b.x, a.y - b.y);
    return c.size();
}
double dotProduct(const Vect& a, const Vect& b)
{
    return a.x * b.x + a.y * b.y;
}
double crossProduct(const Vect& a, const Vect& b)
{
    return a.x * b.y - a.y * b.x;
}
double cosangle(const Vect& a, const Vect& b)
{
    if(a.size() == 0 || b.size() == 0)
        return 0;
    return dotProduct(a,b) / (a.size() * b.size());
}

int ccw(const Point& p0, const Point& p1, const Point& p2)
{
    Vect v01(p1.x - p0.x, p1.y - p0.y);
    Vect v12(p2.x - p1.x, p2.y - p1.y);

    double val = crossProduct(v01, v12);
    if(val < 0) return CW;
    if(val > EPS) return CCW;
    return CL;
}

Point hull[maxn];
int m;
int idx[maxn];
Point p0;

//bool cmp(int i, int j)
//{
//    Vect ux(1, 0);
//    Vect v0i = Vect(p[i].x - p0.x, p[i].y - p0.y);
//    Vect v0j = Vect(p[j].x - p0.x, p[j].y - p0.y);
//    return cosangle(v0i, ux) > cosangle(v0j, ux);
//}

bool cmp(const Point& a, const Point& b)
{
    Vect ux(1, 0);
    Vect v0a = Vect(a.x - p0.x, a.y - p0.y);
    Vect v0b = Vect(b.x - p0.x, b.y - p0.y);
    return cosangle(v0a, ux) > cosangle(v0b, ux);
}
void grahamScan()
{
    int i, j, k, c;
    // sorting

    sort(p + 1, p + n, cmp);


//    puts("=============== AFTER SORT ==============");
//    for(i = 0; i < n; ++i)
//    {
//        printf("p[%d] = (%.2lf, %.2lf) \n", i, p[i].x, p[i].y);
//    }
//    puts("=============== END ==========");

    // scanning
    hull[0] = p[0];
    hull[1] = p[1];
    m = 2;
    for(k = 2; k < n; ++k)
    {
        for(;;)
        {
            c = ccw(hull[m-2], hull[m-1], p[k]);
//        printf("k = %d, hull[m-2] = (%.2lf, %.2lf), hull[m-1] = (%.2lf, %.2lf), p[k] = (%.2lf, %.2lf), c = %d\n",
//               k, hull[m-2].x, hull[m-2].y, hull[m-1].x, hull[m-1].y, p[k].x, p[k].y,
//               c
//               );
            if(c == CW || c == CL) // cw or collinear
            {
                // delete middle point
                --m;
            }
            else
            {
                hull[m] = p[k];
                ++m;
                break;
            }
        }
    }
}

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //time_t t1, t2; t1 = clock();
#else
    freopen("fc.in","r",stdin) ; freopen("fc.out", "w", stdout);
#endif
    int i, j, k;

    //scanf("%d", &ntest);
    for(itest = 1; itest <= ntest; ++itest)
    {
        p0.x = 1000001;
        p0.y = 1000001;

        int min_idx = 0;

        scanf("%d", &n);
        for(i = 0; i < n; ++i)
        {
            scanf("%lf %lf", &p[i].x, &p[i].y);

            if( (p[i].y < p[min_idx].y) || (p[i].y == p[min_idx].y && p[i].x < p[min_idx].x) )
            {
                min_idx = i;
            }
        }
        swap(p[0], p[min_idx]); // p[0] is guaranteed to be in the convex hull
        p0 = p[0];

        //printf("min_idx = %d, p0 = (%.2lf, %.2lf) \n", min_idx, p0.x, p0.y);

        grahamScan();

        double res = 0;
        for(i = 0; i < m; ++i)
        {
            res += dist(hull[i], hull[(i+1)%m]);

           //printf("hull[%d] = (%.2lf, %.2lf), res = %.2lf \n", i, hull[i].x, hull[i].y, res);
        }
        printf("%.2lf\n", res);
    }

    return 0;
}
