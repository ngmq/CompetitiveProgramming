//// ngmq
//// AC on http://wcipeg.com/problem/coi06p1

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
#include <cassert>

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
#define ms(x,val_add) memset(x, val_add, sizeof(x))
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
    "NE", "SE", "SW", "NW"
};

const ll Mod = 1000000007LL;
const int maxn = 10000 + 5;
const int maxv = 10000 + 5;
const int maxe = 2 * 200000 + 5;

int a[500000];
int main()
{
#ifdef HOME
    freopen( "input.txt", "r", stdin );
    //freopen( "output.txt", "w", stdout );
#endif

    //scanf("%d", &ntest);

    for( itest = 1; itest <= ntest; ++itest )
    {
        stack<int> st, st_cnt;
        int n;
        scanf("%d", &n);

        ll res = 0;
        for(int i = 0; i < n; ++i)
        {
            int x;
            scanf("%d", &x);
            a[i] = x;
            if(!st.empty())
            {
                while(!st.empty() && a[st.top()] < a[i])
                {
                    ++res;
                    st.pop();
                    st_cnt.pop();
                }
                if(!st.empty())
                {
                    int cur_size = st.size();
                    int val = a[st.top()];
                    if(val == a[i])
                    {
                        res += st_cnt.top();
                        if(cur_size > st_cnt.top())
                        {
                            ++res;
                        }
                    }
                    else
                    {
                        ++res;
                    }
                }
            }
            //printf("after i = %d, res = %d\n", i, res);
            if(!st.empty())
            {
                int val = a[st.top()];
                int cnt = st_cnt.top();

                st.push(i);
                if(a[i] == val)
                {
                    cnt++;
                }
                else cnt = 1;
                st_cnt.push(cnt);
            }
            else
            {
                st.push(i);
                st_cnt.push(1);
            }

        }
        printf("%lld\n", res);
    }

    return 0;
}

