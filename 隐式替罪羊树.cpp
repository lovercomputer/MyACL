template<class S,
		auto&& op,
		auto&& e
>struct SeqTree{
	static constexpr int AN=3,AD=4;	//α=AN/AD=3/4
	struct Node{int lc,rc,cnt;S v,g;};	//AoS:同节点字段同 cache line
	vector<Node>tr;	//tr[0] 为空节点
	static constexpr int MAXH=64;
	int stk[MAXH],top;
	vector<int>buf;
	int root;
	SeqTree(int cap=0){
		root=0,top=0;
		tr.assign(1,Node{0,0,0,e(),e()});
		tr.reserve(cap+1),buf.reserve(cap+1);
	}
	int size()const{return root?tr[root].cnt:0;}
	//在 0-indexed 位置 p 插入 x
	void insert(int p,const S&x){
		int nn=(int)tr.size();
		tr.push_back(Node{0,0,1,x,x});
		if(!root){root=nn;return;}
		top=0;
		int u=root;
		while(1){
			stk[top++]=u;
			int lsz=tr[tr[u].lc].cnt;
			if(p<=lsz){
				if(!tr[u].lc){tr[u].lc=nn;break;}
				u=tr[u].lc;
			}else{
				p-=lsz+1;
				if(!tr[u].rc){tr[u].rc=nn;break;}
				u=tr[u].rc;
			}
		}
		//自底向上:更新字段 + 找最深的不平衡点
		int sg=0,par=0,child=nn;
		for(int i=top-1;i>=0;--i){
			int v=stk[i];
			tr[v].cnt=tr[tr[v].lc].cnt+tr[tr[v].rc].cnt+1;
			tr[v].g=op(op(tr[tr[v].lc].g,tr[v].v),tr[tr[v].rc].g);
			if(!sg&&tr[child].cnt*AD>tr[v].cnt*AN)sg=v,par=(i?stk[i-1]:0);
			child=v;
		}
		if(!sg)return;
		buf.clear();
		flatten(sg);
		int nw=build(0,(int)buf.size());
		if(!par)root=nw;
		else if(tr[par].lc==sg)tr[par].lc=nw;else tr[par].rc=nw;
	}
	int get(int p)const{
		int u=root;
		while(1){
			int lsz=tr[tr[u].lc].cnt;
			if(p<lsz)u=tr[u].lc;
			else if(p==lsz)return tr[u].v;
			else p-=lsz+1,u=tr[u].rc;
		}
	}
	S prod(int l,int r)const{return l>=r?e():prod(root,l,r);}
	S all_prod()const{return root?tr[root].g:e();}
	vector<S>to_vector()const{
		vector<S>res;
		res.reserve(size());
		collect(root,res);
		return res;
	}
private:
	void flatten(int v){
		if(!v)return;
		flatten(tr[v].lc);
		buf.push_back(v);
		flatten(tr[v].rc);
	}
	int build(int l,int r){
		if(l>=r)return 0;
		int m=(l+r)/2,v=buf[m];
		int a=build(l,m),b=build(m+1,r);
		tr[v].lc=a,tr[v].rc=b;
		tr[v].cnt=tr[a].cnt+tr[b].cnt+1;
		tr[v].g=op(op(tr[a].g,tr[v].v),tr[b].g);
		return v;
	}
	S prod(int v,int l,int r)const{
		if(!v||l>=r)return e();
		if(l==0&&r==tr[v].cnt)return tr[v].g;
		int lsz=tr[tr[v].lc].cnt;
		S res=e();
		if(l<lsz)res=op(res,prod(tr[v].lc,l,min(r,lsz)));
		if(l<=lsz&&lsz<r)res=op(res,tr[v].v);
		if(r>lsz+1)res=op(res,prod(tr[v].rc,max(l,lsz+1)-(lsz+1),r-(lsz+1)));
		return res;
	}
	void collect(int v,vector<S>&res)const{
		if(!v)return;
		collect(tr[v].lc,res);
		res.push_back(tr[v].v);
		collect(tr[v].rc,res);
	}
};
/*
tr.insert(p,x);		//在位置 p 插入 x(p 从 0 数,可以等于当前长度即尾插)
tr.get(p);		//取第 p 个元素
tr.size();		//当前元素个数
tr.to_vector();		//返回整个序列(vector),一般最后输出用
tr.set(p,x);		//改第 p 个元素
tr.prod(l,r);		//聚合 [l,r),用的是你的 op/e。如 tr.prod(0,3) 求和
tr.all_prod();		//整个序列的聚合
tr.empty();		//是否为空
*/