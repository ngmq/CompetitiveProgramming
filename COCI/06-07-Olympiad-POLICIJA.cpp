//// ngmq
//// AC on http://wcipeg.com/problem/coi06p2
//// Solution: LCA on DFS Tree

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
#include <cassert>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define inf 1e9
#define linf 1e18
#define BASE 1000000
#define EPS 1e-10
#define PI acos(-1)
#define pii pair<int,int>
#define vi vector<int>
#define fi first
#define se second
#define ALL(x) (x).begin(), (x).end()
#define ms(x,val_add) memset(x, val_add, sizeof(x))
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
    "NE", "SE", "SW", "NW"
};

const ll Mod = 1000000007LL;
const int maxn = 100000 + 5;
const int maxv = 100000 + 5;
const int maxe = 2 * 500000 + 5;

const int LogN = 17;
int E, elast[maxn], eadj[maxe], enext[maxe];
int n, m, lgn;
int Num[maxn], Low[maxn], father[maxn][LogN], Level[maxn];
bool visited[maxn];

void add(int u, int v)
{
    eadj[E] = v; enext[E] = elast[u]; elast[u] = E; ++E;
    eadj[E] = u; enext[E] = elast[v]; elast[v] = E; ++E;
}

int run = 0;
void dfs(int u, int lev)
{
    visited[u] = true;
    Num[u] = ++run;
    Low[u] = Num[u];
    Level[u] = lev;

    for(int e = elast[u]; e != -1; e = enext[e])
    {
        int v = eadj[e];
        if(!visited[v])
        {
            //printf("%d -> %d\n", u, v);
            father[v][0] = u;
            dfs(v, lev + 1);
            Low[u] = min(Low[u], Low[v]);
        }
        else if(v != father[u][0])
        {
            Low[u] = min(Low[u], Num[v]);
        }
    }
}

void build_father()
{
    for(int k = 1; k <= lgn; ++k)
    {
        for(int u = 1; u <= n; ++u)
        {
            int fu = father[u][k-1];
            if(fu != -1)
            {
                father[u][k] = father[fu][k-1];
            }
        }
    }
}

bool isFather(int u, int v) // is u father of v?
{
    if(Num[u] > Num[v])
        return false;

    for(int k = lgn; k >= 0; --k)
    {
        int fv = father[v][k];
        if(fv != -1 && Num[fv] >= Num[u])
        {
            v = fv;
        }
    }
    return v == u;
}

int lca(int u, int v) // lowest common ancestor
{
    if(Level[u] > Level[v])
        swap(u, v);
    for(int k = lgn; k >= 0; --k)
    {
        int fv = father[v][k];
        if(fv != -1 && Level[fv] >= Level[u])
        {
            v = fv;
        }
    }
    if(v == u) return u;
    assert(Level[u] == Level[v]);
    for(int k = lgn; k >= 0; --k)
    {
        int fu = father[u][k];
        int fv = father[v][k];
        if(fu != fv)
        {
            u = fu;
            v = fv;
        }
    }
    int fu = father[u][0];
    int fv = father[v][0];
    assert(fu == fv);
    return fu;
}

int findBackwardVertexPassAVertex(int v, int u) // find first father of v that is after u and goes backward pass u
{
    if(Low[v] < Num[u])
        return v;
    int res = -1;
    for(int k = lgn; k >= 0; --k)
    {
        int fv = father[v][k];
        if(fv != -1 && Num[fv] >= Num[u])
        {
            if(Low[fv] < Num[u])
            {
                res = fv;
            }
            else
            {
                v = fv;
            }
        }
    }
    return res;
}

int main()
{
    #ifdef HOME
    freopen( "input.txt", "r", stdin );
    freopen( "output.txt", "w", stdout );
    #endif // HOME

    //scanf("%d", &ntest);

    for( itest = 1; itest <= ntest; ++itest )
    {
        ms(elast, -1);

        scanf("%d %d", &n, &m);
        for(int i = 0; i < m; ++i)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            add(u, v);
        }

        ms(visited, false);
        ms(father, -1);
        dfs(1, 1);

        for(lgn = 1; (1<<lgn) <= n; ++lgn); --lgn;
        build_father();

        int Q;
        int id, a, b, c, g1, g2;
        scanf("%d", &Q);
        for(int i = 0; i < Q; ++i)
        {
            scanf("%d %d %d", &id, &a, &b);
            if(Num[b] < Num[a])
                swap(a, b);
            if(id == 1)
            {
                scanf("%d %d", &g1, &g2);
                if(Num[g2] < Num[g1])
                    swap(g1, g2);

                if(Low[g2] <= Num[g1] ||
                   ( isFather(g2, a) == isFather(g2, b))
                   )
                {
                    puts("yes");
                }
                else puts("no");
            }
            else
            {
                scanf("%d", &c);
                bool ca = isFather(c, a);
                bool cb = isFather(c, b);
                if(!ca && !cb)
                {
                    puts("yes");
                }
                else if(!ca && cb)
                {
                    int pb = findBackwardVertexPassAVertex(b, c);
                    if(pb != -1 && pb != c)
                    {
                        puts("yes");
                    }
                    else puts("no");
                }
                else if(ca && !cb)
                {
                    int pa = findBackwardVertexPassAVertex(a, c);
                    if(pa != -1 && pa != c)
                    {
                        puts("yes");
                    }
                    else puts("no");
                }
                else
                {
                    // ca and cb are true
                    int f = lca(a, b);
                    if(f != c)
                    {
                        puts("yes");
                    }
                    else
                    {
                        int pa = findBackwardVertexPassAVertex(a, c);
                        int pb = findBackwardVertexPassAVertex(b, c);
                        if(pa != -1 && pa != c && pb != -1 && pb != c)
                        {
                            puts("yes");
                        }
                        else puts("no");
                    }

                }
            }
        }
    }

    return 0;
}

