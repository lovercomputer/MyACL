template<class S,auto Less,auto Step,class Adj>
vector<optional<S>>dijkstra(const Adj&g,vector<S>src)
{
    auto cmp=[&](const S&a,const S&b){return Less(b,a);};
    priority_queue<S,vector<S>,decltype(cmp)>pq(cmp);
    vector<optional<S>>res(g.size());
    int r=-1;
    optional<S>last;
    for(auto&x:src)pq.push(move(x));
    while(!pq.empty()){
        S u=pq.top();pq.pop();
        if(res[u.v])continue;
        if(!last||Less(*last,u)||Less(u,*last))last=u,++r;
        res[u.v]=u;
        for(const auto&e:g[u.v]){
            if(res[e.to])continue;
            auto c=Step(e,u,r);
            if constexpr(is_same_v<decay_t<decltype(c)>,optional<S>>){if(c)pq.push(move(*c));}
            else pq.push(move(c));
        }
    }
    return res;
}
//==== 481F
struct E{int to,c;};
struct S{int r,c,v;ll d;};//r 父顶点名次  c 边数字  v 顶点  d 分数取模
auto lessS=[](const S&u,const S&v){return u.r!=v.r?u.r<v.r:u.c<v.c;};
auto stepS=[](const E&e,const S&u,int r){return S{r,e.c,e.to,(10*u.d+e.c)%998244353};};
//==== 泛化 dijkstra
// S    : 堆元素，须含成员 v
// Less : Less(a,b)==true 表示 a 先出堆，须为严格弱序
// Step : Step(e,u,r) 产生候选，r 是 u 的名次；可返回 S 或 optional<S>
// 返回 : res[v] 为空=不可达
//若是返回optional<S>就是return nullopt