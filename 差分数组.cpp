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
const int inf = 1e9;
const int mod = 998244353;
template<typename T>
struct PPD{//乙级胖达
    vector<T>ori,fin;//初始状态，最终状态
    int n,d,pos;
    PPD(int _n,int _d,int _pos,vector<T>&_ori):n(_n),d(_d),pos(_pos),ori(_ori),fin(_ori){}//数组大小，间隔，每次变化幅度，预处理数组
    void work(){
        for(int i=1;i<n;++i){
            int cnt=abs(fin[i]-fin[i-1]);
            if(cnt<=d)continue;
            if(pos>0){
                if(fin[i]>fin[i-1])fin[i-1]+=cnt-d;
                else fin[i]+=cnt-d;
            }else{
                if(fin[i]>fin[i-1])fin[i]-=cnt-d;
                else fin[i-1]-=cnt-d;
            }
        }
        for(int i=n-2;i>=0;--i){
            int cnt=abs(fin[i]-fin[i+1]);
            if(cnt<=d)continue;
            if(pos>0){
                if(fin[i]>fin[i+1])fin[i+1]+=cnt-d;
                else fin[i]+=cnt-d;
            }else{
                if(fin[i]>fin[i+1])fin[i]-=cnt-d;
                else fin[i+1]-=cnt-d;
            }
        }
    }
    int get_res(){
        int res=0;
        for(int i=0;i<n;++i)res+=abs(ori[i]-fin[i]);
        return res;
    }
};
struct diff2D{//二维差分+work前缀和
    int n;
    vec<vec<int>>dif;
    diff2D(int _n):n(_n),dif(_n+2,vec<int>(_n+2,0)){}
    void add(int x1,int y1,int x2,int y2,int d){
        dif[x1][y1]+=d;
        dif[x1][y2+1]-=d;
        dif[x2+1][y1]-=d;
        dif[x2+1][y2+1]+=d;
    }
    void work(){
        for(int i=0;i<=n+1;++i)for(int j=0;j<=n+1;++j)if(j)dif[i][j]+=dif[i][j-1];//注意是更规范的是把n改成n+1
        for(int i=0;i<=n+1;++i)for(int j=0;j<=n+1;++j)if(i)dif[i][j]+=dif[i-1][j];
    }
};
struct diff1D{//一维差分+前缀和
    vec<int>cnt;
    int n;
    diff1D(int _n):n(_n),cnt(_n+2,0){}
    void add(int s,int t,int d){
        cnt[s]+=d;
        cnt[t+1]-=d;
    }
    void work(){
        for(int i=1;i<=n+1;++i){
            cnt[i]+=cnt[i-1];
        }
    }
};
int main()
{
    cout<<"Hello World\n";
    return 0;
}
