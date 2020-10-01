#include "processor.h"
#include "linux_parser.h"

using namespace::LinuxParser;

// TODO: Return the aggregate CPU utilization
// https://github.com/Leo-G/Data-Science-Wiki/wiki/How-Linux-CPU-Usage-Time-and-Percentage-is-calculated
float Processor::Utilization()
{
    auto cpuValues = LinuxParser::CpuUtilization();
    float totalCPUTimeSinceBoot = atof(cpuValues[CPUStates::kUser_].c_str()) +
    atof(cpuValues[CPUStates::kNice_].c_str()) +
    atof(cpuValues[CPUStates::kSystem_].c_str()) +
    atof(cpuValues[CPUStates::kIdle_].c_str()) +
    atof(cpuValues[CPUStates::kIOwait_].c_str()) +
    atof(cpuValues[CPUStates::kIRQ_].c_str()) +
    atof(cpuValues[CPUStates::kSoftIRQ_].c_str()) +
    atof(cpuValues[CPUStates::kSteal_].c_str());

    float totalCPUIdleTimeSinceBoot = atof(cpuValues[CPUStates::kIdle_].c_str()) + atof(cpuValues[CPUStates::kIOwait_].c_str());

    float totalCPUUsageTimeSinceBoot = totalCPUTimeSinceBoot - totalCPUIdleTimeSinceBoot;

    float result = (totalCPUUsageTimeSinceBoot - _lastCPUUsageTimeSinceBoot) / (totalCPUTimeSinceBoot - _lastCPUTimeSinceBoot);
    _lastCPUUsageTimeSinceBoot = totalCPUUsageTimeSinceBoot;
    _lastCPUTimeSinceBoot = totalCPUTimeSinceBoot;
    return result;
}
