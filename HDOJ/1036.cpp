//Prob 1035: Robot Motion
//输入输出格式处理

//--------------------->>>>>>>>>>>>>>>>>>>>>>>>
//利用该行代码可以将cin指针移动到下一行
//char temp[10000];
//cout << setfill(' ') << setw(3) << serial << ": -" << endl;
//cin.getline(temp, 10000);
//<<<<<<<<<<<<<<<<<<<<<--------------------------------------------------------------

//--------------------->>>>>>>>>>>>>>>>>>>>>>>>
//cin不能读取空格，制表符，回车等
//取而代之，可以使用cin.get();
//<<<<<<<<<<<<<<<<<<<<<--------------------------------------------------------------

//--------------------->>>>>>>>>>>>>>>>>>>>>>>>
//setfill('S')
//setw(size_t)只对下一个对象起作用
//<<<<<<<<<<<<<<<<<<<<<--------------------------------------------------------------

//Problem Description
//A relay is a race for two or more teams of runners.Each member of a team runs one section of the race.Your task is to help to evaluate the results of a relay race.
//
//You have to process several teams.For each team you are given a list with the running times for every section of the race.You are to compute the average time per kilometer over the whole distance.That's easy, isn't it ?
//So if you like the fun and challenge competing at this contest, perhaps you like a relay race, too.Students from Ulm participated e.g.at the "SOLA" relay in Zurich, Switzerland.For more information visit http ://www.sola.asvz.ethz.ch/ after the contest is over.
//
//
//Input
//The first line of the input specifies the number of sections n followed by the total distance of the relay d in kilometers.You may safely assume that 1 <= n <= 20 and 0.0 < d < 200.0.Every following line gives information about one team : the team number t(an integer, right - justified in a field of width 3) is followed by the n results for each section, separated by a single space.These running times are given in the format "h:mm:ss" with integer numbers for the hours, minutes and seconds, respectively.In the special case of a runner being disqualified, the running time will be denoted by "-:--:--".Finally, the data on every line is terminated by a newline character.Input is terminated by EOF.
//
//
//	Output
//	For each team output exactly one line giving the team's number t right aligned in a field of width 3, and the average time for this team rounded to whole seconds in the format "m:ss". If at least one of the team's runners has been disqualified, output "-" instead.Adhere to the sample output for the exact format of presentation.
//
//
//	Sample Input
//	2 12.5
//	5 0:23 : 21 0 : 25 : 01
//	42 0 : 23 : 32 - : -- : --
//	7 0 : 33 : 20 0 : 41 : 35
//
//
//	Sample Output
//	5 : 3 : 52 min / km
//	42 : -
//	7 : 6 : 00 min / km
//
//
//	Source
//	University of Ulm Local Contest 2001
//
//
//	Recommend
//	We have carefully selected several similar problems for you:  1039 1037 1038 1048 1062

#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;
#define MAXNUM 11

void time_cal(int num_people, int serial, double dis)
{
	int sum_h = 0, sum_m = 0, sum_s = 0;
	for (size_t i = 0; i < num_people; i++)
	{
		char temp;
		cin >> temp;//hour
		if (temp == '-')
		{
			char temp[160];//less than 8 * 20
			cout << setfill(' ') << setw(3) << serial << ": -" << endl;
			cin.getline(temp, 160);
			return;
		}
		sum_h += temp - '0';
		cin >> temp;//':'
		cin >> temp;//m*10
		sum_m += (temp - '0') * 10;
		cin >> temp;//m
		sum_m += temp - '0';

		cin >> temp;//':'
		cin >> temp;//s*10
		sum_s += (temp - '0') * 10;
		cin >> temp;//s
		sum_s += temp - '0';
	}
	unsigned total_sec = sum_h * 3600 + sum_m * 60 + sum_s * 1;
	int avg_s = int(round(total_sec / dis));
	sum_m = avg_s / 60;
	sum_s = avg_s % 60;
	
	cout << setfill(' ') << setw(3) << serial << ":";
	cout << setfill(' ') << setw(2) << sum_m << ":" << setfill('0') << setw(2) << sum_s << " min/km" << endl;
	return;


}

int main()
{
	unsigned num_people;
	double dis;
	cin >> num_people >> dis;
	int serial;
	while (cin >> serial)
	{
		time_cal(num_people, serial, dis);
	}
	
	return 0;
}