template<class T,class M>
struct SWAG{
    vector<T>bac;
    queue<T>front_prod;
    T back_prod;
    void push(const T& x){
        if(bac.empty()){
            bac.push_back(x);
            back_prod=x;
        }else {
            bac.push_back(x);
            back_prod=M()(back_prod,x);
        }
    }
    void pop(){
        if(front_prod.empty()){
            int siz=sz(bac);
            for(int i=siz-2;i>=0;--i){
                bac[i]=M()(bac[i],bac[i+1]);
            }
            for(int i=0;i<siz;++i)front_prod.push(bac[i]);
            bac.clear();
        }
        front_prod.pop();
    }
    size_t size(){
        return bac.size()+front_prod.size();
    }
    T all_prod(){
        //if(bac.empty()&&front_prod.empty())return 0;
        if(bac.empty())return front_prod.front();
        else if(front_prod.empty()) return back_prod;
        else return M()(front_prod.front(),back_prod);
    }
    bool empty(){return bac.empty()&&front_prod.empty();}
};
struct M{
    int operator()(const int&a,const int&b){
        return a+b;
    }
};
