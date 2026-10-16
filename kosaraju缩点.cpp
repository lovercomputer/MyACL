struct scc{//kosaraju求强连通分量，0-indexed
    int n,sccount;
    vector<vector<int>>g,rg,groups;//正向图，反向图，各分量（按拓扑序）,group是编号映射节点
    vector<int>id;//id[u]：u所属分量的编号，编号越小拓扑序越靠前；-1表示未访问
    vector<bool>vis;
    stack<int>st;
    scc(int _n):n(_n),sccount(0),g(_n),rg(_n),groups(),id(_n,-1),vis(_n,false){}
    void add(int u,int v){//0-indexed
        g[u].push_back(v);
        rg[v].push_back(u);
    }
    void dfs1(int u){
        vis[u]=true;
        for(const int&v:g[u])if(!vis[v])dfs1(v);
        st.push(u);
    }
    void dfs2(int x,int po){
        id[x]=po;
        groups[po].push_back(x);
        for(const int&v:rg[x])if(id[v]==-1)dfs2(v,po);
    }
    void init(){
        sccount=0;
        groups.clear();
        id.assign(n,-1);
        vis.assign(n,false);
        while(!st.empty())st.pop();
        for(int i=0;i<n;++i)if(!vis[i])dfs1(i);
        while(!st.empty()){
            int x=st.top();
            st.pop();
            if(id[x]==-1){
                groups.push_back(vector<int>());
                dfs2(x,sccount++);
            }
        }
    }
};
struct sat{//2-sat，0-indexed；节点2i表示x_i=0，2i+1表示x_i=1
    int n;
    scc S;
    vector<bool>ans;
    sat(int _n):n(_n),S(2*_n),ans(_n,false){}
    void add(int i,bool f,int j,bool g){//加子句(x_i=f)或(x_j=g)
        S.add(2*i+(f?0:1),2*j+(g?1:0));
        S.add(2*j+(g?0:1),2*i+(f?1:0));
    }
    bool init(){//返回是否有解；有解时ans[i]就是x_i的取值
        S.init();
        for(int i=0;i<n;++i){
            if(S.id[2*i]==S.id[2*i+1])return false;
            ans[i]=S.id[2*i]<S.id[2*i+1];
        }
        return true;
    }
};