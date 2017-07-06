#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
typedef long long LL;

struct Complex{
	double x, y;
	Complex(): x(0), y(0) { }
	Complex(const double &_x, const double &_y): x(_x), y(_y) { }
};

inline Complex operator+(const Complex &a, const Complex &b) { return Complex(a.x + b.x, a.y + b.y); }
inline Complex operator-(const Complex &a, const Complex &b) { return Complex(a.x - b.x, a.y - b.y); }
inline Complex operator*(const Complex &a, const Complex &b) { return Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
inline Complex conj(const Complex &a) { return Complex(a.x, -a.y); }


const double PI = acos(-1);
const int Mod = 1e9 + 7;
const int max0 = 1 << 18;

Complex w[max0 + 5];
int bitrev[max0 + 5] , N = 1 << 18 , L = 18;

void fft(Complex *a, const int &n)
{
	REP(i, 0, n) if (i < bitrev[i]) swap(a[i], a[bitrev[i]]);
	for (int i = 2, lyc = n >> 1; i <= n; i <<= 1, lyc >>= 1)
		for (int j = 0; j < n; j += i)
		{
			Complex *l = a + j, *r = a + j + (i >> 1), *p = w;
			REP(k, 0, i >> 1)
			{
				Complex tmp = *r * *p;
				*r = *l - tmp, *l = *l + tmp;
				++l, ++r, p += lyc;
			}
		}
}

inline void fft_prepare()
{
	REP(i, 0, N) bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << (L - 1));
	REP(i, 0, N) w[i] = Complex(cos(2 * PI * i / N), sin(2 * PI * i / N));
}

inline void conv(int *x, int *y, int *z)
{
	REP(i, 0, N) (x[i] += Mod) %= Mod, (y[i] += Mod) %= Mod;
	static Complex a[max0 + 5], b[max0 + 5];
	static Complex dfta[max0 + 5], dftb[max0 + 5], dftc[max0 + 5], dftd[max0 + 5];

	REP(i, 0, N) a[i] = Complex(x[i] & 32767, x[i] >> 15);
	REP(i, 0, N) b[i] = Complex(y[i] & 32767, y[i] >> 15);
	fft(a, N), fft(b, N);
	REP(i, 0, N)
	{
		int j = (N - i) & (N - 1);
		static Complex da, db, dc, dd;
		da = (a[i] + conj(a[j])) * Complex(0.5, 0);
		db = (a[i] - conj(a[j])) * Complex(0, -0.5);
		dc = (b[i] + conj(b[j])) * Complex(0.5, 0);
		dd = (b[i] - conj(b[j])) * Complex(0, -0.5);
		dfta[j] = da * dc;
		dftb[j] = da * dd;
		dftc[j] = db * dc;
		dftd[j] = db * dd;
	}
	REP(i, 0, N) a[i] = dfta[i] + dftb[i] * Complex(0, 1);
	REP(i, 0, N) b[i] = dftc[i] + dftd[i] * Complex(0, 1);
	fft(a, N), fft(b, N);
	REP(i, 0, N)
	{
		int da = (LL)(a[i].x / N + 0.5) % Mod;
		int db = (LL)(a[i].y / N + 0.5) % Mod;
		int dc = (LL)(b[i].x / N + 0.5) % Mod;
		int dd = (LL)(b[i].y / N + 0.5) % Mod;
		z[i] = (da + ((LL)(db + dc) << 15) + ((LL)dd << 30)) % Mod;
	}
}

int main( int argc , char * argv[] ){

	return 0;
}