#include <iostream>
#include <algorithm>
#define MOD 1000

using namespace std;

int n;
long long **default_matrix;

void	print_matrix(long long **matrix) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (j != n)
				cout << matrix[i][j] << " ";
			else
				cout << matrix[i][j];
		}
		cout << endl;
	}
}

long long	**matrix_mf(long long **m, long long **m2)
{
	long long **ret_m = new long long *[5];
	for (int i = 0; i < 5; i++)
		ret_m[i] = new long long [5];
	fill(&ret_m[0][0],&ret_m[4][5], 0);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				ret_m[i][j] = (ret_m[i][j] + ((m[i][k] * m2[k][j]) % MOD)) % MOD;
	return (ret_m);
}

long long	**recur(long long m)
{
	if (m == 1)
		return (default_matrix);

	long long **half_matrix = recur(m / 2);
	long long **ret_m = matrix_mf(half_matrix, half_matrix);
	if (m % 2 != 0)
		ret_m = matrix_mf(ret_m, default_matrix);
	return (ret_m);
}

int	main(void)
{
	long long b;
	cin >> n >> b;

	default_matrix = new long long*[5];
	for (int i = 0; i < 5; i++)
		default_matrix[i] = new long long[5];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
				cin >> default_matrix[i][j];

	long long **matrix = recur(b);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] %= MOD;
	print_matrix(matrix);
	return (0);
}
