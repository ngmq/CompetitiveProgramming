// main.cpp
/*
ID: tiendao1
LANG: C++
TASK: picture
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
//#include <deque>
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
const int maxn = 5000 + 5;
const int maxv = 666 + 5;
const int maxe = 100000 + 5;
//const int root = 1;

struct Data
{
    //int idx;
    int tpe;
    int val, l, r, o;
    Data(){
        tpe = val = l = r = o = 0;
    }
    bool operator <(const Data& other) const
    {
        if(val != other.val)
            return val < other.val;
        if(tpe != other.tpe)
            return tpe < other.tpe;
        if(l != other.l)
            return l < other.l;
        if(r != other.r)
            return r < other.r;
        return o < other.o;
    }
    Data(int _tpe, int _val)
    {
        tpe = _tpe;
        val = _val;
    }
     Data(int _tpe, int _val, int _l, int _r)
    {
        tpe = _tpe;
        val = _val;
        l = _l;
        r = _r;
    }
     Data(int _tpe, int _val, int _l, int _r, int _o)
    {
        tpe = _tpe;
        val = _val;
        l = _l;
        r = _r;
        o = _o;
    }
};

bool cmp(const Data& x, const Data& y)
{
    if(x.val != y.val)
        return x.val < y.val;
    if(x.tpe != y.tpe)
        return x.tpe < y.tpe;
    return x.l < y.l;
}

int n, m;
Data V[maxn + maxn], H[maxn + maxn];
int prev[maxn + maxn], next[maxn + maxn];

#define OPEN 0
#define CLOSE 1

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //time_t t1, t2; t1 = clock();
#else
    freopen("picture.in","r",stdin) ;
    freopen("picture.out", "w", stdout);
#endif
    int i, j, k;
    int x1, y1, x2, y2;

    for(itest = 1; itest <= ntest; ++itest)
    {
        scanf("%d", &n);
        for(i = j = 0; i < n; ++i, j += 2)
        {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

            //V[j].idx = i;
            V[j].tpe = OPEN;
            V[j].val = x1;
            V[j].l = y1;
            V[j].r = y2;
            V[j].o = x2;

            //H[j].idx = i;
            H[j].tpe = OPEN;
            H[j].val = y1;
            H[j].l = x1;
            H[j].r = x2;
            H[j].o = y2;

            //V[j+1].idx = i;
            V[j+1].tpe = CLOSE;
            V[j+1].val = x2;
            V[j+1].l = y1;
            V[j+1].r = y2;
            V[j+1].o = x1;

            //H[j+1].idx = i;
            H[j+1].tpe = CLOSE;
            H[j+1].val = y2;
            H[j+1].l = x1;
            H[j+1].r = x2;
            H[j+1].o = y1;
        }
        m = n + n;

        sort(V, V + m);
        sort(H, H + m);

        //for(i = 0; i < m; ++i) printf("V[%d] = %d\n", i, V[i].val);

        int L, U, nopen, l, r, tpe, val; // lower and upper bound
        int res = 0;

        set<Data> sd;
        set<Data>::iterator it;
        vector<Data> del;
        for(i = 0; i + 1 < m; ++i)
        {
            nopen = 0;
            L = V[i].val;

            x1 = V[i].l;
            x2 = V[i].r;
            y1 = V[i].val;
            y2 = V[i].o;
            if(y1 > y2) swap(y1, y2);

            sd.insert(Data(OPEN, x1, y1, y2, x2));
            sd.insert(Data(CLOSE, x2, y1, y2, x1));

            U = V[i+1].val;

            x1 = V[i+1].l;
            x2 = V[i+1].r;
            y1 = V[i+1].val;
            y2 = V[i+1].o;
            if(y1 > y2) swap(y1, y2);

            sd.insert(Data(OPEN, x1, y1, y2, x2));
            sd.insert(Data(CLOSE, x2, y1, y2, x1));

            //printf("VERTICAL, (L, U) = %d, %d\n", L, U);

            del.clear();
            for(it = sd.begin(); it != sd.end(); ++it)
            {
                l = (*it).l;
                r = (*it).r;
                tpe = (*it).tpe;
                val = (*it).val;

                //printf("(l, r, tpe, val) = %d, %d, %d, %d\n", l, r, tpe, val);

                if(l <= L && U <= r)
                {
                    if(tpe == OPEN)
                    {
                        if(nopen == 0)
                            res += U - L;
                        ++nopen;
                    }
                    else
                    {
                        if(nopen == 1)
                            res += U - L;
                        --nopen;
                    }
                }
                else if(r < U)
                {
                    del.push_back(*it);
                }
            }
            for(j = 0; j < del.size(); ++j)
            {
                sd.erase(del[j]);
            }
        }
        //printf("res = %d\n", res);
        //continue;

        sd.clear();
        for(i = 0; i + 1 < m; ++i)
        {
            nopen = 0;
            L = H[i].val;

            x1 = H[i].l;
            x2 = H[i].r;
            y1 = H[i].val;
            y2 = H[i].o;
            if(y1 > y2) swap(y1, y2);

            sd.insert(Data(OPEN, x1, y1, y2, x2));
            sd.insert(Data(CLOSE, x2, y1, y2, x1));

            U = H[i+1].val;
            x1 = H[i+1].l;
            x2 = H[i+1].r;
            y1 = H[i+1].val;
            y2 = H[i+1].o;
            if(y1 > y2) swap(y1, y2);

            sd.insert(Data(OPEN, x1, y1, y2, x2));
            sd.insert(Data(CLOSE, x2, y1, y2, x1));

            //printf("HORIZONTAL, (L, U) = %d, %d\n", L, U);

            del.clear();
            for(it = sd.begin(); it != sd.end(); ++it)
            {
                l = (*it).l;
                r = (*it).r;
                tpe = (*it).tpe;
                val = (*it).val;

                //printf("(l, r, tpe, val, nopen) = %d, %d, %d, %d, %d\n", l, r, tpe, val, nopen);

                if(l <= L && U <= r)
                {
                    if(tpe == OPEN)
                    {
                        if(nopen == 0)
                            res += U - L;
                        ++nopen;
                    }
                    else
                    {
                        if(nopen == 1)
                            res += U - L;
                        --nopen;
                    }
                }
                else if(r < U)
                {
                    del.push_back(*it);
                }
            }
            for(j = 0; j < del.size(); ++j)
            {
                sd.erase(del[j]);
            }
        }

        printf("%d\n", res);
    }

    return 0;
}
