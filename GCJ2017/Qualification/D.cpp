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

const int GRASS = 0;

int n, m;
int grid[111][111], original[111][111];
map<int, bool> diag1, diag2, topdown, leftright;

int get_diag1(int r, int c)
{
    return r - c;
}

int get_diag2(int r, int c)
{
    return r + c;
}

int get_topdown(int r, int c)
{
    return c;
}
int get_leftright(int r, int c)
{
    return r;
}

int main()
{
#ifdef HOME
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif
    int i, j, k;

    scanf("%d", &ntest);

    for(itest = 1; itest <= ntest; ++itest)
    {
        diag1.clear();
        diag2.clear();
        topdown.clear();
        leftright.clear();
        ms(grid, GRASS);

        scanf("%d %d", &n, &m);
        int r, c, d1, d2, td, lr;
        char s[3];
        for(i = 0; i < m; ++i)
        {
            scanf("%s %d %d", &s, &r, &c);
            d1 = get_diag1(r, c);
            d2 = get_diag2(r, c);
            td = get_topdown(r, c);
            lr = get_leftright(r, c);

            if(s[0] == '+')
            {
                grid[r][c] = 2;
                diag1[d1] = true;
                diag2[d2] = true;
            }
            if(s[0] == 'x')
            {
                grid[r][c] = 1;
                topdown[td] = true;
                leftright[lr] = true;
            }
            if(s[0] == 'o')
            {
                grid[r][c] = 3;
                diag1[d1] = true;
                diag2[d2] = true;
                topdown[td] = true;
                leftright[lr] = true;
            }
        }
        for(r = 1; r <= n; ++r)
        {
            for(c = 1; c <= n; ++c)
            {
                original[r][c] = grid[r][c];
            }
        }
        int res = 0;
        for(r = 1; r <= n; ++r)
        {
            for(c = 1; c <= n; ++c)
            {
                td = get_topdown(r, c);
                lr = get_leftright(r, c);
                if(topdown[td] == false && leftright[lr] == false)
                {
                    // put 'x' at (r,c)
                    topdown[td] = true;
                    leftright[lr] = true;
                    grid[r][c] += 1;
                }
            }
        }
        for(i = 1; i <= n; ++i)
        {
            r = 1;
            c = i;
            //d1 = get_diag1(r, c);
            d2 = get_diag2(r, c);
            if(diag2[d2] == false)
            {
                for(j = 0; r + j <= n && c - j >= 1; ++j)
                {
                    d1 = get_diag1(r + j, c - j);
                    if(diag1[d1] == false && diag2[d2] == false)
                    {
                        diag1[d1] = true;
                        diag2[d2] = true;
                        grid[r + j][c - j] += 2;

                        //printf("put + at %d, %d\n", r + j, c - j);
                        //break;
                    }
                }
            }

            r = n;
            c = n - i + 1;
            //d1 = get_diag1(r, c);
            d2 = get_diag2(r, c);
            if(diag2[d2] == false)
            {
                for(j = 0; r - j >= 1 && c + j <= n; ++j)
                {
                    d1 = get_diag1(r - j, c + j);
                    if(diag1[d1] == false && diag2[d2] == false)
                    {
                        diag1[d1] = true;
                        diag2[d2] = true;
                        grid[r - j][c + j] += 2;

                        //printf("put + at %d, %d\n", r - j, c + j);
                        //break;
                    }
                }
            }
        }

//        for(int i = 1; i <= n; i++) {
//    		for(int j = 1; j <= i; j++) {
//
//    			r = j;
//    			c = i - j + 1;
//                d1 = get_diag1(r, c);
//                d2 = get_diag2(r, c);
//    			//cout << "put + at " << r << ", " << c << ", " << endl;
//    			if(!diag1[d1] && !diag2[d2]) {
//    				diag1[d1] = true;
//    				diag2[d2] = true;
//    				grid[r][c] += 2;
//                }
//
//    			r = n - j + 1;
//    			c = n - i + j;
//    			d1 = get_diag1(r, c);
//    			d2 = get_diag2(r, c);
//    			//cout << "put + at " << r << ", " << c << endl;
//    			if(!diag1[d1] && !diag2[d2]) {
//    				diag1[d1] = true;
//    				diag2[d2] = true;
//    				grid[r][c] += 2;
//                }
//    		}
//    	}


        vector<pair<char, pii> > vres;
        for(r = 1; r <= n; ++r)
        {
            for(c = 1; c <= n; ++c)
            {
                if(grid[r][c] == GRASS)
                    continue;
//                if(grid[r][c] > 3)
//                {
//                    puts("!!!!! WRONG !!!!!");
//                }
                res += grid[r][c] == 3 ? 2 : 1;
                if(original[r][c] != grid[r][c])
                {
                    char ss = grid[r][c] == 3 ? 'o' : (grid[r][c] == 2 ? '+' : 'x');
                    vres.push_back(pair<char, pii>(ss, pii(r, c)));
                }
            }
        }
        printf("Case #%d: %d %d\n", itest, res, vres.size());
        for(i = 0; i < vres.size(); ++i)
        {
            printf("%c %d %d\n", vres[i].fi, vres[i].se.fi, vres[i].se.se);
        }
    }

    return 0;
}

