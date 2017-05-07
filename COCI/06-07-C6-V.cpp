//// ngmq
//// AC on http://wcipeg.com/problem/coci066p5
//// Note: a standard dp-on-digits counting problem. Basically, if we are given X * Y <= B where X, Y, B is large and we need to count
//// number of possible B, then it is obvious to consider two cases wherein X and Y is smaller than sqrt(B) and solve for each case.

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

const char wall = 'X';
const char rock = 'O';
const char blank = '.';

ll X, A, B, ndigits, digits[11], f[11][100000], remain[10][11];
bool allowed[10];

bool isallowed(ll num)
{
    for(; num > 0; num /= 10)
    {
        if( !allowed[ num % 10 ] ) return false;
    }
    return true;
}

ll calc(ll upperBound)
{
    //cout << "upperBound = " << upperBound << endl;
    ll res = 0;
    if( upperBound == 0 )
    {
        res = allowed[0];
    }
    else if( X > 100000 )
    {
        int Y = upperBound / X;
        for( int i = 1; i <= Y; ++i ) res += isallowed( X * i );
    }
    else
    {
        for( ndigits = 0; upperBound > 0; upperBound /= 10 ) digits[ ndigits++ ] = upperBound % 10;
        std::reverse( digits, digits + ndigits );

        // build f array
        f[0][0] = 1;
        for( int i = 1; i < ndigits; ++i )
        {
            for( int k = 0; k < X; ++k )
            {
                f[i][k] = 0;
                for( int j = 0; j <= 9; ++j )
                {
                    if( !allowed[j] ) continue;
                    int r_need = ( k - remain[j][i-1] + X ) % X ;
                    f[i][k] += f[i - 1][r_need];
                }
            }
            if( allowed[0] && i > 1 )
                res += f[i][0] - f[i-1][0];
            else
                res += f[i][0];
        }
        //cout << "Less digits than upperBound, res = " << res << endl;
        int r_sofar = 0, isUpperBoundAllowed = true;
        for( int i = 0; i < ndigits; ++i )
        {
            for( int k = 0; k < digits[i]; ++k )
            {
                if( !allowed[k] || ( i == 0 && k == 0 && ndigits > 1 ) ) continue;
                int r_next = ( r_sofar + remain[k][ndigits - i - 1] ) % X;
                int r_need = ( 0 - r_next + X ) % X;
                res += f[ndigits - i - 1][r_need];
            }
            isUpperBoundAllowed &= allowed[ digits[i] ];
            if( !isUpperBoundAllowed ) break;
            r_sofar = ( r_sofar + remain[digits[i]][ndigits - i - 1] ) % X;
        }
        if( r_sofar == 0 && isUpperBoundAllowed ) res += 1;
    }
    //cout << "res = " << res << endl;
    return res;
}

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    //scanf("%d", &ntest);

    for(itest = 1; itest <= ntest; ++itest)
    {
        cin >> X >> A >> B;
        char s[11];
        cin >> s;
        for( int i = 0; s[i]; ++i ) allowed[ s[i] - '0' ] = true;
        for( int i = 0; i <= 9; ++i )
        {
            remain[i][0] = i % X;
            for( int j = 1; j <= 10; ++j )
            {
                remain[i][j] = ( remain[i][j-1] * 10 ) % X;
            }
        }
        printf( "%lld\n", calc(B) - calc(A-1) );
    }

    return 0;
}

