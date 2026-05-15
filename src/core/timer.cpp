#include <cmath>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "timer.hpp"

using namespace std;

namespace
{
constexpr int TIME_IN_SECONDS = 0;
constexpr int STATUS = 1;
constexpr int NUMBER_OF_MOVES = 2;
constexpr int SCORE = 3;
constexpr int CURRENT_AVG = 4;
constexpr int CURRENT_STDEV = 5;

std::vector<ScoreTimeRow> times;

double round_to_centiseconds(double value)
{
    return std::round(value * 100.0) / 100.0;
}

void compute_current_stats(double &avg, double &stdev)
{
    double sum = 0.0;
    int count = 0;
    for (const ScoreTimeRow &row : times)
    {
        if (row[STATUS] != 0.0)
        {
            sum += row[TIME_IN_SECONDS];
            ++count;
        }
    }

    if (count == 0)
    {
        avg = 0.0;
        stdev = 0.0;
        return;
    }

    avg = sum / static_cast<double>(count);

    double variance_sum = 0.0;
    for (const ScoreTimeRow &row : times)
    {
        if (row[STATUS] != 0.0)
        {
            double diff = row[TIME_IN_SECONDS] - avg;
            variance_sum += diff * diff;
        }
    }

    stdev = std::sqrt(variance_sum / static_cast<double>(count));
    avg = round_to_centiseconds(avg);
    stdev = round_to_centiseconds(stdev);
}
}

// Converts elapsed time in seconds to a formatted string (e.g., "01:23.45").
string time_to_string(double elapsed_seconds)
{
    int total_centiseconds = static_cast<int>(elapsed_seconds * 100.0);
    int total_seconds = total_centiseconds / 100;
    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    int centiseconds = total_centiseconds % 100;
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%02d:%02d.%02d", minutes, seconds, centiseconds);
    return string(buffer);
}

double compute_score(double elapsed_seconds, int move_count)
{
    double raw_score = atan(elapsed_seconds * move_count / 1000.0) * 200.0 / M_PI;
    return 100.0 - raw_score;
}

string format_score(double score)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << score;
    return oss.str();
}

void register_time_sample(double elapsed_seconds, int move_count, int status)
{
    double time_in_seconds = round_to_centiseconds(elapsed_seconds);
    if (status == 2)
        time_in_seconds += 2.0;
    double score = (status == 0) ? 0.0 : compute_score(time_in_seconds, move_count);

    ScoreTimeRow row = {
        time_in_seconds,
        static_cast<double>(status),
        static_cast<double>(move_count),
        score,
        0.0,
        0.0};
    times.push_back(row);

    double avg = 0.0;
    double stdev = 0.0;
    compute_current_stats(avg, stdev);
    times.back()[CURRENT_AVG] = avg;
    times.back()[CURRENT_STDEV] = stdev;
}

void print_time()
{
    if (times.empty())
        return;

    const ScoreTimeRow &last = times.back();
    int status = static_cast<int>(last[STATUS]);
    const char *status_text = "DNF";
    if (status == 1)
        status_text = "ok";
    else if (status == 2)
        status_text = "+2";

    int count_non_dnf = 0;
    for (const ScoreTimeRow &row : times)
    {
        if (static_cast<int>(row[STATUS]) != 0)
            ++count_non_dnf;
    }

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "> time status moves score avg stdev\n";
    oss << "> " << last[TIME_IN_SECONDS]
        << ' ' << status_text
        << ' ' << static_cast<int>(last[NUMBER_OF_MOVES])
        << ' ' << last[SCORE]
        << ' ';

    if (count_non_dnf == 0)
        oss << "nan nan";
    else
        oss << last[CURRENT_AVG] << ' ' << last[CURRENT_STDEV];

    std::cout << oss.str() << std::endl;
}

bool export_times()
{
    std::ofstream out("./export/times.csv", std::ios::trunc);
    if (!out.is_open())
        return false;

    out << "time, status, moves, score, avg, stdev\n";
    out << std::fixed << std::setprecision(2);

    int count_non_dnf = 0;
    for (const ScoreTimeRow &row : times)
    {
        int status = static_cast<int>(row[STATUS]);
        const char *status_text = "DNF";
        if (status == 1)
            status_text = "ok";
        else if (status == 2)
            status_text = "+2";

        if (status != 0)
            ++count_non_dnf;

        out << row[TIME_IN_SECONDS]
            << ", " << status_text
            << ", " << static_cast<int>(row[NUMBER_OF_MOVES])
            << ", " << row[SCORE]
            << ", ";

        if (count_non_dnf == 0)
            out << "nan, nan";
        else
            out << row[CURRENT_AVG] << ", " << row[CURRENT_STDEV];

        out << '\n';
    }

    return out.good();
}

const std::vector<ScoreTimeRow> &times_table()
{
    return times;
}