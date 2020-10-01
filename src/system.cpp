#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

System::System() {
    _cpu = Processor();
}

// TODO: Return the system's CPU
Processor& System::Cpu()
{
    return _cpu;
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes()
{
    auto pids = LinuxParser::Pids();
    for (auto pid : pids) {
        auto p = Process(pid);
        auto found = std::find(_processes.begin(), _processes.end(), p);
        if (found == _processes.end())
            _processes.push_back(Process(pid));
    }

    for (auto pid : _processes) {
        int p = pid.Pid();
        auto found = std::find(pids.begin(), pids.end(), p);
        if (found == pids.end())            
            _processes.erase(std::find(_processes.begin(), _processes.end(), pid));
    }
    std::sort(_processes.rbegin(), _processes.rend());
    return _processes;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }