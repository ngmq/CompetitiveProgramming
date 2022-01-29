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

// use the fact that the prime gap is small for large primes
// denote S = length(n) = number of digits in n
// for each prefix of length L of n: find the next prime larger, 
// then concatenate with the smallest prime number that has at least
// max(d, S - L)
// S max is 10, L min is 1, so S - L could be 9
// use the small prime gap property to find the second part as well

ll tens[11];

int smallest[11];

bool isPrime(ll x)
{
	if(x < 2) return false;
	if(x == 2) return true;
	for(ll k = 2; k * k <= x; ++k)
	{
		if(x % k == 0) return false;
	}
	return true;
}

void init()
{
	tens[0] = 1;
	for(int k = 1; k <= 10; ++k) tens[k] = tens[k-1] * 10;

	for(int k = 1; k <= 10; ++k)
	{
		ll beg = tens[k-1];
		while(!isPrime(beg))
		{
			++beg;
		}
		smallest[k] = beg;

		//cout << "k = " << k << "; smallest = " << smallest[k] << endl;
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

	init();

	cin >> ntest;

    for(itest = 1; itest <= ntest; ++itest)
    {		
    	ll n; cin >> n;
    	int d; cin >> d;
    	vector<int> digits;
    	while(n)
    	{
    		digits.pb(n % 10); 
    		n /= 10;
    	}
    	reverse(ALL(digits));
    	int S = digits.size();

    	if(S < d*2)
    	{
    		cout << smallest[d] << smallest[d] << endl;
    	}
    	else 
    	{
    		ll best = -1;
    		for(int L = d; L <= S; ++L)
    		{
    			// first half
    			ll beg = 0;
    			for(int i = 0; i < L; ++i)
    			{
    				beg = beg * 10 + digits[i];
    			}
    			ll save = beg;
    			while(!isPrime(beg))
    			{
    				++beg;
    			}
    			int nleft = max(d, S - L);
    			ll ret;
    			if(beg > save)
    				ret = beg * tens[nleft] + smallest[nleft];
    			else
    			{
    				assert(beg == save);
    				ll beg2 = 0;
    				for(int i = L; i < S; ++i)
    				{
    					beg2 = beg2 * 10 + digits[i];
    				}
    				beg2 = max(beg2, tens[nleft-1]);
    				while(!isPrime(beg2))
    				{
    					++beg2;
    				}
    				save = beg2; 
    				int cnt = 0; 
    				while(save > 0)
    				{
    					save /= 10;
    					cnt++;
    				}
    				ret = beg * tens[cnt] + beg2;
    			}
    			
    			if(best == -1 || best > ret)
    			{
    				best = ret;
    			}
    		}
    		assert(best != -1);
    		cout << best << endl;
    	}
    }


	#ifdef HOME
	cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
	#endif

	return 0;
}

