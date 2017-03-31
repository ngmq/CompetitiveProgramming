//// ngmq
//// COCI 2006/2007 #4, task JOGURT
//// AC on http://wcipeg.com/problem/coci064p5
////Execution Results
////Test case #1: AC [0.003s, 3824K] (10/10)
////Test case #2: AC [0.003s, 3824K] (10/10)
////Test case #3: AC [0.003s, 3824K] (10/10)
////Test case #4: AC [0.000s, 3824K] (10/10)
////Test case #5: AC [0.003s, 3824K] (10/10)
////Test case #6: AC [0.003s, 3824K] (10/10)
////Test case #7: AC [0.003s, 3824K] (10/10)
////Test case #8: AC [0.006s, 3824K] (10/10)
////Test case #9: AC [0.006s, 3824K] (10/10)
////Test case #10: AC [0.006s, 3824K] (10/10)
////
////Final score: 100/100
//// Algorithm: note that this solution is different from coci's solution. It does not construct
//// tree of depth n from tree of depth n-1 but build tree of depth n directly from 1, 2, 3,...2^n-1 numbers.
//// Foremost, we observe that it is always possible to have the right sub-tree greater than the left sub-tree.
//// Consider the root of the tree. First we can have the sum of leaves of its right sub-tree larger than
//// the leaves of its left sub-tree by an amount of 2^(n-2) (in a from of deposit). We do so by assigning all even
//// numbers from the set of first 2^(n-1) to right leaves and all odd numbers from the same set to left leaves.
//// for example if n = 4 we have on the right leaves: {2, 4, 6, 8} and on the left: {1, 3, 5, 7}.
//// We can use other nodes to gradually "deposit" from the right tree to the left, until the right only differ by 1
//// To make it symmetric: {1 5 3 7 | 2 6 4 8}
//// Other examples: n = 5, the leaves are
//// {1 9 5 13 3 11 7 15 | 2 10 6 141 4 12 8 16}
//// Notice that we need to assign the first 2^(n-1) to the last level, next 2^(n-2) to the second-to-last level and so on
//// Until the root = 2^n - 1.
//// All levels are arranged in big-to-small order except for the last level (remember that we need to "deposit" from right to left).


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
const int maxn = 40000 + 5;
const int maxv = 100000 + 5;
const int maxe = 1000011 + 5;

int n, V;
int idx[maxn], a[maxn], b[maxn], Lnode[maxn], Rnode[maxn];

void printTree(int node)
{
    if(node <= 0)
        return;
    if(node != V)
        printf(" ");
    printf("%d", node);
    printTree(Lnode[node]);
    printTree(Rnode[node]);
}

void build_leaves(int sz, int beg, int level)
{
    if(sz == 1)
    {
        a[1] = 1 + (1<<(n-2));
        return;
    }
    build_leaves(sz / 2, beg + (1<<level), level + 1);
    for(int i = 0; i < sz; ++i)
    {
        a[i + sz] = a[i] + beg - 1;
    }
}


int sum[maxn];
void calc(int node)
{
    if(node <= 0)
        return;
    sum[node] = node;
    int ln = Lnode[node], rn = Rnode[node];

    calc(ln);
    calc(rn);
    sum[node] += sum[ln] + sum[rn];
}
void verify(int node, int level)
{
    if(node <= 0 || level == n-1)
        return;

    int ln = Lnode[node], rn = Rnode[node];
    if( sum[rn] - sum[ln] != (1<<level) )
    {
        printf("!!! WRONG at node = %d, level = %d, expected = %d, rn = %d, ln = %d, sum[rn] = %d, sum[ln] = %d\n", node, level, (1<<level), rn, ln, sum[rn], sum[ln]);
    }
    verify(ln, level + 1);
    verify(rn, level + 1);

}


int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int i, j, k;

    //scanf("%d", &ntest);

    for(itest = 1; itest <= ntest; ++itest)
    {
        scanf("%d", &n);
        if(n == 1)
        {
            puts("1");
            break;
        }
        V = (1<<n) - 1;

        a[0] = 1;
        build_leaves(1<<(n-2), 2, 0);
//        for(i = 0; i < (1<<(n-1)); ++i)
//        {
//            printf("%d ", a[i]);
//        }


        int last_val = 1<<(n-1);
        for(i = n - 2; i >= 0; --i)
        {
            for(j = 0; j < (1<<(i+1)); j += 2)
            {
                b[j / 2] = a[j];
            }
            int hi = last_val + (1<<i);
            for(j = 0; j < (1<<i); ++j)
            {
                k = hi + 1 - b[j];
                if(i == n-2)
                {
                    Lnode[k] = a[j*2];
                    Rnode[k] = a[j*2 + 1];
                }
                else
                {
                    Lnode[k] = last_val + 1 - a[j*2];
                    Rnode[k] = last_val + 1 - a[j*2 + 1];
                }
            }
            for(j = 0; j < (1<<i); ++j)
            {
                a[j] = b[j];
            }
            last_val = hi;
        }

        printTree(V);
    }

    return 0;
}

