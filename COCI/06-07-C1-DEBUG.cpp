//// COCI #1, 2006/2007, task DEBUG
//// AC on http://wcipeg.com/problem/coci061p6
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
const int maxn = 300 + 5;
const int maxv = 5000 + 5;
const int maxe = 1000011 + 5;

int n, m;
char s[maxn][maxn];
unsigned long long hfv[maxn][maxn], hbv[maxn][maxn], vfv[maxn][maxn], vbv[maxn][maxn];
// hfv = horizontal forward value
// hbv = horizontal backward value
// vfv = vertical forward value
// vbv = vertical backward value

const int NBIT = 32;

void build_value()
{
    int i, j, k, t;

    for(i = 0; i < n; ++i)
    {
        for(j = 0; j + NBIT - 1 < m; ++j)
        {
            for(k = 0; k <= NBIT-1; ++k)
            {
                t = s[i][j+k] - '0';
                hfv[i][j] = (hfv[i][j] << 1) | t;
            }
        }
    }

    for(i = 0; i < n; ++i)
    {
        for(j = m-1; j - NBIT-1 >= 0; --j)
        {
            for(k = 0; k <= NBIT-1; ++k)
            {
                t = s[i][j-k] - '0';
                hbv[i][j] = (hbv[i][j] << 1) | t;
            }
        }
    }

    for(j = 0; j < m; ++j)
    {
        for(i = 0; i + NBIT-1 < n; ++i)
        {
            for(k = 0; k <= NBIT-1; ++k)
            {
                t = s[i+k][j] - '0';
                vfv[i][j] = (vfv[i][j] << 1) | t;
            }
        }
    }

    for(j = 0; j < m; ++j)
    {
        for(i = n - 1; i - NBIT-1 >= 0; --i)
        {
            for(k = 0; k <= NBIT-1; ++k)
            {
               t = s[i-k][j] - '0';
               vbv[i][j] = (vbv[i][j] << 1) | t;
            }
        }
    }
}

int check()
{
    int res = -1;
    int i, j, k, t, r, c, x, y; // dealing with grids, no easy going
    for(i = 0; i + 1 < n; ++i)
    {
        for(j = 0; j + 1 < m; ++j)
        {
            for(int start_value = 1; start_value <= 2; ++start_value)
            {
                r = i + start_value - 1;
                c = j + start_value - 1;
                if(r < n && c < m && s[r][c] == s[i][j] && s[i][c] == s[r][j])
                {
                    //printf("i = %d, j = %d\n", i, j);
                    int lr = i - 1, lc = j - 1, hr = r + 1, hc = c + 1;
                    for(k = 0; lr >= 0 && lc >= 0 && hr < n && hc < m; k += 2)
                    {
                        // horizontal check
                        bool invalid = false;
                        for(c = lc, y = hc; hc - c + 1 > NBIT;)
                        {
                            if(hfv[lr][c] != hbv[hr][y])
                            {
                                invalid = true;
                                break;
                            }
                            c += NBIT;
                            y -= NBIT;
                        }
                        for(; c <= hc; ++c, --y)
                        {
                            if(s[lr][c] != s[hr][y])
                            {
                                invalid = true;
                                break;
                            }
                        }
                        if(invalid)
                            break;
                        // vertical check
                        for(r = lr, x = hr; hr - r + 1 > NBIT;)
                        {
                            if(vfv[r][lc] != vbv[x][hc])
                            {
                                invalid = true;
                                break;
                            }
                            r += NBIT;
                            x -= NBIT;
                        }
                        for(; r <= hr; ++r, --x)
                        {
                            if(s[r][lc] != s[x][hc])
                            {
                                invalid = true;
                                break;
                            }
                        }
                        if(invalid)
                            break;

                        --lr;
                        --lc;
                        ++hr;
                        ++hc;
                    }
                    if(start_value + k > 1 && res < start_value + k)
                    {
                        //printf("i = %d, j = %d, start_value = %d, k = %d\n", i, j, start_value, k);
                        res = start_value + k;
                    }
                }
            }
        }
    }
    return res;
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
        for(i = 0; i < n; ++i)
        {
            scanf("%s", s[i]);
            //printf("%s\n", s[i]);
        }
        build_value();
        //printf("%u\n", hbv[2][2][2]);

        int res = check();
        printf("%d\n", res);
    }

    return 0;
}

