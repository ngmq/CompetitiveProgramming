#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define inf 1e9
#define linf 1e18
#define BASE 1000000
#define EPS 1e-10
#define PI acos(-1)
#define pii pair<int,int>
#define piii pair<int, pair<int,int>>
#define pli pair<long long, int>
#define pll pair<long long, long long>
#define pdi pair<double,int>
#define vi vector<int>
#define fi first
#define se second
#define ALL(x) (x).begin(), (x).end()
#define pb(x) push_back(x)
#define make_unique(x) sort(ALL(x)) ; x.erase( unique(ALL(x)), x.end()) ;
#define dbg(x) do { cout << #x << " = " << x << endl; } while(0)
#define mp(x, y) make_pair(x, y)
template<class T> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; }

bool exitInput = false;
int ntest = 1, itest = 1 ;

const int dx[4] =
{
	-1, 0, 1, 0
};
const int dy[4] =
{
	0, 1, 0, -1
};

void addMod( ll &x, ll y, ll Mod )
{
	x = ( x + y % Mod ) % Mod;
}

ll modPow( ll x, ll p, ll Mod )
{
	if( p == 0 )
		return 1;
	ll r = modPow( x, p / 2, Mod );
	r = ( r * r ) % Mod;
	if( p & 1 )
		r = ( r * x ) % Mod;
	return r;
}

ll modInverse(ll x, ll Mod)
{
    // return 1/x mod Mod
    return modPow(x, Mod-2, Mod);
}

// copy BigInt from Um_nik
/* using Int = __int128;
Int gcd( Int x, Int y )
{
	return y == 0 ? x : gcd( y, x % y );
}
void printInt( Int x )
{
	if ( x == 0 )
	{
		cout << 0; //printf("0");
		return;
	}
	vector<int> w;
	while( x > 0 )
	{
		w.push_back( x % 10 );
		x /= 10;
	}
	reverse( ALL( w ) );
	for ( int z : w )
		cout << z; //printf("%d", z);
}
void printAns(Int p, Int q) {
	Int g = gcd(p, q);
	p /= g;
	q /= g;
	printInt(p);
	cout << "/";
	printInt(q);
	cout << endl;
} */

ll gcd(ll p, ll q)
{
	return __gcd(p, q);
}

ll lcm(ll x, ll y)
{
	return x * y / gcd(x, y);
}

/*** CODE START HERE ***/
const ll Mod = 1000000007LL;
const int maxn = 200000 + 5;

// to handle the last requirement, notice that
// for a substring starting from i and can end at
// different j's, choose the j that s[j+1] is smallest

string s; 

int main()
{
#ifdef HOME
	freopen( "input.txt", "r", stdin );
	//freopen( "output.txt", "w", stdout );
#endif // HOME

	ios::sync_with_stdio( false );
	cin.tie( 0 );
	cout.tie( NULL );
	cout << setprecision( 2 );
	cout << fixed;

	cin >> ntest;

    for(itest = 1; itest <= ntest; ++itest)
    {		
    	cin >> s;
    	int n = s.size();
    	vector<int> f(n+1, 51);
    	f[n] = 0;
    	for(int i = n-1; i >= 0; --i)
    	{
    		vector<int> cnt(26, 0);
    		for(int j = i; j < n; ++j)
    		{
    			char c = s[j];
    			int x = c - 'a';
    			if(cnt[x] == 1)
    				break;
    			else
    			{
    				cnt[x] = 1;
    				f[i] = min(f[i], 1 + f[j+1]);
    			}
    		}
    		//printf("f[%d] = %d\n", i, f[i]);
    	}
    	vector<string> vres;
    	for(int i = 0; i < n; ++i)
    	{
    		vector<int> cnt(26, 0);
    		cnt[s[i]-'a']++;

    		int best = -1, bestIdx = -1;
    		for(int j = i+1; j <= n; ++j)
    		{
    			if(f[j] == f[i]-1)
    			{
    				if(best == -1 || best > s[j] - 'a')
    				{
    					best = s[j] - 'a';
    					bestIdx = j;
    				}
    			}
    			if(cnt[s[j]-'a'] > 0)
    				break;
    			cnt[s[j]-'a'] = 1;
    		}
    		assert(bestIdx > i);
    		string tmp = "";
    		for(int k = i; k < bestIdx; ++k)
    		{
    			tmp += s[k];
    		}
    		tmp[0] = tmp[0] - 'a' + 'A';
    		vres.push_back(tmp);
    		i = bestIdx-1;
    	}
    	assert((int)vres.size() == f[0]);
    	sort(ALL(vres));
    	for(string t : vres)
    	{
    		cout << t;
    	}
    	cout << endl;
    }


	#ifdef HOME
	cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
	#endif

	return 0;
}

