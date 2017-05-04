//// ngmq
//// AC on http://wcipeg.com/problem/coci065p5 and http://www.spoj.com/problems/CR07C5P5/
//// Note: a relatively easy problem. It might takes some time to realize this is a DP problem though. Perhaps that's why this was
//// the second to last problem in the contest.

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

int n, a[222], f[222][222];

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
        scanf("%d", &n);
        for(i = 1; i <= n; ++i) scanf("%d", a + i), a[i] %= 2;
        for(i = n + 1; i <= n + n; ++i) a[i] = a[i-n];
        for(i = 1; i <= n + n; ++i)
        {
            for(j = 1; j <= n + n; ++j)
            {
                f[i][j] = -inf;
            }
        }
        for(i = 1; i <= n + n; ++i) f[i][i] = a[i];
        for(k = 1; k <= n-1; ++k)
        {
            for(i = 1; i + k <= n + n; ++i)
            {
                j = i + k;
                f[i][j] = max(a[i] - f[i+1][j], a[j] - f[i][j-1]);
            }
        }
        int res = 0, ans;
        for(i = 1; i <= n; ++i)
        {
            ans = a[i] - f[i+1][i-1+n];
            if(ans > 0)
            {
                ++res;
            }
        }
        printf("%d\n", res);
    }

    return 0;
}

