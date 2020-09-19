#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <vector>
#include <string>

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  Processor(std::vector<std::string> cpuValues) {
      _cpuValues = cpuValues;
    }
  // TODO: Declare any necessary private members
 private:
 std::vector<std::string> _cpuValues;
};

#endif