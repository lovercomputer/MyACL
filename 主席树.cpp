template<class S,auto op,auto e>
struct Persistent_Seg{
    int n;
    vector<int>lc,rc;
    vector<S>val;
    vector<int>root;
    int tot;
    Persistent_Seg():n(0),tot(0){}
    explicit Persistent_Seg(const vector<S>& t,int m=0):n(0),tot(0){
        init(t,m);
    }
    void init(const vector<S>& t,int m=0){
        n=(int)t.size();
        int depth=1;
        for(int x=n;x>1;x=(x+1)>>1)++depth;
        int cap=2*n+depth*m+5;
        lc.assign(cap,0);
        rc.assign(cap,0);
        val.assign(cap,S());
        tot=0;
        root.clear();
        root.reserve(m+1);
        root.push_back(build(0,n,t));
    }
    int build(int l,int r,const vector<S>& t){
        int u=++tot;
        if(l+1==r){val[u]=t[l];return u;}
        int mid=(l+r)>>1;
        lc[u]=build(l,mid,t);
        rc[u]=build(mid,r,t);
        val[u]=op(val[lc[u]],val[rc[u]]);
        return u;
    }
    int update(int pre,int l,int r,int pos,const S& x){
        int u=++tot;
        if(l+1==r){val[u]=x;return u;}
        int mid=(l+r)>>1;
        if(pos<mid){
            lc[u]=update(lc[pre],l,mid,pos,x);
            rc[u]=rc[pre];
        }else{
            lc[u]=lc[pre];
            rc[u]=update(rc[pre],mid,r,pos,x);
        }
        val[u]=op(val[lc[u]],val[rc[u]]);
        return u;
    }
    S query(int u,int l,int r,int ql,int qr)const{
        if(r<=ql||qr<=l)return e();
        if(ql<=l&&r<=qr)return val[u];
        int mid=(l+r)>>1;
        return op(query(lc[u],l,mid,ql,qr),query(rc[u],mid,r,ql,qr));
    }
    /* ---------- 对外接口 ---------- */
    int update(int ver,int pos,const S& x){
        root.push_back(update(root[ver],0,n,pos,x));
        return (int)root.size()-1;
    }
    int copy(int ver){
        root.push_back(root[ver]);
        return (int)root.size()-1;
    }
    S prod(int ver,int ql,int qr)const{
        return query(root[ver],0,n,ql,qr);
    }
    S get(int ver,int pos)const{
        int u=root[ver],l=0,r=n;
        while(l+1!=r){
            int mid=(l+r)>>1;
            if(pos<mid){u=lc[u];r=mid;}
            else{u=rc[u];l=mid;}
        }
        return val[u];
    }
};
/*
Persistent_Seg(vec<S>&,m=0)初始化传进来的数字，预留m次update次数
update(ver,pos,x)将版本ver的第pos个位置更新成x,返回生成的版本号
copy(ver)生成一个版本为ver的数,返回生成的版本号
prod(ver,ql,qr)查询版本ver里[ql,qr),返回值
get(ver,pos)查询版本ver的第pos个位置的值,返回值
*/