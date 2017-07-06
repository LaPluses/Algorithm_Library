const long long modx = 1e9 + 7;
const long long check_mod = 1e15;

inline long long getval(long long x)
{
	if(x >= modx) return x % modx;
	else if(x >= 0) return x;
	else return (x%modx+modx)%modx;
}

struct Matrix
{
  // Made by xiper , Last updata : 2015 / 6 / 14
  int r , c ;
  long long ele[22][22];
  Matrix(const int & r , const int & c)
   {
      this->r = r , this->c = c;     // i will not init for ele , u should do it
   }
  friend ostream& operator << (ostream & os,const Matrix & x)
   {
         for(int i = 0 ; i < x.r ; ++ i)
          {
             for(int j = 0 ; j < x.c ; ++ j)
              os << x.ele[i][j] << " ";
          os << endl;    
       }
      return os;
   }
  Matrix operator * (const Matrix & x) const
   {     
      Matrix res(r,x.c);
      for(int i = 0 ; i < r ; ++ i)
       for(int j = 0 ; j < x.c ; ++ j)
        {
           long long sum = 0;
           for(int k = 0 ; k < c ; ++ k)
           {
                sum += ele[i][k] * x.ele[k][j];
                if(sum >= check_mod) sum %= modx;
           }
           if(sum >= modx) sum %= modx;
           res.ele[i][j] = sum;
        }
      return res;
   }
  Matrix operator * (const int & x ) const
   {
         Matrix res(r,c);
         for(int i = 0 ; i < r ; ++ i)
          for(int j = 0 ; j < c ; ++ j)
           res.ele[i][j] = ele[i][j]*x;
         return res;
   }
  Matrix operator + (const Matrix & x) const
   {
         if (x.r != r || x.c != c)
          {
             cout << "Error on Matrix operator + , (r1 != r2 || c1 != c2)" << endl;
          return Matrix(0,0);    
       }
      Matrix res(r,c);
      for(int i = 0 ; i < r ; ++ i)
       for(int j = 0 ; j < c ; ++ j){
       	res.ele[i][j] = ele[i][j] + x.ele[i][j];
       	if(res.ele[i][j] >= modx) res.ele[i][j] -= modx;
       }
      return res;
   }
  Matrix operator - (const Matrix & x) const
   {
         if (x.r != r || x.c != c)
          {
             cout << "Error on Matrix operator + , (r1 != r2 || c1 != c2)" << endl;
          return Matrix(0,0);    
       }
      Matrix res(r,c);
      for(int i = 0 ; i < r ; ++ i)
       for(int j = 0 ; j < c ; ++ j)
        res.ele[i][j] = ele[i][j] - x.ele[i][j];
      return res;
   }
  void r_ope(int  whichr , int  num)
   {
         for(int i = 0 ; i < c ; ++ i)
          ele[whichr][i] += num;
   }
  void c_ope(int  whichc , int  num)
   {
         for(int i = 0 ; i < r ; ++ i)
          ele[i][whichc] += num;
   }
  void init(int x)
   {
         for(int i = 0 ; i < r ; ++ i)
          for(int j = 0 ; j < c ; ++ j)
           ele[i][j] = x;
   }
  void init_dig()
   {
         memset(ele,0,sizeof(ele));
         for(int i = 0 ; i < min(r,c) ; ++ i)
          ele[i][i] = 1;
   }
  Matrix reverse()
  {
      Matrix res(c,r);
      for(int i = 0 ; i < r ; ++ i)
        for(int j = 0 ; j < c ; ++ j)
         res.ele[j][i] = ele[i][j];
      return res;   
  }
  Matrix Mulite (const Matrix & x) const
   {      
      Matrix res(r,x.c);
      for(int i = 0 ; i < r ; ++ i)
       for(int j = 0 ; j < x.c ; ++ j)
        {
           long long sum = 0;
           for(int k = 0 ; k < c ; ++ k){
           	sum += ele[i][k]*x.ele[k][j];
           	if(sum >= check_mod) sum %= modx;
           }
           res.ele[i][j] = sum%modx;
        }
      return res;
   }
  Matrix pow(long long n)
   {
        Matrix tmp(r,c);
        memcpy(tmp.ele,ele,sizeof(ele));
        Matrix res(r,c);
        res.init_dig();
        while(n)
          {
            if (n & 1LL) res = res.Mulite(tmp);
            n >>= 1LL;
            tmp = tmp.Mulite(tmp);
          }
        return res;
   }
};