struct STable{
    vec<vec<int>>up;
    vec<vec<int>>sum;
    int n,m;
    template<typename Q>
    STable(int _n,int _m,Q&&init):n(_n),m(_m+1),up(_n,vec<int>(_m+1,-1)),sum(_n,vec<int>(_m+1,0)){//权值表
        init(*this);
        for(int j=1;j<m;++j){
            for(int i=0;i<n;++i){
                int mid=up[i][j-1];
                up[i][j]=up[mid][j-1];
                sum[i][j]=op(sum[i][j-1],sum[mid][j-1]);
            }
        }
    }
};
//全局变量，使用示例
//int op(int a,int b){
//    return a+b;
//}
//下面这个是放到主函数solve的
//auto init_func = [&](auto&& t) {
//    for (int i = 0; i < n; ++i) {
//        t.up[i][0] = (i + A[i]) % n;
//        t.sum[i][0] = A[i];
//    }
//};
//STable<int,op> st(n,40,init_func);
