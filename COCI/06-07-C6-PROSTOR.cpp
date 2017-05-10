//// ngmq
//// AC on http://wcipeg.com/problem/coci066p6
//// Note: this is a really nice problem. It's not too hard, experienced programmer can "smell" sweep lines algorithm. It's also not
//// too easy - one needs to consider carefully how to decompose the sum into three components of (X, Z), (Z, Y) and (Y, Z). 
//// Additionaly, implementing each component is not that trivial - carefully design how sweep lines algorithm should be performed
//// certainly requires some time and drawing things on paper.
//// This solution is written in OOP style after consulting the COCI's solution.

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
const int maxn = 100000 + 5;
const int maxv = 100000 + 5;
const int maxe = 1000011 + 5;

const int MAXD = 1000;
struct BIT2D
{
    int f[MAXD+1][MAXD+1];
    BIT2D()
    {

    }
    void update( int X, int Z, int val )
    {
        for( int x = X; x <= MAXD; x += x & -x )
        {
            for( int z = Z; z <= MAXD; z += z & - z )
            {
                f[x][z] += val;
            }
        }
    }
    int query( int X, int Z )
    {
        int res = 0;
        for( int x = X; x > 0; x -= x & - x )
        {
            for( int z = Z; z > 0; z -= z & -z )
            {
                res += f[x][z];
            }
        }
        return res;
    }
    int query( int X1, int X2, int Z1, int Z2 )
    {
        return query( X2, Z2 ) + query( X1 - 1, Z1 - 1 ) - query( X1 - 1, Z2 ) - query( X2, Z1 - 1 );
    }
    void reset()
    {
        ms( f, 0 );
    }
} LowEndPoints, HighEndPoints;

struct Cube
{
    int lx, hx, ly, hy, lz, hz;
    Cube() {}
};

const int EventTypeOpenRectangle = 1;
const int EventTypeVerticalSegment = 2;
const int EventTypeCloseRectangle = 3;

struct Event
{
    int eventType;
    int y, x1, x2, z1, z2;
    Event() {}
    Event( int _eventType, int _y, int _x1, int _x2, int _z1, int _z2 )
    {
        eventType = _eventType;
        y = _y;
        x1 = _x1;
        x2 = _x2;
        z1 = _z1;
        z2 = _z2;
    }
    bool operator <( const Event& other ) const
    {
        if( y != other.y ) return y < other.y;
        return eventType < other.eventType;
    }
} events[maxn * 2];

int n, nEvent;
Cube a[maxn];

ll solveEvents()
{
    ll res = 0;

    LowEndPoints.reset();
    HighEndPoints.reset();

    sort( events, events + nEvent );
    for( int i = 0; i < nEvent; ++i )
    {
        if( events[i].eventType == EventTypeOpenRectangle || events[i].eventType == EventTypeVerticalSegment )
        {
            res += LowEndPoints.query( events[i].x1, events[i].x2, 1, events[i].z2 )
                   - HighEndPoints.query( events[i].x1, events[i].x2, 1, events[i].z1-1 );
        }
        if( events[i].eventType == EventTypeOpenRectangle )
        {
            LowEndPoints.update( events[i].x1, events[i].z1, 1 );
            HighEndPoints.update( events[i].x2, events[i].z2, 1 );
        }
        if( events[i].eventType == EventTypeCloseRectangle )
        {
            LowEndPoints.update( events[i].x1, events[i].z1, -1 );
            HighEndPoints.update( events[i].x2, events[i].z2, -1 );
        }
    }
    return res;
}

int main()
{
#ifdef HOME
    freopen( "input.txt", "r", stdin );
    freopen( "output.txt", "w", stdout );
#endif

    //scanf("%d", &ntest);

    for( itest = 1; itest <= ntest; ++itest )
    {
        scanf( "%d", &n );
        for( int i = 0; i < n; ++i )
        {
            scanf( "%d %d %d %d %d %d", &a[i].lx, &a[i].ly, &a[i].lz, &a[i].hx, &a[i].hy, &a[i].hz );
            if( a[i].lx > a[i].hx ) swap( a[i].lx, a[i].hx );
            if( a[i].ly > a[i].hy ) swap( a[i].ly, a[i].hy );
            if( a[i].lz > a[i].hz ) swap( a[i].lz, a[i].hz );
        }

        ll res = 0;

        nEvent = 0;
        for( int i = 0; i < n; ++i )
        {
            if( a[i].lx == a[i].hx )
            {
                events[nEvent++] = Event( EventTypeOpenRectangle, a[i].ly, a[i].lx, a[i].lx, a[i].lz, a[i].hz );
                events[nEvent++] = Event( EventTypeCloseRectangle, a[i].hy, a[i].hx, a[i].hx, a[i].lz, a[i].hz );
            }
            else if( a[i].ly == a[i].hy )
            {
                events[nEvent++] = Event( EventTypeVerticalSegment, a[i].ly, a[i].lx, a[i].hx, a[i].lz, a[i].hz );
            }
        }
        res += solveEvents();

        nEvent = 0;
        for( int i = 0; i < n; ++i )
        {
            if( a[i].ly == a[i].hy )
            {
                events[nEvent++] = Event( EventTypeOpenRectangle, a[i].lz, a[i].ly, a[i].ly, a[i].lx, a[i].hx );
                events[nEvent++] = Event( EventTypeCloseRectangle, a[i].hz, a[i].hy, a[i].hy, a[i].lx, a[i].hx );
            }
            else if( a[i].lz == a[i].hz )
            {
                events[nEvent++] = Event( EventTypeVerticalSegment, a[i].lz, a[i].ly, a[i].hy, a[i].lx, a[i].hx );
            }
        }
        res += solveEvents();

        nEvent = 0;
        for( int i = 0; i < n; ++i )
        {
            if( a[i].lz == a[i].hz )
            {
                events[nEvent++] = Event( EventTypeOpenRectangle, a[i].lx, a[i].lz, a[i].lz, a[i].ly, a[i].hy );
                events[nEvent++] = Event( EventTypeCloseRectangle, a[i].hx, a[i].hz, a[i].hz, a[i].ly, a[i].hy );
            }
            else if( a[i].lx == a[i].hx )
            {
                events[nEvent++] = Event( EventTypeVerticalSegment, a[i].lx, a[i].lz, a[i].hz, a[i].ly, a[i].hy );
            }
        }
        res += solveEvents();

        printf( "%lld\n", res );
    }

    return 0;
}

