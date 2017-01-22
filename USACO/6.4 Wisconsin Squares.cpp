// main.cpp
/*
ID: tiendao1
LANG: C++
TASK: wissqu
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

const int EMPTY = 100000;
const int FULL  = 133343;
ll INIT = 1;
ll p10[18];
map<ll, int> nway;
map<ll, ll> track;
map<ll, pii> trackp;
map<ll, char> trackc;
char board[6][6];

int get_cnt(int x, int id)
{
    return ( x / p10[ 4 - id ] ) % 10;
}
int sub_cnt(int x, int id)
{
    return x - p10[4 - id];
}
int get_digit(ll x, int pos)
{
    return ( x / p10[ 15 - pos ] ) % 10;
}
ll replace_digit(ll x, int pos, int from, int to)
{
    return x - from * p10[15 - pos] + to * p10[15 - pos];
}
char get_char(ll x, int pos)
{
    return 'A' + get_digit(x, pos);
}

bool notEqual(int r, int c, char x)
{
    if(r < 0 || r > 4 || c < 0 || c > 4)
        return true;
    return board[r][c] != x;
}

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //time_t t1, t2; t1 = clock();
#else
    freopen("wissqu.in","r",stdin) ;
    freopen("wissqu.out", "w", stdout);
#endif
    int i, j, k, t;

    p10[0] = 1;
    for(i = 1; i <= 17; ++i) p10[i] = p10[i-1] * 10;

    //scanf("%d", &ntest);

    for(itest = 1; itest <= ntest; ++itest)
    {
        char s[6];
        for(i = 0; i < 4; ++i)
        {
            scanf("%s", s);
            for(j = 0; j < 4; ++j)
            {
                INIT = INIT * 10 + (s[j] - 'A');
                //cout << s[j] << "; INIT = " << INIT << endl;
            }
        }
        //cout << "INIT = " << INIT << endl;
        nway[INIT] = 1;
        queue<ll> que;
        queue<int> quecnt;
        que.push(INIT);
        quecnt.push(FULL);

        ll num, num2;
        int cnt[5];
        int res = 0;
        int save, pos;
        bool printFirst = true;
        while( !que.empty() )
        {
            num = que.front(); que.pop();
            k = quecnt.front(); quecnt.pop();

            //cout << num << ' ' << k << endl;

            for(i = 0; i < 4; ++i)
            {
                for(j = 0; j < 4; ++j)
                {
                    board[i][j] = get_char(num, 4 * i + j);
                }
            }
            if(k == EMPTY)
            {
                if(printFirst)
                {
                    printFirst = false;
//                    for(i = 0; i < 4; ++i)
//                    {
//                        printf("%s\n", board[i]);
//                    }
                    stack<pii> stp;
                    stack<char> stc;

                    num2 = num;
                    while(num2 != INIT)
                    {
                        stp.push(trackp[num2]);
                        stc.push(trackc[num2]);
                        num2 = track[num2];
                    }
                    while(!stc.empty())
                    {
                        printf("%c %d %d\n", stc.top(), stp.top().fi + 1, stp.top().se + 1);
                        stc.pop();
                        stp.pop();
                    }
                }
                res += nway[num];
                continue;
            }
            for(i = 0; i < 5; ++i)
            {
                cnt[i] = get_cnt(k, i);
            }
            save = k;
            if(save == FULL)
            {
                // first round, choose D
                for(i = 0; i < 4; ++i)
                {
                    for(j = 0; j < 4; ++j)
                    {
                        pos = 4 * i + j;
                        k = board[i][j] - 'A';
                        if( board[i][j] != 'D' && k == get_digit(INIT, pos) )
                        {
                            if(
                                       notEqual(i-1, j, 'D') &&
                                       notEqual(i+1, j, 'D') &&
                                       notEqual(i, j-1, 'D') &&
                                       notEqual(i, j+1, 'D') &&

                                       notEqual(i-1, j-1, 'D') &&
                                       notEqual(i+1, j+1, 'D') &&
                                       notEqual(i-1, j+1, 'D') &&
                                       notEqual(i+1, j-1, 'D')

                                       )
                           {
                               t = 'D' - 'A';
                               num2 = replace_digit(num, pos, k, t);
                                if(nway[num2] == 0)
                                {
                                    que.push( num2 );
                                    quecnt.push( sub_cnt(save, t) );
                                    if(printFirst)
                                    {
                                        track[num2] = num;
                                        trackp[num2] = pii(i,j);
                                        trackc[num2] = 'D';
                                    }
                                }
                                nway[num2] += nway[num];
                           }
                        }
                    }
                }
            }
            else
            {
                //continue;
                // not first round, test from A to D
                for(int t = 0; t < 5; ++t)
                {
                    if(cnt[t] > 0)
                    {
                        for(i = 0; i < 4; ++i)
                        {
                            for(j = 0; j < 4; ++j)
                            {
                                pos = 4 * i + j;
                                k = board[i][j] - 'A';
                                if( k != t && k == get_digit(INIT, pos) )
                                {
                                    if(
                                       notEqual(i-1, j, t + 'A') &&
                                       notEqual(i+1, j, t + 'A') &&
                                       notEqual(i, j-1, t + 'A') &&
                                       notEqual(i, j+1, t + 'A') &&

                                       notEqual(i-1, j-1, t + 'A') &&
                                       notEqual(i+1, j+1, t + 'A') &&
                                       notEqual(i-1, j+1, t + 'A') &&
                                       notEqual(i+1, j-1, t + 'A')

                                       )
                                    {
                                        num2 = replace_digit(num, pos, k, t);
                                        if(nway[num2] == 0)
                                        {
                                            que.push( num2 );
                                            quecnt.push( sub_cnt(save, t) );
                                            if(printFirst)
                                            {
                                                track[num2] = num;
                                                trackp[num2] = pii(i,j);
                                                trackc[num2] = t + 'A';
                                            }
                                        }
                                        nway[num2] += nway[num];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        printf("%d\n", res);
    }

    return 0;
}

