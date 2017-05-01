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

const int Cameron = 0;
const int James = 1;
const int LAST = 1440;

struct Task
{
    int b, e, p; // start, end, person
    Task()
    {

    }
    bool operator <(const Task& other) const
    {
        if(b != other.b)
            return b < other.b;
        if(e != other.e)
            return e < other.e;
        return p < other.p;
    }
};

int n, m;
Task a[222];
int idfix[1444], f[1444][2][722];

// f[i, k, t]: minute i to i+1 put person k with Cameron has t time has been done
// timeLeftJames + timeLeftCameron = 1440 no matter what

int main()
{
#ifdef HOME
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    int i, j, k;

    scanf("%d", &ntest);

    for(itest = 1; itest <= ntest; ++itest)
    {
        // reset
        for(i = 0; i <= LAST; ++i)
        {
            idfix[i] = -1;
            for(j = 0; j <= 1; ++j)
            {
                for(k = 0; k <= LAST / 2; ++k)
                {
                    f[i][j][k] = inf;
                }
            }
        }

        // read
        scanf("%d %d", &n, &m);
        for(i = 1; i <= n; ++i)
        {
            scanf("%d %d", &a[i].b, &a[i].e);
            a[i].p = Cameron;
        }
        for(i = 1; i <= m; ++i)
        {
            scanf("%d %d", &a[n+i].b, &a[n+i].e);
            a[n+i].p = James;
        }
        sort(a + 1, a + 1 + n + m);

        int diff = a[1].b;
        for(i = 1; i <= n + m; ++i)
        {
            a[i].b -= diff;
            a[i].e -= diff;
        }
        if(a[1].p == Cameron)
        {
            for(i = 1; i <= n + m; ++i)
            {
                a[i].p ^= 1; // to make the start one is always Cameron
            }
        }
        for(i = 1; i <= n + m; ++i)
        {
            for(j = a[i].b; j < a[i].e; ++j)
            {
                idfix[j] = a[i].p ^ 1;
            }
        }

        int t, p, tdone, thasto;
        f[0][Cameron][1] = 0;
        //f[0][James][0] = inf;

        thasto = 1;
        for(t = 1; t <= LAST-1; ++t)
        {
            for(p = 0; p <= 1; ++p)
            {
                for(tdone = thasto; tdone <= min(t+1, LAST / 2); ++tdone)
                {
                    f[t][p][tdone] = inf;

                    if(idfix[t] == -1 || idfix[t] == p)
                    {
                        f[t][p][tdone] = min(f[t-1][p][tdone-(p==0)], f[t-1][p^1][tdone-(p==0)] + 1);
                        if(t == LAST - 1 && p == James)
                        {
                            f[t][p][tdone] += 1;
                        }
                    }

                    //printf("t, p, tdone = %d, %d, %d -> f = %d\n", t, p, tdone, f[t][p][tdone]);
                }
            }
            thasto += idfix[t] == Cameron;
            //printf("t = %d, idfix = %d\n", t, idfix[t]);
        }
        int res1 = f[LAST-1][0][LAST / 2];
        int res2 = f[LAST-1][1][LAST / 2];
        int res = min(res1, res2);
        printf("Case #%d: %d\n", itest, res);
    }

    return 0;
}

