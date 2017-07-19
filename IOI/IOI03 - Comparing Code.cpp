//// ngmq
/*
IOI 2003 - Comparing Code.
AC on http://wcipeg.com/problem/ioi0312

Đây là một trong số những bài hay nhất và đòi hỏi kỹ năng code nhiều nhất mình từng làm. Ý tưởng thì giống như trong bài giải của BTC, nghĩa là thực hiện duyệt O(R * H) qua tất cả các điểm bắt đầu có thể ở 2 dãy, sau đó có thao tác xóa cạnh ở đầu. Tuy nhiên khi lập điều kiện để xem khi nào dừng thì điều kiện đó phải khá tỉ mỉ để tránh sai sót. Để cài đặt tốt thì việc đặt biến và tổ chức hàm phải vừa đầy đủ, vừa gọn nhẹ. Mình thích nhất là ý tưởng thành lập hàm sure() để tính ra xem một biến trong chương trình có "sure" là đang phải gán vào một biến duy nhất của chương trình kia không. Ý tưởng dùng hàm sure() và abstract đống hàm gọi / sửa leftMatch và rightMatch giúp cho việc cài đặt và debug thuận lợi hơn nhiều lần. Đây là một trong những bài làm xong rất sướng vì có nhiều không gian để nghĩ cả thuật toán cả cách cài đặt.

Rất khâm phục 04 người AC ngay trong contest như  Marius Victor Costan(http://www.costan.us/), Alex Schwendner(https://www.linkedin.com/in/alexschwendner/) (2 người này đều vào học MIT), Carl Nettelblad (https://www.it.uu.se/katalog/carln) (hiện đang là giáo sư DH Uppsala), Qiming Hou (http://www.houqiming.net/) (hiện đang là giáo sư đại học Chiết Giang).
*/

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
#include <cassert>

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
    "NE", "SE", "SW", "NW"
};

const ll Mod = 1000000007LL;
const int maxn = 1000 + 5;
const int maxv = 100000 + 5;
const int maxe = 1000011 + 5;

struct Line
{
    int blockid, l, r1, r2;
    Line() {
        blockid = -1;
    }
    Line( int _l, int _r1, int _r2 ) {
        l = _l;
        r1 = _r1;
        r2 = _r2;
    }
};

char variables[2][3002][10];
Line code[2][maxn];
int N[2];
int nid[2];

#define RBN 0
#define HAL 1

int get_id( char* s, int gid )
{
    for( int i = nid[gid] - 1; i >= 0; --i )
    {
        if( strcmp( s, variables[gid][i] ) == 0 )
        {
            return i;
        }
    }
    return -1;
}

int add_new_var( char* s, int gid )
{
    strcpy( variables[gid][nid[gid]], s );
    nid[gid]++;
    return nid[gid]-1;
}

// number of variable could be up to 3000 (all 1000 lines introduce new 3 variables)
int leftMatch[2][3002], leftMatchCount[2][3002], rightMatch[2][3002][2], rightMatchCount[2][3002][2];

inline int getMinRightMatch( int gid, int u )
{
    return min( rightMatch[gid][u][0], rightMatch[gid][u][1] );
}

inline int getMaxRightMatch( int gid, int u )
{
    return max( rightMatch[gid][u][0], rightMatch[gid][u][1] );
}

inline int getRightMach( int gid, int u, int idx )
{
    return rightMatch[gid][u][idx];
}

inline int getRightMachCount( int gid, int u, int idx )
{
    return rightMatchCount[gid][u][idx];
}

int getMaxRightMatchCount( int gid, int u )
{
    return max( rightMatchCount[gid][u][0], rightMatchCount[gid][u][1] );
}

int argMaxRightMatchCount( int gid, int u )
{
    int k = getMaxRightMatchCount( gid, u );
    //printf("argMaxRightMatchCount, gid = %d, u = %d, maxCount = %d, rightCount = (%d, %d)\n", gid, u,
    //       k, getRightMachCount( gid, u, 0 ), getRightMachCount( gid, u, 1 ));

    if(  getRightMachCount( gid, u, 0 ) == k && getRightMachCount( gid, u, 1 ) == k )
    {
        // two max
        return -2;
    }
    if(  getRightMachCount( gid, u, 0 ) == k )
    {
        return getRightMach( gid, u, 0 );
    }
    return getRightMach( gid, u, 1 );
}

