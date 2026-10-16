template<class S,
		 auto&& op,
		 auto&& e
>struct SegTree{
	vector<S>tree;
	int n;
	SegTree():SegTree(0){}
	SegTree(int _n):n(_n){
		tree.assign(4*n,e());
	}
	SegTree(const vector<S>&t):n(sz(t)){
		n=sz(t);
		tree.assign(4*n,e());
		Build(1,0,n-1,t);
	}
	void Build(int p,int l,int r,const vector<S>&t)
	{
		//assert(l>=0&&r<n&&l<=r);
		if(l==r){tree[p]=t[l];return;}
		int mid=(l+r)/2;
		Build(p<<1,l,mid,t);
		Build(p<<1|1,mid+1,r,t);
		tree[p]=op(tree[p<<1],tree[p<<1|1]);
	}
	S Get(int p,int l,int r,int ql,int qr)
	{
		//assert(ql>=0&&qr<=n&&l<=r);
		if(r<ql||l>=qr)return e();
		if(ql<=l&&qr>r){return tree[p];}
		int mid=(l+r)/2;
		return op(Get(p<<1,l,mid,ql,qr),Get(p<<1|1,mid+1,r,ql,qr));
	}
	S Get(int pos){return Get(1,0,n-1,pos,pos+1);}
	S Prod(int l,int r){return Get(1,0,n-1,l,r);}
	S All_Prod(){return Get(1,0,n-1,0,n);}
	void Set(int p,int l,int r,int ql,int qr,S x){
	    if(l>=qr||r<ql)return;
        if(ql<=l&&qr>r){tree[p]=x;return;}
        int mid=(l+r)/2;
        Set(p<<1,l,mid,ql,qr,x);
        Set(p<<1|1,mid+1,r,ql,qr,x);
        tree[p]=op(tree[p<<1],tree[p<<1|1]);
	}
	void Set(int pos,S x){Set(1,0,n-1,pos,pos+1,x);}
    template<class F>
    int Max_Right(int l,F f){
        if(l==n)return n;
        S sm=e();
        int res=Find_Right(1,0,n-1,l,f,sm);
        return res==-1?n:res;
    }
	template<bool(*f)(S)>
    int Max_Right(int l){return Max_Right(l,[](S x){return f(x);});}
    template<class F>
    int Find_Right(int p,int l,int r,int ql,F&f,S&sm){
        if(r<ql)return -1;
        if(l>=ql){
            if(f(op(sm,tree[p]))){sm=op(sm,tree[p]);return -1;}
            if(l==r)return l;
        }
        int mid=(l+r)/2;
        int res=Find_Right(p<<1,l,mid,ql,f,sm);
        if(res!=-1)return res;
        return Find_Right(p<<1|1,mid+1,r,ql,f,sm);
    }
    template<bool(*f)(S)>
    int Min_Left(int r){return Min_Left(r,[](S x){return f(x);});}
    template<class F>
    int Min_Left(int r,F f){
        if(r==0)return 0;
        S sm=e();
        int res=Find_Left(1,0,n-1,r,f,sm);
        return res==-1?0:res;
    }
    template<class F>
    int Find_Left(int p,int l,int r,int qr,F&f,S&sm){
        if(l>=qr)return -1;
        if(r<qr){
            if(f(op(sm,tree[p]))){sm=op(sm,tree[p]);return -1;}
            if(l==r)return l;
        }
        int mid=(l+r)/2;
        int res=Find_Left(p<<1,l,mid,qr,f,sm);
        if(res!=-1)return res;
        return Find_Left(p<<1|1,mid+1,r,qr,f,sm);
    }
};
/*
    SegTree()构造大小为0的线段树
    SegTree(n)构造可以处理长度为n的数组的线段树
    SegTree(向量数组)直接处理数组
    Get(pos)取线段树第pos个
    Prod(l,r)取区间[l,r]
    All_Prod()取区间[0,n-1]
    Set(pos,S x)将pos设为x
    template<f>Max_Right(l)从左往右找第一个不满足f函数的r,在函数内部是[l,res),res是第一个不满足的，同时
    也是下个区间的开始位置
    template<f>Min_Left(r)从右往左找第一个不满足f函数的l，函数内部是[res,r),若要包含r,则传入r+1
	使用Max_Right(int l)的是，要将f放全局，若要让f判断基准可变，在全局设个全局变量即可，详情见模板题
*/