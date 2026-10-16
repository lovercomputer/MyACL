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
