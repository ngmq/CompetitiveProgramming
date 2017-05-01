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

char s[maxn];
int n;

int main()
{
#ifdef HOME
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    int i, j, k;

    scanf("%d", &ntest);

    for(itest = 1; itest <= ntest; ++itest)
    {
        scanf("%s %d", &s, &n);
        int m = strlen(s);
        int cnt = 0;
        for(i = 0; i <= m - n; ++i)
        {
            if(s[i] == '-')
            {
                // flip
                for(k = 0, j = i; k < n; ++k, ++j)
                {
                    if(s[j] == '-')
                    {
                        s[j] = '+';
                    }
                    else s[j] = '-';
                }
                ++cnt;
            }
        }
        for(i = 0; i < m; ++i)
        {
            if(s[i] == '-')
            {
                cnt = -1;
                break;
            }
        }
        if(cnt == -1) printf("Case #%d: IMPOSSIBLE\n", itest);
        else printf("Case #%d: %d\n", itest, cnt);
    }

    return 0;
}

