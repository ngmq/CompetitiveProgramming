//// ngmq
//// AC on http://wcipeg.com/problem/coci065p6
//// Note: a direct application of Suffix Array. This might be a very hard problem in 2006
//// but quite trivial in 2017, thanks to the popularity of suffix array.

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
const int maxn = 200000 + 5;
const int maxv = 100000 + 5;
const int maxe = 1000011 + 5;

char s[maxn];
int n, m, gap; // m = max(n, 52)
int lcp[maxn]; // longest common prefix between sa[i] and sa[i-1]
int sa[maxn], pos[maxn], rank_sa[maxn]; // store sorted suffix indices in sa[]

void print()
{
	puts("=============");
	int i;
	for(i = 0; i < n; ++i)
	{
		printf("%d: %s ------- rank = %d\n", sa[i], s + sa[i], rank_sa[sa[i]]);
	}
}

bool cmpSuffix(int i, int j)
{
	if(rank_sa[i] != rank_sa[j])
		return rank_sa[i] < rank_sa[j];
	i += gap;
	j += gap;
	if(i < n && j < n)
		return rank_sa[i] < rank_sa[j];
	return i < j;
}

void build_SA()
{
	int i, j, k;
	for(i = 0; s[i]; ++i)
	{
		sa[i] = i;
		rank_sa[i] = s[i];

		//printf("i = %d, rank = %d\n", i, rank[i]);
	}
	//n = i;
	gap = 0;
	//sort(sa, sa + n, cmpSuffix);
	//print();

	for(gap = 1; (gap >> 1) < n; gap <<= 1)
	{
		sort(sa, sa + n, cmpSuffix);

		pos[sa[0]] = j = 0;
		// consider pos[] as a 'temporary' array that stores the new rank
		for(i = 1; i < n; ++i)
		{
			k = cmpSuffix(sa[i-1], sa[i]);
			j += k;
			pos[sa[i]] = j;
		}
		for(i = 0; i < n; ++i)
		{
			rank_sa[i] = pos[i];
		}
		if(rank_sa[sa[n-1]] == n-1)
			break;
	}
	//printf("gap = %d\n", gap);
	//print();
}
void build_LCP()
{
	int i, j, k;
	for(i = 0; i < n; ++i)
		pos[sa[i]] = i;
	int last = 0;
	for(i = 0; i < n; ++i)
	{
		if(pos[i] == 0) continue;
		j = sa[pos[i] - 1];
		for(; i + last < n && j + last < n && s[i + last] == s[j + last]; ++last);
		lcp[pos[i]] = last;
		if(last > 0) --last;
	}
}
void build()
{
	build_SA();
	build_LCP();
}

int find_longest_repeated_substring()
{
    int res = 0;
    int i;
    for(i = 1; i < n; ++i)
    {
        res = max(res, lcp[i]);
    }

    return res;
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
        scanf("%s", s);
        build();
        k = find_longest_repeated_substring();
        printf("%d\n", k);
    }

    return 0;
}

