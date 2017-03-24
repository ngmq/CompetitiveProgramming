//// ngmq
//// AC on http://wcipeg.com/problem/coci063p6
//Execution Results
//Test case #1: AC [0.003s, 11192K] (10/10)
//Test case #2: AC [0.003s, 11192K] (10/10)
//Test case #3: AC [0.026s, 11192K] (10/10)
//Test case #4: AC [0.003s, 11192K] (10/10)
//Test case #5: AC [0.003s, 11192K] (10/10)
//Test case #6: AC [0.026s, 11192K] (10/10)
//Test case #7: AC [0.059s, 11192K] (10/10)
//Test case #8: AC [0.096s, 11192K] (10/10)
//Test case #9: AC [0.148s, 11192K] (10/10)
//
//Final score: 90/90
// Algorithm: after find the lis, bfs from elements in lis to other elements and put the incorrect ones to right places
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
const int maxn = 500000 + 5;
const int maxv = 100000 + 5;
const int maxe = 1000011 + 5;

int n, m, nxt[maxn], pre[maxn];
int F, L; // First and Last

void show()
{
    puts("----");
    for(int i = nxt[F]; i != L; i = nxt[i])
    {
        printf("%d -> ", i);
    }
}

void TakeUout(int u)
{
    int a, b;
    a = pre[u];
    b = nxt[u];

    nxt[a] = b;
    pre[b] = a;
}
void Auv(int u, int v)
{
    int a, b;
    // take u out
    TakeUout(u);
    // put it in front of v
    a = pre[v];
    nxt[a] = u;
    pre[u] = a;
    nxt[u] = v;
    pre[v] = u;
}

void Buv(int u, int v)
{
    int a, b;
    // take u out
    TakeUout(u);
    // put it after v
    b = nxt[v];
    pre[b] = u;
    pre[u] = v;
    nxt[u] = b;
    nxt[v] = u;
}

int lis[maxn], nlis, ft[maxn]; // lis = longest increasing subsequence
bool isInLis[maxn];

int get(int u)
{
    int res = 0;
    while(u > 0)
    {
        res = max(res, ft[u]);
        u -= u & -u;
    }
    return res;
}

void update(int u, int x)
{
    while(u <= n)
    {
        ft[u] = max(ft[u], x);
        u += u & -u;
    }
}

void make_lis()
{
    int i, j, k;
    int u;
    for(u = nxt[F]; u != L; u = nxt[u])
    {
        k = get(u - 1);
        lis[u] = k + 1;
        update(u, lis[u]);
        nlis = max(nlis, lis[u]);
    }
    for(u = nxt[F]; u != L && lis[u] != nlis; u = nxt[u]);
    for(k = nlis; k >= 1 && u != F; u = pre[u])
    {
        if(lis[u] == k)
        {
            isInLis[u] = true;
            --k;
        }
    }
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

        F = 0;
        L = n + 1;

        for(i = 1; i <= n; ++i)
        {
            pre[i] = i-1;
            nxt[i] = i+1;
        }
        nxt[F] = F+1;
        pre[L] = L-1;

        char s[3];
        int u, v;
        for(i = 0; i < m; ++i)
        {
            scanf("%s %d %d", s, &u, &v);
            if(s[0] == 'A')
            {
                Auv(u, v);
            }
            else
            {
                Buv(u, v);
            }
        }
        //show();
        make_lis();
        vector<pair<char, pii> > vres;
        queue<int> qu;
        for(u = 1; u <= n; ++u) if(isInLis[u]) qu.push(u);
        while(!qu.empty())
        {
            u = qu.front(); qu.pop();
            if(u > 1 && !isInLis[u-1])
            {
                Auv(u-1, u);
                isInLis[u-1] = true;
                qu.push(u-1);
                vres.push_back(pair<char, pii>('A', pii(u-1, u)));
            }
            if(u < n && !isInLis[u+1])
            {
                Buv(u+1, u);
                isInLis[u+1] = true;
                qu.push(u+1);
                vres.push_back(pair<char, pii>('B', pii(u+1, u)));
            }
        }

        printf("%d\n", vres.size());
        for(i = 0; i < vres.size(); ++i)
        {
            printf("%c %d %d\n", vres[i].fi, vres[i].se.fi, vres[i].se.se);
        }
    }

    return 0;
}

