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

struct Ingredient
{
    int quantity, serving_min, serving_max;
    Ingredient(){}
    Ingredient(int _q)
    {
        quantity = _q;
    }
    Ingredient(int _q, int _smin, int _smax)
    {
        quantity = _q;
        serving_min = _smin;
        serving_max = _smax;
    }
    bool operator <(const Ingredient& other) const
    {
        if(quantity != other.quantity)
            return quantity < other.quantity;
        return false;
    }
    void calcMinMaxServing(int r)
    {
        serving_max = quantity * 10 / (9 * r);
        serving_min = quantity * 10 / (11 * r);
        if(serving_min * r * 11 < quantity * 10)
            ++serving_min;
        if(serving_min > serving_max)
            serving_min = serving_max = -1;
    }
    bool isInRange(int nserving)
    {
        return serving_min <= nserving && nserving <= serving_max;
    }
};

int n, m, R[55], lastIdx[55], lastKit;
Ingredient a[55][55];

bool isok(int nserving)
{
    int i, lo, hi, mid, ret;
    for(i = 1; i <= n; ++i)
    {
        lo = lastIdx[i] + 1;
        hi = m;
        ret = -1;
        while(lo <= hi)
        {
            mid = (lo + hi) / 2;
            if(a[i][mid].isInRange(nserving))
            {
                ret = mid;
                break;
            }
            else if(a[i][mid].serving_min > nserving)
            {
                hi = mid - 1;
            }
            else
            {
                lo = mid + 1;
            }
        }
        if(ret == -1)
        {
            return false;
        }
    }
    return true;
}

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
        scanf("%d %d", &n, &m);
        for(i = 1; i <= n; ++i)
        {
            scanf("%d", &R[i]);
        }
        for(i = 1; i <= n; ++i)
        {
            for(j = 1; j <= m; ++j)
            {
                scanf("%d", &a[i][j].quantity);
                a[i][j].calcMinMaxServing(R[i]);
            }
            sort(a[i]+1, a[i]+1+m);
        }
        ms(lastIdx, 0);
        for(i = 1; i <= n; ++i) lastIdx[i] = 1;

        int res = 0;
        bool done = false;
        for(;!done;)
        {
            int max_serving_min = 0, min_serving_max = 1e6;
            for(i = 1; i <= n; ++i)
            {
                max_serving_min = max(max_serving_min, a[i][lastIdx[i]].serving_min);
                min_serving_max = min(min_serving_max, a[i][lastIdx[i]].serving_max);
            }
            if(min_serving_max < max_serving_min)
            {
                for(i = 1; i <= n; ++i)
                {
                    if( a[i][lastIdx[i]].serving_max == min_serving_max )
                    {
                        ++lastIdx[i];
                    }
                }
            }
            else
            {
                ++res;
                for(i = 1; i <= n; ++i)
                {
                    ++lastIdx[i];
                }
            }
            for(i = 1; i <= n; ++i)
            {
                done |= lastIdx[i] > m;
            }
        }
        printf("Case #%d: %d\n", itest, res);
    }

    return 0;
}

