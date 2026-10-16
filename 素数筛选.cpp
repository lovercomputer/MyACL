#include <bits/stdc++.h>
using namespace std;
#define int long long
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
struct cal_pr{//计算每个数的最小质因数/素数
    int n;
    vec<int>lpf,prime;
    cal_pr(int _n):n(_n),lpf(_n+1){
        iota(all(lpf),0);
        for(int i=2;i<=n;++i){
            if(lpf[i]==i)prime.pb(i);
            for(auto& p:prime){
                if(p*i>n||p>lpf[i])break;
                lpf[p*i]=p;
            }
        }
    }
};
struct big_prime{//判断大整数是否是素数
        int power (__int128 a ,int b,int m) {
        __int128 res=1;
        while (b){
            if (b&1)res*=a,res%=m;
            a=a*a%m;
            b>>=1;
        }
        return (int)res;
    }
    bool is_prime(const int& n){
        if (n<=2)return n==2;
        if (n%2==0)return false;
        vec<int>pri={2,3,5,7,11};
        int d=(n-1)/((1-n)&(n-1));
        for (int& x:pri) {
            int t=d;
            int a=power(x,t,n);
            if (a==0||a==1)continue;
            while (a!=n-1) {
                t *=2;
                if (t==n-1)return false;
                a = ( ll )((__int128)a*a%n);
                if (a==1)return false;
            }
        }
        return true;
    }
};
struct aisp{//埃氏筛
    int n;
    vec<bool>isp;
    aisp(int _n):n(_n),isp(_n+1,false){
        isp[0]=isp[1]=true;
        for(int i=2;i<=n;++i){
            if(!isp[i]){
                for(int j=i*i;j<=n;j+=i){
                    isp[j]=true;
                }
            }
        }
    }
};
signed main()
{
    return 0;
}
