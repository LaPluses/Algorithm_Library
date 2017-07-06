struct mat{
    int r , c , ele[12][12];
    void init_dig(){
        for(int i = 0 ; i < r ; ++ i) 
            for(int j = 0 ; j < c ; ++ j)
                ele[i][j] = (i == j);
    }
    void init(){ memset( ele , 0 , sizeof( ele ) ); }
};

mat mul(const mat & a , const mat & b){
    mat res ; res.r = a.r , res.c = b.c;
    for(int i = 0 ; i < a.r ; ++ i){
        for(int j = 0 ; j < b.c ; ++ j){
            int cnt = 0;
            for(int k = 0 ; k < a.c ; ++ k){
                cnt += a.ele[i][k]*b.ele[k][j];
                if( cnt >= mod ) cnt %= mod ;
            }
            res.ele[i][j] = cnt;
        }
    }
    return res;
}

mat pow( mat a , int b ){
    mat res ; res.r = a.r , res.c = a.c;
    res.init_dig();
    while( b ){
        if( b & 1 ) res = mul( res , a );
        b>>=1;
        a = mul( a , a );
    }
    return res;
}