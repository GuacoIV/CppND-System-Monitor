#include "processor.h"
#include "linux_parser.h"

using namespace::LinuxParser;

// TODO: Return the aggregate CPU utilization
// https://github.com/Leo-G/Data-Science-Wiki/wiki/How-Linux-CPU-Usage-Time-and-Percentage-is-calculated
float Processor::Utilization()
{
    float totalCPUTimeSinceBoot = atof(_cpuValues[CPUStates::kUser_].c_str()) +
    atof(_cpuValues[CPUStates::kNice_].c_str()) +
    atof(_cpuValues[CPUStates::kSystem_].c_str()) +
    atof(_cpuValues[CPUStates::kIdle_].c_str()) +
    atof(_cpuValues[CPUStates::kIOwait_].c_str()) +
    atof(_cpuValues[CPUStates::kIRQ_].c_str()) +
    atof(_cpuValues[CPUStates::kSoftIRQ_].c_str()) +
    atof(_cpuValues[CPUStates::kSteal_].c_str());

    float totalCPUIdleTimeSinceBoot = atof(_cpuValues[CPUStates::kIdle_].c_str()) + atof(_cpuValues[CPUStates::kIOwait_].c_str());

    float totalCPUUsageTimeSinceBoot = totalCPUTimeSinceBoot - totalCPUIdleTimeSinceBoot;

    return totalCPUUsageTimeSinceBoot / totalCPUTimeSinceBoot;
}
