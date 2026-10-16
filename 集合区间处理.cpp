struct interset{//需要inf
    int inf;
    set<pair<int,int>>st;
    int total;
    interset(int _inf):total(0),inf(_inf){}
    void add(int l,int r){//左闭右开
        if(l>=r)return;
        auto it=st.lower_bound({l,-inf});
        if(it!=st.begin()&&prev(it)->second>=l)it--;
        while(it!=st.end()&&it->first<=r){
            l=min(l,it->first);
            r=max(r,it->second);
            total-=(it->second-it->first);
            it=st.erase(it);
        }
        total+=(r-l);
        st.insert({l,r});
    }
    void remv(int l,int r){
        if(l>=r)return;
        auto it=st.lower_bound({l,inf});
        if(it!=st.begin()&&prev(it)->second>l)it--;
        while(it!=st.end()&&it->first<r){
            auto[pl,pr]=*it;
            total-=pr-pl;
            it=st.erase(it);
            if(pl<l)st.insert({pl,l}),total+=l-pl;
            if(pr>r)st.insert({r,pr}),total+=pr-r;
        }
    }
    int len(){return total;}
    size_t size(){return st.size();}
    bool cover(int l,int r)const {//区间完全覆盖
        if(l>=r)return true;
        auto it=st.upper_bound({l,inf});
        if(it==st.begin())return false;
        --it;
        return it->first<=l&&it->second>=r;
    }
    bool insects(int l,int r)const {//有无重叠
        if(l>=r)return false;
        auto it=st.lower_bound({l,inf});
        if(it!=st.begin()&&prev(it)->second>l)return true;
        return it!=st.end()&&it->first<r;
    }
    bool empty(){
        if(sz(st))return false;
        return true;
    }
};
struct cmp_first {//配下面的，只用first来进行二分
    using is_transparent = void;
    bool operator()(const pair<int,int>& a, const pair<int,int>& b) const {
        return a < b;
    }
    bool operator()(const pair<int,int>& a, const int& b) const {
        return a.first < b;
    }
    bool operator()(const int& a, const pair<int,int>& b) const {
        return a < b.first;
    }
};
struct interset{
    set<pair<int,int>,cmp_first>st;
    int total;
    interset():total(0){}
    void add(int l,int r){//左闭右开
        if(l>=r)return;
        auto it=st.lower_bound(l);
        if(it!=st.begin()&&prev(it)->second>=l)it--;
        while(it!=st.end()&&it->first<=r){
            l=min(l,it->first);
            r=max(r,it->second);
            total-=(it->second-it->first);
            it=st.erase(it);
        }
        total+=(r-l);
        st.insert({l,r});
    }
    void remv(int l,int r){
        if(l>=r)return;
        auto it=st.upper_bound(l);
        if(it!=st.begin()&&prev(it)->second>l)it--;
        while(it!=st.end()&&it->first<r){
            auto[pl,pr]=*it;
            total-=pr-pl;
            it=st.erase(it);
            if(pl<l)st.insert({pl,l}),total+=l-pl;
            if(pr>r)st.insert({r,pr}),total+=pr-r;
        }
    }
    int len(){return total;}
    size_t size(){return st.size();}
    bool cover(int l,int r)const {//区间完全覆盖
        if(l>=r)return true;
        auto it=st.upper_bound(l);
        if(it==st.begin())return false;
        --it;
        return it->first<=l&&it->second>=r;
    }
    bool insects(int l,int r)const {//有无重叠
        if(l>=r)return false;
        auto it=st.upper_bound(l);
        if(it!=st.begin()&&prev(it)->second>l)return true;
        return it!=st.end()&&it->first<r;
    }
    bool empty(){
        if(sz(st))return false;
        return true;
    }
};
