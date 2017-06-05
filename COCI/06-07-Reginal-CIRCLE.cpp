//// ngmq
//// AC on http://wcipeg.com/problem/coci067p4

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
const int maxv = 100000 + 5;
const int maxe = 1000011 + 5;

int n, K, a[maxn];

void printArr(int* arr)
{
    for(int i = 0; i < n; ++i) printf("%d ", arr[i]);
    puts("");
}

bool isValid(int* arr)
{
    int k = 0;
    for(int i = 0; i < n; ++i) k ^= arr[i];
    return k == 0;
}

bool isEqual(int* arr, int* brr)
{
    for(int i = 0; i < n; ++i)
    {
        bool tmp = true;
        for(int k = 0; k < n; ++k)
        {
            if( arr[ (i + k) % n ] != brr[k] )
            {
                tmp = false;
                break;
            }
        }
        if(tmp) return true;
    }
    return false;
}

void goForward(int* arr)
{
    arr[n] = arr[0];
    for(int i = 0; i < n; ++i)
    {
       arr[i] = arr[i] ^ arr[i+1];
    }
}

int res = 0;

bool goBackwardOneStep(int* brr, int firstVal = 0)
{
    int a0, anext;
    a0 = firstVal;
    anext = a0 ^ brr[0];

    for(int i = 1; i <= n-2; ++i)
    {
        anext = anext ^ brr[i];
    }

    if(anext ^ brr[n-1] != a0) return false;

    int arr[maxn];

    arr[0] = firstVal;
    for(int i = 1; i <= n-1; ++i)
    {
        arr[i] = arr[i-1] ^ brr[i-1];
    }
    for(int i = 0; i < n; ++i) brr[i] = arr[i];
    return true;
}

void goBackward(int* arr, int cnt)
{
    if(cnt == 0)
    {
        ++res;
        return;
    }
    int b[maxn], c[maxn];
    for(int i = 0; i < n; ++i) b[i] = c[i] = arr[i];
    bool tmp1 = goBackwardOneStep(b, 0);
    bool tmp2 = goBackwardOneStep(c, 1);
    bool isBC = isEqual(b, c);

    if(tmp1)
    {
        goBackward(b, cnt - 1);
    }
    if(tmp2 && !isBC)
    {
        goBackward(c, cnt - 1);
    }
}


int main()
{
#ifdef HOME
    freopen( "input.txt", "r", stdin );
    freopen( "output.txt", "w", stdout );
#endif

    //scanf("%d", &ntest);

    for( itest = 1; itest <= ntest; ++itest )
    {
        scanf("%d %d", &n, &K);
        char s[maxn];
        scanf("%s", &s);

        for(int i = 0; i < n; ++i)
        {
            if(s[i] == 'W')
                a[i] = 1;
            else
                a[i] = 0;
        }

        for(int i = 0; i < K; ++i) goForward(a);

//        printf("======= FINAL =======");
//        printArr(a);

        goBackward(a, K);
        printf("%d\n", res);
    }

    return 0;
}

