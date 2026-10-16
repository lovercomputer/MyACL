struct MinCostFlow{//最小费用最大流，SPFA找增广路，0-indexed
    struct edge{
        int to,cap,cost,rev;//rev：反向边的下标
    };
    int n;
    vector<vector<edge>>g;
    MinCostFlow(int _n):n(_n),g(_n){}
    void Add(int u,int v,int cap,int cost){//u→v,容量，花费
        g[u].push_back({v,cap,cost,(int)g[v].size()});
        g[v].push_back({u,0,-cost,(int)g[u].size()-1});
    }
        pair<int,ll> Flow(int s,int t,int limit=INT_MAX){
        int fl=0;ll cost=0;
        const ll INF=numeric_limits<ll>::max()/4;
        vector<ll>dis(n);vector<int>pre_e(n),pre_v(n),inq(n);
        while(fl<limit){
            fill(all(dis),INF);fill(all(inq),0);
            dis[s]=0;queue<int>q;q.push(s);inq[s]=1;
            while(!q.empty()){
                int u=q.front();q.pop();inq[u]=0;
                for(int i=0;i<(int)g[u].size();++i){
                    edge&e=g[u][i];
                    if(e.cap>0&&dis[u]+e.cost<dis[e.to]){
                        dis[e.to]=dis[u]+e.cost;
                        pre_v[e.to]=u;pre_e[e.to]=i;
                        if(!inq[e.to]){q.push(e.to);inq[e.to]=1;}
                    }
                }
            }
            if(dis[t]>=0)break;              // 关键：单位费用非负即停
            int c=limit-fl;
            for(int v=t;v!=s;v=pre_v[v])c=min(c,g[pre_v[v]][pre_e[v]].cap);
            for(int v=t;v!=s;v=pre_v[v]){
                edge&e=g[pre_v[v]][pre_e[v]];
                e.cap-=c;g[v][e.rev].cap+=c;
            }
            fl+=c;cost+=(ll)c*dis[t];
        }
        return {fl,cost};
    }
};
