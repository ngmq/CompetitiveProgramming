// main.cpp
/*
ID: tiendao1
LANG: C++
TASK: vans
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
//#include <stack>
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

/*
We can view a rectangle as the combination of 4 shapes, each shape consists of multiple line segment of length 1
follows either row or column
- First shape: starts at (row=1,col=1) ends at (row=4,col=1)
- Second shape: starts at (row=4,col=1) ends at (row=4,col=N)
- Third shape: starts at (row=4,col=N) ends at (rows=1,col=N)
- Fourth shape: starts at (row=1,col=N) ends at (rows=1,col=1)

The 1st shape looks like this:
|
----
   |
----
|

The 3rd shape mirrors the 1st one

We count how many ways to fill the rest of rectangle with 2nd and 4th shape
*/
struct BigNumber
{
    BigNumber()
    {
        len = 1;
        ms(num, 0);
    }
    int len;
    char num[1000];
    BigNumber operator =(BigNumber a)
    {
        len = a.len;
        for(int i = 0; i < len; ++i)
        {
            num[i] = a.num[i];
        }
        return *this;
    }
    void output()
    {
        for(int i=len-1;i>=0;i--)
        {
            printf("%d",num[i]);
        }
        printf("\n");
    }
};

BigNumber operator +(BigNumber a, BigNumber b)
{
    BigNumber c;
    memset(c.num,0,sizeof(c.num));
    int maxLen=max(a.len,b.len);
    for(int i=0;i<maxLen;i++)
    {
        c.num[i]+=a.num[i]+b.num[i];
        if(c.num[i]>9)
        {
            c.num[i+1]++;
            c.num[i]-=10;
        }
    }
    if(c.num[maxLen])
    {
        c.len=maxLen+1;
    }
    else
    {
        c.len=maxLen;
    }
    return c;
}

BigNumber f[1005], sumf[1005], res;

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //time_t t1, t2; t1 = clock();
#else
    freopen("vans.in","r",stdin) ;
    freopen("vans.out", "w", stdout);
#endif
    int i, j, k;

    //scanf("%d", &ntest);
    for(itest = 1; itest <= ntest; ++itest)
    {
        int n;

        scanf("%d", &n);

        //f[0] = 1;
        //f[1] = 0;
        f[0].len = 1; f[0].num[0] = 1;
        f[2].len = 1; f[2].num[0] = 3;
        f[3].len = 1; f[3].num[0] = 4;

        BigNumber sum, last;
        last = f[0] + f[0];
        for(i = 4; i <= n; ++i)
        {
            sum  = sum + f[i-4];
            last = last + f[i-3] + f[i-3] + sum;
            f[i] = f[i] + f[i-2] + f[i-2] + f[i-2];
            f[i] = f[i] + last + last;

//          f[i] = f[i-2]
//            for(j = 2; j <= i; ++j)
//            {
//                f[i] += 2*(j-1)*f[i-j];
//            }
        }
        sumf[0] = f[0];
        for(i = 1; i <= n; ++i)
            sumf[i] = sumf[i-1] + f[i];

//        for(i = 1; i <= n - 1; ++i)
//        {
//            for(j = i + 1; j <= n; ++j)
//            {
//                k = (j-1) - (i+1) + 1; // j - i - 1
//
//                res = res + f[k];
//
//                printf("i = %d, j = %d, k = %d, f = %lld\n", i, j, k, f[k]);
//            }
//        }

        for(i = 2; i <= n; ++i)
        {
            res = res + sumf[i-2];
        }
        res = res + res;
        res.output();
        //printf("%lld\n", res * 2);
    }


    return 0;
}
