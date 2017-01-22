#line 2 "ColorfulDecoration.cpp"

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
// #include <map>
#include <set>
//#include <deque>
#include <queue>
#include <stack>
// #include <cstdlib>
// #include <climits>
// #include <functional>
// #include <ctime>
#include <cmath>
//#include <bitset>
// #include <utility>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define inf 1e9 + 1
#define linf 1e18
#define BASE 1000000
#define EPS 1e-10
#define PI acos(-1)
#define pii pair<int,int>
#define fi first
#define se second
#define ALL(x) (x).begin(), (x).end()
#define ms(x,val) memset(x, val, sizeof(x))
#define pb(x) push_back(x)
#define make_unique(x) sort(ALL(x)) ; x.erase( unique(ALL(x)), x.end()) ;
#define dbg(x) do { cout << #x << " = " << x << endl; } while(0)
#define mp(x, y) make_pair(x, y)

#ifdef HOME
#define DBG(x, ...) printf(x, __VA_ARGS__)
#else
#define DBG(x, ...)
#endif

/*** IMPLEMENTATION ***/
bool exitInput = false;
int ntest = 1, itest = 1 ;

// const int dx[4] =
// {
// 0, 0, -1, 1
// };
// const int dy[4] =
// {
// 1, -1, 0, 0
// };
// const int dx[8] = {-2, -1, -1, +0, +0, +1, +1, +2};
// const int dy[8] = {+0, -1, +1, -2, +2, -1, +1, +0};

/** Knight Move **/
// const int dx[8] = {+1, +2, +2, +1, -1, -2, -2, -1};
// const int dy[8] = {+2, +1, -1, -2, -2, -1, +1, +2};

const char * directions[4] =
{
    "NE", "SE", "SW", "NW"
};
const ll Mod = 1000000000LL + 7;
const int maxn = 50 + 2;
const int maxv = 100000+ 5;
const int maxe = 600000 + 5;
const int root = 1;

bool is_overlap(int _size, int x0, int y0, int x1, int y1)
{
    // x0, y0 now is on the left of x1, y1
    if(_size <= abs(x1 - x0))
        return false;
    if(_size <= abs(y1 - y0))
        return false;
    return true;
}

int n, ans[maxn], ax[maxn], ay[maxn], bx[maxn], by[maxn];
int x[maxn], y[maxn];
bool conflict[maxn][2][maxn][2], canBe[maxn][2];
int setBy[maxn];

void build_conflict(int _size)
{
    ms(conflict, false);
    int i, j;
    for(i = 0; i < n; ++i)
    {
        for(j = i + 1; j < n; ++j)
        {
            // 0-0
            x[i] = ax[i];
            y[i] = ay[i];
            x[j] = ax[j];
            y[j] = ay[j];
            if(is_overlap(_size, x[i], y[i], x[j], y[j]))
            {
                conflict[i][0][j][0] = true;
                conflict[j][0][i][0] = true;
            }
            // 0-1
            x[i] = ax[i];
            y[i] = ay[i];
            x[j] = bx[j];
            y[j] = by[j];
            if(is_overlap(_size, x[i], y[i], x[j], y[j]))
            {
                conflict[i][0][j][1] = true;
                conflict[j][1][i][0] = true;
            }
            // 1-0
            x[i] = bx[i];
            y[i] = by[i];
            x[j] = ax[j];
            y[j] = ay[j];
            if(is_overlap(_size, x[i], y[i], x[j], y[j]))
            {
                conflict[i][1][j][0] = true;
                conflict[j][0][i][1] = true;
            }
            // 1-1
            x[i] = bx[i];
            y[i] = by[i];
            x[j] = bx[j];
            y[j] = by[j];
            if(is_overlap(_size, x[i], y[i], x[j], y[j]))
            {
                conflict[i][1][j][1] = true;
                conflict[j][1][i][1] = true;
            }
        }
    }
}

