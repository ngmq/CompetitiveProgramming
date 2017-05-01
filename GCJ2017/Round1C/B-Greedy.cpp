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

const int Cameron = 0;
const int James = 1;
const int LAST = 1440;

struct Task
{
    int b, e, p; // start, end, person
    Task()
    {

    }
    bool operator <(const Task& other) const
    {
        if(b != other.b)
            return b < other.b;
        if(e != other.e)
            return e < other.e;
        return p < other.p;
    }
};

bool cmp(const Task& a, const Task& b)
{
    if(a.e - a.b != b.e - b.b)
        return a.e - a.b < b.e - b.b;
    return a.p > b.p;
}

typedef Task Interval;

int n, m;
Task a[222];
int idfix[1444], timeToDo[2];
Interval b[222];

int main()
{
#ifdef HOME
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    int i, j, k;

    scanf("%d", &ntest);

    for(itest = 1; itest <= ntest; ++itest)
    {
        // reset
        ms(idfix, -1);
        timeToDo[Cameron] = timeToDo[James] = 720;

        // read
        scanf("%d %d", &n, &m);
        if(n + m == 0)
        {
            puts("2");
            continue;
        }
        for(i = 1; i <= n; ++i)
        {
            scanf("%d %d", &a[i].b, &a[i].e);
            a[i].p = James;
        }
        for(i = 1; i <= m; ++i)
        {
            scanf("%d %d", &a[n+i].b, &a[n+i].e);
            a[n+i].p = Cameron;
        }
        sort(a + 1, a + 1 + n + m);

        int diff = a[1].b;
        for(i = 1; i <= n + m; ++i)
        {
            a[i].b -= diff;
            a[i].e -= diff;
        }
        if(a[1].p == James)
        {
            for(i = 1; i <= n + m; ++i)
            {
                a[i].p ^= 1; // to make the start one is always Cameron
            }
        }
        for(i = 1; i <= n + m; ++i)
        {
            for(j = a[i].b; j < a[i].e; ++j)
            {
                idfix[j] = a[i].p;
            }
            timeToDo[a[i].p] -= a[i].e - a[i].b;

            //printf("a[%d] = %d, %d and %d\n", i, a[i].b, a[i].e, a[i].p);
        }

        //printf("timeToDo = %d, %d\n", timeToDo[Cameron], timeToDo[James]);

        //for(i = 0; i <= LAST - 1; ++i) printf("idfix[%d] = %d\n", i, idfix[i]);

        for(i = 1; i + 1 <= n + m; ++i)
        {
            b[i].p = a[i].p == a[i+1].p;
            b[i].p = (1<<b[i].p) | a[i].p;
            b[i].b = a[i].e;
            b[i].e = a[i+1].b;
        }
        b[n+m].p = a[n+m].p == a[1].p;
        b[i].p = (1<<b[i].p) | a[n+m].p;
        b[n+m].b = a[n+m].e;
        b[n+m].e = LAST;

        sort(b + 1, b + 1 + n + m, cmp);

        //for(i = 0; i <= LAST - 1; ++i) printf("idfix[%d] = %d\n", i, idfix[i]);

        for(i = 1; i <= n + m; ++i)
        {
            //printf("b[%d] = %d, %d and %d\n", i, b[i].b, b[i].e, b[i].p);
            if(b[i].p & 2)
            {
                k = b[i].p & 1;
                if( b[i].e - b[i].b <= timeToDo[k] )
                {
                    timeToDo[k] -= b[i].e - b[i].b;
                    for(j = b[i].b; j < b[i].e; ++j)
                    {
                        idfix[j] = k;
                    }
                }
            }
        }
//        for(i = 1; i <= n + m; ++i)
//        {
//            printf("b[%d] = %d, %d and %d\n", i, b[i].b, b[i].e, b[i].p);
//            if((~b[i].p) & 2)
//            {
//                k = b[i].p & 1;
//                if( b[i].e - b[i].b <= timeToDo[k] )
//                {
//                    timeToDo[k] -= b[i].e - b[i].b;
//                    for(j = b[i].b; j < b[i].e; ++j)
//                    {
//                        idfix[j] = k;
//                    }
//                }
//                else if( b[i].e - b[i].b <= timeToDo[k^1] )
//                {
//                    timeToDo[k^1] -= b[i].e - b[i].b;
//                    for(j = b[i].b; j < b[i].e; ++j)
//                    {
//                        idfix[j] = k^1;
//                    }
//                }
//            }
//        }
        idfix[LAST] = idfix[0];

        int res = 0;
        for(i = 0; i <= LAST - 1; ++i)
        {
            if(idfix[i] != idfix[i+1])
            {
                if(idfix[i] != -1 && idfix[i+1] != -1)
                    ++res;
                else if(idfix[i+1] == -1)
                {
                    for(j = i + 1; j <= LAST && idfix[j] == -1; ++j);

                    if(idfix[i] == idfix[j])
                    {
                        res += 2;
                    }
                    else
                    {
                        res += 1;
                    }
                    i = j-1;
                }
            }

        }
        printf("Case #%d: %d\n", itest, res);
    }

    return 0;
}

