//// ngmq
//// Google Kickstart (APAC) Round A, 2017, task C-Space Cubes
//// AC on https://codejam.withgoogle.com/codejam/contest/8284486
//// Main idea: 
//// First of all, binary search the result to get the length of boxes' edge first
//// Consider the two boxes and spheres on each 2D dimension Oxy, Oxz, Oyz,
//// the lowest point (low-bottom-left) of the first box need to be (lowest_x, some_y, some_z)
//// that some_y, some_z provide the first box either the highest or lowest y, z on Oxy, Oyz and Oxz
//// Hence, try different combination of miny, minz, maxy - d and maxz - d
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
const int maxn = 2000 + 5;
const int maxv = 5000 + 5;
const int maxe = 1000011 + 5;

struct Point
{
    int x, y, z;
    Point()
    {

    }
    Point(int _x, int _y, int _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
};
struct Sphere
{
    Point p;
    int R;
    int lx, ly, lz;
    int hx, hy, hz;
    Sphere()
    {

    }
    void calc()
    {
        lx = p.x - R;
        ly = p.y - R;
        lz = p.z - R;

        hx = p.x + R;
        hy = p.y + R;
        hz = p.z + R;
    }
    bool operator <(const Sphere& other) const
    {
        if(lx != other.lx)
            return lx < other.lx;
        if(ly != other.ly)
            return ly < other.ly;
        return lz < other.lz;
    }
};

int n, minx, miny, minz, maxx, maxy, maxz;
Sphere a[maxn];
bool covered[maxn];

bool isInside(Sphere s, Point b, int d)
{
    int lx = b.x, ly = b.y, lz = b.z;
    int hx = lx + d, hy = ly + d, hz = lz + d;

    if(lx <= s.lx && s.hx <= hx &&
       ly <= s.ly && s.hy <= hy &&
       lz <= s.lz && s.hz <= hz
       )
    {
        return true;
    }
    return false;
}

bool getDone(Point H, int d)
{
    int i, j, k, minx2, miny2, minz2;

    ms(covered, false);
    minx2 = miny2 = minz2 = 1e9;
    for(i = 0; i < n; ++i)
    {
        if( isInside(a[i], H, d) )
        {
            covered[i] = true;
        }
        else
        {
            minx2 = min(minx2, a[i].lx);
            miny2 = min(miny2, a[i].ly);
            minz2 = min(minz2, a[i].lz);
        }
    }
    //printf("minx2 = %d, miny2 = %d, minz2 = %d\n", minx2, miny2, minz2);
    Point K = Point(minx2, miny2, minz2);

    for(i = 0; i < n; ++i)
    {
        if( !covered[i] && isInside(a[i], K, d) )
        {
            covered[i] = true;
        }
        if( !covered[i] )
        {
            break;
        }
    }
    if(i == n)
    {
        return true;
    }
    return false;
}
bool isok(int d)
{
    int i, j, k, t;
    int minx2, miny2, minz2;

    Point H;

    H = Point(minx, miny, minz);
    if(getDone(H, d))
    {
        return true;
    }

    H = Point(minx, miny, maxz - d);
    if(getDone(H, d))
    {
        return true;
    }

    H = Point(minx, maxy - d, minz);
    if(getDone(H, d))
    {
        return true;
    }

    H = Point(minx, maxy - d, maxz - d);
    if(getDone(H, d))
    {
        return true;
    }

    return false;
}

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int i, j, k;

    scanf("%d", &ntest);

    for(itest = 1; itest <= ntest; ++itest)
    {
        minx = miny = minz = 1e9;
        maxx = maxy = maxz = -1e9;

        scanf("%d", &n);
        for(i = 0; i < n; ++i)
        {
            scanf("%d %d %d %d", &a[i].p.x, &a[i].p.y, &a[i].p.z, &a[i].R);

            a[i].calc();

            minx = min(minx, a[i].lx);
            miny = min(miny, a[i].ly);
            minz = min(minz, a[i].lz);

            maxx = max(maxx, a[i].hx);
            maxy = max(maxy, a[i].hy);
            maxz = max(maxz, a[i].hz);
        }
        sort(a, a + n);
        int lo = 1, hi = 1000000000, mid, res = -1;
        while(lo <= hi)
        {
            mid = (lo + hi) / 2;

            if(isok(mid))
            {
                res = mid;
                hi = mid - 1;
            }
            else
            {
                lo = mid + 1;
            }
        }
        printf("Case #%d: %d\n", itest, res);
    }

    return 0;
}


