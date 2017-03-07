//// ngmq
//// COCI #2, 2006/2007, task STOL
//// AC on http://wcipeg.com/problem/coci062p5
//// Execution Results
//// Test case #1: AC [0.003s, 3688K] (10/10)
//// Test case #2: AC [0.003s, 3688K] (10/10)
//// Test case #3: AC [0.003s, 3688K] (10/10)
//// Test case #4: AC [0.003s, 3688K] (10/10)
//// Test case #5: AC [0.000s, 3688K] (10/10)
//// Test case #6: AC [0.003s, 3688K] (10/10)
//// Test case #7: AC [0.006s, 3688K] (10/10)
//// Test case #8: AC [0.039s, 3688K] (10/10)
//// Test case #9: AC [0.043s, 3688K] (10/10)
//// Test case #10: AC [0.036s, 3688K] (10/10)
//// 
//// Final score: 100/100
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
const int maxn = 400 + 5;
const int maxv = 5000 + 5;
const int maxe = 1000011 + 5;

int n, m;
char s[maxn][maxn];
int f[maxn][maxn] ;

//// Algorithm: go from left-to-right, top-down fashion. f[i, j, h] = w means the rectangles that have the bottom right 
//// at the square (i, j) and height has the longest width of w
//// DP: f[i, j, x] = f[i, j-1, x] + 1 for x = 1...MAXH where MAXH is height of longest consecutive '.' in vertical direction from
//// row i back to the first row
//// Update result: res = max(res, w + h)

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
	    }
	    int res = 0;
	    for(i = 1; i <= n; ++i)
	    {
		    for(j = 1; j <= m; ++j)
		    {
			   for(k = 1; k <= n; ++k) f[j][k] = 0;
			   if(s[i-1][j-1] == 'X')
				  continue;
			   int cnt = 0;
			   for(k = i; k >= 1 && s[k-1][j-1] == '.'; --k, ++cnt);
			   for(k = 1; k <= cnt; ++k)
			   {
				   f[j][k] = f[j-1][k] + 1;
				   res = max(res, f[j][k] + k);
			   }
				   
		    }
	    }

	    printf("%d\n", res*2 - 1);

    }

    return 0;
}
