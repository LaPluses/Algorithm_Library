struct SBT{

	const static int maxn = 1e5 + 15;

	int lft[maxn] , rht[maxn] , key[maxn] , s[maxn] , tot , root ;

	void init(){ tot = root = 0 ; }

	void init( int x , int val = 0 ){
		lft[x] = rht[x] = 0 , key[x] = val , s[x] = 1;
	}

	inline void up(int x){
        s[x] = s[lft[x]] + s[rht[x]] + 1;
    }

    void lr(int &t){
        int k = rht[t];
        rht[t] = lft[k];
        lft[k] = t;
        s[k] = s[t];
        up(t);
        t = k;
    }

    void rr(int &t){
        int k = lft[t];
        lft[t] = rht[k];
        rht[k]= t;
        s[k] = s[t];
        up(t);
        t = k;
    }

    void Maintain(int &t,bool dir){
        if(dir == false){
            if(s[lft[lft[t]]] > s[rht[t]])
                rr(t);
            else if(s[rht[lft[t]]] > s[rht[t]]){
                lr(lft[t]);
                rr(t);
            }
            else return;
        }
        else{
            if(s[rht[rht[t]]] > s[lft[t]]) lr(t);
            else if(s[lft[rht[t]]] > s[lft[t]]){
                rr(rht[t]);
                lr(t);
            }
            else return;
        }
        Maintain(lft[t],false);
        Maintain(rht[t],true);
        Maintain(t,true);
        Maintain(t,false);
    }
    

	void Insert( int & t , int val ){
		if( t == 0 ){
			t = ++ tot;
			init( t , val );
		}else{
			++ s[t];
			if( val < key[t] ) Insert( lft[t] , val );
			else Insert( rht[t] , val );
			Maintain( t , val >= key[t] );
		}
	}

	// 删除操作必须保证元素存在
    int Delete(int &t , int v){
        int ret = 0;
        s[t] --;
        if((v == key[t]) || (v<key[t] && lft[t]  == 0) ||(v > key[t] && rht[t] == 0) ){
            ret = key[t];
            if(lft[t] == 0 || rht[t] == 0) t = lft[t] + rht[t];
            else key[t]  = Delete(lft[t],key[t] + 1);
        }
        else{
            if(v < key[t]) ret = Delete(lft[t] , v);
            else ret = Delete(rht[t] , v);
        }
        return ret;
    }

    bool find( int t , int val ){
    	if( t == 0 ) return false;
    	else if( key[t] == val ) return true;
    	else if( val < key[t] ) return find( lft[t] , val );
    	else return find( rht[t] , val );
    }


    void preorder( int x ){
    	if( lft[x] ) preorder( lft[x] );
    	printf("%d " , key[x]);
    	if( rht[x] ) preorder( rht[x] );
    }

    int size(){
    	return s[root];
    }
    // 查第 k 小 , 必须保证合法
    int kth( int x , int k ){
    	if( k == s[lft[x]] + 1 ) return key[x];
    	else if( k <= s[lft[x]] ) return kth( lft[x] , k );
    	else return kth( rht[x] , k - s[lft[x]] - 1 );
    } 

    //找前驱
    int pred( int t , int v ){
    	if( t == 0 ) return v;
    	else{
    		if( v <= key[t] ) return pred( lft[t] , v );
    		else{
    			int ans =  pred( rht[t] , v );
    			if( ans == v ) ans = key[t];
    			return ans;
    		}
    	}
    }

    // 严格小于 v 的有多少个
    int less( int t , int v ){
    	if( t == 0 ) return 0;
    	if( v <= key[t] ) return less( lft[t] , v );
    	else return s[lft[t]] + 1 + less( rht[t] , v );
    }

    //找后继
    int succ( int t , int v ){
    	if( t == 0 ) return v;
    	else{
    		if( v >= key[t] ) return succ( rht[t] , v );
    		else{
    			int ans =  succ( lft[t] , v );
    			if( ans == v ) ans = key[t];
    			return ans;
    		}
    	}
    }

}sbt;