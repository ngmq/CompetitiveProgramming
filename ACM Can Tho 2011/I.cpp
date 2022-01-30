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

// Put all circles onto the 2D plane in an arbitrary order
// Consider the last circle.
// Since circles are convex, their intersections is a convex region
// Then, the last circle has to intersect some previous circle (if ans is 1)
// Then this intersection point  belongs to all circles
// The converse is also true.
// Algo: Pre-process so that no circle is completely inside a bigger cirlce
// If a circle is inside a bigger circle then delete the bigger circle
// Then: find all 2 * N^2 intersections. Check each of them.
// Complexity: 100 * 100 * 100 * 20 = 2 * 10^7, not too big

double x[122], y[122], R[122];

double sqr(double x)
{
	return x * x;
}
double dist(int i, int j)
{
	return sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j]));
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

	cin >> ntest;

    for(itest = 1; itest <= ntest; ++itest)
    {		
    	int n; cin >> n;
    	for(int i = 0; i < n; ++i)
    	{
    		cin >> x[i] >> y[i] >> R[i];
    	}
    	
    	// pre-processing
    	for(int i = 0; i < n; ++i)
    	{
    		for(int j = 0; j < n; ++j)
    		{
    			if(j == i || R[j] < 0) continue;
    			double O2O = dist(i, j);
    			double tmp = O2O + R[j];
    			if(tmp < R[i] + EPS)
    			{
    				R[i] = -1.0; break;
    			}
    		}
    	}
    	bool ans = false;
    	
    	// no cirlce is inside another circle
    	for(int i = 0; i < n; ++i)
    	{
    		if(R[i] == -1) continue;
    		vector<double> inx, iny; // intersection points
    		double movex = x[i], movey = y[i];		
    		for(int j = 0; j < n; ++j)
			{
				if(R[j] == -1) continue;
				x[j] -= movex;
				y[j] -= movex;
			}
			bool non_intersect = false;
			for(int j = 0; j < n; ++j)
			{
				// cp-algorithms Circle-Circle intersection
				double a = -2 * x[j];
				double b = -2 * y[j];
				double c = sqr(x[j]) + sqr(y[j]) + sqr(R[i]) - sqr(R[j]);
				// cp-algorthms Circle-Line intersection
				double x0 = -a*c/(a*a+b*b), y0 = -b*c/(a*a+b*b);
				double r = R[i];

				if (c*c > r*r*(a*a+b*b)+EPS)
				{
					non_intersect = true;
					break;
				}
				else if (abs (c*c - r*r*(a*a+b*b)) < EPS) {
			    	inx.pb(x0);
			    	iny.pb(y0);
				}
				else
				{
					double d = r*r - c*c/(a*a+b*b);
				    double mult = sqrt (d / (a*a+b*b));
				    double ax, ay, bx, by;
				    ax = x0 + b * mult;
				    bx = x0 - b * mult;
				    ay = y0 - a * mult;
				    by = y0 + a * mult;
				    inx.pb(ax); iny.pb(ay);
				    inx.pb(bx); iny.pb(by);
				}
			}
			if(non_intersect)
				break;
			
			for(int k = 0; k < inx.size(); ++k)
			{
				bool found = true;
				double Ix = inx[k], Iy = iny[k];
				for(int j = 0; j < n; ++j)
				{
					if(R[j] == -1) continue;
					double I2O = sqr(Ix - x[j]) + sqr(Iy - y[j]);
					if(I2O > R[j] + EPS)
					{
						found = false;
						break;
					}
				}
				if(found)
				{
					ans = true;
					break;
				}
			}

			for(int j = 0; j < n; ++j)
			{
				if(R[j] == -1) continue;
				x[j] += movex;
				y[j] += movex;
			}

			if(ans) break;
    	}
    	if(!ans)
    	{
    		puts("0");
    	}
    	else puts("1");
    }


	#ifdef HOME
	cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
	#endif

	return 0;
}