bool isEmptyRightMatch( int gid, int u )
{
    return getMaxRightMatchCount(gid, u) == 0;
}

int getLeftMatch( int gid, int u )
{
    return leftMatch[gid][u];
}

void updateLeftMatch( int gid, int u, int val, int up_val )
{
    leftMatchCount[gid][u] += up_val;
    if( leftMatchCount[gid][u] == 0 )
        leftMatch[gid][u] = -1;
    else
        leftMatch[gid][u] = val;
}

void updateRightMatch( int gid, int u, int idx, int val, int up_val )
{
    rightMatchCount[gid][u][idx] += up_val;
    if( rightMatchCount[gid][u][idx] == 0 )
        rightMatch[gid][u][idx] = -1;
    else
        rightMatch[gid][u][idx] = val;
}

void assignRightMatch( int gid, int u, int idx, int val )
{
    rightMatch[gid][u][idx] = val;
    rightMatchCount[gid][u][idx] = 1;
}

int sure( int gid, int u )
{
    //printf("sure, gid = %d, u = %d, getLeftMatch( gid, u ) = %d\n", gid, u, getLeftMatch( gid, u ));

    if( getLeftMatch( gid, u ) == -1 && isEmptyRightMatch( gid, u ) )
    {
        return -1; // no body
    }
    if( getLeftMatch( gid, u ) != -1 )
    {
        return getLeftMatch( gid, u );
    }
    return argMaxRightMatchCount( gid, u );

}

bool canMatch( int u, int v ) // u is RBN, v is HAL
{
    int sure_u = sure( RBN, u ), sure_v = sure( HAL, v );

    if( sure_u >= 0  ) return sure_u == v;
    if( sure_v >= 0  ) return sure_v == u;

    //printf("NOT sure, u = %d, rightMatch = (%d, %d)\n", u, getRightMach( RBN, u, 0 ), getRightMach( RBN, u, 1 ));
    //printf("NOT sure, v = %d, rightMatch = (%d, %d)\n", v, getRightMach( HAL, v, 1 ), getRightMach( HAL, v, 1 ));

    if( sure_u == -2 )
    {
        return getRightMach( RBN, u, 0 ) == v || getRightMach( RBN, u, 1 ) == v;
    }

    if( sure_v == -2 )
    {
        return getRightMach( HAL, v, 0 ) == u || getRightMach( HAL, v, 1 ) == u;
    }

    // sure_u == sure_v == 1

    return true;
}

void addRightMatch( int gid, int u, int v )
{
    int sure_u = sure( gid, u );

    //printf("addRightMatch, gid = %d, u = %d, v = %d, sure_u = %d, rightMatch = %d, %d\n", gid, u, v,
    //       sure_u, getRightMach( gid, u, 0 ), getRightMach( gid, u, 1    ));

    if( sure_u >= 0 )
    {
        if( sure_u == v )
        {
            for( int i = 0; i < 2; ++i )
            {
                if( getRightMach( gid, u, i ) == v )
                {
                    updateRightMatch( gid, u, i, v, 1 );
                    break;
                }
            }
        }
        else
        {
            for( int i = 0; i < 2; ++i )
            {
                if( getRightMach( gid, u, i ) != sure_u )
                {
                    if( getRightMach( gid, u, i ) == -1 || getRightMach( gid, u, i ) == v)
                        updateRightMatch( gid, u, i, v, 1 );
                    else
                        assignRightMatch(gid, u, i, v);
                    break;
                }
            }
        }

    }
    else
    {
        if( sure_u == -1 )
        {
            assignRightMatch( gid, u, 0, v );
            //updateRightMatch( gid, u, 0, v, 1 );
        }
        else
        {
            for( int i = 0; i < 2; ++i )
            {
                if( getRightMach( gid, u, i ) == v )
                {
                    updateRightMatch( gid, u, i, v, 1 );
                    break;
                }
            }
        }
    }
}

