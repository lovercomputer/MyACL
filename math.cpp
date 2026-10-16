int pow_mod(ll a,ll b,ll m){
    assert(0<=b&&m>=1);
    a%=m;
    if(a<0)a+=m;
    ll res=1;
    while(b){
        if(b&1)res=res*a%m;
        a=a*a%m;
        b>>=1;
    }
    return res;
}
int inv_mod(ll a,ll m){
    assert(m>=1);
    a%=m;
    if(a<0)a+=m;
    assert(__gcd(a,m)==1);
    ll b=m,u=1,v=0;
    while(b){
      ll t=a/b;
      a-=t*b;swap(a,b);
      u-=t*v;swap(u,v);
    }
    u%=m;
    if(u<0)u+=m;
    return u;
}
long long extgcd(long long a,long long b,long long &x,long long &y){//a在b下的逆元，x是逆元结果，y是副产物，没用
    if(b==0){x=1;y=0;return a;}
    long long x1,y1;
    long long d=extgcd(b,a%b,x1,y1);
    x=y1;
    y=x1-(a/b)*y1;
    return d;
}
pair<long long,long long> crt(const std::vector<long long>& r,const std::vector<long long>& m){
    assert(r.size()==m.size());
    int n=(int)r.size();
    long long r0=0,m0=1;
    for(int i=0;i<n;++i){
        assert(m[i]>=1);
        long long r1=r[i]%m[i];
        if(r1<0) r1+=m[i];
        long long m1=m[i];
        if(m0<m1){swap(r0,r1);swap(m0,m1);}
        if(m0%m1==0){
            if(r0%m1!=r1) return {0,0};
            continue;
        }
        long long x,y;
        long long g=extgcd(m0,m1,x,y);
        if(g==0) return {0,0};
        long long u1=m1/g;
        if((r1-r0)%g!=0) return {0,0};
        long long im=(x%u1+u1)%u1;
        long long diff=(r1-r0)/g;
        long long x0=(diff%u1+u1)%u1;
        x0=(__int128)x0*im%u1;
        r0=(long long)((__int128)r0+(__int128)x0*m0);
        m0=(long long)((__int128)m0*u1);
        r0%=m0;
        if(r0<0) r0+=m0;
    }
    return {r0,m0};
}
namespace internal{
long long safe_mod(long long x,long long m){
    x%=m;
    if(x<0)x+=m;
    return x;
}
unsigned long long floor_sum_unsigned(unsigned long long n,unsigned long long m,unsigned long long a,unsigned long long b){
      unsigned long long ans=0;
      while(true){
            if(a>=m){
                  ans+=n*(n-1)/2*(a/m);
                  a%=m;
            }
            if(b>=m){
                  ans+=n*(b/m);
                  b%=m;
            }
                unsigned long long y_max=a*n+b;
                if(y_max<m)break;
                n=(unsigned long long)(y_max/m);
                b=(unsigned long long)(y_max%m);
                std::swap(m,a);
      }
        return ans;
    }
}
long long floor_sum(long long n,long long m,long long a,long long b){//列欧几里得算法
  assert(0<=n);
  assert(1<=m);
  unsigned long long ans=0;
  if(a<0){
    unsigned long long a2=internal::safe_mod(a,m);
    ans-=1ULL*n*(n-1)/2*((a2-a)/m);
    a=a2;
  }
  if(b<0){
    unsigned long long b2=internal::safe_mod(b,m);
    ans-=1ULL*n*((b2-b)/m);
    b=b2;
  }
  return ans+internal::floor_sum_unsigned((unsigned long long)n,(unsigned long long)m,(unsigned long long)a,(unsigned long long)b);
}
