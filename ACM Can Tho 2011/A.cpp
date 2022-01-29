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
const int maxn = 1000000 + 5;

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
    	int n; cin >> n;
    	int save = n;
    	int cnt = 0;
    	while(n > 0)
    	{
    		int x = n % 10;
    		n /= 10;
    		if(x != 0 && save % x == 0)
    			++cnt;
    	}
    	cout << cnt << endl;
    }


	#ifdef HOME
	cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
	#endif

	return 0;
}
