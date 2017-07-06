const double PI = acos(-1.0);

struct Complex{
	double a,b;
	Complex operator+(const Complex&y)const{return (Complex){a+y.a,b+y.b};}
	Complex operator-(const Complex&y)const{return (Complex){a-y.a,b-y.b};}
	Complex operator*(const Complex&y)const{return (Complex){a*y.a-b*y.b,a*y.b+b*y.a};}
	Complex operator!()const{return (Complex){a,-b};};
};

const double pi = acos( -1 );

namespace fft{

	#define rep(i,a,b) for (int i=(a),_ed=(b);i<_ed;i++)

	const static int FFT_MAXN = 1 << 18;

	int bitrev[FFT_MAXN];
	Complex nw[FFT_MAXN+1];

	void dft(Complex*a,int n,int flag=1){
		int d=0;while((1<<d)*n!=FFT_MAXN)d++;
		rep(i,0,n)if(i<(bitrev[i]>>d))swap(a[i],a[bitrev[i]>>d]);
		for (int l=2;l<=n;l<<=1){
			int del=FFT_MAXN/l*flag;
			for (int i=0;i<n;i+=l){
				Complex *le=a+i,*ri=a+i+(l>>1),*w=flag==1?nw:nw+FFT_MAXN;
				rep(k,0,l>>1){
					Complex ne=*ri**w;
					*ri=*le-ne,*le=*le+ne;
					le++,ri++,w+=del;
				}
			}
		}
		if(flag!=1)rep(i,0,n)a[i].a/=n,a[i].b/=n;
	}
	void fft_init(){
		int L=0;while((1<<L)!=FFT_MAXN)L++;
		bitrev[0]=0;rep(i,1,FFT_MAXN)bitrev[i]=bitrev[i>>1]>>1|((i&1)<<(L-1));
		Complex ste=(Complex){cosl(2*pi/FFT_MAXN),sinl(2*pi/FFT_MAXN)};
		nw[0]=nw[FFT_MAXN]=(Complex){1,0};
		rep(i,1,(FFT_MAXN>>1)+1)nw[i]=nw[i-1]*ste;
		rep(i,(FFT_MAXN>>1)+1,FFT_MAXN)nw[i]=!nw[FFT_MAXN-i];
	}

	void convo(int*a,int n,int*b,int m,double*c){
		static Complex f[FFT_MAXN>>1],g[FFT_MAXN>>1],t[FFT_MAXN>>1];
		int N=2;while(N<=n+m)N<<=1;
		rep(i,0,N)
			if(i&1){
				f[i>>1].b=(i<=n)?a[i]:0.0;
				g[i>>1].b=(i<=m)?b[i]:0.0;
			}else{
				f[i>>1].a=(i<=n)?a[i]:0.0;
				g[i>>1].a=(i<=m)?b[i]:0.0;
			}
		dft(f,N>>1);dft(g,N>>1);
		int del=FFT_MAXN/(N>>1);
		Complex qua=(Complex){0,0.25},one=(Complex){1,0},four=(Complex){4,0},*w=nw;
		rep(i,0,N>>1){
			int j=i?(N>>1)-i:0;
			t[i]=(four*!(f[j]*g[j])-(!f[j]-f[i])*(!g[j]-g[i])*(one+*w))*qua;
			w+=del;
		}
		dft(t,N>>1,-1);
		rep(i,0,n+m+1)c[i]=(i&1)?t[i>>1].a:t[i>>1].b;
	}
}