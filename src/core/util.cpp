#include <cstdlib>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "util.hpp"
#include "position.hpp"

using namespace std;

int random_int(int a, int b)
{
    int range = b - a + 1;
    int draw = (rand() % range) + a;
    return draw;
}

void shuffle_int_array(int *values, int size)
{
    for (int k = size - 1; k > 0; k--)
    {
        int j = random_int(0, k);
        int temp = values[k];
        values[k] = values[j];
        values[j] = temp;
    }
}

string int_to_string(int n)
{
    return to_string(n);
}

void copy_array_10(Position &dest, const Position &src)
{
    dest = src;
}

int char_to_int(char c)
{
	return c - 48;
}

string current_datetime_string()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    std::tm local_tm{};
#if defined(_WIN32)
    localtime_s(&local_tm, &now_time_t);
#else
    localtime_r(&now_time_t, &local_tm);
#endif

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    int centiseconds = ms.count() / 10;

    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S")
        << '.' << std::setfill('0') << std::setw(2) << centiseconds;
    return oss.str();
}

void log_action(const string &message_action)
{
    std::cout << current_datetime_string() << " : " << message_action << std::endl;
}