// main.cpp
/*
ID: tiendao1
LANG: C++
TASK: rectbarn
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

int n, m, P, h[maxn], L[maxn], R[maxn];
char a[maxn][maxn];
int res;

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //time_t t1, t2; t1 = clock();
#else
    freopen("rectbarn.in","r",stdin) ;
    freopen("rectbarn.out", "w", stdout);
#endif
    int i, j, k, t;
    deque<int> que;

    res = 0;
    //scanf("%d", &ntest);
    for(itest = 1; itest <= ntest; ++itest)
    {
        scanf("%d %d %d", &n, &m, &P);
        for(i = 0; i < P; ++i)
        {
            scanf("%d %d", &j, &k);
            a[j][k] = 1;
        }
        for(i = 1; i <= n; ++i)
        {
            for(j = 1; j <= m; ++j)
            {
                if(a[i][j] == 1)
                {
                    h[j] = 0;
                }
                else
                {
                    h[j]++;
                }
                // h is height of histograms
            }
            // build L
            while(!que.empty()) que.pop_front();
            for(j = 1; j <= m; ++j)
            {
                while( !que.empty() && h[que.front()] >= h[j] )
                {
                    que.pop_front();
                }
                if(que.empty())
                    L[j] = 0;
                else
                    L[j] = que.front();
                que.push_front(j);
            }
            // build R
            while(!que.empty()) que.pop_back();
            for(j = m; j >= 1; --j)
            {
                while( !que.empty() && h[que.back()] >= h[j] )
                {
                    que.pop_back();
                }
                if(que.empty())
                    R[j] = m+1;
                else
                    R[j] = que.back();
                que.push_back(j);
            }
            //printf("--- ROW %d ---\n", i);
            for(j = 1; j <= m; ++j)
            {
                res = max(res, h[j] * (R[j] - L[j] - 1));

                //printf("(j, h, L, R) = ( %d, %d, %d, %d )\n", j, h[j], L[j], R[j]);
            }
        }
        printf("%d\n", res);
    }


    return 0;
}
