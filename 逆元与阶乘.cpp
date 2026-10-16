struct Mint{
    ll x;
    Mint():x(0){}
    Mint(ll _x):x(_x%mod){if(x<0)x+=mod;}
    Mint inv()const{
        ll a=x,b=mod-2;
        ll res=1;
        while(b){
            if(b&1)res*=a,res%=mod;
            a=(a*a)%mod;
            b>>=1;
        }
        return Mint(res);
    }
    Mint pow(ll n)const{
        ll a=x,b=n;
        ll res=1;
        while(b){
            if(b&1)res*=a,res%=mod;
            a=(a*a)%mod;
            b>>=1;
        }
        return Mint(res);
    }
    Mint& operator+=(const Mint& o){x+=o.x;if(x>=mod)x-=mod;return *this;}
    Mint& operator-= (const Mint& o){x-=o.x;if(x<0)x+=mod;return *this;}
    Mint& operator*=(const Mint& o){x=(x*o.x)%mod;return *this;}
    Mint& operator/=(const Mint& o){return *this*=o.inv();}
    Mint    operator+ (const Mint& o)const {Mint res=*this;return res+=o;}
    Mint    operator-  (const Mint& o)const {Mint res=*this;return res-=o;}
    Mint    operator*  (const Mint& o)const {Mint res=*this;return res*=o;}
    Mint    operator/  (const Mint& o)const {Mint res=*this;return res*=o.inv();}
    bool    operator==(const Mint&o) const { return x==o.x; }
    bool    operator!=(const Mint&o) const { return x!=o.x; }
    bool    operator<(const Mint&o) const { return x<o.x; }
    Mint&  operator++() {x++;if (x == mod) x = 0;return *this;}
    Mint    operator++(int) {Mint old = *this;++(*this);return old;}
    Mint& operator--() {if (x == 0) x = mod;x--;return *this;}
    Mint    operator--(int) {Mint old = *this;--(*this);return old;}
};
vector<Mint>fact,inv_fact;
void init(int n){
    fact.resize(n+1,1);
    inv_fact.resize(n+1,1);
    for(int i=2;i<=n;++i)fact[i]=fact[i-1]*i;
    inv_fact[n]=fact[n].inv();
    for(int i=n-1;i>=1;--i)inv_fact[i]=inv_fact[i+1]*(i+1);
}
Mint C(const int& a,const int& b){
    if(b<0||b>a)return Mint(0);
    return fact[a]*inv_fact[a-b]*inv_fact[b];
}
ostream& operator<<(ostream& out,const Mint& m){
        return out<<m.x;
    }
istream& operator>>(istream& in,Mint& m){
    ll val;
    in>>val;
    m=Mint(val);
    return in;
}
