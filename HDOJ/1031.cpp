//Prob: 1031 
//
//
//Problem Description
//Soon after he decided to design a T - shirt for our Algorithm Board on Free - City BBS, XKA found that he was trapped by all kinds of suggestions from everyone on the board.It is indeed a mission - impossible to have everybody perfectly satisfied.So he took a poll to collect people's opinions. Here are what he obtained: N people voted for M design elements (such as the ACM-ICPC logo, big names in computer science, well-known graphs, etc.). Everyone assigned each element a number of satisfaction. However, XKA can only put K (<=M) elements into his design. He needs you to pick for him the K elements such that the total number of satisfaction is maximized.
//
//
//Input
//The input consists of multiple test cases.For each case, the first line contains three positive integers N, M and K where N is the number of people, M is the number of design elements, and K is the number of elements XKA will put into his design.Then N lines follow, each contains M numbers.The j - th number in the i - th line represents the i - th person's satisfaction on the j-th element.
//
//
//Output
//For each test case, print in one line the indices of the K elements you would suggest XKA to take into consideration so that the total number of satisfaction is maximized.If there are more than one solutions, you must output the one with minimal indices.The indices start from 1 and must be printed in non - increasing order.There must be exactly one space between two adjacent indices, and no extra space at the end of the line.
//
//
//Sample Input
//3 6 4
//2 2.5 5 1 3 4
//5 1 3.5 2 2 2
//1 1 1 1 1 10
//3 3 2
//1 2 3
//2 3 1
//3 1 2
//
//
//Sample Output
//6 5 3 1
//2 1
//
//
//Author
//CHEN, Yue
//
//
//Source
//CYJJ's Funny Contest #1, Killing in Seconds
//
//
//Recommend
//Ignatius.L | We have carefully selected several similar problems for you:  1036 1032 1033 1037 1039



#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, double> POLL;

bool cmp(POLL a, POLL b)
{
	if (a.second != b.second)
		return a.second > b.second;
	else
		return a.first < b.first;
}
bool cmp2(POLL a, POLL b)
{
	return a.first > b.first;
}
int main()
{
	int N, M, K;
	while (scanf("%d%d%d", &N, &M, &K) != EOF) 
	{
		vector<POLL> test;
		double poll_socre;
		for (size_t i = 0; i < M; i++)
		{
			POLL initial(i, 0);
			test.push_back(initial);
		}
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < M; j++)
			{
				cin >> poll_socre;
				test.at(j).second += poll_socre;
			}
		}
		sort(test.begin(), test.end(), cmp);
		sort(test.begin(), test.begin() + K, cmp2);
		for (size_t i = 0; i < K - 1; i++)
		{
			cout << test.at(i).first + 1 << " ";
		}
		cout << test.at(K - 1).first + 1 << endl;
	}
	return 0;
}