bool dfs(int u)
{
    //visit[u] = 1;
    int v;
    //printf("u = %d, ans = %d\n", u, ans[u]);
    bool ok = true;
    for(v = 0; v < n; ++v)
    {
        if(u == v)
            continue;
        //printf("INSIDE (u = %d, ans[u] = %d) v = %d, ans = %d\n", u, ans[u], v, ans[v]);
        if(ans[v] != -1 && conflict[u][ans[u]][v][ans[v]])
        {
            //printf("--- GOT FALSE 1 ---\n");
            return false;
        }
        if(ans[v] == -1)
        {
            if(conflict[u][ans[u]][v][0] && conflict[u][ans[u]][v][1])
            {
                //printf("--- GOT FALSE 2 ---\n");
                return false;
            }
            if(conflict[u][ans[u]][v][0])
            {
                ans[v] = 1;
                //printf("--- ASSIGN 1 ---\n");
                ok &= dfs(v);
            }
            else
            if(conflict[u][ans[u]][v][1])
            {
                ans[v] = 0;
                //printf("--- ASSIGN 0 ---\n");
                ok &= dfs(v);
            }
        }
    }
    return ok;
}

//void  build_canBe()
//{
//    int i, j;
//    bool ok;
//    for(i = 0; i < n; ++i)
//    {
//        for(j = 0; j <= 1; ++j)
//        {
//            ms(ans, -1);
//            ans[i] = j;
//            ok = dfs(i);
//            canBe[i][j] = ok;
//        }
//    }
//}
//
bool isok()
{
    // let's find the impossible!
    int i;
    bool ok;
    for(i = 0; i < n; ++i)
    {
        ms(ans, -1);
        ans[i] = 0;
        ok = dfs(i);
        //printf("i = %d, try 0, ok = %d\n", i, ok);
        if(ok)
            continue;
        // ok = false now
        ms(ans, -1);
        ans[i] = 1;
        ok = dfs(i);
        //printf("i = %d, try 1, ok = %d\n", i, ok);
        if(!ok)
            return false;
    }
    return true;
}


