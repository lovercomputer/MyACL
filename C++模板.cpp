//#define LOCAL
//#define _GLIBCXX_DEBUG
//#define DBG_USE_COLOR
//#define DBG_OSTREAM
//
#include<bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define se " "
#define en "\n"
#define En "\n"
#define yes "Yes"
#define no "No"
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using ui128=unsigned __int128;
const int infi=0x3f3f3f3f;
const ll inf=1e17;
const ll infLL=4e18;
const ll mod=1e9+7;
#ifdef LOCAL
#pragma message("LOCAL ON")
#ifdef DBG_USE_COLOR
#define ESC_(c) "\033[" c "m"
#else
#define ESC_(c) ""
#endif
#define ESC_RESET   ESC_("0")
#define ESC_GRAY    ESC_("90")
#define ESC_CYAN    ESC_("36")
string short_func(const char*p){string s=p;size_t i=s.find("::<lambda");if(i==string::npos)i=s.find("::{lambda");if(i!=string::npos)s=s.substr(0,i);size_t j=s.find('(');if(j!=string::npos)s=s.substr(0,j);size_t k=s.find("::");if(k!=string::npos)s=s.substr(k+2);k=s.rfind(' ');if(k!=string::npos)s=s.substr(k+1);return s;}
#define CAT_(a,b) a##b
#define CAT(a,b) CAT_(a,b)
#define DBG_LOC ESC_CYAN "[" << short_func(__PRETTY_FUNCTION__) << ":" << __LINE__ << "]" ESC_RESET " "
#ifdef DBG_OSTREAM
template<class A,class B>ostream& operator<<(ostream&os,const pair<A,B>&p){return os<<'('<<p.first<<", "<<p.second<<')';}
#define DBG_CON(Con) template<class...A>ostream& operator<<(ostream&os,const Con<A...>&v){os<<'{';bool f=1;for(const auto&e:v){if(!f)os<<", ";f=0;os<<e;}return os<<'}';}
DBG_CON(vector) DBG_CON(deque) DBG_CON(list) DBG_CON(set) DBG_CON(multiset)
DBG_CON(unordered_set) DBG_CON(unordered_multiset) DBG_CON(map) DBG_CON(multimap)
DBG_CON(unordered_map) DBG_CON(unordered_multimap)
#undef DBG_CON
template<class T,size_t N>ostream& operator<<(ostream&os,const array<T,N>&v){os<<'{';bool f=1;for(const auto&e:v){if(!f)os<<", ";f=0;os<<e;}return os<<'}';}
#endif
struct trace_guard{static inline int depth=0;string name;explicit trace_guard(string n):name(move(n)){cerr<<string(2*depth,' ')<<ESC_GRAY<<"-> "<<name<<ESC_RESET<<'\n';++depth;}~trace_guard(){--depth;cerr<<string(2*depth,' ')<<ESC_GRAY<<"<- "<<name<<ESC_RESET<<'\n';}};
#define DBG_IND string(2*trace_guard::depth,' ')
template<class T,class=void>struct has_begin_end:false_type{};
template<class T>struct has_begin_end<T,void_t<decltype(begin(declval<T&>())),decltype(end(declval<T&>()))>>:true_type{};
template<class T>struct is_pair_t:false_type{};
template<class A,class B>struct is_pair_t<pair<A,B>>:true_type{};
template<class T,class=void>struct is_tuple_t:false_type{};
template<class T>struct is_tuple_t<T,void_t<decltype(tuple_size<T>::value)>>:true_type{};
template<class T>void dbg(const T&x);
template<class T>void dbg(const pair<T*,int>&p);
template<size_t N>void dbg(const bitset<N>&b);
template<class T>void dbg(stack<T>s);
template<class T>void dbg(queue<T>q);
template<class T,class C,class Cmp>void dbg(priority_queue<T,C,Cmp>q);
void dbg_i128(i128 v){if(v==0){cerr<<'0';return;}bool neg=v<0;ui128 u=neg?(ui128)-(v+1)+1:(ui128)v;string s;while(u){s+=char('0'+int(u%10));u/=10;}if(neg)cerr<<'-';reverse(all(s));cerr<<s;}
void dbg_u128(ui128 v){if(v==0){cerr<<'0';return;}string s;while(v){s+=char('0'+int(v%10));v/=10;}reverse(all(s));cerr<<s;}
template<class T>void dbg_seq(const T&v){cerr<<'{';bool first=true;for(const auto&e:v){if(!first)cerr<<", ";first=false;dbg(e);}cerr<<'}';}
template<class T,size_t...I>void dbg_tuple(const T&t,index_sequence<I...>){cerr<<'(';size_t k=0;((cerr<<(k++?", ":""),dbg(get<I>(t))),...);cerr<<')';}
template<class T>void dbg(const pair<T*,int>&p){cerr<<'[';for(int i=0;i<p.second;++i){if(i)cerr<<", ";dbg(p.first[i]);}cerr<<']';}
template<size_t N>void dbg(const bitset<N>&b){cerr<<"0b";for(int i=(int)N-1;i>=0;--i)cerr<<b[i];cerr<<"(pc="<<(int)b.count()<<')';}
template<class T>void dbg(stack<T>s){cerr<<"{top";while(!s.empty()){cerr<<", ";dbg(s.top());s.pop();}cerr<<'}';}
template<class T>void dbg(queue<T>q){cerr<<"{front";while(!q.empty()){cerr<<", ";dbg(q.front());q.pop();}cerr<<'}';}
template<class T,class C,class Cmp>void dbg(priority_queue<T,C,Cmp>q){cerr<<"{top";while(!q.empty()){cerr<<", ";dbg(q.top());q.pop();}cerr<<'}';}
template<class T>void dbg_bits(T x){static_assert(is_integral_v<T>&&sizeof(T)<=8);ull v=(ull)x;for(int i=8*sizeof(T)-1;i>=0;--i){cerr<<char('0'+int(v>>i&1));if(i%4==0&&i)cerr<<' ';}cerr<<" popcnt="<<__builtin_popcountll(v);}
template<class T>void dbg(const T&x){
    if constexpr(is_same_v<T,i128>)dbg_i128(x);
    else if constexpr(is_same_v<T,ui128>)dbg_u128(x);
    else if constexpr(is_same_v<T,nullptr_t>)cerr<<"nullptr";
    else if constexpr(is_same_v<T,bool>)cerr<<(x?"true":"false");
    else if constexpr(is_same_v<T,char>||is_same_v<T,signed char>||is_same_v<T,unsigned char>)cerr<<'\''<<(char)x<<'\'';
    else if constexpr(is_convertible_v<T,string_view>)cerr<<'"'<<x<<'"';
    else if constexpr(is_pair_t<T>::value){cerr<<'(';dbg(x.first);cerr<<", ";dbg(x.second);cerr<<')';}
    else if constexpr(has_begin_end<T>::value)dbg_seq(x);
    else if constexpr(is_tuple_t<T>::value)dbg_tuple(x,make_index_sequence<tuple_size_v<T>>{});
    else if constexpr(is_integral_v<T>){if((ll)x==inf||(ll)x==infLL)cerr<<"inf";else if constexpr(is_signed_v<T>){if((ll)x==-inf||(ll)x==-infLL)cerr<<"-inf";else cerr<<x;}else cerr<<x;}
    else cerr<<x;
}
void dbg_all(){cerr<<'\n';}
template<class T,class...R>void dbg_all(const T&t,const R&...r){dbg(t);if(sizeof...(r))cerr<<", ";dbg_all(r...);}
#define debug(...) do{cerr<<DBG_IND<<DBG_LOC<<"["<<#__VA_ARGS__<<"] = ";dbg_all(__VA_ARGS__);}while(0)
#define HERE do{cerr<<DBG_IND<<DBG_LOC<<"here\n";}while(0)
#define DBGN(n,...) do{static ll _dbgn=0;if(_dbgn++<(ll)(n))debug(__VA_ARGS__);}while(0)
#define DBGB(x) do{cerr<<DBG_IND<<DBG_LOC<<#x" = 0b";dbg_bits(x);cerr<<'\n';}while(0)
#define DBGX(x) do{cerr<<DBG_IND<<DBG_LOC<<#x" = 0x"<<hex<<(ull)(x)<<dec<<" popcnt="<<__builtin_popcountll((ull)(x))<<'\n';}while(0)
#define db(x) "[" #x " = " << (x) << "] "
template<class T>void dbg_mat(const T&m){for(const auto&r:m){cerr<<DBG_IND<<'[';bool f=1;for(const auto&e:r){if(!f)cerr<<' ';f=0;cerr<<setw(3)<<e;}cerr<<"]\n";}}
#define DBM(...) do{cerr<<DBG_IND<<DBG_LOC<<"["<<#__VA_ARGS__<<"] =\n";dbg_mat(__VA_ARGS__);}while(0)
template<class...A>string trace_str(const A&...a){if(!sizeof...(a))return "";ostringstream os;os<<'(';int k=0;((os<<(k++?", ":"")<<a),...);os<<')';return os.str();}
#define TRACE(f,...) trace_guard CAT(_trace,__LINE__)(string(#f)+trace_str(__VA_ARGS__))
#define DB(...) trace_guard CAT(_dbgblk,__LINE__)(short_func(__PRETTY_FUNCTION__)+":"+to_string(__LINE__)+trace_str(__VA_ARGS__))
struct timer_guard{chrono::steady_clock::time_point t0;timer_guard():t0(chrono::steady_clock::now()){}~timer_guard(){cerr<<chrono::duration<double>(chrono::steady_clock::now()-t0).count()<<"s\n";}};
#define TIMEIT timer_guard CAT(_timer,__LINE__)
#define ASSERT(c) do{if(!(c)){cerr<<DBG_IND<<DBG_LOC<<"NG: "#c<<'\n';abort();}}while(0)
#define ASSERT_EQ(a,b) do{if(!((a)==(b))){cerr<<DBG_IND<<DBG_LOC<<"NG: "#a" == "#b<<'\n';debug(a,b);abort();}}while(0)
#else
#define debug(...) do{}while(0)
#define HERE do{}while(0)
#define DBGN(...) do{}while(0)
#define DBGB(...) do{}while(0)
#define DBGX(...) do{}while(0)
#define DBM(...) do{}while(0)
#define DB(...) do{}while(0)
#define db(...) ""
#define TRACE(...) do{}while(0)
#define ASSERT(c) do{}while(0)
#define ASSERT_EQ(a,b) do{}while(0)
#define TIMEIT do{}while(0)
#endif
//====
void solve()
{
	
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t=1;
    //cin>>t;
    while(t--)solve();
}
