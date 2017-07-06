#include <algorithm>
#include <cmath>
#include <iostream>
#include <ctime>
using namespace std;

const int mod = 1e9 + 7;

const int max0 = 1 << 18;

struct comp
{
	double x, y;

	comp() : x(0), y(0) {}
	comp(const double &_x, const double &_y) : x(_x), y(_y) {}
};

inline comp operator+(const comp &a, const comp &b)
{
	return comp(a.x + b.x, a.y + b.y);
}

inline comp operator-(const comp &a, const comp &b)
{
	return comp(a.x - b.x, a.y - b.y);
}

inline comp operator*(const comp &a, const comp &b)
{
	return comp(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

inline comp conj(const comp &a) { return comp(a.x, -a.y); }

const double PI = acos(-1);

int N, L;

comp w[max0 + 5];
int bitrev[max0 + 5];

void fft(comp *a, const int &n)
{
	for (int i = 0; i < n; ++i)
		if (i < bitrev[i])
			swap(a[i], a[bitrev[i]]);
	for (int i = 2, lyc = n >> 1; i <= n; i <<= 1, lyc >>= 1)
		for (int j = 0; j < n; j += i)
		{
			comp *l = a + j, *r = a + j + (i >> 1), *p = w;
			for (int k = 0; k<i>> 1; ++k)
			{
				comp tmp = *r * *p;
				*r = *l - tmp, *l = *l + tmp;
				++l, ++r, p += lyc;
			}
		}
}

inline void fft_prepare()
{
	for (int i = 0; i < N; ++i)
		bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << (L - 1));
	for (int i = 0; i < N; ++i)
		w[i] = comp(cos(2 * PI * i / N), sin(2 * PI * i / N));
}

inline vector<int> conv(const vector<int> &x, const vector<int> &y)
{
	static comp a[max0 + 5], b[max0 + 5];
	static comp dfta[max0 + 5], dftb[max0 + 5], dftc[max0 + 5], dftd[max0 + 5];
	L = 0;
	while ((1 << L) < x.size() + y.size() - 1)
		++L;
	N = 1 << L;
	fft_prepare();
	for (int i = 0; i < N; ++i)
		a[i] = b[i] = comp(0, 0);
	for (int i = 0; i < x.size(); ++i)
		a[i] = comp(x[i] & 32767, x[i] >> 15);
	for (int i = 0; i < y.size(); ++i)
		b[i] = comp(y[i] & 32767, y[i] >> 15);
	fft(a, N), fft(b, N);
	for (int i = 0; i < N; ++i)
	{
		int j = (N - i) & (N - 1);
		static comp da, db, dc, dd;
		da = (a[i] + conj(a[j])) * comp(0.5, 0);
		db = (a[i] - conj(a[j])) * comp(0, -0.5);
		dc = (b[i] + conj(b[j])) * comp(0.5, 0);
		dd = (b[i] - conj(b[j])) * comp(0, -0.5);
		dfta[j] = da * dc;
		dftb[j] = da * dd;
		dftc[j] = db * dc;
		dftd[j] = db * dd;
	}
	for (int i = 0; i < N; ++i)
		a[i] = dfta[i] + dftb[i] * comp(0, 1);
	for (int i = 0; i < N; ++i)
		b[i] = dftc[i] + dftd[i] * comp(0, 1);
	fft(a, N), fft(b, N);
	vector<int> z(x.size() + y.size() - 1);
	for (int i = 0; i < x.size() + y.size() - 1; ++i)
	{
		int da = (long long)(a[i].x / N + 0.5) % mod;
		int db = (long long)(a[i].y / N + 0.5) % mod;
		int dc = (long long)(b[i].x / N + 0.5) % mod;
		int dd = (long long)(b[i].y / N + 0.5) % mod;
		z[i] =
			(da + ((long long)(db + dc) << 15) + ((long long)dd << 30)) % mod;
	}
	return z;
}

vector < int > sa , sb;

int main(int argc , char * argv[]){
	int n = 1e5;
	sa.resize( n , 0 );
	sb.resize( n , 0 );
	vector < int > sc;
	for(int t = 0 ; t < 9 ; ++ t){
		for(int i = 0 ; i < n ; ++ i) sa[i] = i;
		for(int i = 0 ; i < n ; ++ i) sb[i] = i;
		sc = conv( sa , sb );
	}
	cout << sc.size() << endl;
	cout << "run time is " << clock() << endl;
	return 0;
}