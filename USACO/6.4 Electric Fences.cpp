// main.cpp
/*
ID: tiendao1
LANG: C++
TASK: fence3
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
#include <deque>
#include <queue>
//#include <stack>
#include <cstdlib>
// #include <climits>
// #include <functional>
// #include <ctime>
#include <cmath>
//#include <bitset>
// #include <utility>
#include<fstream>

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
const int maxn = 3000 + 5;
const int maxv = 666 + 5;
const int maxe = 100000 + 5;
//const int root = 1;

int n;
int X1[155], X2[155], Y1[155], Y2[155], kind[155];
int minX, maxX, minY, maxY;

double dist(double x, double y, double a, double b)
{
    return sqrt( (x-a)*(x-a) + (y-b)*(y-b) );
}

#define H 0
#define V 1

double all_dist(double x, double y)
{
    int i, j, k;
    double tmp = 0;
    for(i = 1; i <= n; ++i)
    {
        if(kind[i] == H && X1[i] <= x && x <= X2[i])
        {
            tmp += abs(y - Y1[i]);
        }
        else if(kind[i] == V && Y1[i] <= y && y <= Y2[i])
        {
            tmp += abs(x - X1[i]);
        }
        else
        {
            tmp += min(dist(x, y, X1[i], Y1[i]), dist(x, y, X2[i], Y2[i]));
        }
    }
    return tmp;
}

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //time_t t1, t2; t1 = clock();
#else
    freopen("fence3.in","r",stdin) ;
    freopen("fence3.out", "w", stdout);
#endif
    int i, j, k;

    //scanf("%d", &ntest);

    double x, y, resx, resy, res, tmp;
    for(itest = 1; itest <= ntest; ++itest)
    {
        scanf("%d", &n);
        for(i = 1; i <= n; ++i)
        {
            scanf("%d %d %d %d", &X1[i], &Y1[i], &X2[i], &Y2[i]);

            if(Y1[i] == Y2[i])
                kind[i] = H;
            else
                kind[i] = V;

            if(i == 1)
            {
                minX = X1[i]; maxX = X2[i];
                minY = Y1[i]; maxY = Y2[i];
            }
            else
            {
                minX = min(minX, X1[i]);
                maxX = max(maxX, X2[i]);

                minY = min(minY, X1[i]);
                maxY = max(maxY, X2[i]);
            }

            if(X1[i] > X2[i])
            {
                swap(X1[i], X2[i]);
            }
            else if(Y1[i] > Y2[i])
            {
                swap(Y1[i], Y2[i]);
            }
        }

        res = 150.0 * 100 * 2.0;
        int lo, hi, mid1, mid2;
        double r1, r2;
        for(j = minX * 10; j <= maxX * 10; ++j)
        {
            //cout << "------ j = ------" << j << endl;

            x = 1.0 * j / 10.0;
            lo = minY * 10;
            hi = maxY * 10;
            while(lo <= hi)
            {
                mid1 = lo + (hi-lo) / 3;
                mid2 = hi - (hi-lo) / 3;

                //cout << lo << ' ' << mid1 << ' ' << mid2 << ' ' << hi << endl;

                y = 1.0 * mid1 / 10.0;
                r1 = all_dist(x, y);

                y = 1.0 * mid2 / 10.0;
                r2 = all_dist(x, y);

                //cout << "res1 and res2: " << r1 << ' ' << r2 << endl;

                if(res > r1)
                {
                    res = r1;
                    resx = x;
                    resy = 1.0 * mid1 / 10.0;
                }
                if(res > r2)
                {
                    res = r2;
                    resx = x;
                    resy = 1.0 * mid2 / 10.0;
                }
                if(r1 < r2)
                {
                    hi = mid2 - 1;
                    //cerr << "1, new hi = " << hi << endl;
                }
                else
                {
                    lo = mid1 + 1;
                    //cerr << "2, new lo = " << lo << endl;
                }
                //cerr << "************ end" << endl;
            }
        }
        printf("%.1lf %.1lf %.1lf\n", resx, resy, res);
    }


    return 0;
}
