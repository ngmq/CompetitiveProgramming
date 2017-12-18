//// ngmq
//// AC on http://wcipeg.com/problem/coci067p1

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
const int maxn = 100 + 5;
const int maxv = 100000 + 5;
const int maxe = 1000011 + 5;

int n, m;
bool visit[maxn], connect[maxn][maxn], hasOne[55];
int a[55][maxn], cnt[maxn];

void dfs(int u)
{
    cnt[u]++;
    visit[u] = true;
    for(int v = 1; v <= n; ++v) if(connect[u][v] && !visit[v]) {
        dfs(v);
    }
}

int main()
{
#ifdef HOME
    freopen( "input.txt", "r", stdin );
    freopen( "output.txt", "w", stdout );
#endif

    //scanf("%d", &ntest);

    for( itest = 1; itest <= ntest; ++itest )
    {
        scanf("%d %d", &n, &m);
        for(int j = 1; j <= m; ++j)
        {
            scanf("%d", &a[j][0]);
            for(int i = 1; i <= a[j][0]; ++i)
            {
                scanf("%d", &a[j][i]);

                //printf("j = %d, i = %d, a[j, i] = %d\n", j, i, a[j][i]);

                if(a[j][i] == 1)
                    hasOne[j] = true;
            }
        }
        int nsong = 0;
        for(int j = m; j >= 1; --j)
        {
            if(hasOne[j])
            {
                ++nsong;
                ms(visit, false);
                for(int i = 1; i <= a[j][0]; ++i)
                {
                    if(!visit[ a[j][i] ]) dfs(a[j][i]);
                }
                //for(int i = 1; i <= n; ++i) printf("j = %d, cnt[%d] = %d\n", j, i, cnt[i]);
            }
            else
            {
                for(int i = 1; i <= a[j][0]; ++i)
                {
                    for(int k = i+1; k <= a[j][0]; ++k)
                    {
                        connect[ a[j][i] ][ a[j][k] ] = connect[ a[j][k] ][ a[j][i] ] = true;
                    }
                }
            }

        }
        for(int i = 1; i <= n; ++i) if( cnt[i] == nsong ) printf("%d\n", i);
    }

    return 0;
}

