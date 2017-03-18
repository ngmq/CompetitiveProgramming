//// ngmq
//COCI 2006/2007 #3 Task TROJKE
//AC on http://wcipeg.com/problem/coci063p3
//Execution Results
//Test case #1: AC [0.003s, 2948K] (10/10)
//Test case #2: AC [0.003s, 2948K] (10/10)
//Test case #3: AC [0.000s, 2948K] (10/10)
//Test case #4: AC [0.003s, 2948K] (10/10)
//Test case #5: AC [0.013s, 2948K] (10/10)
//Test case #6: AC [0.026s, 2948K] (10/10)
//Test case #7: AC [0.089s, 2948K] (10/10)
//Test case #8: AC [0.118s, 2948K] (10/10)
//Test case #9: AC [0.165s, 2948K] (10/10)
//Test case #10: AC [0.146s, 2948K] (10/10)
//
//Final score: 100/100
//Reminde me about Line Detection in Computer Vision lectures :))
//Basically the same idea: each letter votes for a Line ax + by + c = 0 with normalized (a,b)
//i.e gcd(a, b) = 1
// For lines with voted count X >= 3: answer += 3CX = X! / (3! (X-3)!) = (X-2)(X-1)X/3
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
const int maxv = 5000 + 5;
const int maxe = 1000011 + 5;

struct Line{
    int a, b, c;
    Line()
    {

    }
    Line(int _a, int _b, int _c)
    {
        a = _a;
        b = _b;
        c = _c;
        normalize();
    }
    void normalize()
    {
        if(a < 0)
        {
            a = -a;
            b = -b;
            c = -c;
        }
        else if(a == 0 && b < 0)
        {
            b = -b;
            c = -c;
        }
        int k = __gcd(__gcd(a, b), c);
        if(k < 0)
            k = -k;
        a /= k;
        b /= k;
        c /= k;
    }
    bool operator <(const Line& other) const
    {
        if(a != other.a)
            return a < other.a;
        if(b != other.b)
            return b <  other.b;
        return c < other.c;
    }
    void display() const
    {
        printf("-----------------");
        printf("(a, b, c) = %d, %d, %d\n", a, b, c);
    }
};

int n;
char s[maxn][maxn];
pii p[6100];
map<Line, int> mp;

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
        scanf("%d", &n);
        for(i = 0; i < n; ++i)
        {
            scanf("%s", s[i]);
        }
        int np = 0;
        for(i = 0; i <= n; ++i)
        {
            for(j = i; j <= n; ++j)
            {
                if(__gcd(i, j) == 1)
                {
                    //printf("%d %d\n", i, j);
                    p[np].fi = i;
                    p[np].se = j;
                    ++np;
                }
            }
        }
        for(i = 0; i < n; ++i)
        {
            for(j = 0; j < n; ++j)
            {
                if(s[i][j] != '.')
                {
                    for(k = 0; k < np; ++k)
                    {
                        int a = p[k].fi;
                        int b = p[k].se;
                        int c = -(a * i + b * j);
                        mp[Line(a, b, -(a * i + b * j))]++;
                        if(a != 0 && b != 0) mp[Line(a, -b, -(a * i + -b * j))]++;
                        if(b != a)
                        {
                            mp[Line(b, a, -(b * i + a * j))]++;
                            if(a != 0) mp[Line(b, -a, -(b * i + -a * j))]++;
                        }
                    }
                }
            }
        }
        ll res = 0;
        for(map<Line, int>::iterator it = mp.begin(); it != mp.end(); ++it)
        {
            k = (*it).se;
            if(k >= 3)
            {
                //(*it).fi.display();
                //printf("k = %d\n", k);
                res += 1LL * k * (k-2) * (k-1) / 6;
            }

        }
        printf("%lld\n", res);
    }

    return 0;
}

