#ifndef _ABSTRACT_PROFILER
#define _ABSTRACT_PROFILER
#include <cstdint>

class AbstractProfiler
{
public:
    virtual void on_produce() = 0;
    virtual void on_consume() = 0;
    virtual void on_complete() = 0;

    virtual uint64_t average_nanoseconds_latency() = 0;
    virtual uint64_t quantile95_nanoseconds_latency() = 0;
    virtual uint64_t quantile99_nanoseconds_latency() = 0;
    virtual uint64_t max_nanoseconds_latency() = 0;

    virtual ~AbstractProfiler() { }
};

#endif
