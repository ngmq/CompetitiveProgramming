//// ngmq
//// AC on http://wcipeg.com/problem/coci065p4
//// Execution Results
//// Test case #1: AC [0.006s, 2888K] (10/10)
//// Test case #2: AC [0.006s, 2888K] (10/10)
//// Test case #3: AC [0.006s, 2888K] (10/10)
//// Test case #4: AC [0.009s, 2888K] (10/10)
//// Test case #5: AC [0.026s, 2888K] (10/10)
//// Note: I find this problem quite interesting, not because it is hard to come up with a solution but how easily people can fall 
//// into the trap of coding many if-else conditions. This solution is obviously not the most elegent one but satisfying enough to me.
//// The trick to avoid having a lot of if-else conditions is using for-loop for 03 values wins, draws, loses (x, y, t), but do so
//// cleverly that the solution runs fast enough for large tests.

Final score: 50/50
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
const int maxn = 200000 + 5;
const int maxv = 100000 + 5;
const int maxe = 1000011 + 5;


int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int i, j, k;

    scanf("%d", &ntest);
    int n, x, y, t, p;
    int nmin, nmax, xmin, xmax, ymin, ymax, tmin, tmax, pmin, pmax;
    char s[5];

    for(itest = 1; itest <= ntest; ++itest)
    {
        n = x = y = t = p = -1;
        nmin = 0;
        nmax = 100;
        xmin = 0;
        xmax = nmax;
        ymin = 0;
        ymax = nmax;
        tmin = 0;
        tmax = nmax;
        pmin = 3*xmin + ymin;
        pmax = 3*nmax;

        scanf("%s", s);
        if(s[0] != '?')
        {
            sscanf(s, "%d", &n);
        }
        scanf("%s", s);
        if(s[0] != '?')
        {
            sscanf(s, "%d", &x);
        }
        scanf("%s", s);
        if(s[0] != '?')
        {
            sscanf(s, "%d", &y);
        }
        scanf("%s", s);
        if(s[0] != '?')
        {
            sscanf(s, "%d", &t);
        }
        scanf("%s", s);
        if(s[0] != '?')
        {
            sscanf(s, "%d", &p);
        }

        if(x != -1) xmin = xmax = x;
        if(y != -1) ymin = ymax = y;
        if(t != -1) tmin = tmax = t;
        if(n != -1) nmin = nmax = n;
        if(p != -1) pmin = pmax = p;

        xmax = min(xmax, pmax / 3);
        xmax = min(xmax, nmax - tmin);
        ymax = min(ymax, pmax);
        ymax = min(ymax, nmax - tmin);
        nmin = max(nmin, xmin + ymin + tmin);
        pmin = max(pmin, 3*xmin + ymin);

        for(x = xmin; x <= xmax; ++x)
        {
            for(y = ymin; y <= ymax; ++y)
            {
                for(t = tmin; t <= tmax; ++t)
                {
                    n = x + y + t;
                    p = 3*x + y;
                    if(nmin <= n && n <= nmax && pmin <= p && p <= pmax)
                    {
                        printf("%d %d %d %d %d\n", n, x, y, t, p);
                    }
                }
            }
        }
    }

    return 0;
}

