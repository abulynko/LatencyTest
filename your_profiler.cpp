#include <thread>
#include <iostream>
#include <algorithm>

#include "your_profiler.hpp"

YourProfiler::YourProfiler(int32_t observations_count)
{
  observations_count_ = static_cast<uint64_t >(observations_count);

  max_value_ = 0;
  avg_value_ = 0;
  quantile95_ = 0;
  quantile99_ = 0;
  records_produce_.reserve(static_cast<uint64_t >(observations_count_));
  records_consume_.reserve(static_cast<uint64_t >(observations_count_));
  diffs_.reserve(static_cast<uint64_t >(observations_count_));
}

void YourProfiler::on_produce()
{
  records_produce_.push_back(std::chrono::high_resolution_clock::now());
}

void YourProfiler::on_consume()
{
  records_consume_.push_back(std::chrono::high_resolution_clock::now());
}

void YourProfiler::on_complete()
{
  using std::chrono::nanoseconds;
  using std::chrono::duration_cast;

  for (int32_t i = 0; i < observations_count_; ++i) {
    diffs_.push_back(
        static_cast<uint64_t >(
            duration_cast<nanoseconds>(
                records_consume_[i] - records_produce_[i])
                .count()));
  }

  std::sort(diffs_.begin(), diffs_.end());

  max_value_ = diffs_.back();

  uint64_t quantile_95_count = (observations_count_*95)/100;
  uint64_t quantile_99_count = (observations_count_*99)/100;

  for (uint32_t i = 0; i < observations_count_; i++) {
    avg_value_ += diffs_[i];

    if (i == quantile_95_count - 1) {
      quantile95_ = avg_value_/quantile_95_count;
    }
    if (i == quantile_99_count - 1) {
      quantile99_ = avg_value_/quantile_99_count;
    }
  }
  avg_value_ = avg_value_/observations_count_;
}

uint64_t YourProfiler::average_nanoseconds_latency()
{
  return avg_value_;
}

uint64_t YourProfiler::quantile95_nanoseconds_latency()
{
  return quantile95_;
}

uint64_t YourProfiler::quantile99_nanoseconds_latency()
{
  return quantile99_;
}

uint64_t YourProfiler::max_nanoseconds_latency()
{
  return max_value_;
}

YourProfiler::~YourProfiler()
{

}
