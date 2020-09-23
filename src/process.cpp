#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

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
    long utime = atol(cpuValues[13].c_str());
    long stime = atol(cpuValues[14].c_str());
    long cutime = atol(cpuValues[15].c_str());
    long cstime = atol(cpuValues[16].c_str());
    long starttime = atol(cpuValues[21].c_str());

    long total_time = utime + stime;
    total_time += cutime + cstime;
    long secondsElapsed = systemUptime - (starttime / sysconf(_SC_CLK_TCK));
    return (total_time /sysconf(_SC_CLK_TCK)) / secondsElapsed;
}

// TODO: Return the command that generated this process
string Process::Command() { return string(); }

// TODO: Return this process's memory utilization
string Process::Ram() { return string(); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(_pid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(_pid); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }