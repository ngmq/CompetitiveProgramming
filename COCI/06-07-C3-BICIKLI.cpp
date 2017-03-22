//// ngmq
//// AC on both http://wcipeg.com/problem/coci063p5 and http://www.spoj.com/problems/CR07C3P5/
////Execution Results
////Test case #1: AC [0.003s, 5460K] (10/10)
////Test case #2: AC [0.003s, 5460K] (10/10)
////Test case #3: AC [0.003s, 5460K] (10/10)
////Test case #4: AC [0.000s, 5460K] (10/10)
////Test case #5: AC [0.003s, 5460K] (10/10)
////Test case #6: AC [0.009s, 5460K] (10/10)
////Test case #7: AC [0.003s, 5460K] (10/10)
////Test case #8: AC [0.052s, 5460K] (10/10)
////Test case #9: AC [0.039s, 5460K] (10/10)
////Test case #10: AC [0.049s, 5460K] (10/10)
////
////Final score: 100/100
////  Algorithm: construct topological order from DAG by dfs with formula order[u] = max(order[u], order[v] + 1) with edge (u -> v)
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
const int maxn = 10000 + 5;
const int maxv = 200000 + 5;
const int maxe = 1000011 + 5;

const int source = 1, destination = 2;

int n, m;
int E, enext[maxv], last[maxn], adj[maxv], dir[maxv];
bool reachToDest[maxn], reachFromSource[maxn], valid[maxn];
int visit[maxn];
ll ans[maxn];

void add(int u, int v)
{
    adj[E] = v; dir[E] = 1;  enext[E] = last[u]; last[u] = E; ++E;
    adj[E] = u; dir[E] = -1; enext[E] = last[v]; last[v] = E; ++E;
}

void dfs(int u, int edge_type)
{
    visit[u] = 0;
    if(edge_type == 1)
        reachFromSource[u] = true;
    else
        reachToDest[u] = true;

    int e, v;
    for(e = last[u]; e != -1; e = enext[e])
    {
        if(dir[e] == edge_type)
        {
            v = adj[e];
            if(visit[v] == -1)
                dfs(v, edge_type);
        }
    }
    visit[u] = 1;
}

bool dfs_detect_cycle(int u)
{
    visit[u] = 0;
    int e, v;
    for(e = last[u]; e != -1; e = enext[e])
    {
        if(dir[e] == 1)
        {
            v = adj[e];
            if(visit[v] == 0)
            {
                return true;
            }
            if(visit[v] == -1 && valid[v])
            {
                if(dfs_detect_cycle(v))
                {
                    return true;
                }
            }
        }
    }
    visit[u] = 1;
    return false;
}

int order[maxn];

void dfs_order(int u)
{
    visit[u] = 0;
    int e, v;
    for(e = last[u]; e != -1; e = enext[e])
    {
        if(dir[e] == 1)
        {
            v = adj[e];
            if(valid[v])
            {
                if(visit[v] == -1)
                {
                    dfs_order(v);
                }
                order[u] = max(order[u], order[v] + 1);
            }
        }
    }
    visit[u] = 1;
}

void buildDAG()
{
    int i;
    for(i = 1; i <= n; ++i)
    {
        order[i] = 0;
        visit[i] = -1;
    }
    dfs_order(source);
}

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
        scanf("%d %d", &n, &m);

        for(i = 1; i <= n; ++i) last[i] = -1;
        for(i = 0; i < m; ++i)
        {
            scanf("%d %d", &j, &k);
            add(j, k);
        }

        for(i = 1; i <= n; ++i) visit[i] = -1;
        dfs(source, 1);
        for(i = 1; i <= n; ++i) visit[i] = -1;
        dfs(destination, -1);
        for(i = 1; i <= n; ++i) valid[i] = reachFromSource[i] & reachToDest[i];

        if(!valid[source])
        {
            puts("0");
            break;
        }
        for(i = 1; i <= n; ++i) visit[i] = -1;
        if(dfs_detect_cycle(source))
        {
            puts("inf");
            break;
        }
        buildDAG();
        vector<pii> vp;
        for(i = 1; i <= n; ++i)
        {
            if(valid[i])
            {
                //printf("order[%d] = %d\n", i, order[i]);
                vp.push_back(pii(-order[i], i));
            }
        }
        sort(vp.begin(), vp.end());

        int u, v, e;
        ans[source] = 1;
        bool big = false;
        for(i = 0; i < vp.size(); ++i)
        {
            u = vp[i].se;
            for(e = last[u]; e != -1; e = enext[e])
            {
                if(dir[e] == -1)
                {
                    v = adj[e];
                    if(valid[v])
                    {
                        ans[u] += ans[v];
                        if(!big && ans[u] >= 1000000000)
                        {
                            big = true;
                        }
                        if(big)
                        {
                            ans[u] %= 1000000000;
                        }
                    }
                }
            }
        }
        if(big)
        {
            printf("%09lld\n", ans[destination]);
        }
        else
        {
            printf("%lld\n", ans[destination]);
        }
    }

    return 0;
}

