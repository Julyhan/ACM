//Prob: 1029 Ignatius and the Princess IV
//设置标志寄存器
//占据一半以上的数和其它数抵消依然占据主流
//Problem Description
//"OK, you are not too bad, em... But you can never pass the next test." feng5166 says.
//
//"I will tell you an odd number N, and then N integers. There will be a special integer among them, you have to tell me which integer is the special one after I tell you all the integers." feng5166 says.
//
//"But what is the characteristic of the special integer?" Ignatius asks.
//
//"The integer will appear at least (N+1)/2 times. If you can't find the right integer, I will kill the Princess, and you will be my dinner, too. Hahahaha....." feng5166 says.
//
//Can you find the special integer for Ignatius ?
//
//
//Input
//The input contains several test cases.Each test case contains two lines.The first line consists of an odd integer N(1 <= N <= 999999) which indicate the number of the integers feng5166 will tell our hero.The second line contains the N integers.The input is terminated by the end of file.
//
//
//Output
//For each test case, you have to output only one line which contains the special number you have found.
//
//
//Sample Input
//5
//1 3 2 3 3
//11
//1 1 1 1 1 5 5 5 5 5 5
//7
//1 1 1 1 1 1 1
//
//
//Sample Output
//3
//5
//1
//
//
//Author
//Ignatius.L
//
//
//Recommend
//We have carefully selected several similar problems for you:  1040 1074 1171 1203 1087

#include <iostream>
using namespace std;



int main()
{
	int n;
	while (scanf("%d", &n) != EOF) {
		int count = 0;//count the number of (right - wrong)
		int result, num;
		for (size_t i = 0; i < n; i++)
		{
			cin >> num;
			if (!count)
			{
				result = num;
				count++;
				continue;
			}
			if (num == result)
			{
				count++;
			}
			else
			{
				count--;
			}
			
		}
		cout << result << endl;
	}

	return 0;
}

