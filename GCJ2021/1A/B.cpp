#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
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
#define ms(x,val_add) memset(x, val_add, sizeof(x))
#define pb(x) push_back(x)
#define make_unique(x) sort(ALL(x)) ; x.erase( unique(ALL(x)), x.end()) ;
#define dbg(x) do { cout << #x << " = " << x << endl; } while(0)
#define mp(x, y) make_pair(x, y)
#define minimize(x, y) x = min(x, y)
#define maximize(x, y) x = max(x, y)

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

void addMod(ll &x, ll y, ll Mod)
{
    x = (x + y) % Mod;
}

ll modPow(ll x, ll p, ll Mod)
{
    if(p == 0)
        return 1;
    ll r = modPow(x, p / 2, Mod);
    r = (r * r) % Mod;
    if(p & 1)
        r = (r * x) % Mod;
    return r;
}

/*** CODE START HERE ***/
const ll Mod = 100000000LL; //1000000007LL;
const int maxn = 95 + 5;

int m;
int P[maxn];
ll cnt[555];
ll N[maxn], S;
vector<int> primes;

bool isprime(int x)
{
    for(int j = 3; j <= x / j; j += 2)
    {
        if(x % j == 0)
            return false;
    }
    return true;
}

int main()
{
    #ifdef HOME
    freopen( "input.txt", "r", stdin );
    freopen( "output.txt", "w", stdout );
    #endif // HOME
    #ifdef HOME // Copied from Um_nik
	#   define eprintf(...) fprintf(stdout, __VA_ARGS__);fflush(stdout);
    #else
        #define eprintf(...) 42
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(10);
    cout << fixed;

    primes.resize(95);
    primes[0] = 2;
    primes[1] = 3;

    for(int i = 5, k = 2; i < 500; i += 2)
    {
        if(isprime(i))
        {
            //cout << "k = " << k << "; i = " << i << endl;
            primes[k] = i;
            ++k;
        }
    }

    cin >> ntest;
    for(itest = 1; itest <= ntest; ++itest)
    {
        S = 0;
        ms(cnt, 0);
        cin >> m;
        for(int i = 1; i <= m; ++i)
        {
            cin >> P[i] >> N[i];
            S += 1LL * N[i] * P[i];
            cnt[P[i]] = N[i];
        }
        //cout << "S = " << S << endl;
        ll res = 0;
        for(ll sumB = 2; sumB <= 499 * 60 && sumB < S; ++sumB)
        {
            ll tmp = S - sumB;
            ll tmpS = 0;
            bool ok = true;
            for(int p: primes)
            {
                if(p > tmp) break;
                else if(tmp % p == 0)
                {
                    int k = 0;
                    while(tmp % p == 0)
                    {
                        tmpS += p;
                        tmp /= p;
                        ++k;
                    }
                    if(k > cnt[p])
                    {
                        //cout << "p = " << p << "; k = " << k << endl;
                        ok = false; break;
                    }
                }
            }
            //cout << ok << endl;
            //cout << tmp << " ; " << (tmpS == sumB) << endl;
            if(tmp > 1 || tmpS != sumB) ok = false;
            if(ok)
            {
                //cout << "tmp = " << S - sumB << endl;
                res = S - sumB;
                break;
            }
        }
        cout << "Case #" << itest << ": " << res << endl;
    }

    return 0;
}
