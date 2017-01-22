// main.cpp
/*
ID: tiendao1
LANG: C++
TASK: window
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
//#include <queue>
//#include <stack>
#include <cstdlib>
// #include <climits>
// #include <functional>
// #include <ctime>
#include <cmath>
//#include <bitset>
// #include <utility>

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
const int maxn = 100000 + 5;
const int maxv = 100000 + 5;
const int maxe = 100000 + 5;
//const int root = 1;

struct Data
{
    int y, x0, x1, p;
    Data()
    {

    }
    Data(int _y, int _x0, int _x1, int _p)
    {
        y = _y;
        x0 = _x0;
        x1 = _x1;
        p = _p;
    }
    bool operator <(const Data& other) const
    {
        if(y != other.y)
            return y < other.y;
        if(p != other.p)
            return p < other.p;
        if(x0 != other.x0)
            return x0 < other.x0;
        return x1 < other.x1;
    }
};
int next[101], prev[101];
int X[66][2], Y[66][2];
int n, m;
vector<Data> vy;
vector<int> vx;

const int tail = 0;
const int head = 100;

int get_id(char x)
{
    if('0' <= x && x <= '9')
        return x - '0' + 1;
    if('a' <= x && x <= 'z')
        return 11 + x - 'a';
    return 11 + 26 + x - 'A';
}

double calc(int id)
{
    double S = (X[id][1] - X[id][0]) * (Y[id][1] - Y[id][0]);
    int C = 0;

    vx.clear();
    vy.clear();
    int i, j, k, x0, x1, y0, y1;
    for(i = id; i != head; i = next[i])
    {
        x0 = max(X[id][0], X[i][0]);
        x1 = min(X[id][1], X[i][1]);
        y0 = max(Y[id][0], Y[i][0]);
        y1 = min(Y[id][1], Y[i][1]);

        //printf("i = %d, x0, x1, y0, y1 = %d, %d, %d, %d\n", i, x0, x1, y0, y1);
        if(x0 < x1 && y0 < y1)
        {
            vy.push_back(Data(y0, x0, x1, 0));
            vy.push_back(Data(y1, x0, x1, 1));
            vx.push_back(x0);
            vx.push_back(x1);
        }
    }
    sort(ALL(vx));
    sort(ALL(vy));

    int h, open, lasty;
    for(i = 1; i < vx.size(); ++i)
    {
        //printf("------ BETWEEN %d and %d\n", vx[i-1], vx[i]);
        h = 0;
        open = 0;
        lasty = Y[id][0];
        for(j = 0; j < vy.size(); ++j)
        {
            if( vy[j].x1 <= vx[i-1] || vy[j].x0 >= vx[i] )
                continue;
            //printf("vy = (%d, %d), open = %d, h = %d\n", vy[j].y, vy[j].p, open, h);
            if(vy[j].p == 1)
            {
                if(open == 1)
                {
                    if(j == 0)
                    {
                        printf("SOMETHING WRONG!\n");
                    }
                    else h += vy[j].y - lasty;
                }
                --open;
            }
            else
            {
                if(open == 1)
                {
                    if(j == 0)
                    {
                        printf("SOMETHING WRONG!\n");
                    }
                    else h += vy[j].y - lasty;
                }
                ++open;
            }
            lasty = vy[j].y;
        }
        C += h * (vx[i] - vx[i-1]);
        //printf("FINAL: h = %d, C = %d\n", h, C);
    }

    return 100.0 * C / S;
}

void printList()
{
    puts("-------LIST--------------");
    for(int i = next[tail]; i != head; i = next[i])
    {
        printf("%d -->", i);
    }
    puts("\n---------------------");
}

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //time_t t1, t2; t1 = clock();
#else
    freopen("window.in","r",stdin) ;
    freopen("window.out", "w", stdout);
#endif
    int i, j, k;

    //scanf("%d", &ntest);
    char s[40];
    int x, y, a, b;

    next[tail] = head;
    prev[head] = tail;
    for(itest = 1; itest <= ntest; ++itest)
    {
        for(; scanf("%s", s) != EOF;)
        {
            if(s[0] == 'w')
            {
                k = get_id(s[2]);

                for(x = 0, i = 4; isdigit(s[i]); ++i)
                {
                    x = x * 10 + s[i] - '0';
                }
                for(y = 0, ++i; isdigit(s[i]); ++i)
                {
                    y = y * 10 + s[i] - '0';
                }
                for(a = 0, ++i; isdigit(s[i]); ++i)
                {
                    a = a * 10 + s[i] - '0';
                }
                for(b = 0, ++i; isdigit(s[i]); ++i)
                {
                    b = b * 10 + s[i] - '0';
                }
                if(x > a) swap(x, a);
                if(y > b) swap(y, b);
                X[k][0] = x;
                X[k][1] = a;
                Y[k][0] = y;
                Y[k][1] = b;

                i = prev[head];
                next[i] = k;
                prev[k] = i;
                next[k] = head;
                prev[head] = k;

                //cout << "i = " << i << endl;
                //cout << k << ';' << x << ' ' << y << ' ' << a << ' ' << b << endl;
            }
            else if(s[0] == 't')
            {
                k = get_id(s[2]);
                if(next[k] == head)
                    continue;

                i = prev[k];
                j = next[k];

                next[i] = j;
                prev[j] = i;

                i = prev[head];
                next[i] = k;
                prev[k] = i;
                next[k] = head;
                prev[head] = k;
            }
            else if(s[0] == 'b')
            {
                k = get_id(s[2]);

                i = prev[k];
                j = next[k];
                next[i] = j;
                prev[j] = i;

                i = next[tail];
                prev[i] = k;
                next[k] = i;
                next[tail] = k;
                prev[k] = tail;
            }
            else if(s[0] == 'd')
            {
                k = get_id(s[2]);

                i = prev[k];
                j = next[k];
                next[i] = j;
                prev[j] = i;
            }
            else
            {
                k = get_id(s[2]);
                double res = calc(k);
                printf("%.3lf\n", res);
            }

            //printList();
        }
    }

    return 0;
}
