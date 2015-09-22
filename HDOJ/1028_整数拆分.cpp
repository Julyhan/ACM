//Prob 1028 Ignatius and the Princess III
//整数拆分
// f[n][k] = f[n - k][k] + f[n][k-1]  
// equals to for(i = 1; i <= n; i++) result+=f(n - i, i)

//整数拆分：给它计数最简单的方法是定义函数f(n, k)，代表n的整数拆分中，最大项不超过k的方案数。
//对于任意满足条件的拆分，最大项要么达到这个限制，要么小于它，因此f(n, k) = f(n-k, k) + f(n, k - 1)。
//边界条件：f(n, 1) = 1, f(0, 0) = 1, f(1, 1) = 1， 另外，f(n, k) = f(n, n),如果k大于n的话。

//Problem Description
//"Well, it seems the first problem is too easy. I will let you know how foolish you are later." feng5166 says.
//
//"The second problem is, given an positive integer N, we define an equation like this:
//N = a[1] + a[2] + a[3] + ... + a[m];
//a[i]>0, 1 <= m <= N;
//My question is how many different equations you can find for a given N.
//For example, assume N is 4, we can find :
//4 = 4;
//4 = 3 + 1;
//4 = 2 + 2;
//4 = 2 + 1 + 1;
//4 = 1 + 1 + 1 + 1;
//so the result is 5 when N is 4. Note that "4 = 3 + 1" and "4 = 1 + 3" is the same in this problem.Now, you do it!"
//
//
//Input
//The input contains several test cases.Each test case contains a positive integer N(1 <= N <= 120) which is mentioned above.The input is terminated by the end of file.
//
//
//Output
//For each test case, you have to output a line contains an integer P which indicate the different equations you have found.
//
//
//Sample Input
//4
//10
//20
//
//
//Sample Output
//5
//42
//627
//
//
//Author
//Ignatius.L
//
//
//Recommend
//We have carefully selected several similar problems for you:  1171 1085 1398 2152 1709

#include <iostream>
using namespace std;

#define MAXNUM 122
long long result[MAXNUM][MAXNUM];

void init()
{
	for (size_t i = 0; i < MAXNUM; i++)
	{
		result[i][0] = 0;
	}
	for (size_t i = 0; i < MAXNUM; i++)
	{
		result[0][i] = 1;
	}
	for (size_t i = 1; i < MAXNUM; i++)
	{
		for (size_t j = 1; j <= i; j++)
		{
			result[i][j] = result[i - j][j] + result[i][j - 1];
		}
		for (size_t j = i + 1; j < MAXNUM; j++)
		{
			result[i][j] = result[i][i];
		}

	}
}

int main()
{
	init();
	int n;
	while (scanf("%d", &n) != EOF) {
		printf("%lld\n", result[n][n]);
	}

	return 0;
}