void removeRightMatch( int gid, int u, int v )
{
    for( int idx = 0; idx < 2; ++idx )
    {
        if( getRightMach( gid, u, idx ) == v )
        {
            updateRightMatch( gid, u, idx, v, -1 );
            break;
        }
    }
}

bool addLine( int line_rbn, int line_hal )
{
    //printf("Try Line %d and Line %d\n", line_rbn, line_hal);

    int lft[2], r1[2], r2[2];
    lft[RBN] = code[RBN][line_rbn].l;
    r1[RBN] = code[RBN][line_rbn].r1;
    r2[RBN] = code[RBN][line_rbn].r2;

    lft[HAL] = code[HAL][line_hal].l;
    r1[HAL] = code[HAL][line_hal].r1;
    r2[HAL] = code[HAL][line_hal].r2;

    if( r1[RBN] == r2[RBN] && r1[HAL] != r2[HAL] )
    {
        //puts("addLine failed, @@@1");
        return false;
    }
    if( r1[RBN] != r2[RBN] && r1[HAL] == r2[HAL] )
    {
        //("addLine failed, @@@2");
        return false;
    }

    if( !canMatch( lft[RBN], lft[HAL] ) )
    {
        //puts("addLine failed, ^^^");
        return false;
    }

    updateLeftMatch( RBN, lft[RBN], lft[HAL], 1 );
    updateLeftMatch( HAL, lft[HAL], lft[RBN], 1 );

    if( !canMatch( r1[RBN], r1[HAL] ) && !canMatch( r1[RBN], r2[HAL] ) )
    {
        //printf("addLine failed, r1[RBN] = %d, r1[HAL] = %d, r2[HAL] = %d\n", r1[RBN], r1[HAL], r2[HAL]);
        updateLeftMatch( RBN, lft[RBN], lft[HAL], -1 );
        updateLeftMatch( HAL, lft[HAL], lft[RBN], -1 );
        return false;
    }

    if( !canMatch( r2[RBN], r1[HAL] ) && !canMatch( r2[RBN], r2[HAL] ) )
    {
        //printf("addLine failed, r2[RBN] = %d, r1[HAL] = %d, r2[HAL] = %d\n", r2[RBN], r1[HAL], r2[HAL]);
        updateLeftMatch( RBN, lft[RBN], lft[HAL], -1 );
        updateLeftMatch( HAL, lft[HAL], lft[RBN], -1 );
        return false;
    }

    if( !canMatch( r1[RBN], r1[HAL] ) && !canMatch( r2[RBN], r1[HAL] ) )
    {
        //printf("addLine failed, r1[HAL] = %d, r1[RBN] = %d, r2[RBN] = %d\n", r1[HAL], r1[RBN], r2[RBN]);
        updateLeftMatch( RBN, lft[RBN], lft[HAL], -1 );
        updateLeftMatch( HAL, lft[HAL], lft[RBN], -1 );
        return false;
    }

    if( !canMatch( r1[RBN], r2[HAL] ) && !canMatch( r2[RBN], r2[HAL] ) )
    {
        //printf("addLine failed, r2[HAL] = %d, r1[RBN] = %d, r2[RBN] = %d\n", r2[HAL], r1[RBN], r2[RBN]);
        updateLeftMatch( RBN, lft[RBN], lft[HAL], -1 );
        updateLeftMatch( HAL, lft[HAL], lft[RBN], -1 );
        return false;
    }

    addRightMatch( RBN, r1[RBN], r1[HAL] );
    addRightMatch( RBN, r1[RBN], r2[HAL] );

    addRightMatch( RBN, r2[RBN], r1[HAL] );
    addRightMatch( RBN, r2[RBN], r2[HAL] );

    addRightMatch( HAL, r1[HAL], r1[RBN] );
    addRightMatch( HAL, r1[HAL], r2[RBN] );

    addRightMatch( HAL, r2[HAL], r1[RBN] );
    addRightMatch( HAL, r2[HAL], r2[RBN] );

    return true;
}

