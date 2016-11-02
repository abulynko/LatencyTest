#ifndef _YOUR_PROFILER
#define _YOUR_PROFILER

#include <vector>

#include "abstract_profiler.hpp"

class YourProfiler : public AbstractProfiler
{
// TODO

public:
    virtual void on_produce() override;
    virtual void on_consume() override;
    virtual void on_complete() override;

    virtual uint64_t average_nanoseconds_latency() override;
    virtual uint64_t quantile95_nanoseconds_latency() override;
    virtual uint64_t quantile99_nanoseconds_latency() override;
    virtual uint64_t max_nanoseconds_latency() override;

    YourProfiler(int32_t observations_count);

    virtual ~YourProfiler() override;

 private:
  uint64_t observations_count_;
  std::vector<std::chrono::high_resolution_clock::time_point> records_produce_;
  std::vector<std::chrono::high_resolution_clock::time_point> records_consume_;
  std::vector<uint64_t > diffs_;
  uint64_t max_value_;
  uint64_t avg_value_;
  uint64_t quantile95_;
  uint64_t quantile99_;
};

#endif
