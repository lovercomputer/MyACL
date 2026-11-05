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
        vector<ll>dis(n);vector<int>cur(n);vector<char>vis(n),inq(n);
        auto dfs=[&](auto&&self,int u,int f)->int{
            if(u==t)return f;
            vis[u]=1;
            int res=0;
            for(int&i=cur[u];i<(int)g[u].size();++i){
                edge&e=g[u][i];
                if(e.cap>0&&!vis[e.to]&&dis[u]+e.cost==dis[e.to]){
                    int r=self(self,e.to,min(f-res,e.cap));
                    if(r){e.cap-=r;g[e.to][e.rev].cap+=r;res+=r;if(res==f)break;}
                }
            }
            return res;
        };
        while(fl<limit){
            fill(all(dis),INF);fill(all(inq),0);
            dis[s]=0;deque<int>q;q.push_back(s);inq[s]=1;
            while(!q.empty()){
                int u=q.front();q.pop_front();inq[u]=0;
                for(auto&e:g[u]){
                    if(e.cap>0&&dis[u]+e.cost<dis[e.to]){
                        dis[e.to]=dis[u]+e.cost;
                        if(!inq[e.to]){
                            inq[e.to]=1;
                            if(!q.empty()&&dis[e.to]<dis[q.front()])q.push_front(e.to);
                            else q.push_back(e.to);
                        }
                    }
                }
            }
            if(dis[t]>=INF/2)break;
            fill(all(cur),0);
            int add;
            do{
                fill(all(vis),0);
                add=dfs(dfs,s,limit-fl);
                fl+=add;cost+=(ll)add*dis[t];
            }while(add>0&&fl<limit);
        }
        return {fl,cost};
    }
};