void removeLine( int line_rbn, int line_hal )
{
    int lft[2], r1[2], r2[2];
    lft[RBN] = code[RBN][line_rbn].l;
    r1[RBN] = code[RBN][line_rbn].r1;
    r2[RBN] = code[RBN][line_rbn].r2;

    lft[HAL] = code[HAL][line_hal].l;
    r1[HAL] = code[HAL][line_hal].r1;
    r2[HAL] = code[HAL][line_hal].r2;

    updateLeftMatch( RBN, lft[RBN], lft[HAL], -1 );
    updateLeftMatch( HAL, lft[HAL], lft[RBN], -1 );

    removeRightMatch( RBN, r1[RBN], r1[HAL] );
    removeRightMatch( RBN, r1[RBN], r2[HAL] );

    removeRightMatch( RBN, r2[RBN], r1[HAL] );
    removeRightMatch( RBN, r2[RBN], r2[HAL] );

    removeRightMatch( HAL, r1[HAL], r1[RBN] );
    removeRightMatch( HAL, r1[HAL], r2[RBN] );

    removeRightMatch( HAL, r2[HAL], r1[RBN] );
    removeRightMatch( HAL, r2[HAL], r2[RBN] );
}

int solve( int line_rbn, int line_hal )
{
    int ret = 0;

    int up0, up1, d0, d1;

    up0 = d0 = line_rbn;
    up1 = d1 = line_hal;

    while( d0 < N[RBN] && d1 < N[HAL] )
    {
//        printf("Trying adding line %d and %d <=> %d = %d + %d and %d = %d + %d\n",
//               d0, d1,
//               code[RBN][d0].l, code[RBN][d0].r1, code[RBN][d0].r2,
//               code[HAL][d1].l, code[HAL][d1].r1, code[HAL][d1].r2
//               );
        while( up0 <= d0 && up1 <= d1 && !addLine( d0, d1 ) )
        {
            if(up0 < d0 && up1 < d1)
            {
                removeLine( up0, up1 );
            }
            ++up0;
            ++up1;
        }

        //printf("Now up0 and up1 are %d and %d, ret = %d\n", up0, up1, d0 - up0 + 1);

        ret = max( ret, d0 - up0 + 1 );
        ++d0;
        ++d1;

    }

    // clean arrays

    while( up0 < d0 )
    {
        removeLine( up0, up1 );
        ++up0;
        ++up1;
    }

    return ret;
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

        char s1[10], s2[10], s3[10];

        nid[0] = nid[1] = 0;
        scanf( "%d %d", &N[0], &N[1] );
        for( int gid = 0; gid < 2; ++gid )
        {
            for( int i = 0; i < N[gid]; ++i )
            {
                scanf( "%s = %s + %s", &s1, &s2, &s3 );

                int k;

                k = get_id( s1, gid );
                if( k == -1 ) k = add_new_var( s1, gid );
                code[gid][i].l = k;

                k = get_id( s2, gid );
                if( k == -1 ) k = add_new_var( s2, gid );
                code[gid][i].r1 = k;

                k = get_id( s3, gid );
                if( k == -1 ) k = add_new_var( s3, gid );
                code[gid][i].r2 = k;

                //printf( "%d = %d + %d\n", code[gid][i].l, code[gid][i].r1, code[gid][i].r2 );
            }
//            for( int i = 0; i < nid[gid]; ++i )
//            {
//                printf( "=== Subprogram variable %d, name = %s\n", i, variables[gid][i] );
//            }

            //puts("=====================");
        }

        /*
        offset:
        line0 + offset = line1
        */

        //printf("nid = (%d, %d)\n", nid[0], nid[1]);

        ms( leftMatch, -1 );
        ms( rightMatch, -1 );

        int res = 0;
        for( int line_offset = -N[RBN]; line_offset <= N[HAL]; ++line_offset )
        //;int line_offset = 29;
        {
            //printf("offset = %d\n", line_offset);
            for( int start_rbn = 0; start_rbn < N[RBN]; ++start_rbn )
            {
                if( start_rbn + line_offset >= 0 && start_rbn + line_offset < N[HAL] )
                {
                    //printf("*********** NEW START: start_rbn = %d, start_hal = %d\n", start_rbn, start_rbn + line_offset);
                    int k = solve( start_rbn, start_rbn + line_offset );
                    //printf("*********** NEW START RETURN: ret = %d\n", k);

                    res = max( res, k );
                    break;
                }
            }
        }
        printf( "%d\n", res );
    }

    return 0;
}

