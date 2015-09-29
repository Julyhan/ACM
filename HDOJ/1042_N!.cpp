//Prob: 1042 N!

//Problem Description
//Given an integer N(0 °‹ N °‹ 10000), your task is to calculate N!
//
//
//Input
//One N in one line, process to the end of file.
//
//
//Output
//For each N, output N!in one line.
//
//
//Sample Input
//1
//2
//3
//
//
//Sample Output
//1
//2
//6
//
//
//Author
//JGShining£®º´π‚Ï≈”∞£©
//
//
//Recommend
//We have carefully selected several similar problems for you:  1715 1047 1063 1753 1316

#include <cmath>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 10001
#define LENGTH 35661
int main() {
	double sum = 0;
	for (size_t i = 1; i < MAXN; i++)
	{
		sum += log10(i);
	}
	//cout << sum;//35659.+

	unsigned N;
	while (cin >> N)
	{
		unsigned result[LENGTH];
		memset(result, 0, LENGTH * sizeof(unsigned));
		result[0] = 1;
		unsigned highest = 1;
		unsigned g_highest = 1;

		for (size_t i = 2; i <= N; i++)
		{
			unsigned carry = 0;
			highest = g_highest;
			for (size_t j = 0; j < highest; j++) 
			{
				result[j] = result[j] * i + carry;
				carry = result[j] / 10;
				if (carry && (j == (highest -1)))
				{
					highest++;
				}
				result[j] %= 10;
			}
			g_highest = highest;
		}
		for (int i = g_highest - 1; i >= 0; i--)
		{
			cout << result[i];
		}
		cout << endl;
	}
	return 0;
}
