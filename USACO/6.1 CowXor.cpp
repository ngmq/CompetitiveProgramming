// main.cpp
/*
ID: tiendao1
LANG: C++
TASK: cowxor
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
const int maxn = 100000 + 5;
const int maxv = 666 + 5;
const int maxe = 100000 + 5;
//const int root = 1;

int n, a[maxn], f[maxn], val[maxn], first, last;
int has[(1<<21)];
int res;

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //time_t t1, t2; t1 = clock();
#else
    freopen("cowxor.in","r",stdin) ;
    freopen("cowxor.out", "w", stdout);
#endif
    int i, j, k, t;

    int expect, need;

    //scanf("%d", &ntest);
    for(itest = 1; itest <= ntest; ++itest)
    {
        scanf("%d", &n);
        for(i = 1; i <= n; ++i)
        {
            scanf("%d", &k);
            a[i] = k;
            f[i] = f[i-1] ^ k;

            //printf("f[%d] = %d\n", i, f[i]);
        }
        ms(has, -1);
        res = 0;
        last = first = 0;

        for(k = 20; k >= 0; --k)
        {
            // reset has
            for(i = 1; i <= n; ++i)
            {
                has[val[i]] = -1;
            }
            has[0] = 0; // a[0] = 0 always true
            // attempt to set bit k-th 1
            expect = res | (1<<k);

            //printf("k = %d, expect = %d\n", k, expect);

            for(i = 1; i <= n; ++i)
            {
                if(f[i] & (1<<k))
                {
                    val[i] = val[i] | (1<<(k));
                }
                j = val[i];

                need = j ^ expect;

                t = has[need];

                if(t != -1)
                {
                    if(res != expect)
                    {
                        res = expect;
                        last = i;
                        first = t;
                    }
                }
                has[val[i]] = i;
            }
            //printf("after k = %d, res = %d\n", k, res);
        }
        if(res == 0)
        {
            first = 0;
            last = 1;
        }
        printf("%d %d %d\n", res, first+1, last);
    }

    return 0;
}
