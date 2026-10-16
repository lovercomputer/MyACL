#include <bits/stdc++.h>
using namespace std;
//#define int long long
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define vec vector
#define str string
#define yes "Yes"
#define no "No"
#define En "\n"
#define en "\n"
#define se " "
#define atan2l(x,y) atan2l(y,x)
typedef long long ll;
const int inf = INT_MAX;
const int mod = 998244353;
struct DSU{
    int n;
    vec<int>par,siz;
    DSU(int _n):n(_n),par(_n+1),siz(_n+1,0){
        iota(all(par),0);
    }
    int find(int x){
        return par[x]==x?x:par[x]=find(par[x]);
    }
    bool unite(int x,int y){
        int rx=find(x);
        int ry=find(y);
        if(rx==ry)return false;
        if(siz[rx]<siz[ry])swap(rx,ry);
        par[ry]=rx;
        siz[rx]+=siz[ry];
        return true;
    }
};
template<class T>
struct wuf{
    vec<int>par,ranks;
    vec<T>diff_wei;
    wuf(int _n=0,T _sum=0):par(_n+1),ranks(_n+1,1),diff_wei(_n+1,_sum){
        iota(all(par),0);
    }
    int root(int x){
        if(par[x]==x)return x;
        else {
            int r=root(par[x]);
            diff_wei[x]+=diff_wei[par[x]];
            return par[x]=r;
        }
    }
    int weight(int u){
        root(u);
        return diff_wei[u];
    }
    bool issame(int x,int y){return root(x)==root(y);}
    bool add(int u,int v,int w){
        w+=weight(u),w-=weight(v);
        if(u==v)return false;
        int fu=root(u),fv=root(v);
        if(ranks[fu]<ranks[fv])swap(fu,fv),w=-w;
        if(ranks[fu]==ranks[fv])++ranks[fu];
        par[fv]=fu;
        diff_wei[fv]=w;
        return true;
    }
    T diff(int u,int v){
        return weight(u)-weight(v);
    }
};
signed main()
{
    return 0;
}
