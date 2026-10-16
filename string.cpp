struct SA{
    int n;
    vector<int>sa;
    SA(int _n,const string& s):n(_n),sa(_n){
        assert(_n==(int)s.size());
        init(s);
    }
    static vector<int> naive(const vector<int>& s){
        int n=(int)s.size();
        vector<int> sa(n);
        iota(all(sa),0);
        sort(all(sa),[&](int l,int r){
            if(l==r)return false;
            while(l<n&&r<n){
                if(s[l]!=s[r])return s[l]<s[r];
                l++;r++;
            }
            return l==n;
        });
        return sa;
    }
    static vector<int> doubling(const vector<int>& s){
        int n=(int)s.size();
        vector<int> sa(n),rnk=s,tmp(n);
        iota(all(sa),0);
        for(int k=1;k<n;k*=2){
            auto cmp=[&](int x,int y){
                if(rnk[x]!=rnk[y])return rnk[x]<rnk[y];
                int rx=x+k<n?rnk[x+k]:-1;
                int ry=y+k<n?rnk[y+k]:-1;
                return rx<ry;
            };
            sort(all(sa),cmp);
            tmp[sa[0]]=0;
            for(int i=1;i<n;++i)tmp[sa[i]]=tmp[sa[i-1]]+(cmp(sa[i-1],sa[i])?1:0);
            swap(tmp,rnk);
        }
        return sa;
    }
    static vector<int> sais(const vector<int>& s,int upper){
        int n=(int)s.size();
        if(n==0)return {};
        if(n==1)return {0};
        if(n==2)return s[0]<s[1]?vector<int>{0,1}:vector<int>{1,0};
        if(n<10)return naive(s);
        if(n<40)return doubling(s);
        vector<int> sa(n);
        vector<char> ls(n);
        for(int i=n-2;i>=0;--i)ls[i]=(s[i]==s[i+1])?ls[i+1]:(s[i]<s[i+1]);
        vector<int> sum_l(upper+1),sum_s(upper+1);
        for(int i=0;i<n;++i){
            if(!ls[i])sum_s[s[i]]++;
            else sum_l[s[i]+1]++;
        }
        for(int i=0;i<=upper;++i){
            sum_s[i]+=sum_l[i];
            if(i<upper)sum_l[i+1]+=sum_s[i];
        }
        auto induce=[&](const vector<int>& lms){
            fill(all(sa),-1);
            vector<int> buf(upper+1);
            copy(all(sum_s),buf.begin());
            for(auto d:lms){
                if(d==n)continue;
                sa[buf[s[d]]++]=d;
            }
            copy(all(sum_l),buf.begin());
            sa[buf[s[n-1]]++]=n-1;
            for(int i=0;i<n;++i){
                int v=sa[i];
                if(v>=1&&!ls[v-1])sa[buf[s[v-1]]++]=v-1;
            }
            copy(all(sum_l),buf.begin());
            for(int i=n-1;i>=0;--i){
                int v=sa[i];
                if(v>=1&&ls[v-1])sa[--buf[s[v-1]+1]]=v-1;
            }
        };
        vector<int> lms_map(n+1,-1);
        int m=0;
        for(int i=1;i<n;++i)if(!ls[i-1]&&ls[i])lms_map[i]=m++;
        vector<int> lms;
        lms.reserve(m);
        for(int i=1;i<n;++i)if(!ls[i-1]&&ls[i])lms.push_back(i);
        induce(lms);
        if(m){
            vector<int> sorted_lms;
            sorted_lms.reserve(m);
            for(int v:sa)if(lms_map[v]!=-1)sorted_lms.push_back(v);
            vector<int> rec_s(m);
            int rec_upper=0;
            rec_s[lms_map[sorted_lms[0]]]=0;
            for(int i=1;i<m;++i){
                int l=sorted_lms[i-1],r=sorted_lms[i];
                int end_l=(lms_map[l]+1<m)?lms[lms_map[l]+1]:n;
                int end_r=(lms_map[r]+1<m)?lms[lms_map[r]+1]:n;
                bool same=true;
                if(end_l-l!=end_r-r)same=false;
                else{
                    while(l<end_l){
                        if(s[l]!=s[r])break;
                        l++;r++;
                    }
                    if(l==n||s[l]!=s[r])same=false;
                }
                if(!same)rec_upper++;
                rec_s[lms_map[sorted_lms[i]]]=rec_upper;
            }
            vector<int> rec_sa=sais(rec_s,rec_upper);
            for(int i=0;i<m;++i)sorted_lms[i]=lms[rec_sa[i]];
            induce(sorted_lms);
        }
        return sa;
    }
    void init(const string& s){
        vector<int> a(s.size());
        for(int i=0;i<(int)s.size();++i)a[i]=(unsigned char)s[i];
        sa=sais(a,255);
    }
};
struct LCP{
    int n;
    vector<int>lcp;
    LCP(int _n,const string& s,const vector<int>& sa):n(_n),lcp(_n>0?_n-1:0){
        assert(_n==(int)s.size());
        assert((int)sa.size()==_n);
        if(_n==0)return;
        vector<int> rank(_n);
        for(int i=0;i<_n;++i)rank[sa[i]]=i;
        int h=0;
        for(int i=0;i<_n;++i){
            if(h)h--;
            if(rank[i]==0)continue;
            int j=sa[rank[i]-1];
            while(i+h<_n&&j+h<_n&&s[i+h]==s[j+h])h++;
            lcp[rank[i]-1]=h;
        }
    }
};
struct Z{
    int n;
    vector<int>z;
    Z(int _n,const string& s):n(_n),z(_n){
        assert(_n==(int)s.size());
        if(_n==0)return;
        for(int i=1,j=0;i<_n;++i){
            int& k=z[i];
            k=(j+z[j]<=i)?0:min(j+z[j]-i,z[i-j]);
            while(i+k<_n&&s[k]==s[i+k])k++;
            if(j+z[j]<i+z[i])j=i;
        }
        z[0]=_n;
    }
};
