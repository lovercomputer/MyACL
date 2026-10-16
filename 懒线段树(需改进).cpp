template<class S,//tree数据类型
		 auto Op,//合并操作
		 auto E,//tr单位元
		 class F,//懒标记类型
		 auto Mapping,//合成懒标记到tr
		 auto Composition,//懒标记下传
		 auto Id//懒标记单位元
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
	    if(tf[p]==Id())return ;
		tf[p<<1]=Composition(tf[p],tf[p<<1]);
		tree[p<<1]=Mapping(tf[p],tree[p<<1]);
		tf[p<<1|1]=Composition(tf[p],tf[p<<1|1]);
		tree[p<<1|1]=Mapping(tf[p],tree[p<<1|1]);
		tf[p]=Id();
	}
	void Apply(int p,int l,int r,F f,int ql,int qr){//左闭右开
		if(r<ql||l>=qr)return;
		if(ql<=l&&qr>r){tf[p]=Composition(f,tf[p]),tree[p]=Mapping(f,tree[p]);return;}
		if(tf[p]!=Id())PushDown(p);
		int mid=(l+r)/2;
		Apply(p<<1,l,mid,f,ql,qr);
		Apply(p<<1|1,mid+1,r,f,ql,qr);
		tree[p]=Op(tree[p<<1],tree[p<<1|1]);
	}
	S Get(int p,int l,int r,int ql,int qr){
		if(r<ql||l>=qr)return E();
		if(ql<=l&&qr>r){return tree[p];}
		if(tf[p]!=Id())PushDown(p);
		int mid=(l+r)/2;
		return Op(Get(p<<1,l,mid,ql,qr),Get(p<<1|1,mid+1,r,ql,qr));
    }
	void Apply(int l,int r,F f){Apply(1,0,n-1,f,l,r);}
	void Apply(int pos,F f){Apply(1,0,n-1,f,pos,pos+1);}
	S Get(int pos){return Get(1,0,n-1,pos,pos+1);}
	S Prod(int l,int r){return Get(1,0,n-1,l,r);}//左闭右开
	S AllProd(){return Get(1,0,n-1,0,n);}
};