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
const int maxn = 500000 + 5;

bitset<maxn> isPrime;

void sieve()
{
	isPrime.flip();
	isPrime[0] = isPrime[1] = false;
	for(int x = 2; x < maxn; ++x)
	{
		if(isPrime.test(x))
		{
			for(ll k = 1LL * x * x; k < (ll)maxn; k += x)
			{
				isPrime.set((int)k, false);
			}
		}
	}
}

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

	sieve();

	cin >> ntest;

    for(itest = 1; itest <= ntest; ++itest)
    {		
    	string s; cin >> s;
    	int n = s.size();
    	
    	queue<string> Left;
    	stack<string> Right;

    	#define RIGHT 0
    	#define LEFT 1
    	int side = RIGHT;
    	int R = n-1, L = 0, len = 1;
    	while(R >= L)
    	{
    		string tmp = "";
    		if(side == RIGHT)
    		{
    			int beg = max(R - len + 1, L);
    			for(int i = beg; i <= R; ++i)
    			{
    				tmp += s[i];
    			}
    			R = beg - 1;
    			Left.push(tmp);
    		}
    		else
    		{
    			int eNd = min(L + len - 1, R);
    			for(int i = L; i <= eNd; ++i)
    			{
    				tmp += s[i];
    			}
    			L = eNd + 1;
    			Right.push(tmp);
    		}
    		side ^= 1;
    		++len;
    	}

    	string t = ""; // original string
    	
    	while(!Left.empty())
    	{
    		t += Left.front(); Left.pop();
    	}
    	while(!Right.empty())
    	{
    		t += Right.top(); Right.pop();
    	}
    	
    	//cout << t << endl;
    	string res = "";
    	int cnt = 1;
    	for(int i = 0; i < n; ++i)
    	{
    		assert('A' <= t[i] && t[i] <= 'Z');
    		
    		int j = i+1;
    		for(; 'a' <= t[j] && t[j] <= 'z'; ++j);
    		if(isPrime.test(cnt))
    		{
    			while(i < j)
    			{
    				res += t[i];
    				++i;
    			}
    		}
    		i = j-1;
    		++cnt;
    	}
    	cout << res << endl;
    }


	#ifdef HOME
	cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
	#endif

	return 0;
}
