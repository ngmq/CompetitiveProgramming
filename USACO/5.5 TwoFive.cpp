// main.cpp
/*
ID: tiendao1
LANG: C++
TASK: twofive
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

const int N = 25;
int n;
char s[30], a[30][30];
int f[6][6][6][6][6], lastRow[6], lastCol[6];
int used[30];

void printa()
{
    int i, j;
    for(i = 0; i < 5; ++i)
    {
        for(j = 0; j < 5; ++j)
        {
            if(a[i][j])
                putchar(a[i][j]);
            else
                putchar('*');
        }
        putchar('\n');
    }
    puts("---------------------------");
}
void build_f()
{
    int i1, i2, i3, i4, i5, sum;
    int i, j, k;
    char c;
    f[5][5][5][5][5] = 1;

    sum = 0;
    for(i1 = 5; i1 >= 0; --i1)
    {
        sum += i1;
        lastRow[0] = i1 - 1;

        for(i2 = i1; i2 >= 0; --i2)
        {
            sum += i2;
            lastRow[1] = i2 - 1;

            for(i3 = i2; i3 >= 0; --i3)
            {
                sum += i3;
                lastRow[2] = i3 - 1;

                for(i4 = i3; i4 >= 0; --i4)
                {
                    sum += i4;
                    lastRow[3] = i4 - 1;

                    for(i5 = i4; i5 >= 0; --i5)
                    {
                        sum += i5;
                        lastRow[4] = i5 - 1;

                        for(i = 0; i < 5; ++i) lastCol[i] = -1;

                        for(i = 0; i < i1; ++i) lastCol[i] = 0;
                        for(i = 0; i < i2; ++i) lastCol[i] = 1;
                        for(i = 0; i < i3; ++i) lastCol[i] = 2;
                        for(i = 0; i < i4; ++i) lastCol[i] = 3;
                        for(i = 0; i < i5; ++i) lastCol[i] = 4;

                        for(i = 0; i < 5; ++i)
                        {
                            if(lastRow[i] + 1 < 5)
                            {
                                j = lastRow[i] + 1;
                                if(lastCol[j] + 1 == i)
                                {
                                    k = sum;
                                    c = k + 'A';
                                    // place c at (i,j)
                                    f[i1][i2][i3][i4][i5] +=

                                        f[i1 + (i==0)][i2 + (i==1)][i3 + (i==2)][i4 + (i==3)][i5 + (i==4)]
                                        ;
                                }
                            }
                        }
                        sum -= i5;
                    }
                    sum -= i4;
                }
                sum -= i3;
            }
            sum -= i2;
        }
        sum -= i1;
    }
//    for(i1 = 0; i1 <= 5; ++i1)
//    {
//        for(i2 = i1 + 1; i2 <= 5; ++i2)
//        {
//            for(i3 = i2 + 1; i3 <= 5; ++i3)
//            {
//                for(i4 = i3 + 1; i4 <= 5; ++i4)
//                {
//                    for(i5 = i4 + 1; i5 <= 5; ++i5)
//                    {
//                        f[i1][i2][i3][i4][i5] = -1;
//                    }
//                }
//            }
//        }
//    }
   // printf("%d\n", f[0][0][0][0][0]);

   // printf("%d\n", f[5][5][5][4][0]);

   //printf("%d\n", f[5][5][5][2][1]);
}

int getf()
{
    int i, j, k, cnt[5], Max;

    Max = 0;
    for(i = 0; i < 5; ++i)
    {
        for(j = 0; j < 5; ++j)
        {
            Max = max(Max, a[i][j] - 'A');
        }
    }
    k = 0;
    for(i = 0; i < Max; ++i)
    {
        k += used[i] == 0;
    }
    if(k == 0)
    {
        ms(cnt, 0);
        for(i = 0; i < 5; ++i)
        {
            for(j = 0; j < 5; ++j) cnt[i] += a[i][j] != 0;
        }
        return f[cnt[0]][cnt[1]][cnt[2]][cnt[3]][cnt[4]];
    }
    else
    {
        int res = 0;
        bool ok_left, ok_up;
        for(k = 0; k < Max; ++k)
        {
            if(!used[k])
            {
                for(i = 0; i < 5; ++i)
                {
                    for(j = 0; j < 5; ++j)
                    {
                        if(a[i][j] == 0)
                        {
                            ok_left = j == 0 || (a[i][j-1] != 0 && a[i][j-1] - 'A' < k);
                            ok_up   = i == 0 || (a[i-1][j] != 0 && a[i-1][j] - 'A' < k);
                            if(ok_left && ok_up)
                            {
                                a[i][j] = k;
                                used[k] = 1;

                                res += getf();

                                a[i][j] = 0;
                                used[k] = 0;
                            }
                        }
                    }
                }
                break;
            }
        }
        return res;
    }
}

void go(int r, int c)
{
    if(r >= 5 || c >= 5)
        return;

    int nr = r, nc = c;
    if(nc + 1 < 5) ++nc;
    else
    {
        nc = 0; ++nr;
    }

    int i, j, k, sum = 0, gf;
    bool ok_left = false, ok_up = false;
    for(k = 0; k < N; ++k)
    {
        if(used[k] == 0)
        {
            ok_left = c == 0 || (a[r][c-1] != 0 && a[r][c-1] - 'A' < k);
            ok_up   = r == 0 || (a[r-1][c] != 0 && a[r-1][c] - 'A' < k);
            if(ok_left && ok_up)
            {
                a[r][c] = 'A' + k;
                used[k] = 1;
                gf = getf();
                sum += gf;

//                if(r == 3 && c == 4)
//                {
//                    printf("at (3,4) tried k,c = %d,%c, gf = %d, sum = %d\n", k, 'A' + k, gf, sum);
//                    printa();
//                }
                if(sum >= n)
                {
                    //printf("at (r,c) = (%d, %d) and n = %d, picked (k,c) = (%d,%c)\n", r, c, n, k,k+'A');
                    n -= sum - gf;
                    go(nr, nc);
                    break;
                }
                else
                {

                }
                a[r][c] = 0;
                used[k] = 0;
            }
        }
    }
    if(ok_left && ok_up)
    {

    }
    else
    {
        puts("TRY AGAIN BRO!");
    }
}
void solve_n()
{
    // given n, return s
    int i, j, k, sum;
    int last_ok, last_k;

    sum = n;
    ms(a, 0);
    ms(used, 0);

    go(0, 0);

    // final result
    k = 0;
    for(i = 0; i < 5; ++i)
        for(j = 0; j < 5; ++j)
            s[k++] = a[i][j];
}

void solve_s()
{
    // given s, return n
    // s to a
    int i, j, k, gf;
    bool ok_left, ok_up;

    ms(used, 0);
    ms(a, 0);
    n = 0;

    k = 0;
    for(i = 0; i < 5; ++i)
    {
        for(j = 0; j < 5; ++j)
        {
            for(char c = 'A'; c < s[k]; ++c)
            {
                if( used[c - 'A'] )
                    continue;

                ok_left = j == 0 || (a[i][j-1] != 0 && a[i][j-1] < c);
                ok_up   = i == 0 || (a[i-1][j] != 0 && a[i-1][j] < c);
                if(ok_left && ok_up)
                {
                    used[c - 'A'] = 1;
                    a[i][j] = c;
                    gf = getf();
                    n += gf;

                    //printf("gf = %d, n = %d\n", gf, n);
                    //printa();

                    used[c - 'A'] = 0;
                }
            }
            a[i][j] = s[k];
            used[ a[i][j] - 'A' ] = 1;
            ++k;
        }
    }
    ++n;
}

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //time_t t1, t2; t1 = clock();
#else
    freopen("twofive.in","r",stdin) ;
    freopen("twofive.out", "w", stdout);
#endif
    int i, j, k;

    //scanf("%d", &ntest);
    for(itest = 1; itest <= ntest; ++itest)
    {
        build_f();

        char Quest[4];
        scanf("%s", Quest);
        if(Quest[0] == 'N')
        {
            scanf("%d", &n);
            solve_n();
            printf("%s\n", s);
        }
        else
        {
            scanf("%s", s);
            solve_s();
            printf("%d\n", n);
        }
    }

    return 0;
}
