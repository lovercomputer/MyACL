template<class T>
struct stool{
    set<T> op_and(const set<T>&a,const set<T>&b)const {//a&&b
        set<T>res;
        set_intersection(all(a),all(b),inserter(res,res.end()));
        return res;
    }
    set<T> op_or(const set<T>&a,const set<T>&b)const {//a||b
        set<T>res;
        set_union(all(a),all(b),inserter(res,res.end()));
        return res;
    }
    set<T> op_dif(const set<T>&a,const set<T>&b)const {//a-b
        set<T>res;
        set_difference(all(a),all(b),inserter(res,res.end()));
        return res;
    }
    set<T> op_xor(const set<T>&a,const set<T>&b)const {//!a&&b a&&!b
        set<T>res;
        set_symmetric_difference(all(a),all(b),inserter(res,res.end()));
        return res;
    }
};
