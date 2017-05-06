//// ngmq
//// AC on http://wcipeg.com/problem/coci066p4
//// Note: the idea behind this problem is quite beautiful. While it doesn't take long to come up with the correct solution
//// (avoid redundant computation of paths of rocks dropped in same column over and over), it might not be very obvious to
//// implement this idea in a clear and concise manner. I personally find the object-oriented solution of COCI very interesting.

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

int n, m, N;
char s[3*10000 + 3][33];
int path_column[33][3*10000 + 3], path_last_row[33];

void drop(int colid)
{
    int r = path_last_row[colid];
    int c = path_column[colid][r];
    s[r-1][c] = rock;

    //cerr << "set " << r-1 << "," << c << " to O \n";
}

void update_path(int colid)
{
    int i, j, k, r, c;

    for(;;)
    {
        r = path_last_row[colid];
        c = path_column[colid][r];

        //cerr << r << ", " << c << endl;

        if( r > 2 && s[r-1][c] != blank ) { --path_last_row[colid]; continue; }
        if( s[r][c] == wall ) break;
        if( s[r][c] == blank )
        {
            ++r;
            path_last_row[colid] = r;
            path_column[colid][r] = c;
        }
        else
        {
            if( c > 1 && s[r][c-1] == blank && s[r-1][c-1] == blank )
            {
                ++r;
                --c;
                path_last_row[colid] = r;
                path_column[colid][r] = c;
            }
            else if( c < m && s[r][c+1] == blank && s[r-1][c+1] == blank )
            {
                ++r;
                ++c;
                path_last_row[colid] = r;
                path_column[colid][r] = c;
            }
            else break;
        }
    }
    path_last_row[colid] = r;
    path_column[colid][r] = c;
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
        scanf("%d %d", &n, &m); // R = n, C = m
        for(i = 1; i <= n; ++i)
        {
            scanf("%s", s[i] + 1);
        }
        for( i = 1; i <= m; ++i )
        {
            path_last_row[i] = 1;
            path_column[i][1] = i;
            update_path(i);
        }

        scanf("%d", &N);
        while(N--)
        {
            scanf("%d", &j);
            drop(j);
            for( i = 1; i <= m; ++i )
            {
                //cerr << "update path " << i << "...\n";
                update_path(i);

                //cerr << "(r, c) = " << path_last_row[i] << ", " << path_column[i][path_last_row[i]] << endl;
            }
        }
        for(i = 1; i <= n; ++i) printf("%s\n", s[i]+1);
    }

    return 0;
}

