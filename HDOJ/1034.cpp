//Prob: 1034 Candy Sharing Game
//Problem Description


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//@brief: give the candy
//@param test: the candy before pathing
//@return: the new candy children owns
vector<unsigned> candy_path(vector<unsigned>& test)
{
	
	int len = test.size();
	unsigned temp = test.at(len - 1);
	for (size_t i = len - 1; i > 0; i--)
	{
		test.at(i) /= 2;
		test.at(i) += test.at(i - 1)/2;
	}
	test.at(0) /= 2;
	test.at(0) += temp/2;
	return test;
}

//@brief: make candy_number -> candy_number % 2 == 0
//@param test: the candy before even
//@return: the even number candy
vector<unsigned> candy_even(vector<unsigned>& test)
{
	int len = test.size();
	if (!len)
		return test;
	for (size_t i = 0; i < len; i++)
	{
		if (1 == test.at(i) % 2)
		{
			test.at(i)++;
		}
	}
	return test;
}

//@brief: make sure whether the element is all the same
//@param test: the input vector
//@return: true: they are same, false: they are different
bool samevector(vector<unsigned> test)
{
	int len = test.size();
	unsigned flag;
	if (len!=0)
		flag = test.at(0);
	else
		return false;
	for (size_t i = 1; i < len; i++)
	{
		if (flag != test.at(i))
			return false;
	}
	return true;
}

int main()
{
	unsigned int num_stu;
	while (cin >> num_stu)
	{
		if (num_stu == 0)
		{
			break;
		}
		vector<unsigned> test;
		unsigned num_candy;
		for (size_t i = 0; i < num_stu; i++)
		{
			cin >> num_candy;
			test.push_back(num_candy);
		}
		int total_count = 0;
		bool flag = samevector(test);
		while (!flag)
		{
			test = candy_path(test);
			total_count++;
			test = candy_even(test);
			flag = samevector(test);
		}
		cout << total_count << " " << test.at(0) << endl;
	}


	return 0;
}

