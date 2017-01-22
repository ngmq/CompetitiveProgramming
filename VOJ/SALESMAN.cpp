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
const int maxn = 500000 + 5;
const int maxv = 5000 + 5;
const int maxe = 1000011 + 5;

struct Fair
{
    int t, l, m;
    Fair()
    {
        t = l = m = 0;
    }
    Fair(int _t, int _l, int _m)
    {
        t = _t;
        l = _l;
        m = _m;
    }
    bool operator <(const Fair& other) const
    {
        if(t != other.t)
            return t < other.t;
        return l < other.l;
    }
};
Fair a[maxn];

int n, D, U, S;
ll ft_downstream[maxn], ft_upstream[maxn];
ll f[maxn], gu[maxn], gd[maxn];

void update_u(int x, ll val)
{
    while(x < maxn)
    {
        ft_upstream[x] = max(ft_upstream[x], val);
        x += x & -x;
    }
}

ll get_u(int x)
{
    ll r = -linf;
    while(x > 0)
    {
        r = max(r, ft_upstream[x]);
        x -= x & -x;
    }
    return r;
}

void update_d(int x, ll val)
{
    while(x > 0)
    {
        ft_downstream[x] = max(ft_downstream[x], val);
        x -= x & -x;
    }
}

ll get_d(int x)
{
    ll r = -linf;
    while(x < maxn)
    {
        r = max(r, ft_downstream[x]);
        x += x & -x;
    }
    return r;
}

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int i, j, k;
    int L, R;

    //scanf("%d", &ntest);
    for(itest = 1; itest <= ntest; ++itest)
    {
        for(i = 0; i < maxn; ++i)
        {
            ft_downstream[i] = ft_upstream[i] = -linf;
        }
        scanf("%d %d %d %d", &n, &U, &D, &S);
        for(i = 1; i <= n; ++i)
        {
            scanf("%d %d %d", &a[i].t, &a[i].l, &a[i].m);
            f[i] = gu[i] = gd[i] = -linf;
        }
        sort(a + 1, a + 1 + n);
        a[0] = Fair(0, S, 0);
        a[n+1] = Fair(maxn - 2, S, 0);
        // f[0] = f[n+1] = 0

        update_u(a[0].l, f[0] + a[0].l * D);
        update_d(a[0].l, f[0] - a[0].l * U);

        for(i = 1; i <= n + 1; ++i)
        {
            L = i;
            for(R = L + 1; R <= n+1 && a[R].t == a[L].t; ++R);
            --R;

//            if(R != L)
//            {
//                puts("SAME DAY!");
//            }

            //// first round: from previous day
            for(j = L; j <= R; ++j)
            {
                ll k;
                k = get_u(a[j].l);

                if(k != -linf)
                    f[j] = max(f[j], k - 1LL * a[j].l * D + a[j].m);

                k = get_d(a[j].l);
                if(k != -linf)
                    f[j] = max(f[j], k + 1LL * a[j].l * U + a[j].m);
            }
            //// second round: from the same day fellas
            //// down stream
            gd[L] = f[L];
            for(j = L+1; j <= R; ++j)
            {

                gd[j] = max(f[j], gd[j-1] - 1LL * (a[j].l - a[j-1].l) * D + a[j].m);
            }
            //// up stream
            gu[R] = f[R];
            for(j = R-1; j >= L; --j)
            {
                gu[j] = max(f[j], gu[j+1] - 1LL * (a[j+1].l - a[j].l) * U + a[j].m);
            }
            for(j = L; j <= R; ++j)
            {
                f[j] = max(f[j], gd[j]);
                f[j] = max(f[j], gu[j]);
            }
            //// in the end
            for(j = L; j <= R; ++j)
            {
                //printf("j = %d, t = %d, l = %d\n", j, a[j].t, a[j].l);
                update_u(a[j].l, f[j] + a[j].l * D);
                update_d(a[j].l, f[j] - a[j].l * U);
            }
            i = R;
        }
        printf("%lld\n", f[n+1]);
    }

    return 0;
}

