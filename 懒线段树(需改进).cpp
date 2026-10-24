template<class S,
         auto Op,
         auto E,
         class F,
         auto Mapping,
         auto Composition,
         auto Id
>struct Lazy_Seg{
    vector<S>tree;
    vector<F>tf;
    int n;
    Lazy_Seg(int _n):n(_n){
        tree.assign(4*n+4,E());
        tf.assign(4*n+4,Id());
    }
    Lazy_Seg(const vector<S>&t):n(sz(t)),tree(4*sz(t),E()),tf(4*sz(t),Id()){
        n=sz(t);
        Build(1,0,n-1,t);
    }
    void Build(int p,int l,int r,const vector<S>&t){
        if(l==r){tree[p]=t[l];return;}
        int mid=(l+r)/2;
        Build(p<<1,l,mid,t);
        Build(p<<1|1,mid+1,r,t);
        tree[p]=Op(tree[p<<1],tree[p<<1|1]);
    }
    void PushDown(int p){
        if(tf[p]==Id())return;
        tf[p<<1]=Composition(tf[p],tf[p<<1]);
        tree[p<<1]=Mapping(tf[p],tree[p<<1]);
        tf[p<<1|1]=Composition(tf[p],tf[p<<1|1]);
        tree[p<<1|1]=Mapping(tf[p],tree[p<<1|1]);
        tf[p]=Id();
    }
    void Apply(int p,int l,int r,F f,int ql,int qr){
        if(r<ql||l>=qr)return;
        if(ql<=l&&qr>r){
            tf[p]=Composition(f,tf[p]),tree[p]=Mapping(f,tree[p]);
            return;
        }
        if(tf[p]!=Id())PushDown(p);
        int mid=(l+r)/2;
        Apply(p<<1,l,mid,f,ql,qr);
        Apply(p<<1|1,mid+1,r,f,ql,qr);
        tree[p]=Op(tree[p<<1],tree[p<<1|1]);
    }
    S Get(int p,int l,int r,int ql,int qr){
        if(r<ql||l>=qr)return E();
        if(ql<=l&&qr>r)return tree[p];
        if(tf[p]!=Id())PushDown(p);
        int mid=(l+r)/2;
        return Op(Get(p<<1,l,mid,ql,qr),Get(p<<1|1,mid+1,r,ql,qr));
    }
    void Set(int p,int l,int r,int pos,S x){
        if(l==r){
            tree[p]=x;
            tf[p]=Id();
            return;
        }
        if(tf[p]!=Id())PushDown(p);
        int mid=(l+r)/2;
        if(pos<=mid)Set(p<<1,l,mid,pos,x);
        else Set(p<<1|1,mid+1,r,pos,x);
        tree[p]=Op(tree[p<<1],tree[p<<1|1]);
    }
    void Set(int pos,S x){Set(1,0,n-1,pos,x);}
    void Apply(int l,int r,F f){Apply(1,0,n-1,f,l,r);}
    void Apply(int pos,F f){Apply(1,0,n-1,f,pos,pos+1);}
    S Get(int pos){return Get(1,0,n-1,pos,pos+1);}
    S Prod(int l,int r){return Get(1,0,n-1,l,r);}
    S AllProd(){return Get(1,0,n-1,0,n);}
};
using S=ll;
S op(const S& a,const S& b){return a>b?b:a;}
S e(){return inf;}
using F=ll;
S mapping(const S& x,const F& f){return x+f;}
F composition(const F& l,const F& r){return l+r;}
F id(){return 0;}
