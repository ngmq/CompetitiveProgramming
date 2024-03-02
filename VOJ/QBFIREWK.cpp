// ngmq. ACed on SPOJ and VOJ on March 1st 2024
// Solution: Dynamic Programming + Burnside Lemma + Lyndon Factorization
// g++ main.cpp -std=c++17 -Wshadow -Wall -o main -O2 -Wno-unused-result -Wextra -Wno-sign-conversion -DHOME
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define data quandata
#define next quannext
#define prev quanprev
#define visit quanvisit
#define PI acos(-1)
#define inf 1e9
#define linf 1e18
#define EPS 1e-10
#define pii pair<int, int>
#define piii pair<int, pair<int, int>>
#define pli pair<long long, int>
#define pll pair<long long, long long>
#define pdi pair<double, int>
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) \
	sort(all(x));      \
	x.erase(unique(all(x)), x.end());
#define dbg(x)                            \
	do                                    \
	{                                     \
		cout << #x << " = " << x << endl; \
	} while (0)
#define mp(x, y) make_pair(x, y)
template <class T>
bool ckmin(T &a, const T &b)
{
	return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckminMinus1(T &a, const T &b)
{
	return (b < a || a == -1) ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b)
{
	return a < b ? a = b, 1 : 0;
}
template<typename T>
T random(T range_from, T range_to) {
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<T>    distr(range_from, range_to);
    return distr(generator);
}

bool exitInput = false;
int ntest = 1, itest = 1;

const int dx[4] =
	{
		-1, 0, 1, 0};
const int dy[4] =
	{
		0, 1, 0, -1};

void addMod(ll &x, ll y, ll Mod)
{
	x = (x + y % Mod) % Mod;
}

ll modPow(ll x, ll p, ll Mod)
{
	if (p == 0)
		return 1;
	ll r = modPow(x, p / 2, Mod);
	r = (r * r) % Mod;
	if (p & 1)
		r = (r * x) % Mod;
	return r;
}

ll modInversePrime(ll x, ll Mod)
{
	// return 1/x mod Mod
	return modPow(x, Mod - 2, Mod);
}

ll cleanMod(ll x, ll Mod)
{
	return (x % Mod + Mod) % Mod;
}

// copy BigInt from Um_nik
// using Int = __int128;
// Int gcd( Int x, Int y )
// {
// 	return y == 0 ? x : gcd( y, x % y );
// }
// void printInt( Int x )
// {
// 	if ( x == 0 )
// 	{
// 		cout << 0; //printf("0");
// 		return;
// 	}
// 	vector<int> w;
// 	while( x > 0 )
// 	{
// 		w.push_back( x % 10 );
// 		x /= 10;
// 	}
// 	reverse( all( w ) );
// 	for ( int z : w )
// 		cout << z; //printf("%d", z);
// }
// void printAns(Int p, Int q) {
// 	Int g = gcd(p, q);
// 	p /= g;
// 	q /= g;
// 	printInt(p);
// 	cout << "/";
// 	printInt(q);
// 	cout << endl;
// }

ll xgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = xgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

ll gcd(ll p, ll q)
{
	return __gcd(p, q);
}

ll modInverse(ll a, ll m)
{
	assert(gcd(a, m) == 1);
	ll x, y;
	ll d = xgcd(a, m, x, y);
	assert(d == 1);
	return (x % m + m) % m;
}

ll lcm(ll x, ll y)
{
	return x * y / gcd(x, y);
}

/*** CODE START HERE ***/
const ll Mod =  (ll)(1e9 + 7);
const int maxn = 200 + 5;

int n, N, m, K, C;
int A[66], a[66], hasC[66];
int cnt_gcd[66][66];
long long f0[66][33][33], f1[66][33][33], f2[66][33][33];
long long f0beg[66][33], f1beg[66][33], f2beg[66][33];
int suff[66][66];
long long g[66][33][33][3], h[66][66][33][3];

void compute_cnt_gcd()
{
	memset(cnt_gcd, 0, sizeof(cnt_gcd));
	for(int x = 1; x <= N; ++x)
	{
		for(int y = 1; y <= x; ++y)
		{
			cnt_gcd[x][gcd(x,y)] += 1;
		}		
	}
}

void dpf()
{
	// reset 
	for(int ell = 0; ell <= N+2; ++ell)
	{
		for(int i = 0; i <= m; ++i)
		{
			for(int j = 0; j <= m; ++j)
			{
				f0[ell][i][j] = f1[ell][i][j] = f2[ell][i][j] = 0;
			}
			f0beg[ell][i] = f1beg[ell][i] = f2beg[ell][i] = 0;
		}
	}
	// f0
	for(int c = 1; c <= m; ++c)
		if(c != C)
			f0[1][c][c] = 1;
	for(int ell = 2; ell <= N+1; ++ell)
	{
		for(int c = 1; c <= m; ++c)
		{
			if(c != C)
			{						
				for(int lastc = 1; lastc <= m; ++lastc)
				{
					if(lastc != C)
					{
						if(lastc - 1 >= 1 && lastc - 1 != C)
							f0[ell][c][lastc] += f0[ell-1][c][lastc - 1];
						if(lastc + 1 <= m && lastc + 1 != C)
							f0[ell][c][lastc] += f0[ell-1][c][lastc + 1];
					}					
				}
			}
		}
	}
	// f1	
	f1[1][C][C] = 1;
	for(int ell = 2; ell <= N+1; ++ell)
	{				
		for(int beg = 1; beg <= m; ++beg)
		{
			for(int lastc = 1; lastc <= m; ++lastc)
			{
				if(beg == C && lastc == C)
					continue; // too many Cs
				if(beg == C)
				{
					if(C - 1 >= 1)
						f1[ell][beg][lastc] += f0[ell-1][C-1][lastc];
					if(C + 1 <= m)
						f1[ell][beg][lastc] += f0[ell-1][C+1][lastc];
				}				
				else if(lastc == C)
				{
					if(C - 1 >= 1)
						f1[ell][beg][lastc] += f0[ell-1][beg][C-1];
					if(C + 1 <= m)
						f1[ell][beg][lastc] += f0[ell-1][beg][C+1];
				}
				else
				{
					if(lastc - 1 >= 1)
						f1[ell][beg][lastc] += f1[ell-1][beg][lastc-1];
					if(lastc + 1 <= m)
						f1[ell][beg][lastc] += f1[ell-1][beg][lastc+1];
				}
			}
		}
	}
	// f2
	for(int ell = 3; ell <= N+1; ++ell)
	{
		for(int beg = 1; beg <= m; ++beg)
		{			
			for(int lastc = 1; lastc <= m; ++lastc)
			{
				if(beg == C && lastc == C)
				{
					if(C - 1 >= 1)
						f2[ell][beg][lastc] += f1[ell-1][beg][C-1];
					if(C + 1 <= m)
						f2[ell][beg][lastc] += f1[ell-1][beg][C+1];
				}
				else if(beg == C)
				{
					if(C - 1 >= 1)
						f2[ell][beg][lastc] += f1[ell-1][C-1][lastc];
					if(C + 1 <= m)
						f2[ell][beg][lastc] += f1[ell-1][C+1][lastc];
				}				
				else if(lastc == C)
				{
					if(C - 1 >= 1)
						f2[ell][beg][lastc] += f1[ell-1][beg][C-1];
					if(C + 1 <= m)
						f2[ell][beg][lastc] += f1[ell-1][beg][C+1];
				}
				else
				{
					if(lastc - 1 >= 1)
						f2[ell][beg][lastc] += f2[ell-1][beg][lastc-1];
					if(lastc + 1 <= m)
						f2[ell][beg][lastc] += f2[ell-1][beg][lastc+1];
				}
			}
		}
	}
	//////////// Build f0beg, f1beg, f2beg
	for(int ell = 1; ell <= N; ++ell)
	{
		for(int beg = 1; beg <= m; ++beg)
		{
			f0beg[ell][beg] = f0[ell+1][beg][beg];
			if(beg != C)
			{
				f1beg[ell][beg] = f1[ell+1][beg][beg];
				f2beg[ell][beg] = f2[ell+1][beg][beg];
			}
			else
			{
				if(C - 1 >= 1)
				{
					f1beg[ell][beg] += f1[ell][beg][C-1];
					f2beg[ell][beg] += f2[ell][beg][C-1];
				}
				if(C + 1 <= m)
				{
					f1beg[ell][beg] += f1[ell][beg][C+1];
					f2beg[ell][beg] += f2[ell][beg][C+1];
				}
			}
		}
	}
}

void solve_count()
{
	long long res = 0;
	for(int d = 2; d <= N; d += 2)
	{
		if(N % d == 0)
		{
			long long ans_d = 0;
			if(K == 0)
			{
				for(int beg = 1; beg <= m; ++beg)
				{
					ans_d += f0beg[d][beg];
				}
			}
			else if(K == 1)
			{
				if(d == N)
				{
					for(int beg = 1; beg <= m; ++beg)
					{
						//cout << "beg = " << beg << "; f1[N, beg] = " << f1beg[N][beg] << endl;
						ans_d += f1beg[N][beg];
					}
				}				
			}
			else
			{
				// K = 2.
				if(d == N)
				{
					for(int beg = 1; beg <= m; ++beg)
					{
						//cout << "beg = " << beg << "; f2beg[N, beg] = " << f2beg[N][beg] << endl;
						ans_d += f2beg[N][beg];
					}
				}
				else if(d + d == N)
				{
					for(int beg = 1; beg <= m; ++beg)
					{
						ans_d += f1beg[d][beg];
					}
				}
			}
			if(ans_d > 0)
			{
				//cout << "COUNT, d = " << d << "; cnt_gcd = " << cnt_gcd[N][d] << "; ans_d = " << ans_d << endl;
				res += 1LL * cnt_gcd[N][d] * ans_d;
			}			
		}
	}
	//dbg(res);
	assert(res % N == 0);
	cout << res / N << endl;
}

long long getf(int k, int len, int beg, int lastc = -1)
{
	assert(0 <= k && k <= 2);
	if(k == 0)
	{
		if(lastc == -1) return f0beg[len][beg];
		else return f0[len][beg][lastc];
	}
	else if(k == 1)
	{
		if(lastc == -1) return f1beg[len][beg];
		else return f1[len][beg][lastc];
	}
	else {
		if(lastc == -1) return f2beg[len][beg];
		else return f2[len][beg][lastc];
	}
	return 0;
}


void add(long long &x, int k, int len, int beg, int lastc = -1)
{
	long long tmp = getf(k, len, beg, lastc);	
	//cout << "f[" << k << ", " << len << ", " << beg << ", " << lastc << " = " << tmp << endl;
	x += tmp;
}

void build_suff(int d)
{
	for(int i = 0; i <= d; ++i)
	{
		for(int j = 0; j <= d; ++j)
		{
			suff[i][j] = 0;
		}
	}
	for(int j = d; j >= 1; --j)
	{
		if(a[j] == a[1])
			suff[j][j] = 1;
		
		for(int i = j-1; i >= 1; --i)
		{
			// not start at a[i]
			suff[i][j] = suff[i+1][j];
			// start at a[i]
			bool full = true;
			for(int k = i; k <= j; ++k)
			{
				if(a[k] != a[1+k-i])
				{
					full = false;
					break;
				}
			}
			if(full)
				suff[i][j] = j - i + 1;
		}
		/* 	for(int i = j; i >= 2; --i)
		{
			cout << "(i, j) = " << i << "; " << j << "; suff = " << suff[i][j] << endl;
		} */
	}
	
}

void dpgh(int d)
{
	// g(length, begc, lastc, numberofC) strictly larger than a[1...d]
	// h(length, prefix length, lastc, numberofC) strictly larger than a[1...d]
	for(int ell = 0; ell <= d; ++ell)
	{
		for(int c = 0; c <= m; ++c)
		{
			for(int lastc = 0; lastc <= m; ++lastc)
			{
				for(int k = 0; k <= 2; ++k)
				{
					g[ell][c][lastc][k] = 0;
				}
			}
		}
		for(int plen = 0; plen <= d; ++plen)
		{
			for(int lastc = 0; lastc <= m; ++lastc)
			{
				for(int k = 0; k <= 2; ++k)
				{
					h[ell][plen][lastc][k] = 0;
				}
			}
		}		
	}
	/// ell = 1 first. When ell = 1, the first character cannot be a[1], must be larger.
	for(int c = a[1]+1; c <= m; ++c)
	{
		g[1][c][c][(c == C)] = 1;
	}
	/// ell = 1 first. When ell = 1, the first character cannot be a[1], must be larger.
/* 	for(int c = a[1]+1; c <= m; ++c)
	{
		h[1][0][c][(c == C)] = 1;	
	} */
	/* g depends on h and h depends on g*/
	/// 2 <= ell <= d
	for(int ell = 2; ell <= d; ++ell)
	{
		/// compute h first
		/// consider plen = ell-1`
		if(a[ell] + 2 <= m && a[ell] == a[ell-1] - 1)
		{
			if(hasC[ell-1] + (a[ell-1] + 1 == C) <= 2)
				h[ell][ell-1][ a[ell] + 2 ][hasC[ell-1] + (a[ell-1] + 1 == C)] = 1;
		}
		/// consider plen = 1, 2, ..., ell-2
		for(int plen = ell-2; plen >= 1; --plen)
		{
			for(int lastc = 1; lastc <= m; ++lastc)
			{
				for(int k = hasC[plen]; k <= 2; ++k)
				{					
					// x = a[plen+1]
					h[ell][plen][lastc][k] += h[ell][plen + 1][lastc][k];
					// x = a[plen] + 1 > a[plen+1] = a[plen] - 1
					if(a[plen + 1] == a[plen]-1 && a[plen] + 1 <= m)
						h[ell][plen][lastc][k] += g[ell - plen][a[plen] + 1][lastc][k - hasC[plen]];
				}
			}
		}
		/// consider plen = 0
/* 		for(int lastc = a[1] + 1; lastc <= m; ++lastc)
		{
			for(int k = 0; k <= 2; ++k)
			{
				/// beg = a[1]
				h[ell][0][lastc][k] += h[ell][1][lastc][k];
				/// beg > a[1]
				for(int beg = a[1] + 1; beg <= m; ++beg)
				{
					if(k - (beg == C) >= 0)
					{
						h[ell][0][lastc][k] += g[ell-1][beg-1][lastc][k - (beg == C)];
						if(beg + 1 <= m)
						{
							h[ell][0][lastc][k] += g[ell-1][beg+1][lastc][k - (beg == C)];
						}
					}
				}
			}			
		} */
		
		/// then compute g
		for(int beg = a[1]; beg <= m; ++beg)
		{
			for(int lastc = 1; lastc <= m; ++lastc)
			{
				for(int k = (lastc == C) + (beg == C); k <= 2; ++k)
				{
					if(beg > a[1])
					{
						// suffix start from beg is already larger than a[1...d], so we care only about suffix start from the next index
						g[ell][beg][lastc][k] += g[ell-1][beg-1][lastc][k - (beg == C)];
						if(beg + 1 <= m)
							g[ell][beg][lastc][k] += g[ell-1][beg+1][lastc][k - (beg == C)];
					}
					else
					{
						// beg == a[1]
						g[ell][beg][lastc][k] = h[ell][1][lastc][k];
					}
				}
			}
		}
	}
	//cout << "g 2 3 2 0 = " << g[2][3][2][0] << endl;
}

int lyn(int d)
{
	int p = 1;
	for(int i = 2; i <= d; ++i)
	{
		if(a[i] > a[i-p])
			p = i;
		else if(a[i] < a[i-p])
			return p;
	}
	return p;
}

bool isnecklace(int d)
{
	int p = 1;
	for(int i = 2; i <= d; ++i)
	{
		if(a[i] > a[i-p])
			p = i;
		else if(a[i] < a[i-p])
			return false;
	}
	return (d % p == 0);
}

bool isfirework(int d)
{
	for(int i = 1; i <= d; ++i)
	{
		if(a[i] < 1 || a[i] > m)
			return false;
		if( abs(a[i] - a[1 + (i%d)]) != 1 )
			return false;
	}
	return true;
}

bool isfireworkID(int d)
{
	return isfirework(d) && isnecklace(d);
}

void largestnecklace(int d)
{
	for(int i = 1; i <= d; ++i)
		a[i] = A[i];
	while(!isnecklace(d))
	{
		int p = lyn(d);
		a[p] -= 1;
		for(int i = p+1; i <= n; ++i)
			a[i] = m;
	}
}

void largestfw(int d)
{
	for(int i = 1; i <= d; ++i)
		a[i] = A[i];
	if(isfireworkID(d))
		return;
	if(a[d] > a[1] + 1)
	{
		a[d] = a[1] + 1;
		if(isfireworkID(d))
			return;
	}
	int Z = d-1;
	while(Z >= 3)
	{
		for(int i = 1; i <= d; ++i)
			a[i] = A[i];
		if( a[Z] > a[Z-1] && a[Z] >= a[1] + 2 )
		{
			// has enough to get to a[1]+1 at d?
			if( (a[Z]-2) - (a[1] + 1) <= d - Z)
			{
				a[Z] -= 2;
				a[d] = a[1] + 1;
				for(int j = Z+1; j <= d-1; ++j)
				{
					if( a[j-1] + 1 <= m && a[j-1] + 1 - (a[1] + 1) <= d - j )
					{
						a[j] = a[j-1] + 1;
					}
					else
					{
						a[j] = a[j-1] - 1;
					}
				}
			}
		}
		if(isfireworkID(d))
			return;
		--Z;
	}
	//cout << "FAILED at d = " << d << endl;
	//assert(false);
}

long long solve_each_d(int d, int nCneed)
{
	largestfw(d); // assign a[1...d] to be the largest firework smaller than or equal to to A[1...d]
	assert(isfireworkID(d));
	//largestnecklace(d);
	hasC[0] = 0;
	for(int i = 1; i <= d; ++i)
	{
		//cout << "a[" << i << "] = " << a[i] << endl;
		hasC[i] = hasC[i-1] + (a[i] == C);
	}		
	
	long long res = 0;
	// j = d first: brute force
	if(hasC[d] == nCneed)
	{
		res += lyn(d);
		/* vector<int> b(d);
		set<vector<int>> svi;
		for(int x = 0; x < d; ++x)
		{
			//cout << "------- x = " << x << " ---------- " << endl;
			for(int i = 0; i < d; ++i)
			{
				b[i] = a[1 + (d + i - x)%d];
				//cout << b[i] << endl;
			}
			svi.insert(b);
		}
		res += svi.size(); */
		//cout << "RANK, d = " << d << "; itself: res = " << res << endl;
	}
	
	// j = 0
	// w = sigma + x + tau
	/// t = 1 first 
	for(int x = 1; x < a[1]; ++x)
	{		
		if(x == C && nCneed == 0)
			continue;
		add(res, nCneed, d, x);		
	}
	//cout << "j = 0 for smaller than a[1], res = " << res << endl;
	/// t >= 2 next.
	// Now, w[t] < a[1]. Note that w[t-1] must be w[t] + 1 and w[t-1] >= a[1], otherwise t-1 is the first index where w is smaller than a[1].
	// but, this means that w[t] + 1 >= a[1], so w[t] >= a[1] - 1. Hence, w[t] must be a[1]-1 and w[t-1] = a[1]. Only one choice!
	// but then, starting at t-1, w is a[1](a[1]-1)a[1].... This is smaller than a[1](a[1]+1)a[3] for sure. Hence, t-1 is the first index 
	// where w is smaller than or equal to a, a contradiction.
	// Hene, we do nothing for j = 0 and t >= 2.
	
	// 1 <= j < d.
	build_suff(d); // build suffix for each d
	dpgh(d); // build new g, h for each d
	for(int j = 1; j < d; ++j)
	{
		if(a[j+1] == a[j] - 1 || a[j+1] <= 2)
			continue; // not possible to have a[1...j](a[j]-1) starting from w[t].
		int needleft = nCneed - hasC[j];
		if(needleft < 0)
			continue;
		/// t = 1 first 		
		if(a[1] - 1 >= 1)
			add(res, needleft, d - j, a[j] - 1, a[1] - 1);		
		if(a[1] + 1 <= m)
			add(res, needleft, d - j, a[j] - 1, a[1] + 1);		
		//cout << "after j = " << j << "; t = 1; res = " << res << endl;
		//return res;
		/// t = 2...d.
		/// Note that w[t-1] must be a[1] + 1.
		for(int t = 2; t <= d; ++t)
		{
			if(t + j <= d)
			{
				for(int beg = a[1]; beg <= m; ++beg)
				{
					for(int lpart = 0; lpart <= needleft; ++lpart)
					{
						int rpart = needleft - lpart;
						if(beg - 1 >= 1)
							res += g[t-1][beg][a[1] + 1][lpart] * getf(rpart, d - (t+j) + 1, a[j] - 1, beg - 1);
						if(beg + 1 <= m)
							res += g[t-1][beg][a[1] + 1][lpart] * getf(rpart, d - (t+j) + 1, a[j] - 1, beg + 1);
					}
/* 					if(j == 2 && t == 4)
					{
						cout << g[3][3][3][0] << endl;
						//cout << g[t-1][beg][a[1] + 1][0] * g[d - (t+j) + 1][ a[j] - 1][ beg + 1 ][0] << endl;
						cout << "j = " << j << "; t = " << t << "; after beg = " << beg << "; res = " << res << endl;
					} */
				}
			}
			else if(t + j == d + 1)
			{
				res += g[t-1][a[j] - 1][a[1]+1][needleft]; // g(length, begc, lastc, numberofC) strictly larger than a[1...d]
			}
			else 
			{				
				/* cout << "STARTING j = " << j << "; t = " << t << endl;
				cout << "d - t + 2 = " << d - t + 2 << endl; */				
				int s = suff[d-t+2][j];
				
				//cout << "s = " << s << endl;
				if( a[j] - 1 == a[s+1] )
				{					
					res += h[d - j + s][s+1][a[1] + 1][needleft + hasC[s]]; // h(length, prefix length, lastc, numberofC) strictly larger than a[1...d]
				}
				else if(a[j] - 1 > a[s+1] )
				{
					res += g[d - j][a[j] - 1][a[1] + 1][needleft];
				}
			}
			//cout << "after j = " << j << "; t = " << t << "; res = " << res << endl;
		}
	}		
	return res;
}

void solve_rank()
{
	long long res = 0;
	for(int d = 2; d <= N; d += 2)
	//int d = 8;
	{
		if(N % d == 0)
		{
			long long ans_d = 0;			
			if(K == 0)
			{
				ans_d = solve_each_d(d, 0);
			}
			else if(K == 1)
			{
				if(d == N)
					ans_d = solve_each_d(d, 1);
			}
			else
			{
				assert(K == 2);
				if(d == N)
				{
					ans_d = solve_each_d(d, 2);
				}
				else if(d + d == N)
				{					
					ans_d = solve_each_d(d, 1);
				}
			}			
			if(ans_d > 0)
			{
				//cout << "RANK, d = " << d << "; cnt_gcd = " << cnt_gcd[N][d] << "; ans_d = " << ans_d << endl;
				res += 1LL * cnt_gcd[N][d] * ans_d;
			}	
		}
	}
	//dbg(res);
	//dbg(res/N);
	assert(res % N == 0);
	cout << res / N << endl;
}

int main()
{
#ifdef HOME
	freopen("input.txt", "r", stdin);
	//freopen( "output.txt", "w", stdout );
#endif // HOME

	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(NULL);
	cout << setprecision(6);
	cout << fixed;

	//cin >> ntest;
	
	//for (itest = 1; itest <= ntest; ++itest)
	while(cin >> n >> m >> K >> C)
	{
		// cout << "Case #" << itest << ":\n";
		//cin >> n >> m >> K >> C;
		
		//cout << "n = " << n << "; m = " << m << "; K = " << K << "; C = " << C << endl;
		N = n+n;
		
		for(int i = 1; i <= N; ++i)
		{
			cin >> A[i];
		}
		compute_cnt_gcd();
		dpf();
		solve_count();
		solve_rank();
		
		//break;
	}

#ifdef HOME
	cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif

	return 0;
}
