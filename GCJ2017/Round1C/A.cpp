//// ngmq

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

struct Plate
{
    int r, h;
    Plate()
    {

    }
    bool operator <(const Plate& other) const
    {
        if(r != other.r)
            return r < other.r;
        return h < other.h;
    }
};

int n, K;
Plate a[1111];
double f[1111][1111], g[1111][1111];

int main()
{
#ifdef HOME
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    int i, j, k;

    scanf("%d", &ntest);

    for(itest = 1; itest <= ntest; ++itest)
    {
        scanf("%d %d", &n, &K);
        for(i = 1; i <= n; ++i)
        {
            scanf("%d %d", &a[i].r, &a[i].h);
        }
        sort(a + 1, a + 1 + n);
        for(i = 0; i <= n; ++i)
        {
            for(j = 0; j <= n; ++j)
            {
                f[i][j] = g[i][j] = 0.0;
            }
        }

        for(i = 1; i <= n; ++i)
        {
            for(k = 1; k <= K; ++k)
            {
                if(i < k)
                {
                    f[i][k] = 0.0;
                }
                else
                {
                    //cout << PI * a[i].r * a[i].r + 2.0 * PI * a[i].r * a[i].h + g[i-1][k-1] << endl;
                    f[i][k] = max(f[i-1][k], 1.0 * PI * a[i].r * a[i].r + 2.0 * PI * a[i].r * a[i].h + g[i-1][k-1]);
                    g[i][k] = max(g[i-1][k], g[i-1][k-1] + 2.0 * PI * a[i].r * a[i].h);
                }
                //printf("%d %d %.10f\n", i, k, f[i][k]);
            }
        }
        // f[i, k] = max(f[i-1, k], pi * r[i] * r[i] + 2 * pi * r[i] * h[i] + g[i-1, k-1])
        printf("Case #%d: %.10f\n", itest, f[n][K]);
    }

    return 0;
}

