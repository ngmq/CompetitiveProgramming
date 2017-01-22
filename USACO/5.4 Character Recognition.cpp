// main.cpp
/*
ID: tiendao1
LANG: C++
TASK: charrec
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
const int maxn = 222 + 5;
const int maxv = 666 + 5;
const int maxe = 100000 + 5;
//const int root = 1;

const int oo = 1200 * 21 * 21 + 1;
const int maxdiff = 120; // 20 * 20 * 3/10 = 400 * 3 / 10 = 120
const int N = 27;
const int m = 540;

char sample[540][20], img[27][21][21];
char txt[1200][21];
int diff[1200+22][540], cntDiff[1200+22][27][21];
int n, f[1201], track[1201], track_char[1201];

void readFont()
{
    int i, j, k;
    string line;
    ifstream font("font.in");
    getline(font, line);
    i = k = 0;
    int tline = 0;
    while(getline(font, line))
    {
        for(j = 0; j < line.size(); ++j)
        {
            sample[tline][j] = line[j];
            img[i][k][j] = line[j];
        }
        ++tline;
        ++k;
        if(k == 20)
        {
            ++i;
            k = 0;
        }
    }
    //printf("%d\n", i);
    font.close();
}

void readTxt()
{
    int i, j, k;
    scanf("%d", &n);

    for(i = 0; i < n; ++i)
    {
        scanf("%s", txt[i]);
    }
}

void buildDiff()
{
    int i, j, k;
    for(i = 0; i < n+20; ++i)
    {
        for(j = 0; j < m; ++j)
        {
            if(i >= n)
            {
                diff[i][j] = oo;
                continue;
            }
            diff[i][j] = 0;
            for(k = 0; k < 20; ++k)
            {
                diff[i][j] += txt[i][k] != sample[j][k];
            }
        }
    }
    for(i = n+20; i >= 0; --i)
    {
        for(j = 0; j < N; ++j)
        {
            cntDiff[i][j][0] = 0;
            for(k = 1; k <= 20; ++k)
            {
                if(i >= n)
                {
                    cntDiff[i][j][k] = oo;
                }
                else
                {
                    cntDiff[i][j][k] = cntDiff[i+1][j][k-1] + diff[i][j * 20 + 20-k];
//                    if(j == 1 && cntDiff[i][j][k] < oo && i + k == 20)
//                    {
//                        printf("cntDiff[%d, %d, %d] = %d, prev = %d\n", i, j, k, cntDiff[i][j][k], cntDiff[i+1][j][k-1]);
//                    }
                }
            }
//            if(i == 0)
//            {
//                if(j == 1 || j == 19)
//                {
//                    printf("K=20, cntDiff = %d\n", cntDiff[i][j][20]);
//                    for(k = 0; k < 20; ++k)
//                        printf("%s\n", txt[i+k]);
//                }
//            }
        }
    }
    //cout << cntDiff[0][1][19] << endl;
}

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //time_t t1, t2; t1 = clock();
#else
    freopen("charrec.in","r",stdin) ;
    freopen("charrec.out", "w", stdout);
#endif
    int i, j, k;

    int tmp, curDiff, line;
    for(itest = 1; itest <= ntest; ++itest)
    {
        readFont();
        readTxt();
        buildDiff();
        // dp
        for(i = n - 1; i >= 0; --i)
        {
            f[i] = oo;
            track[i] = track_char[i] = -1;
            // try '?'
//            if(i + 20 <= n)
//            {
//                f[i] = 20 * 20 + f[i+20];
//                track[i] = i + 20;
//                track_char[i] = -1;
//            }
            for(j = 0; j < N; ++j)
            {
                // missing
                curDiff = 0;
                for(line = 1; line <= 20 && curDiff < oo; ++line)
                {
                    // missing line is line-th
                    if(curDiff + cntDiff[i+line-1][j][20-line] <= maxdiff)
                    {
                        tmp = curDiff + cntDiff[i+line-1][j][20-line] + f[i+19];
                        if(f[i] > tmp)
                        {
                            f[i] = tmp;
                            track[i] = i + 19;
                            track_char[i] = j;
//                            if(i == 0 && j == 4 && tmp == 65)
//                            {
//printf("i = 0, j = 4 -------------> line = %d, curDiff = %d, cntDiff = %d\n", line, curDiff, cntDiff[i+line-1][j][20-line]);
//                            }
                        }
                    }
                    curDiff += diff[i+line-1][j*20 + line - 1];
//                    if(i == 0 && j == 4)
//                    {
//                        printf("after line = %d, diff = %d\n", line, curDiff);
//                    }
                }
                //if(i == 0) printf("missing, f = %d, after j = %d, track char = %d\n", f[i], j, track_char[i]);
                // equal
                curDiff = cntDiff[i][j][20];
                if(curDiff <= maxdiff)
                {
                    tmp = curDiff + f[i + 20];
//                    if(i == 0)
//                    {
//                        printf("j = %d, curDiff = %d, f[i+20] = %d, tmp = %d\n", j, curDiff, f[i+20], tmp);
//                    }
                    if(f[i] > tmp)
                    {
                        f[i] = tmp;
                        track[i] = i + 20;
                        track_char[i] = j;
                    }
                }
                //if(i == 550) printf("equal, f = %d, after j = %d, tack char = %d\n", f[i], j, track_char[i]);
                // duplicated
                curDiff = 0;
                for(line = 1; line <= 20 && curDiff < oo; ++line)
                {
                    // duplicated line is line-th
                    if(curDiff + min(diff[i+line-1][j*20 + line-1], diff[i+line][j*20+line-1]) + cntDiff[i+line+1][j][20-line] <= maxdiff)
                    {
                        tmp = curDiff + min(diff[i+line-1][j*20 + line-1], diff[i+line][j*20+line-1]) + cntDiff[i+line+1][j][20-line] + f[i+21];
                        if(f[i] > tmp)
                        {
                            f[i] = tmp;
                            track[i] = i + 21;
                            track_char[i] = j;
                        }
                    }
                    curDiff += diff[i+line-1][j*20 + line - 1];
                }
                //if(i == 0) printf("duplicated, f = %d, after j = %d, tack char = %d\n", f[i], j, track_char[i]);
            }
        }
        //printf("%d %d %d\n", f[0], track[0], track_char[0]);
        //printf("%d %d %d\n", f[track[0]], track[track[0]], track_char[ track[0] ]);
        //for(i = 0; i <= n; ++i) printf("dp[%d] = %d\n", i, f[i] < oo ? f[i] : -1);

        i = 0;
        while(i < n)
        {
            //printf("i = %d; char = ", i);
            if(track_char[i] == -1)
            {
                putchar('?');
            }
            else if(track_char[i] == 0)
            {
                putchar(' ');
            }
            else printf("%c", track_char[i] + 'a' - 1);

            //puts("");
            i = track[i];
            if(i == -1)
            {
                puts("SOMETHING WRONG!");
                break;
            }
        }
        printf("\n");
    }

    return 0;
}
