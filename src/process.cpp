#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return _pid; }

// TODO: Return this process's CPU utilization
// As recommended by course: https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599
// Note: This is currently calculating average since start of the process
float Process::CpuUtilization() {
    long systemUptime = LinuxParser::UpTime();
    auto cpuValues = LinuxParser::CpuUtilization(_pid);
    float utime = atof(cpuValues[13].c_str());
    float stime = atof(cpuValues[14].c_str());
    float cutime = atof(cpuValues[15].c_str());
    float cstime = atof(cpuValues[16].c_str());
    float starttime = atof(cpuValues[21].c_str());

    float total_time = utime + stime;
    total_time += cutime + cstime;
    float secondsElapsed = systemUptime - (starttime / sysconf(_SC_CLK_TCK));
    return (total_time /sysconf(_SC_CLK_TCK)) / secondsElapsed;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(_pid); }

// TODO: Return this process's memory utilization
string Process::Ram() {
    float kb = atof(LinuxParser::Ram(_pid).c_str());
    std::stringstream result("");
    result << std::fixed << std::setprecision(2) << (_ram = (kb / (float)1024));
    return result.str();
}

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(_pid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(_pid); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& p) const {
    return _ram < p._ram;
}