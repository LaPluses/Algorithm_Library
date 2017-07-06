typedef struct Matrix
{
  // Made by xiper , Last updata : 2015 / 6 / 14
  int r , c , ele[50][50];
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
         if (c != x.r)
       {
          cout << "Error on Matrix operator * , (c1 != r1)" << endl;
          return Matrix(0,0);    
       }       
      Matrix res(r,x.c);
      for(int i = 0 ; i < r ; ++ i)
       for(int j = 0 ; j < x.c ; ++ j)
        {
           int sum = 0;
           for(int k = 0 ; k < c ; ++ k)
            sum += ele[i][k]*x.ele[k][j];
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
       for(int j = 0 ; j < c ; ++ j)
        res.ele[i][j] = ele[i][j] + x.ele[i][j];
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
  Matrix reverse(const Matrix & x)
  {
      Matrix res(x.c,x.r);
      for(int i = 0 ; i < x.r ; ++ i)
        for(int j = 0 ; j < x.c ; ++ j)
         res.ele[j][i] = x.ele[i][j];
      return res;   
  }
  Matrix Mulite (const Matrix & x ,int mod) const
   {
         if (c != x.r)
       {
          cout << "Error on Matrix function Mulite(pow may be) , (c1 != r1)" << endl;
          return Matrix(0,0);    
       }       
      Matrix res(r,x.c);
      for(int i = 0 ; i < r ; ++ i)
       for(int j = 0 ; j < x.c ; ++ j)
        {
           int sum = 0;
           for(int k = 0 ; k < c ; ++ k)
            sum += (ele[i][k]*x.ele[k][j]) % mod;
           res.ele[i][j] = sum % mod;
        }
      return res;
   }
  Matrix pow(int n , int mod)
   {
         if (r != c)
          {
             cout << "Error on Matrix function pow , (r != c)" << endl;    
             return Matrix(0,0);
       }
         Matrix tmp(r,c);
         memcpy(tmp.ele,ele,sizeof(ele));
         Matrix res(r,c);
         res.init_dig();
         while(n)
          {
             if (n & 1)
            res = res.Mulite(tmp,mod);
          n >>= 1;
          tmp = tmp.Mulite(tmp,mod);
       }
      return res;
   }
};