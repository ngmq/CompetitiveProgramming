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
const int maxn = 1000 + 5;
const int maxv = 100000 + 5;
const int maxe = 1000011 + 5;

int ndigits, digits[20];
ll save_num, num;

bool isTidy(int val)
{
    int a[20], na = 0;
    while(val)
    {
        a[na] = val % 10; val /= 10;
        ++na;
    }
    reverse(a, a + na);
    for(int i = 0; i + 1 < na; ++i)
    {
        if(a[i] > a[i+1])
            return false;
    }
    return true;
}
void verify()
{
    num = save_num;
    int res = 0, i, j, k;
    for(i = 0; i < ndigits; ++i)
    {
        res = res * 10 + digits[i];
    }
    for(k = num; k >= 1; --k)
    {
        if(isTidy(k))
        {
            break;
        }
    }
    printf("res = %d, k = %d, correct = %d\n", res, k, res == k);
}

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
        ndigits = 0;
        scanf("%lld", &num); save_num = num;
        while(num > 0)
        {
            digits[ndigits] = num % 10;
            num /= 10;
            ++ndigits;
        }
        reverse(digits, digits + ndigits);
        for(i = 0; i+1 < ndigits; ++i)
        {
            if(digits[i] > digits[i+1])
            {
                break;
            }
        }
        if(i + 1 < ndigits)
        {
            if(digits[i] > 1)
            {
                k = digits[i];
                for(j = i; j >= 0; --j)
                {
                    if(digits[j] != k)
                    {
                        break;
                    }
                }
                ++j;
                digits[j]--;
                for(++j; j < ndigits; ++j) digits[j] = 9;
            }
            else
            {
                --ndigits;
                for(j = 0; j < ndigits; ++j) digits[j] = 9;
            }
        }
        printf("Case #%d: ", itest);
        for(i = 0; i < ndigits; ++i) printf("%d", digits[i]);
        puts("");

        //verify();
    }

    return 0;
}

