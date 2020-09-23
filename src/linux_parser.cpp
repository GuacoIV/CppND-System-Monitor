#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  string label, value;
  string line;
  float memTotal, memFree;
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);

      linestream >> label >> value;
      if (label == "MemTotal:")
        memTotal = stof(value);
      else if (label == "MemFree:")
        memFree = stof(value);
    }
  }
  return (memTotal - memFree) / memTotal;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string upTime, idleTime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> upTime >> idleTime;
  }
  return std::stol(upTime);
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  vector<string> result;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    string label, value;
    std::istringstream linestream(line);
    linestream >> label;
    while (linestream >> value) {
      result.push_back(value);
    }
  }
  return result;
 }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string label, totalProcesses;
  string line;
  const string processesPrefex = "processes";
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> label >> totalProcesses;

      if (label == processesPrefex)
        return std::stoi(totalProcesses);
    }
  }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses()
{
  string label, runningProcs;
  string line;
  const string runningProcsPrefex = "procs_running";
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
        linestream >> label >> runningProcs;

      if (label == runningProcsPrefex)
        return std::stoi(runningProcs);
    }
  }
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string label, value;
  string line;
  std::ifstream stream(kProcDirectory + '/' + to_string(pid) + '/' + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> label >> value;
      if (label == "Uid:")
        return value;
    }
  }
   return string();
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string searchUid = Uid(pid);
  string user, x, uid;
  string line;
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      int firstColon = line.find(':');
      string user = line.substr(0, firstColon);
      int secondColon = line.find(':', firstColon + 1);
      int thirdColon = line.find(':', secondColon + 1);
      string uidLine = line.substr(secondColon + 1, thirdColon - secondColon - 1);
      if (uidLine == searchUid)
        return user;
    }
  }
  return string();
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string value;
  string line;
  std::ifstream stream(kProcDirectory + '/' + to_string(pid) + '/' + kStatFilename);
  if (stream.is_open() && std::getline(stream, line)) {
      std::istringstream linestream (line);
      int i = 1;
      while (linestream >> value) {
        if (i == 22)
        {
          time_t now;
          time(&now);
          time_t bootTime = difftime(now, UpTime());
          time_t processStart = std::atof(value.c_str()) / sysconf(_SC_CLK_TCK);
          return now - bootTime + processStart;
        }
        i++;
      }
    }
  return 0;
}