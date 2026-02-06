#ifndef TEMPLATE
#define TEMPLATE

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
// #pragma GCC optimize("O3,unroll-loops")

using namespace std;
using namespace __gnu_pbds;

typedef tree<long long, null_type, less_equal<long long>, rb_tree_tag, tree_order_statistics_node_update> pbds;


// -------------------- DEBUGGING --------------------

#define fastio   ios_base::sync_with_stdio(false);   cin.tie(NULL);
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" = "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(int x) {cerr << x;}
void _print(long x) {cerr << x;}    
void _print(long long x) {cerr << x;}
void _print(unsigned x) {cerr << x;}
void _print(unsigned long x) {cerr << x;}
void _print(unsigned long long x) {cerr << x;}
void _print(float x) {cerr << x;}
void _print(double x) {cerr << x;}
void _print(long double x) {cerr << x;}
void _print(char x) {cerr << '\'' << x << '\'';}
void _print(const char* x) {cerr << '\"' << x << '\"';}
void _print(const string &x) {cerr << '\"' << x << '\"';}
void _print(const bitset<17>& x) {cerr << x;}
void _print(bool x) {cerr << boolalpha << x;}

template<typename T> void _print(stack<T> v);
template<typename T> void _print(deque<T> v);
template<typename T> void _print(queue<T> v);
template<typename T> void _print(priority_queue<T> v);
template<typename T, typename V> void _print(const unordered_multimap<T, V> &v);
template<typename T, typename V> void _print(const unordered_map<T, V> &v);
template<typename T, typename V> void _print(const multimap<T, V> &v);
template<typename T, typename V> void _print(const map<T, V> &v);
template<typename T> void _print(const unordered_multiset<T> &v);
template<typename T> void _print(const unordered_set<T> &v);
template<typename T> void _print(const multiset<T> &v);
template<typename T> void _print(const set<T> &v);
template<typename T> void _print(const vector<T> &v);
template<typename T, typename V> void _print(const pair<T, V> &x);
template<typename T> void _print(const pbds &v);

void _print(const pbds &v)
    {   cerr << '['; for (auto &i : v)  cerr << i << " "; cerr << ']';}
template<typename T, typename V> void _print(const pair<T, V> &x)
    {   cerr << '{'; _print(x.first); cerr << ", "; _print(x.second); cerr << '}';}
template<typename T> void _print(const vector<T> &v)
    {   cerr << '['; for (size_t i = 0; i < v.size(); ++i) { _print(v[i]); if (i != v.size()-1) cerr << ", "; } cerr << ']';}
template<typename T> void _print(const set<T> &v)
    {   cerr << '{'; for (auto i : v) { _print(i); cerr << " "; } cerr << '}';}
template<typename T> void _print(const multiset<T> &v)
    {   cerr << '{'; for (auto i : v) { _print(i); cerr << " "; } cerr << '}';}
template<typename T> void _print(const unordered_set<T> &v)
    {   cerr << '{'; for (auto i : v) { _print(i); cerr << " "; } cerr << '}';}
template<typename T> void _print(const unordered_multiset<T> &v)
    {   cerr << '{'; for (auto i : v) { _print(i); cerr << " "; } cerr << '}';}
template<typename T, typename V> void _print(const map<T, V> &v)
    {   cerr << '|'; for (auto i : v) { cerr << endl; _print(i.first); cerr << " : "; _print(i.second);}}
template<typename T, typename V> void _print(const multimap<T, V> &v)
    {   cerr << '|'; for (auto i : v) { cerr << endl; _print(i.first); cerr << " : "; _print(i.second);}}
template<typename T, typename V> void _print(const unordered_map<T, V> &v)
    {   cerr << '|'; for (auto i : v) { cerr << endl; _print(i.first); cerr << " : "; _print(i.second);}}
template<typename T, typename V> void _print(const unordered_multimap<T, V> &v)
    {   cerr << '|'; for (auto i : v) { cerr << endl; _print(i.first); cerr << " : "; _print(i.second);}}
template<typename T> void _print(priority_queue<T> v)
    {   cerr << '>'; while(! v.empty()) { cerr << " "; _print(v.top()); v.pop();}}
template<typename T> void _print(queue<T> v)
    {   cerr << '>'; while(! v.empty()) { cerr << " "; _print(v.front()); v.pop();}}
