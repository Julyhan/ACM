#pragma once
#ifndef _TTIMER_
#define _TTIMER_
#include <chrono>
#include <iostream>
#include <iomanip>
#include <string>

// ----------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//usage:
//TTimer test;
//test.start();
//Sleep(1000);
//test.stop();
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<--------------------------------------------------

//@param PRINT: true:打印精度信息 false：不打印精度信息
bool PRINT = false;


//@brief: 打印三种系统时间的精度
//使用说明：
//std::cout << "system_clock: " << std::endl;
//printClockData<std::chrono::system_clock>();
//std::cout << "\nhigh_resolution_clock: " << std::endl;
//printClockData<std::chrono::high_resolution_clock>();
//std::cout << "\nsteady_clock: " << std::endl;
//printClockData<std::chrono::steady_clock>();
template <typename C>
void printClockData()
{
	using namespace std;
	if (PRINT)
		cout << "- precision: ";
	// if time unit isless or equal one millisecond
	typedef typename C::period P; // type of time unit
	if (ratio_less_equal<P, milli>::value) {
		// convert to and print as milliseconds
		typedef typename ratio_multiply<P, kilo>::type TT;
		if (PRINT)
			cout << fixed << double(TT::num) / TT::den
			<< " milliseconds" << endl;
	}
	else {
		// print asseconds
		if (PRINT)
			cout << fixed << double(P::num) / P::den << " seconds" << endl;
	}
	if (PRINT)
		cout << "- is_steady: " << boolalpha << C::is_steady << endl;
}


#define CLOCKTYPE steady_clock
class TTimer
{
private:
	std::chrono::CLOCKTYPE::time_point system_start;
	enum Precison
	{
		nanoseconds = 0,
		microseconds = 1,
		milliseconds = 2,
		seconds = 4
	};
	Precison prec;
public:
	TTimer()
	{
		typedef std::chrono::CLOCKTYPE::period P;
		if (std::ratio_less_equal<P, std::milli>::value) {
			// convert to and print as milliseconds
			typedef std::ratio_multiply<P, std::kilo>::type TT;
			double precision = double(TT::num) / TT::den;
			if (PRINT)
				std::cout << std::fixed << precision
				<< " milliseconds" << std::endl;
			if (precision >= 1)
				prec = milliseconds;
			else if (precision >= 0.001)
				prec = microseconds;
			else
				prec = nanoseconds;
		}
		else {
			// print asseconds
			if (PRINT)
				std::cout << std::fixed << double(P::num) / P::den << " seconds" << std::endl;
			prec = seconds;
		}
	}
	void start()
	{
		system_start = std::chrono::CLOCKTYPE::now();
	}
	void stop()
	{
		auto diff = std::chrono::CLOCKTYPE::now() - system_start;
		auto sec = std::chrono::duration_cast<std::chrono::nanoseconds>(diff);
		std::string prec_name;
		int num_pow;
		switch (prec)
		{
		case TTimer::nanoseconds:
			num_pow = 1;
			prec_name = "nanoseconds";
			break;
		case TTimer::microseconds:
			num_pow = 1000;
			prec_name = "microseconds";
			break;
		case TTimer::milliseconds:
			num_pow = 1000000;
			prec_name = "milliseconds";
			break;
		case TTimer::seconds:
			num_pow = 1000000000;
			prec_name = "seconds";
			break;
		default:
			break;
		}
		std::cout << "this program runs: " << int(sec.count() / num_pow) << prec_name << std::endl;
	}
};
#endif