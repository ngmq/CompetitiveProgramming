//// ngmq
//// AC on http://wcipeg.com/problem/coci067p2

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

int h[maxn];

int main()
{
#ifdef HOME
    freopen( "input.txt", "r", stdin );
    freopen( "output.txt", "w", stdout );
#endif

    //scanf("%d", &ntest);

    for( itest = 1; itest <= ntest; ++itest )
    {
        int C, P;
        scanf("%d %d", &C, &P);
        for(int i = 1; i <= C; ++i)
        {
            int k;
            scanf("%d", &k);
            h[i] = k;
        }
        int res = 0;
        if(P == 1)
        {
            res = C;
            for(int i = 1; i + 3 <= C; ++i)
            {
                if( h[i] == h[i+1] && h[i] == h[i+1] && h[i] == h[i+2] && h[i] == h[i+3] )
                {
                    ++res;
                }
            }
        }
        else if(P == 2)
        {
            for(int i = 1; i + 1 <= C; ++i)
            {
                if( h[i] == h[i+1] )
                {
                    ++res;
                }
            }
        }
        else if(P == 3)
        {
            for(int i = 1; i + 1 <= C; ++i)
            {
                if( h[i] - 1 == h[i+1] )
                {
                    ++res;
                }
                if( i + 2 <= C && h[i] == h[i+1] && h[i+1] + 1 == h[i+2] )
                {
                    ++res;
                }
            }
        }
        else if(P == 4)
        {
            for(int i = 1; i + 1 <= C; ++i)
            {
                if( h[i] + 1 == h[i+1] )
                {
                    ++res;
                }
                if( i + 2 <= C && h[i] - 1 == h[i+1] && h[i+1] == h[i+2] )
                {
                    ++res;
                }
            }
        }
        else if(P == 5)
        {
            for(int i = 1; i + 1 <= C; ++i)
            {
                if( h[i] + 1 == h[i+1] || h[i] - 1 == h[i+1] )
                {
                    ++res;
                }
                if( i + 2 <= C && ( (h[i] == h[i+1] && h[i+1] == h[i+2]) || (h[i] == h[i+2] && h[i] - 1 == h[i+1]) ) )
                {
                    ++res;
                }
            }
        }
        else if(P == 6)
        {
            for(int i = 1; i + 1 <= C; ++i)
            {
                if( h[i] == h[i+1] || h[i] - 2 == h[i+1] )
                {
                    ++res;
                }
                if( i + 2 <= C && ( (h[i] == h[i+1] && h[i+1] == h[i+2]) || (h[i+1] == h[i+2] && h[i] + 1 == h[i+1]) ) )
                {
                    ++res;
                }
            }
        }
        else if(P == 7)
        {
            for(int i = 1; i + 1 <= C; ++i)
            {
                if( h[i] == h[i+1] || h[i] + 2 == h[i+1] )
                {
                    ++res;
                }
                if( i + 2 <= C && ( (h[i] == h[i+1] && h[i+1] == h[i+2]) || (h[i] == h[i+1] && h[i] - 1 == h[i+2]) ) )
                {
                    ++res;
                }
            }
        }
        printf("%d\n", res);
    }

    return 0;
}

