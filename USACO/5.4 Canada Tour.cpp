// main.cpp
/*
ID: tiendao1
LANG: C++
TASK: tour
*/

/*
Bai nay su dung QHD. Cong thuc la

f[i, j] = so luong nodes theo 2 path (1->i) va (1->j)
ma 2 path nay khong co diem nao trung nhau except 1.

Tuy nhien cong thuc QHD rat de bi trung. Cong thuc dung la:

voi i < j va k < j va k != i:

f[i, j] = max(f[i,j], f[i,k] + 1)

tat ca cac cong thuc khac deu dan toi truong hop
bi trung node.
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
const int maxn = 100000 + 5;
const int maxv = 100000 + 5;
const int maxe = 100000 + 5;
//const int root = 1;

int n, V;

map<string, int> id;

int vis[111];
int nadj[111], adj[111][111], f[111][111];
int res = 0;

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //time_t t1, t2; t1 = clock();
#else
    freopen("tour.in","r",stdin) ;
    freopen("tour.out", "w", stdout);
#endif
    int i, j, k;

    //scanf("%d", &ntest);
    for(itest = 1; itest <= ntest; ++itest)
    {
        scanf("%d %d", &n, &V);
        char s[20], p[20];

        for(i = 1; i <= n; ++i)
        {
            scanf("%s", s);
            id[string(s)] = i;
        }
        ms(nadj, 0);
        for(i = 0; i < V; ++i)
        {
            scanf("%s %s", s, p);
            j = id[string(s)];
            k = id[string(p)];

            //adj[j][nadj[j]] = k; ++nadj[j];
            //adj[k][nadj[k]] = j; ++nadj[k];
            adj[j][k] = adj[k][j] = 1;

            //printf("%d %d\n", j, k);
        }
        int t;

        f[1][1] = 1;
        for(i = 2; i <= n; ++i)
        {
            for(j = 1; j < i; ++j)
            {
                if(adj[j][i] && f[1][j] > 0)
                {
                    f[1][i] = max(f[1][i], f[1][j] + 1);
                }
            }
            f[i][1] = f[1][i];

            //printf("f[1, %d] = %d\n", i, f[1][i]);
        }
        for(i = 2; i <= n; ++i)
        {
            for(j = i+1; j <= n; ++j)
            {
                for(k = 1; k < j; ++k)
                {
                    if(adj[k][j] && k != i && f[k][i] > 0)
                    {
                        f[i][j] = max(f[i][j], f[k][i] + 1);
                    }
                }
                f[j][i] = f[i][j];
               //printf("--- f[%d %d] = %d\n", i, j, f[i][j]);
            }
        }
        for(i = 1; i <= n; ++i)
        {
            if(adj[i][n])
            {
                res = max(res, f[i][n]);
            }
        }

        if(res == 0)
            res = 1;
        printf("%d\n", res);
    }

    return 0;
}
