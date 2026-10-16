struct MaxDinic{//最大网络流
    struct edge{
        int to,rev,cap;
    };
    vector<vector<edge>>g;
    vector<int>level,iter;
    MaxDinic(int _n):level(_n),iter(_n),g(_n){}
    void Add(const int& u,const int& v,const int& cap){
        g[u].push_back({v,sz(g[v]),cap});
        g[v].push_back({u,sz(g[u])-1,0});
    }
    void bfs(int s){
        fill(all(level),-1);//把层级设为-1
        queue<int>q;
        q.push(s);
        level[s]=0;
        while(!q.empty()){
            int u=q.front();q.pop();
            for(auto&p:g[u]){
                if(p.cap>0&&level[p.to]<0){
                    q.push(p.to);
                    level[p.to]=level[u]+1;
                }
            }
        }
    }
    int dfs(int u,int v,int f){
        if(u==v)return f;
        for(int& i=iter[u];i<sz(g[u]);++i){
            edge& p=g[u][i];
            if(p.cap>0&&level[u]<level[p.to]){
                int d=dfs(p.to,v,min(f,p.cap));
                if(d>0){
                    p.cap-=d;
                    g[p.to][p.rev].cap+=d;
                    return d;
                }
            }
        }
        return 0;
    }
    int MaxFlow(int s,int t){
        int flow=0;
        while(1){
            bfs(s);
            if(level[t]<0)return flow;
            fill(all(iter),0);
            int f=0;
            while((f=dfs(s,t,1e9))>0)flow+=f;
        }
        return flow;
    }
};
/*
    MaxDinic(n)建0~n-1的空节点
    Add(id(i,j),id(dx,dy)u,v,cap)加一条u→v、容量为cap的有向边/最小割时让u与v关联;
    dinic.Add()
    MaxFlow(s,t)返回s到t的最大流/计算最小割
    对于最小割，假设0是源点，2是汇点，1是中间点，如果add(0,1,5)&&add(1,2,3)，那么就是0→1→2，由于最小割
    数的是S→T的流，所以割掉0→1代价5，割掉1→2代价3，所以优先割1→2
    如果add(1,0,5),add(1,2,3)那么就是0←1→2，由于要计算的是S→T，因为原图是0←1，所以割掉的代价是0
*/