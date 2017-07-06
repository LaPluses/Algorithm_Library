#include <cstdio>
#include <vector>

using namespace std;

const int mod = 1e9 + 7;

vector<int> s, C, B;

int pow_mod(int a, int k)
{
	int s = 1;
	while (k)
	{
		if (k & 1)
			s = 1ll * s * a % mod;
		a = 1ll * a * a % mod;
		k >>= 1;
	}
	return s;
}

int main()
{
	C.push_back(1);
	B.push_back(1);
	int L = 0;
	int m = 1;
	int b = 1;
	int n = 0;
	int _s;
	while (scanf("%d", &_s) == 1)
	{
		s.push_back(_s);
		int d = _s;
		for (int i = 1; i <= L; ++i)
			d = (d + 1ll * C[i] * s[n - i] % mod) % mod;
		if (d == 0)
			++m;
		else if (2 * L <= n)
		{
			vector<int> T = C;
			C.resize(n + 1 - L + 1);
			for (int i = L + 1; i <= n + 1 - L; ++i)
				C[i] = 0;
			for (int i = 0; i < B.size(); ++i)
				C[i + m] = (C[i + m] + mod -
							1ll * d * pow_mod(b, mod - 2) % mod * B[i] % mod) %
						   mod;
			L = n + 1 - L;
			B = T;
			b = d;
			m = 1;
		}
		else
		{
			for (int i = 0; i < B.size(); ++i)
				C[i + m] = (C[i + m] + mod -
							1ll * d * pow_mod(b, mod - 2) % mod * B[i] % mod) %
						   mod;
			++m;
		}
		++n;
		printf("F(n)=");
		for (int i = 1; i < C.size(); ++i)
		{
			int output = (mod - C[i]) % mod;
			if (output > mod / 2)
				output -= mod;
			printf("%s%d*F(n-%d)", (output < 0 || i == 1) ? "" : "+", output, i);
		}
		puts("");
	}
	return 0;
}
