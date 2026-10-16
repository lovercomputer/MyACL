template<class T>
struct Array2D{
    int r,c;
    vec<T>data;
    Array2D():r(0),c(0),data(0){}
    Array2D(int _r,int _c):r(_r),c(_c),data(_r*_c,T{}){}
    Array2D(int _r,int _c,T val):r(_r),c(_c),data(_r*_c,val){}
    bool operator==(const Array2D& o)const{return r==o.r&&c==o.c?data==o.data:false;}
    bool operator!=(const Array2D& o)const{return !(*this==o);}
    void assign(int _r,int _c){r=_r;c=_c;data.assign(_r*_c,T{});}
    void assign(int _r,int _c,T val){r=_r;c=_c;data.assign(_r*_c,val);}
    T&operator()(int i,int j){return data[i*c+j];}
    const T&operator()(int i,int j)const{return data[i*c+j];}
    int ID(int i,int j)const {return i*c+j;}
    void fill(T val){for(int i=0;i<r*c;++i)data[i]=val;}
    void rfill(int q,T val){for(int i=0;i<c;++i)data[c*q+i]=val;}
    void cfill(int q,T val){for(int i=0;i<r;++i)data[i*c+q]=val;}
    T allmax()const{return *max_element(all(data));}
    T allmin()const{return *min_element(all(data));}
    T rmax(int q)const{T res=data[q*c+0];for(int i=1;i<c;++i)res=max(res,data[q*c+i]);return res;}
    T rmin(int q)const{T res=data[q*c+0];for(int i=1;i<c;++i)res=min(res,data[q*c+i]);return res;}
    T cmax(int q)const{T res=data[0*c+q];for(int i=1;i<r;++i)res=max(res,data[i*c+q]);return res;}
    T cmin(int q)const{T res=data[0*c+q];for(int i=1;i<r;++i)res=min(res,data[i*c+q]);return res;}
    int rmaxID(int q)const{T res=rmax(q);for(int i=0;i<c;++i)if(res==data[q*c+i])return i;return 0;}
    int rminID(int q)const{T res=rmin(q);for(int i=0;i<c;++i)if(res==data[q*c+i])return i;return 0;}
    int cmaxID(int q)const{T res=cmax(q);for(int i=0;i<r;++i)if(res==data[i*c+q])return i;return 0;}
    int cminID(int q)const{T res=cmin(q);for(int i=0;i<r;++i)if(res==data[i*c+q])return i;return 0;}
    Array2D<T>sub(int U,int D,int L,int R)const{//左闭右开
        int nr=D-U,nc=R-L;
        Array2D<T> res(nr,nc);
        for(int i=U;i<D;++i)for(int j=L;j<R;++j)res(i-U,j-L)=data[i*c+j];
        return res;
    }
    T rot90at(int i,int j){return data[(c-j-1)*c+i];}//旋转90°后当前位置记录元素
    Array2D<T>rot90()const{
        Array2D<T> res(c,r);
        for(int i=0;i<r;++i)for(int j=0;j<c;++j)res(j,r-i-1)=data[i*c+j];
        return res;
    }
    T rot180at(int i,int j){return data[(r-i-1)*c+c-j-1];}
    Array2D<T>rot180()const{
        Array2D<T> res(r,c);
        for(int i=0;i<r;++i)for(int j=0;j<c;++j)res(r-i-1,c-j-1)=data[i*c+j];
        return res;
    }
    T rot270at(int i,int j){return data[j*c+r-i-1];}
    Array2D<T>rot270()const{
        Array2D<T>res(c,r);
        for(int i=0;i<r;++i)for(int j=0;j<c;++j)res(c-j-1,i)=data[i*c+j];
        return res;
    }
    Array2D<T>tran()const{
        Array2D<T>res(c,r);
        for(int i=0;i<r;++i)for(int j=0;j<c;++j)res(j,i)=data[i*c+j];
        return res;
    }
    void print()const{
        for(int i=0;i<r;++i){
            for(int j=0;j<c;++j){
                if(j)cout<<se;
                cout<<data[i*c+j];
            }
            cout<<en;
        }
    }
    void prev_init(){
        for(int i=1;i<r;++i)for(int j=1;j<c;++j)(*this)(i,j)+=(*this)(i-1,j)+(*this)(i,j-1)-(*this)(i-1,j-1);
    }
    T prev_sum(int U,int D,int L,int R)const{
        return (*this)(D,R)-(*this)(D,L-1)-(*this)(U-1,R)+(*this)(U-1,L-1);
    }
};
