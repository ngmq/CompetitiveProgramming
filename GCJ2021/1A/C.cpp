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

void addMod( ll &x, ll y, ll Mod )
{
    x = ( x + y ) % Mod;
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

// copy BigInt from Um_nik
using Int = __int128;
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
}

/*** CODE START HERE ***/
const ll Mod = 100000000LL; //1000000007LL;
const int maxn = 120 + 5;

Int choose[maxn][maxn];

int n, q, score[3];
string s[3];

char opposite( char c )
{
    if( c == 'F' ) return 'T';
    else return 'F';
}

int main()
{
#ifdef HOME
    freopen( "input.txt", "r", stdin );
    freopen( "output.txt", "w", stdout );
#endif // HOME

    ios_base::sync_with_stdio( false );
    cin.tie( NULL );
    cout << setprecision( 10 );
    cout << fixed;

    for( int i = 0; i < maxn; ++i )
    {
        choose[i][0] = 1;
        if( i > 0 )
            choose[0][i] = 0;
    }
    for( int i = 1; i < maxn; ++i )
    {
        for( int j = 1; j <= i; ++j )
        {
            choose[i][j] = choose[i - 1][j] + choose[i - 1][j - 1];
        }
        for( int j = i + 1; j < maxn; ++j )
        {
            choose[i][j] = 0;
        }
    }

    cin >> ntest;
    for( itest = 1; itest <= ntest; ++itest )
    {
        cout << "Case #" << itest << ": ";
        cin >> n >> q;
        for( int i = 0; i < n; ++i )
        {
            cin >> s[i] >> score[i];
        }
        if( n == 1 )
        {
            string sres( q, ' ' );
            for( int j = 0; j < q; ++j )
                if( score[0] >= q - score[0] )
                    sres[j] = s[0][j];
                else
                    sres[j] = opposite( s[0][j] );

            cout << sres << " " << max( score[0], q - score[0] ) << "/1" << endl;
        }
        else if( n == 2 )
        {
            int m = 0;
            for( int j = 0; j < q; ++j )
            {
                m += s[0][j] != s[1][j];
            }
            int x = ( m + score[0] - score[1] ) / 2;
            assert( x * 2 == m + score[0] - score[1] );
            assert( x <= m );
            assert( x <= score[0] );
            assert( score[0] - x <= score[1] );
            string sres( q, ' ' );
            for( int j = 0; j < q; ++j )
                if( s[0][j] != s[1][j] )
                    if( x >= m - x ) sres[j] = s[0][j];
                    else sres[j] = opposite( s[0][j] );
            for( int j = 0; j < q; ++j )
                if( s[0][j] == s[1][j] )
                    if( score[0] - x >= q - m - score[0] + x )
                        sres[j] = s[0][j];
                    else sres[j] = opposite( s[0][j] );

           cout << sres << " " << max( x, m - x ) + max( score[0] - x, q - m - score[0] + x ) << "/1" << endl;
        }
        else
        {
            int s0 = score[0], s1 = score[1], s2 = score[2];
            int A, B, C, D, a, b, c, d;
            A = B = C = D = 0;
            for( int i = 0; i < q; ++i )
            {
                A += s[0][i] != s[1][i] && s[0][i] == s[2][i];
                B += s[0][i] != s[1][i] && s[0][i] != s[2][i];
                C += s[0][i] == s[1][i] && s[0][i] == s[2][i];
                D += s[0][i] == s[1][i] && s[0][i] != s[2][i];
            }
//            cout << "A = " << A << endl;
//            cout << "B = " << B << endl;
//            cout << "C = " << C << endl;
//            cout << "D = " << D << endl;

            Int sum = 0, sum0[4], sum1[4];
            sum0[0] = sum0[1] = sum0[2] = sum0[3] = 0;
            sum1[0] = sum1[1] = sum1[2] = sum1[3] = 0;
            for( a = 0; a <= A; ++a )
            {
                int b2 = ( s0 - s1 + A + B - 2 * a );
                if( b2 < 0 || b2 > 2 * B || b2 % 2 != 0 ) continue;
                b = b2 / 2;
                int c2 = s1 + s2 - A - D - 2 * B + b2;
                if( c2 < 0 || c2 > 2 * C || c2 % 2 != 0 ) continue;
                c = c2 / 2;
                d = s0 - ( a + b ) - c;
                if( a < 0 || a > A || a > s0 || A - a > s1 || a > s2 )
                    continue;
                if( b < 0 || b > B || b > s0 || B - b > s1 || B - b > s2 )
                    continue;
                if( c < 0 || c > C || c > s0 || c > s1 || c > s2 )
                    continue;
                if( d < 0 || d > D || d > s0 || d > s1 || D - d > s2 )
                    continue;
                if( a + b + c + d != s0 )
                    continue;
                if( A - a + B - b + c + d != s1 )
                    continue;
                if( a + B - b + c + D - d != s2 )
                    continue;

                sum += choose[A][a] * choose[B][b] * choose[C][c] * choose[D][d];

                if(A >= 1 && a >= 1)
                    sum0[0] += choose[A - 1][a - 1] * choose[B][b] * choose[C][c] * choose[D][d];
                if(A >= 1)
                    sum1[0] += choose[A - 1][a]     * choose[B][b] * choose[C][c] * choose[D][d];

                if(B >= 1 && b >= 1)
                    sum0[1] += choose[A][a] * choose[B - 1][b - 1] * choose[C][c] * choose[D][d];
                if(B >= 1)
                    sum1[1] += choose[A][a] * choose[B - 1][b]     * choose[C][c] * choose[D][d];

                if(C >= 1 && c >= 1)
                    sum0[2] += choose[A][a] * choose[B][b]         * choose[C-1][c-1] * choose[D][d];
                if(C >= 1)
                    sum1[2] += choose[A][a] * choose[B][b]         * choose[C-1][c]   * choose[D][d];

                if(D >= 1 && d >= 1)
                    sum0[3] += choose[A][a] * choose[B][b]         * choose[C][c]     * choose[D-1][d-1];
                if(D >= 1)
                    sum1[3] += choose[A][a] * choose[B][b]         * choose[C][c]     * choose[D-1][d];
            }

            string sres(q, '*');
            Int escore = 0;

            sum0[0] *= A;
            sum1[0] *= A;
            escore += max(sum0[0], sum1[0]);

            sum0[1] *= B;
            sum1[1] *= B;
            escore += max(sum0[1], sum1[1]);

            sum0[2] *= C;
            sum1[2] *= C;
            escore += max(sum0[2], sum1[2]);

            sum0[3] *= D;
            sum1[3] *= D;
            escore += max(sum0[3], sum1[3]);


            for( int i = 0; i < q; ++i )
            {
                if(s[0][i] != s[1][i] && s[0][i] == s[2][i])
                {
                    if(sum0[0] >= sum1[0])
                        sres[i] = s[0][i];
                    else
                        sres[i] = opposite(s[0][i]);
                }
                else if(s[0][i] != s[1][i] && s[0][i] != s[2][i])
                {
                    if(sum0[1] >= sum1[1])
                        sres[i] = s[0][i];
                    else
                        sres[i] = opposite(s[0][i]);
                }
                else if(s[0][i] == s[1][i] && s[0][i] == s[2][i])
                {
                    if(sum0[2] >= sum1[2])
                        sres[i] = s[0][i];
                    else
                        sres[i] = opposite(s[0][i]);
                }
                else if(s[0][i] == s[1][i] && s[0][i] != s[2][i])
                {
                    if(sum0[3] >= sum1[3])
                        sres[i] = s[0][i];
                    else
                        sres[i] = opposite(s[0][i]);
                }
            }

            cout << sres << " ";
            printAns(escore, sum);
        }
    }

    return 0;
}
