struct hash_str{//配合树状树状
    const int M=998244353,B=911382323;
    const int invB=514180328;
    int n;
    vec<int>Bs;
    vec<int>invBs;
    BIT t1,t2;
    hash_str(const str& s):t1(sz(s)),Bs(sz(s)+1,1),invBs(sz(s)+1,1),t2(sz(s)){
        n=sz(s);
        for(int i=1;i<=n;++i){
            Bs[i]=Bs[i-1]*B%M;
            invBs[i]=invBs[i-1]*invB%mod;
        }
        for(int i=1;i<=n;++i){
            int num=s[i-1]-'a'+1;
            int w=Bs[i-1];
            t1.add(i,num*w%mod);
        }
        for(int i=1;i<=n;++i){
            int num=s[i-1]-'a'+1;
            int pos=n-i+1;
            int w=Bs[n-i];
            t2.add(pos,num*w%mod);
        }
    }
    int hash_val1(int l,int r){//正向
        int res=(t1.sum(r)-t1.sum(l-1)+M)%M;
        res=(res*invBs[l-1])%M;
        return res;
    }
    void change1(int idx,int c){//位置，变化值
        t1.add(idx,c*Bs[idx-1]%M);
    }
    int hash_val2(int l,int r){//反向
        int L=n-r+1;
        int R=n-l+1;
        int res=(t2.sum(R)-t2.sum(L-1)+M)%M;
        res=(res*invBs[L-1])%M;
        return res;
    }
    void change2(int idx,int c){
        int x=n-idx+1;
        int w=Bs[n-idx];
        t2.add(x,c*w%M);
    }
};
struct HashNode{//计算几百位数乘以几百位数的
    static constexpr array<long long,3>MOD={998244353LL,1000000007LL,1000000009LL};
    static constexpr int siz=3;
    array<long long,siz>m;
    HashNode():m{}{}
    HashNode(const str& s){
        bool f=(s[0]=='-');
        int n=sz(s);
        for(int i=0;i<siz;++i){
                int res=0;
                for(int j=f;j<n;++j){
                    res=(res*10+(s[j]-'0'))%MOD[i];
            }
            if(f)m[i]=(MOD[i]-res)%MOD[i];
            else m[i]=res;
        }
    }
    HashNode(const array<long long,siz>&arr):m(arr){}
    HashNode& operator=(const array<long long,siz>arr){for(int i=0;i<siz;++i)m[i]=arr[i];return *this;}
    bool operator==(const HashNode&o)const{return m==o.m;}
    bool operator!=(const HashNode&o)const{return m!=o.m;}
    bool operator<(const HashNode&o)const{return m<o.m;}
    long long inv(const long long& i,const long long& j,const long long& Mod)const{
        long long a=i,b=j-2;
        long long res=1;
        while(b){
            if(b&1)res*=a,res%=Mod;
            a=(a*a)%Mod;
            b>>=1;
        }
        return res;
    }
    HashNode operator*(const HashNode&o)const{array<long long,sz(MOD)>res;
    for(int i=0;i<siz;++i)res[i]=(m[i]*o.m[i])%MOD[i];return HashNode(res);}
    HashNode operator+(const HashNode&o)const{array<long long,sz(MOD)>res;
    for(int i=0;i<siz;++i)res[i]=(m[i]+o.m[i])%MOD[i];return HashNode(res);}
    HashNode operator-(const HashNode&o)const{array<long long,sz(MOD)>res;
    for(int i=0;i<siz;++i)res[i]=(m[i]-o.m[i]+MOD[i])%MOD[i];return HashNode(res);}
    HashNode operator/(const HashNode&o)const{array<long long,sz(MOD)>res;
    for(int i=0;i<siz;++i)res[i]=(m[i]*inv(o.m[i],MOD[i],MOD[i])+MOD[i])%MOD[i];return HashNode(res);}
    HashNode& operator+=(const HashNode&o){for(int i=0;i<siz;++i)m[i]=(m[i]+o.m[i])%MOD[i];return *this;}
    HashNode& operator-=(const HashNode&o){for(int i=0;i<siz;++i)m[i]=(m[i]-o.m[i]+MOD[i])%MOD[i];return *this;}
    HashNode& operator*=(const HashNode&o){for(int i=0;i<siz;++i)m[i]=(m[i]*o.m[i])%MOD[i];return *this;}
    HashNode& operator/=(const HashNode&o){for(int i=0;i<siz;++i)m[i]=(m[i]*inv(o.m[i],MOD[i],MOD[i]))%MOD[i];return *this;}
};
istream& operator>>(istream& in,HashNode&h){
    string s;
    in>>s;
    h=HashNode(s);
    return in;
}
