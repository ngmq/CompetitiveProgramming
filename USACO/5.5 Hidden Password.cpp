// main.cpp
/*
ID: tiendao1
LANG: C++
TASK: hidden
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

int n;
string s;
char min_char;
vector<int> beg; // begin

int min_cyclic_shift()
{
    int m = beg.size();
    if(m == 1 || m == n)
        return beg[0];

    //printf("m = %d\n", m);
    int i1 = 0, i2 = 1;
    int i, j, k;

    k = 0;
    int ret = beg[0];
    char c1, c2;
    for(;k < n;)
    {
        i = beg[i1];
        j = beg[i2];
        c1 = s[i+k];
        c2 = s[j+k];

        //cerr << i1 << "; " << i2 << "; " << k << endl;

        //printf("i1 = %d, i2 = %d, i = %d, j = %d, k = %d, (c1, c2) = %c, %c\n", i1, i2, i, j, k, c1, c2);
        if(c1 == c2)
        {
            ++k;
            if(k == n)
                break;
        }
        else if(c1 < c2)
        {
            while(i2 < m && beg[i2] < j+k)
            {
                ++i2;
            }
            if(i2 == m)
                break;
            k = 1;
        }
        else
        {
            k = 1;
            i1 = i2;
            while(i2 < m && beg[i2] < j+k)
            {
                ++i2;
            }
            if(i2 == m)
                break;
        }
    }
    ret = beg[i1];
    return ret;
}
int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //time_t t1, t2; t1 = clock();
#else
    freopen("hidden.in","r",stdin) ;
    freopen("hidden.out", "w", stdout);
#endif
    int i, j, k;

    //scanf("%d", &ntest);
    for(itest = 1; itest <= ntest; ++itest)
    {
        cin >> n;
        string t;

        while(getline(cin, t))
        {
            cin >> t;
            s += t;
        }

        //cout << s << endl;
        s += s;

        for(i = 0; i < n; ++i)
        {
            s[n+i] = s[i];
        }
        min_char = 'z';
        for(i = 0; i < n; ++i)
            min_char = min(min_char, s[i]);

        beg.clear();
        for(i = 0; i < n; ++i)
        {
            if(min_char == s[i])
            {
                beg.push_back(i);
            }
        }
        int res = min_cyclic_shift();
        printf("%d\n", res);
    }

    return 0;
}
