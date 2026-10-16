template<class S>
struct FenWick{
    vector<S>tree;
    int n;
    FenWick(int _n):n(_n){
        tree.assign(n+2,0);
    }
    void Add(int pos,S val){
        pos++;
        while(pos<=n){
            tree[pos-1]+=val;
            pos+=pos&-pos;
        }
    }
    S Sum(int pos){
        S res=0;
        while(pos>0){
            res+=tree[pos-1];
            pos-=pos&-pos;
        }
        return res;
    }
    S Sum(int l,int r){
        return Sum(r)-Sum(l);
    }
    int Kth(int k){
        int base=1,cur=0;
        while(base<=n)base*=2;
        while(base){
            int nxt=cur+base;
            if(nxt<=n&&tree[nxt-1]<k){
                k-=tree[nxt-1];
                cur=nxt;
            }
            base>>=1;
        }
        return cur+1;
    }
};
