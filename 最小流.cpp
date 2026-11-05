struct MinCostFlow{//最小费用流，SPFA + 多路增广，0-indexed
    struct edge{
        int to,cap,cost,rev;//rev：反向边的下标
    };
    int n;
    vector<vector<edge>>g;
    static constexpr ll BIG=numeric_limits<ll>::max()/4;
    MinCostFlow(int _n):n(_n),g(_n){}
    void Add(int u,int v,int cap,int cost){//u→v,容量，花费
        g[u].push_back({v,cap,cost,(int)g[v].size()});
        g[v].push_back({u,0,-cost,(int)g[u].size()-1});
    }
    ll spfa(int s,vector<ll>&dis){//求原点到各点最短路，返回 dis[t] 由调用方自己读
        fill(all(dis),BIG);
        vector<char>inq(n,0);
        dis[s]=0;deque<int>q;q.push_back(s);inq[s]=1;
        while(!q.empty()){
            int u=q.front();q.pop_front();inq[u]=0;
            if(dis[u]>=BIG/2)continue;          // 加固1：没到过的点不松弛，防溢出误判
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
        return 0;
    }
    int dfs(int u,int t,int f,vector<ll>&dis,vector<int>&cur,vector<char>&vis){
        if(u==t)return f;
        vis[u]=1;
        int res=0;
        for(int&i=cur[u];i<(int)g[u].size();++i){
            edge&e=g[u][i];
            if(e.cap>0&&!vis[e.to]&&dis[u]+e.cost==dis[e.to]){
                int r=dfs(e.to,t,min(f-res,e.cap),dis,cur,vis);
                if(r){
                    e.cap-=r;g[e.to][e.rev].cap+=r;res+=r;
                    if(res==f)break;
                }
            }
        }
        return res;
    }
    pair<int,ll> run(int s,int t,int limit,bool stopAtNonNeg){//内部统一入口
        int fl=0;ll cost=0;
        vector<ll>dis(n);vector<int>cur(n);vector<char>vis(n);
        while(fl<limit){
            spfa(s,dis);
            if(dis[t]>=BIG/2)break;              // 判据一：不可达
            if(stopAtNonNeg&&dis[t]>=0)break;    // 判据二：单价非负
            fill(all(cur),0);
            while(fl<limit){
                fill(all(vis),0);
                int add=dfs(s,t,limit-fl,dis,cur,vis);
                if(!add)break;
                fl+=add;cost+=(ll)add*dis[t];
            }
        }
        return {fl,cost};
    }
    pair<int,ll> Flow(int s,int t,int limit=INT_MAX){return run(s,t,limit,false);}//送满 limit
    pair<int,ll> MaxFlow(int s,int t){return run(s,t,INT_MAX,false);}             //送最大流
    pair<int,ll> FlowWhileNegative(int s,int t,int limit=INT_MAX){return run(s,t,limit,true);}//不亏才送
};
