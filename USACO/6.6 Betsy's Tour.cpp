// main.cpp
/*
ID: tiendao1
LANG: C++
TASK: betsy
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
#include <deque>
#include <queue>
#include <stack>
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
const int maxn = 3000 + 5;
const int maxv = 666 + 5;
const int maxe = 100000 + 5;
//const int root = 1;

int n;
int visit[8][8], nadj[8][8];
int res = 0;

bool bfs(int r, int c, int len)
{
    int i, j, k;
}

void printBoard()
{
    int i, j, k;
    for(i = 1; i <= n; ++i)
    {
        for(j = 1; j <= n; ++j)
        {
            printf("%d", visit[i][j]);
        }
        puts("");
    }

}
void go(int r, int c, int len)
{
    //printf("r = %d, c = %d, len = %d\n", r, c, len);
    if( r == n && c == 1 )
    {
        if( len == n*n )
            ++res;
        return;
    }
    int i, j, k;
    int x, y;
    bool lone = false, wrong = false;
    int lone_id = -1;
    if(c == n)
    {
        if(r - 1 >= 1 && r + 1 <= n && !visit[r-1][c] && !visit[r+1][c])
        {
            wrong = true;
        }
    }
    else if(r == 1)
    {
         if(c - 1 >= 1 && c + 1 <= n && !visit[r][c-1] && !visit[r][c+1])
        {
            wrong = true;
        }
    }
    else if(r == n)
    {
        if(c - 1 >= 1 && c + 1 <= n && !visit[r][c-1] && !visit[r][c+1])
        {
            wrong = true;
        }
    }
    for(i = 0; i < 4; ++i)
    {
        x = r + dx[i];
        y = c + dy[i];
        if( x >= 1 && x <= n && y >= 1 && y <= n && !visit[x][y])
        {
            --nadj[x][y];
            if( nadj[x][y] == 0 )
            {
                if(x == n && y == 1)
                {
                    if(len == n * n - 1)
                        continue;
                }
                wrong = true;
                //break;
            }
            if( nadj[x][y] == 1 && (x != n || y != 1) )
            {
                lone = true;
                lone_id = i;
                //break;
            }
        }
    }
    if(!wrong)
    {
        if(lone)
        {
            i = lone_id;
            x = r + dx[i];
            y = c + dy[i];

            //printf("r = %d, c = %d, len = %d, LONE = %d, to = (%d, %d), nadj = %d\n", r, c, len, lone_id, x, y, nadj[x][y]);
            //printBoard();

            visit[x][y] = 1;

            go(x, y, len + 1);

            visit[x][y] = 0;
        }
        else
        {
            for(i = 0; i < 4; ++i)
            {
                x = r + dx[i];
                y = c + dy[i];
                if(x >= 1 && x <= n && y >= 1 && y <= n && !visit[x][y])
                {
                    visit[x][y] = 1;

                    go(x, y, len+1);

                    visit[x][y] = 0;
                }
            }
        }
    }
    for(i = 0; i < 4; ++i)
    {
        x = r + dx[i];
        y = c + dy[i];
        if( x >= 1 && x <= n && y >= 1 && y <= n && !visit[x][y])
        {
            ++nadj[x][y];
        }
    }
//    if(wrong)
//    {
//        //printf("WRONG:\n");
//        //printBoard();
//    }
}

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //time_t t1, t2; t1 = clock();
#else
    freopen("betsy.in","r",stdin) ;
    freopen("betsy.out", "w", stdout);
#endif
    int i, j, k;

    //scanf("%d", &ntest);

    for(itest = 1; itest <= ntest; ++itest)
    {
        scanf("%d", &n);
        for(i = 1; i <= n; ++i)
        {
            for(j = 1; j <= n; ++j)
            {
                if( (i == 1 && j == 1) ||
                        (i == n && j == n) ||
                        (i == 1 && j == n) ||
                        (i == n && j == 1)
                  )
                    nadj[i][j] = 2;
                else if(i == 1 || i == n || j == 1 || j == n)
                    nadj[i][j] = 3;
                else
                    nadj[i][j] = 4;
            }
        }
        visit[1][1] = 1;
        go(1, 1, 1);
        printf("%d\n", res);
    }

    return 0;
}