template<typename T> void _print(deque<T> v)
    {   cerr << '>'; for (auto i : v) { cerr << " ";  _print(i);}}
template<typename T> void _print(stack<T> v)
    {   cerr << '>'; while(! v.empty()) { cerr << " "; _print(v.top()); v.pop();}}


// -------------------- OUTPUT --------------------

void print(int x) {cout << x << " ";}
void print(long x) {cout << x << " ";}
void print(long long x) {cout << x << " ";}
void print(unsigned x) {cout << x << " ";}
void print(unsigned long x) {cout << x << " ";}
void print(unsigned long long x) {cout << x << " ";}
void print(float x) {cout << x << " ";}
void print(double x) {cout << x << " ";}
void print(long double x) {cout << x << " ";}
void print(char x) {cout << x << " ";}
void print(const char* x) {cout << x << " ";}
void print(const string &x) {cout << x << " ";}
void print(bool x) {cout << (x ? "YES" : "NO") << "\n";}

template<typename T, typename V> void print(const pair<T, V> &x)
    {   print(x.first); cout << ' '; print(x.second); cout << '\n';}
template<typename T> void print(const vector<T> &v)
    {   for (auto i : v) print(i); cout << '\n';}
template<typename T> void print(const set<T> &v)
    {   for (auto i : v) print(i); cout << '\n';}
template<typename T> void print(const multiset<T> &v)
    {   for (auto i : v) print(i); cout << '\n';}
template<typename T> void print(const unordered_set<T> &v)
    {   for (auto i : v) print(i); cout << '\n';}
template<typename T, typename V> void print(const map<T, V> &v)
    {   for (auto i : v) print(i); cout << '\n';}
template<typename T, typename V> void print(const multimap<T, V> &v)
    {   for (auto i : v) print(i); cout << '\n';}
template<typename T, typename V> void print(const unordered_map<T, V> &v)
    {   for (auto i : v) print(i); cout << '\n';}


// -------------------- MACROS -----------------------
#define yes cout << "YES\n"
#define no cout << "NO\n"

// -------------------- CONSTANTS --------------------
const int MOD = 998244353;
const int N = 2e5 + 5;
const long long INF = LLONG_MAX;
    
// -------------------- UTILITIES --------------------
long long __lzzcm(long long a, long long b) { return (a / __gcd(a, b)) * b; }
    
long long addition(long long a, long long b) { return (a + b) % MOD; }
long long subtraction(long long a, long long b) { return (a - b + MOD) % MOD; }
long long multiplication(long long a, long long b) { return (a * b) % MOD; }
long long binaryMultiplication(long long x, long long y)
{
    long long res = 0;
    x %= MOD, y %= MOD;

    while (y)
    {
        if (y & 1)  res = addition(res, x);
        x = addition(x, x);
        y >>= 1;
    }
    return res;
}
long long power(long long x, long long y)
{
    long long res = 1;
    x %= MOD;

    while (y)
    {
        if (y & 1)  res = multiplication(res, x);
        x = multiplication(x, x);
        y >>= 1;
    }
    return res;
}
long long modularInverse(long long a)   { return power(a, MOD - 2); } // when MOD is prime
long long division(long long a, long long b) { return (a * modularInverse(b)) % MOD; }

int nCr(int n, int r)   // For small values of n and r only
{
    if(n < r)   return 0;
    if(n < r << 1)  r = n - r;
    long long x = 1;

    for(int i = 0; i < r; i++)
    {
        x *= (n - i);
        x /= (i + 1);
    }
    return (int)x;
}

vector<int> Factorial = {1};
void precomputeFactorial(const int n)
{
    const int m = Factorial.size();
    Factorial.resize(n + 1);
    
    for(int i = m; i <= n; i++)
        Factorial[i] = (Factorial[i-1] * 1LL * i) % MOD;
}
long long factorial(long long n)
{
    if(n >= MOD)    return 0;
    if(Factorial.size() <= n)   precomputeFactorial(n);
    return Factorial[n];
}

long long NCR(const long long n, const long long r)   // For large values of n and r
{
    if(n < r)   return 0;
    return division(factorial(n), multiplication(factorial(r), factorial(n - r)));
}

#endif