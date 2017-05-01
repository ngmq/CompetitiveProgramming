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
const int maxn = 1000 + 5;
const int maxv = 100000 + 5;
const int maxe = 1000011 + 5;

ll N, K;

//void verify()
//{
//    int i, j, k;
//    bool busy[maxn];
//    ms(busy, false);
//    while(K > 0)
//    {
//        int choose, L, R, l, r;
//        for(i = 0; i < N; ++i)
//        {
//
//        }
//    }
//}

int main()
{
#ifdef HOME
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    int i, j, k;

    scanf("%d", &ntest);

    for(itest = 1; itest <= ntest; ++itest)
    {
        scanf("%lld %lld", &N, &K);
        ll save_k = K;

        //cout << N << ' ' << K << endl;
        map<ll, ll> mpcount;

        mpcount[N] = 1;
        priority_queue<ll> q; q.push(N);

        ll res_min = 0, res_max = 0;

        while(!q.empty() && K > 0)
        {
            ll x = q.top(); q.pop();
            ll cx = mpcount[x];
            ll y = (x-1) / 2, z = x - 1 - y;

            //printf("K = %lld, x = %lld, cx = %lld, y = %lld, z = %lld\n", K, x, cx, y, z);

            if(cx < K)
            {
                K -= cx;
                mpcount[y] += cx;
                if(mpcount[y] == cx) q.push(y);
                mpcount[z] += cx;
                if(mpcount[z] == cx) q.push(z);
            }
            else
            {
                res_max = max(y, z);
                res_min = min(y, z);
                break;
            }
        }
        printf("Case #%d: %lld %lld\n", itest, res_max, res_min);

        K = save_k;
//        verify();
    }

    return 0;
}

