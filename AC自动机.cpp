#define int long long
#define Matrix vector<vector<int>>
const int mod=998244353;
struct Node{
    int fail;
    int nxt[26];
    bool ban;
    Node(){
        for(int i=0;i<26;i++)nxt[i]=0;
        fail=0;
        ban=false;
    }
};
struct AC_auto{
    vector<Node>trie;
    AC_auto(){
        trie.emplace_back();
    }
    void ins(const string& s){
        int v=0;
        for(const char& c:s){
            int idx=c-'a';
            if(!trie[v].nxt[idx]){
                trie[v].nxt[idx]=trie.size();
                trie.emplace_back();
            }
            v=trie[v].nxt[idx];
        }
        trie[v].ban=true;
    }
    void build(){
        queue<int>q;
        for(int c=0;c<26;c++){
            int v=trie[0].nxt[c];
            if(v){
                trie[v].fail=0;
                q.push(v);
            }
        }
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int c=0;c<26;c++){
                int v=trie[u].nxt[c];
                if(v){
                    trie[v].fail=trie[trie[u].fail].nxt[c];
                    if(trie[trie[v].fail].ban)trie[v].ban=true;
                    q.push(v);
                }else{
                    trie[u].nxt[c]=trie[trie[u].fail].nxt[c];
                }
            }
        }
    }
    int query(const str& s){//返回的是结束的位置
        int u=0;
        int cnt=0;
        for(const char& ch:s){
            int c=ch-'a';
            u=trie[u].nxt[c];
            if(trie[u].ban)return cnt;
            cnt++;
        }
        return -1;
    }
};
