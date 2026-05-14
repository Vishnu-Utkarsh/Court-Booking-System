#ifndef TEMPLATE
#define TEMPLATE

#include <bits/stdc++.h>
using namespace std;


// -------------------- DEBUGGING --------------------

#define fastio   ios_base::sync_with_stdio(false);   cin.tie(NULL);
#define debug(x) cerr << #x <<" = "; _print(x); cerr << endl;

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

#endif