class ColorfulDecoration
{
public:
    int getMaximum(vector <int> xa, vector <int> ya, vector <int> xb, vector <int> yb)
    {
        n = xa.size();

        int i;
        for(i = 0; i < n; ++i)
        {
            ax[i] = xa[i];
            ay[i] = ya[i];
            bx[i] = xb[i];
            by[i] = yb[i];
        }
        int lo = 0, hi = 1000000000, mid, res = -1;
        //cerr << "start" << endl;
        while(lo <= hi)
        {
            mid = (lo + hi) / 2;
            //mid = 25;
            build_conflict(mid);
            //build_canBe();
            bool ok = isok();
            if(ok)
            {
                res = mid;
                lo = mid + 1;
            }
            else
            {
                hi = mid - 1;
            }
        }
        return res;
    }


// BEGIN CUT HERE
public:
    void run_test(int Case)
    {
        if ((Case == -1) || (Case == 0)) test_case_0();
        if ((Case == -1) || (Case == 1)) test_case_1();
        if ((Case == -1) || (Case == 2)) test_case_2();
        if ((Case == -1) || (Case == 3)) test_case_3();
        if ((Case == -1) || (Case == 4)) test_case_4();
        if ((Case == -1) || (Case == 5)) test_case_5();
        if ((Case == -1) || (Case == 6)) test_case_6();
    }
private:
    template <typename T> string print_array(const vector<T> &V)
    {
        ostringstream os;
        os << "{ ";
        for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\",";
        os << " }";
        return os.str();
    }
    void verify_case(int Case, const int &Expected, const int &Received)
    {
        cerr << "Test Case #" << Case << "...";
        if (Expected == Received) cerr << "PASSED" << endl;
        else
        {
            cerr << "FAILED" << endl;
            cerr << "\tExpected: \"" << Expected << '\"' << endl;
            cerr << "\tReceived: \"" << Received << '\"' << endl;
        }
    }
    void test_case_0()
    {
        int Arr0[] = { 10,  0,  7 };
        vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {  0, 19,  6 };
        vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = { 20, 10, 25 };
        vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        int Arr3[] = { 20, 35, 25 };
        vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        int Arg4 = 19;
        verify_case(0, Arg4, getMaximum(Arg0, Arg1, Arg2, Arg3));
    }
    void test_case_1()
    {
        int Arr0[] = { 464, 20 };
        vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = { 464, 10 };
        vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = { 464,  3 };
        vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        int Arr3[] = { 464, 16 };
        vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        int Arg4 = 461;
        verify_case(1, Arg4, getMaximum(Arg0, Arg1, Arg2, Arg3));
    }
    void test_case_2()
    {
        int Arr0[] = { 0, 0, 1, 1 };
        vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = { 0, 0, 1, 1 };
        vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = { 1, 1, 0, 0 };
        vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        int Arr3[] = { 1, 1, 0, 0 };
        vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        int Arg4 = 0;
        verify_case(2, Arg4, getMaximum(Arg0, Arg1, Arg2, Arg3));
    }
    void test_case_3()
    {
        int Arr0[] = { 0, 3, 0, 5, 6 };
        vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = { 1, 6, 0, 8, 5 };
        vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = { 6, 1, 7, 4, 7 };
        vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        int Arr3[] = { 5, 9, 2, 8, 9 };
        vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        int Arg4 = 3;
        verify_case(3, Arg4, getMaximum(Arg0, Arg1, Arg2, Arg3));
    }
    void test_case_4()
    {
        int Arr0[] = { 1000000000, 0 };
        vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = { 0, 1000000000 };
        vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = { 0, 1000000000 };
        vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        int Arr3[] = { 0, 1000000000 };
        vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        int Arg4 = 1000000000;
        verify_case(4, Arg4, getMaximum(Arg0, Arg1, Arg2, Arg3));
    }
    void test_case_5()
    {
        int Arr0[] = {10058581, 154753346, 768596011, 537736881, 284951555, 4937767, 551743985, 318153081, 419225035, 209414991, 875163789, 993489591, 638970392, 167678236, 107787858, 580531103, 746599417, 504755671, 950094063, 29100387, 798226506, 11045518, 254991679, 113367501, 668164141, 829862837, 535607577, 68808662, 137243450, 742513443, 750893439, 667989764, 658327080, 909258562, 60066869, 685961927, 19032057, 411758916, 456563278, 133339457, 445054711, 1029969, 635150159, 361326595, 736766227, 96400772, 520693118, 623847331, 300737412, 35274927};
        vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {925029818, 174517079, 1646413, 12773433, 691741493, 793087250, 258279708, 836968051, 48330553, 793820349, 265494765, 866228504, 108721269, 770210579, 591514618, 96403021, 610542722, 251614373, 250008568, 140755255, 828757170, 62984621, 651467852, 665271796, 821974756, 306278680, 840014662, 620053298, 944986353, 986049530, 490524582, 844988170, 105332032, 182087247, 989992648, 874583277, 824621693, 49528275, 933382757, 257971427, 204752946, 952234819, 271878226, 477692114, 234014860, 112319589, 480817107, 671488583, 892760055, 827330102};
        vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = {628888517, 193031190, 535906415, 42867534, 167612121, 425611047, 886995918, 990144636, 150418989, 579353, 269960467, 494671373, 603257354, 765045560, 919959627, 577389078, 700549546, 10406870, 527143207, 429777297, 452008066, 127836989, 400033681, 848851349, 52232933, 152404806, 963174080, 851166587, 327738049, 314562898, 372932500, 788625051, 647329123, 392311216, 261978133, 189202952, 760652464, 999484367, 54033136, 666650344, 992256916, 837243271, 343785416, 230764677, 369881548, 589608044, 869827643, 828157988, 576868010, 69499080};
        vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        int Arr3[] = {712821565, 724002276, 329872441, 11023068, 787396438, 837417619, 430819152, 638473998, 324578903, 41506913, 475461330, 231415948, 266062185, 852007510, 126429367, 895567, 714844332, 328045595, 272031980, 814375651, 20064823, 819066301, 533190570, 793917341, 711620607, 675647486, 419771932, 624922671, 321510647, 729744143, 582662379, 642821200, 722168329, 368164291, 474824653, 88800309, 687375246, 223691516, 682482322, 740559665, 380311110, 378513747, 155034303, 811291915, 785428352, 960361916, 980089755, 265371065, 117859704, 391568364};
        vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        int Arg4 = 59036900;
        verify_case(5, Arg4, getMaximum(Arg0, Arg1, Arg2, Arg3));
    }
    void test_case_6()
    {
        int Arr0[] = {460288319, 779682586, 57549982, 892491035, 855980632, 39873201, 564204779, 40797169, 996017294, 793397316, 178863385, 815429399, 986325123, 738879415, 445840859, 881687895, 311307452, 426849377, 256767017, 817927291, 404698207, 460498577, 127010635, 730964706, 769892278, 794829316, 200250021, 464490039, 993204685, 930249611, 151261182, 657447719, 845965156, 799233336, 355065638, 53124524, 459453728, 400358200, 328695600, 216329975, 601443522, 296449957, 394750273, 751289667, 442495276, 631252002, 354929146, 493480072, 81865111, 966820394};
        vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {700258555, 768611547, 23182312, 703265792, 122503807, 329858657, 992888856, 902521388, 997217570, 595647214, 249631153, 658662853, 910369085, 865136942, 512805590, 127768967, 381099470, 138281814, 863344115, 344982872, 33906353, 637406307, 777498936, 463011050, 25067728, 579454321, 155180179, 518714274, 927324589, 416560471, 554840777, 746008583, 274140415, 607072850, 331279055, 865222919, 848834210, 543698364, 348393101, 100425865, 274208821, 866950453, 942412728, 844810671, 733444032, 273574507, 548243114, 382075282, 196204939, 34747516};
        vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = {54225977, 777144615, 607737925, 193832014, 321051841, 779879239, 866364788, 953325227, 613549825, 986133293, 178672498, 44508670, 117509241, 973341406, 338841336, 267846265, 602584410, 721507992, 50735787, 30250953, 76918304, 600772458, 117011272, 749973757, 445533394, 467012319, 874469996, 882646156, 373749207, 653108693, 935202302, 710366318, 221521522, 12835437, 865919037, 516168808, 313276634, 749673754, 361734756, 932790885, 355272691, 730530561, 982873797, 204245127, 616891046, 864189983, 4650283, 937642301, 387034552, 142010052};
        vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        int Arr3[] = {819822075, 24258334, 907008183, 658748664, 584541773, 538398539, 927552505, 242689766, 291850643, 847114095, 553822930, 104085827, 726423399, 965977934, 91727563, 99107951, 353266151, 541597667, 131547004, 594223181, 654909489, 705462653, 582093325, 814290532, 809182289, 244406740, 464556657, 671864130, 363304843, 952081259, 182749677, 268390922, 799048311, 565037010, 965963644, 74536582, 950884204, 543555719, 469655036, 879117090, 585560113, 847096429, 802304582, 12770098, 469619244, 302675677, 976217038, 914416981, 945807374, 336879059};
        vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        int Arg4 = 53342408;
        verify_case(6, Arg4, getMaximum(Arg0, Arg1, Arg2, Arg3));
    }
// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
    freopen("topcoder.txt", "w", stdout);
    ColorfulDecoration ___test;
    ___test.run_test(-1);
    // system("pause");
}
// END CUT HERE
