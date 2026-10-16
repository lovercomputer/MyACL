template<unsigned int mod=998244353>
struct convolution{
    struct mint{
        unsigned int v;
        static constexpr unsigned int get_mod(){return mod;}
        constexpr mint():v(0){}
        mint(long long x){v=(unsigned int)(((x%(long long)mod)+(long long)mod)%(long long)mod);}
        unsigned int val()const{return v;}
        mint operator-()const{return mint(v?(long long)mod-v:0);}
        mint&operator+=(const mint&o){v+=o.v;if(v>=mod)v-=mod;return *this;}
        mint&operator-=(const mint&o){v+=mod-o.v;if(v>=mod)v-=mod;return *this;}
        mint&operator*=(const mint&o){v=(unsigned int)(1ull*v*o.v%mod);return *this;}
        mint&operator/=(const mint&o){return *this*=o.inv();}
        mint operator+(const mint&o)const{return mint(*this)+=o;}
        mint operator-(const mint&o)const{return mint(*this)-=o;}
        mint operator*(const mint&o)const{return mint(*this)*=o;}
        mint operator/(const mint&o)const{return mint(*this)/=o;}
        mint pow(long long e)const{
            mint r=1,b=*this;
            while(e){
                if(e&1)r*=b;
                b*=b;
                e>>=1;
            }
            return r;
        }
        mint inv()const{return pow((long long)mod-2);}
    };
    static constexpr int countr_zero(unsigned int x){return __builtin_ctz(x);}
    static unsigned int bit_ceil(unsigned int n){
        unsigned int x=1;
        while(x<n)x<<=1;
        return x;
    }
    static constexpr long long pow_mod(long long x,long long n,long long m){
        long long r=1%m;
        x%=m;
        while(n){
            if(n&1)r=r*x%m;
            x=x*x%m;
            n>>=1;
        }
        return r;
    }
    static constexpr int primitive_root(){
        if(mod==2)return 1;
        if(mod==167772161)return 3;
        if(mod==469762049)return 3;
        if(mod==754974721)return 11;
        if(mod==998244353)return 3;
        int divs[20]={},cnt=1,x=(int)((mod-1)/2);
        divs[0]=2;
        while(x%2==0)x/=2;
        for(int i=3;(long long)i*i<=x;i+=2)if(x%i==0){
            divs[cnt++]=i;
            while(x%i==0)x/=i;
        }
        if(x>1)divs[cnt++]=x;
        for(int g=2;;++g){
            bool ok=true;
            for(int i=0;i<cnt;++i)if(pow_mod(g,(long long)(mod-1)/divs[i],(long long)mod)==1){ok=false;break;}
            if(ok)return g;
        }
    }
    static constexpr long long inv_mod(long long a,long long b){
        a%=b;
        if(a<0)a+=b;
        long long s=b,t=a,m0=0,m1=1;
        while(t){
            long long u=s/t;
            s-=t*u;
            m0-=m1*u;
            long long tmp=s;s=t;t=tmp;
            tmp=m0;m0=m1;m1=tmp;
        }
        if(m0<0)m0+=b/s;
        return m0;
    }
    static constexpr long long safe_mod(long long x,long long m){
        x%=m;
        if(x<0)x+=m;
        return x;
    }
    struct fft_info{
        static constexpr int rank2=countr_zero(mod-1);
        array<mint,rank2+1> root,iroot;
        array<mint,max(0,rank2-1)> rate2,irate2;
        array<mint,max(0,rank2-2)> rate3,irate3;
        fft_info(){
            root[rank2]=mint(primitive_root()).pow((long long)(mod-1)>>rank2);
            iroot[rank2]=root[rank2].inv();
            for(int i=rank2-1;i>=0;--i){
                root[i]=root[i+1]*root[i+1];
                iroot[i]=iroot[i+1]*iroot[i+1];
            }
            {
                mint prod=1,iprod=1;
                for(int i=0;i<=rank2-2;++i){
                    rate2[i]=root[i+2]*prod;
                    irate2[i]=iroot[i+2]*iprod;
                    prod*=iroot[i+2];
                    iprod*=root[i+2];
                }
            }
            {
                mint prod=1,iprod=1;
                for(int i=0;i<=rank2-3;++i){
                    rate3[i]=root[i+3]*prod;
                    irate3[i]=iroot[i+3]*iprod;
                    prod*=iroot[i+3];
                    iprod*=root[i+3];
                }
            }
        }
    };
    static void butterfly(vector<mint>&a){
        int n=(int)a.size(),h=countr_zero((unsigned int)n);
        static const fft_info info;
        int len=0;
        while(len<h){
            if(h-len==1){
                int p=1<<(h-len-1);
                mint rot=1;
                for(int s=0;s<(1<<len);++s){
                    int offset=s<<(h-len);
                    for(int i=0;i<p;++i){
                        auto l=a[i+offset],r=a[i+offset+p]*rot;
                        a[i+offset]=l+r;
                        a[i+offset+p]=l-r;
                    }
                    if(s+1!=(1<<len))rot*=info.rate2[countr_zero(~(unsigned int)(s))];
                }
                ++len;
            }else{
                int p=1<<(h-len-2);
                mint rot=1,imag=info.root[2];
                unsigned long long mod2=1ull*mint::get_mod()*mint::get_mod();
                for(int s=0;s<(1<<len);++s){
                    mint rot2=rot*rot,rot3=rot2*rot;
                    int offset=s<<(h-len);
                    for(int i=0;i<p;++i){
                        auto a0=1ull*a[i+offset].val();
                        auto a1=1ull*a[i+offset+p].val()*rot.val();
                        auto a2=1ull*a[i+offset+2*p].val()*rot2.val();
                        auto a3=1ull*a[i+offset+3*p].val()*rot3.val();
                        auto a1na3imag=1ull*mint(a1+mod2-a3).val()*imag.val();
                        auto na2=mod2-a2;
                        a[i+offset]=a0+a2+a1+a3;
                        a[i+offset+p]=a0+a2+(2*mod2-(a1+a3));
                        a[i+offset+2*p]=a0+na2+a1na3imag;
                        a[i+offset+3*p]=a0+na2+(mod2-a1na3imag);
                    }
                    if(s+1!=(1<<len))rot*=info.rate3[countr_zero(~(unsigned int)(s))];
                }
                len+=2;
            }
        }
    }
    static void butterfly_inv(vector<mint>&a){
        int n=(int)a.size(),h=countr_zero((unsigned int)n);
        static const fft_info info;
        int len=h;
        while(len){
            if(len==1){
                int p=1<<(h-len);
                mint irot=1;
                for(int s=0;s<(1<<(len-1));++s){
                    int offset=s<<(h-len+1);
                    for(int i=0;i<p;++i){
                        auto l=a[i+offset],r=a[i+offset+p];
                        a[i+offset]=l+r;
                        a[i+offset+p]=(unsigned long long)((unsigned int)(l.val()-r.val())+mint::get_mod())*irot.val();
                    }
                    if(s+1!=(1<<(len-1)))irot*=info.irate2[countr_zero(~(unsigned int)(s))];
                }
                --len;
            }else{
                int p=1<<(h-len);
                mint irot=1,iimag=info.iroot[2];
                for(int s=0;s<(1<<(len-2));++s){
                    mint irot2=irot*irot,irot3=irot2*irot;
                    int offset=s<<(h-len+2);
                    for(int i=0;i<p;++i){
                        auto a0=1ull*a[i+offset].val();
                        auto a1=1ull*a[i+offset+p].val();
                        auto a2=1ull*a[i+offset+2*p].val();
                        auto a3=1ull*a[i+offset+3*p].val();
                        auto a2na3iimag=1ull*mint((mint::get_mod()+a2-a3)*iimag.val()).val();
                        a[i+offset]=a0+a1+a2+a3;
                        a[i+offset+p]=(a0+(mint::get_mod()-a1)+a2na3iimag)*irot.val();
                        a[i+offset+2*p]=(a0+a1+(mint::get_mod()-a2)+(mint::get_mod()-a3))*irot2.val();
                        a[i+offset+3*p]=(a0+(mint::get_mod()-a1)+(mint::get_mod()-a2na3iimag))*irot3.val();
                    }
                    if(s+1!=(1<<(len-2)))irot*=info.irate3[countr_zero(~(unsigned int)(s))];
                }
                len-=2;
            }
        }
    }
    static vector<mint> conv_naive(const vector<mint>&a,const vector<mint>&b){
        int n=(int)a.size(),m=(int)b.size();
        vector<mint>ans(n+m-1);
        if(n<m){
            for(int j=0;j<m;++j)for(int i=0;i<n;++i)ans[i+j]+=a[i]*b[j];
        }else{
            for(int i=0;i<n;++i)for(int j=0;j<m;++j)ans[i+j]+=a[i]*b[j];
        }
        return ans;
    }
    static vector<mint> conv_fft(vector<mint>a,vector<mint>b){
        int n=(int)a.size(),m=(int)b.size();
        int z=(int)bit_ceil((unsigned int)(n+m-1));
        a.resize(z);
        butterfly(a);
        b.resize(z);
        butterfly(b);
        for(int i=0;i<z;++i)a[i]*=b[i];
        butterfly_inv(a);
        a.resize(n+m-1);
        mint iz=mint(z).inv();
        for(int i=0;i<n+m-1;++i)a[i]*=iz;
        return a;
    }
    static vector<mint> conv(const vector<mint>&a,const vector<mint>&b){
        int n=(int)a.size(),m=(int)b.size();
        if(!n||!m)return {};
        assert((mod-1)%bit_ceil((unsigned int)(n+m-1))==0);
        if(min(n,m)<=60)return conv_naive(a,b);
        return conv_fft(a,b);
    }
    template<class T,enable_if_t<is_integral<T>::value>* =nullptr>
    static vector<T> conv(const vector<T>&a,const vector<T>&b){
        int n=(int)a.size(),m=(int)b.size();
        if(!n||!m)return {};
        assert((mod-1)%bit_ceil((unsigned int)(n+m-1))==0);
        vector<mint>a2(n),b2(m);
        for(int i=0;i<n;++i)a2[i]=mint(a[i]);
        for(int i=0;i<m;++i)b2[i]=mint(b[i]);
        auto c2=conv(move(a2),move(b2));
        vector<T>c(n+m-1);
        for(int i=0;i<n+m-1;++i)c[i]=(T)c2[i].val();
        return c;
    }
    static vector<long long> conv_ll(const vector<long long>&a,const vector<long long>&b){
        int n=(int)a.size(),m=(int)b.size();
        if(!n||!m)return {};
        static constexpr unsigned long long MOD1=754974721;
        static constexpr unsigned long long MOD2=167772161;
        static constexpr unsigned long long MOD3=469762049;
        static constexpr unsigned long long M2M3=MOD2*MOD3,M1M3=MOD1*MOD3,M1M2=MOD1*MOD2,M1M2M3=MOD1*MOD2*MOD3;
        static constexpr long long i1=inv_mod(M2M3,MOD1),i2=inv_mod(M1M3,MOD2),i3=inv_mod(M1M2,MOD3);
        static constexpr int MAX_AB_BIT=24;
        static_assert(MOD1%(1ull<<MAX_AB_BIT)==1,"MOD1 is not enough");
        static_assert(MOD2%(1ull<<MAX_AB_BIT)==1,"MOD2 is not enough");
        static_assert(MOD3%(1ull<<MAX_AB_BIT)==1,"MOD3 is not enough");
        assert(n+m-1<=(1<<MAX_AB_BIT));
        auto c1=convolution<MOD1>::conv(a,b);
        auto c2=convolution<MOD2>::conv(a,b);
        auto c3=convolution<MOD3>::conv(a,b);
        vector<long long>c(n+m-1);
        static constexpr unsigned long long offset[5]={0,0,M1M2M3,2*M1M2M3,3*M1M2M3};
        for(int i=0;i<n+m-1;++i){
            unsigned long long x=0;
            x+=(c1[i]*i1)%MOD1*M2M3;
            x+=(c2[i]*i2)%MOD2*M1M3;
            x+=(c3[i]*i3)%MOD3*M1M2;
            long long diff=c1[i]-safe_mod((long long)x,(long long)MOD3*0+(long long)MOD1);
            if(diff<0)diff+=MOD1;
            x-=offset[diff%5];
            c[i]=(long long)x;
        }
        return c;
    }
};
