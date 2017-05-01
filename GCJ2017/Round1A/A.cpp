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

int n, m;
char grid[33][33], save[33][33];
int cntCol[33];

struct Node
{
    char x;
    int r, c;
    Node()
    {

    }
    Node(char _x, int _r, int _c)
    {
        x = _x;
        r = _r;
        c = _c;
    }
    bool operator <(const Node& other) const
    {
        if(c != other.c)
            return c < other.c;
        return r < other.r;
    }
};


void verify()
{
    int i, j, r, c;
    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < m; ++j)
        {
            if(save[i][j] != '?' && save[i][j] != grid[i][j])
            {
                printf("WRONGGG at %d, %d, should be %c but has %c\n", i, j, save[i][j], grid[i][j]);
                return;
            }
        }
    }
    map<char, pii> start, finish;
    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < m; ++j)
        {
            char x = grid[i][j];
            if(start.count(x) == 0)
            {
                start[x] = pii(i, j);
            }
            finish[x] = pii(i, j);
        }
    }

    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < m; ++j)
        {
            char x = grid[i][j];
            int start_r, start_c, finish_r, finish_c;
            start_r = start[x].fi;
            start_c = start[x].se;
            finish_r = finish[x].fi;
            finish_c = finish[x].se;

            if(i < start_r || i > finish_r)
            {
                printf("WRONGGGG with char = %c at %d, %d, out of range\n", x, i, j);
                return;
            }
            if(j < start_c || j > finish_c)
            {
                printf("WRONGGGG with char = %c at %d, %d, out of range\n", x, i, j);
                return;
            }
        }
    }
}

int main()
{
#ifdef HOME
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    int i, j, k;

    scanf("%d", &ntest);
    int nline = 2;

    for(itest = 1; itest <= ntest; ++itest)
    {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; ++i)
        {
            scanf("%s", grid[i]);
        }

        for(i = 0; i < n; ++i)
        {
            for(j = 0; j < m; ++j)
            {
                save[i][j] = grid[i][j];
            }
        }

        ms(cntCol, 0);

        vector<Node> vn;
        int last_col = 0;
        for(i = 0; i < n; ++i)
        {
            for(j = 0; j < m; ++j)
            {
                if(grid[i][j] != '?')
                {
                    vn.push_back(Node(grid[i][j], i, j));
                    cntCol[j]++;
                    last_col = max(last_col, j);
                }
            }
        }

        sort(vn.begin(), vn.end());
        for(i = 0; i < vn.size(); ++i)
        {
            int r, c;
            char x;
            r = vn[i].r;
            c = vn[i].c;
            x = vn[i].x;
            int L = c - 1, U = r - 1;
            for(; L >= 0 && grid[r][L] == '?'; --L);
            for(; U >= 0 && grid[U][c] == '?'; --U);

            for(j = L + 1; j <= c; ++j)
            {
                for(k = U + 1; k <= r; ++k)
                {
                    grid[k][j] = x;
                }
            }
            if(c == last_col)
            {
                for(k = r; k > U; --k)
                {
                    for(j = c+1; j < m; ++j)
                    {
                        grid[k][j] = x;
                    }
                }
            }
            if(cntCol[c] == 1)
            {
                // this is the last child in this column
                // do something
                for(j = L + 1; j <= c; ++j)
                {
                    for(k = r + 1; k < n; ++k)
                    {
                        grid[k][j] = x;
                    }
                }
            }
            if(c == last_col && cntCol[c] == 1)
            {
                // last child ever!
                for(k = r + 1; k < n; ++k)
                {
                    for(j = c + 1; j < m; ++j)
                    {
                        grid[k][j] = x;
                    }
                }
            }
            --cntCol[c];
        }

        printf("Case #%d:\n", itest);
        //printf("Line = %d\n", nline);
        for(i = 0; i < n; ++i)
        {
            printf("%s\n", grid[i]);
        }

        verify();

        nline += n + 1;
    }

    return 0;
}

