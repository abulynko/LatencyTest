#include <iostream>
#include <iomanip>
#include <fstream>
#include <thread>
#include "default_transport.hpp"
#include "your_transport.hpp"
#include "your_profiler.hpp"

const int32_t OBSERVATIONS_COUNT = 10000000;
const int32_t BUFFER_SIZE = 1024;

class BenchmarkRunner
{
    static const uint32_t GENERATOR_MULTIPLIER = 257;
    static const uint32_t GENERATOR_OFFSET = 53;

    AbstractTransport& transport;
    AbstractProfiler& profiler;
    std::mutex console_protector;
    std::thread* t_producer;
    std::thread* t_consumer;
    const int32_t observations_count;
    int64_t produced_sum;
    int64_t consumed_sum;

    static uint32_t generate(uint32_t x)
    {
        return x * GENERATOR_MULTIPLIER + GENERATOR_OFFSET;
    }

    static void* producer(void* context)
    {
        BenchmarkRunner* application = (BenchmarkRunner*)context;
        uint32_t x = 0;
        uint64_t sum = 0;
        for (int32_t i = 0; i < application->observations_count; ++i)
        {
            x = generate(x);
            sum += x;
            application->profiler.on_produce();
            application->transport.put(x);

        }

        {
            std::lock_guard<std::mutex> lk(application->console_protector);
            application->produced_sum = sum;

            std::cout << "Producer is done. Total sum is " << sum << std::endl;
            return nullptr;
        }
    }

    static void* consumer(void* context)
    {
        BenchmarkRunner* application = (BenchmarkRunner*)context;
        uint64_t sum = 0;
        for (int32_t i = 0; i < application->observations_count; ++i)
        {
            uint32_t x = application->transport.get();
            sum += x;
            application->profiler.on_consume();
        }

        {
            std::lock_guard<std::mutex> lk(application->console_protector);
            application->consumed_sum = sum;

            std::cout << "Consumer is done. Total sum is " << sum << std::endl;
            return nullptr;
        }
    }

public:

    BenchmarkRunner(AbstractTransport& tr, AbstractProfiler& pr, int32_t size) :
        transport(tr),
        profiler(pr),
        observations_count(size),
        console_protector()
    {
    }

    void start()
    {
        t_producer = new std::thread(producer, this);
        t_consumer = new std::thread(consumer, this);
    }

    ~BenchmarkRunner()
    {
        delete t_producer;
        delete t_consumer;
    }

    void wait_for_end()
    {
        t_producer->join();
        t_consumer->join();

        profiler.on_complete();

        std::cout << "Results for: " << typeid(transport).name() << std::endl;

        if (produced_sum != consumed_sum)
        {
            std::cout << "ERROR: Control consumed control sum does not comply with expected value. This often indicates that transporter code is incorrect." << std::endl;
        }
        
        std::cout << "Avg latency " << std::setprecision(9) << std::fixed << (profiler.average_nanoseconds_latency() / 1000000000.0) << " sec." << std::endl;
        std::cout << "Q95 latency " << std::setprecision(9) << std::fixed << (profiler.quantile95_nanoseconds_latency() / 1000000000.0) << " sec." << std::endl;
        std::cout << "Q99 latency " << std::setprecision(9) << std::fixed << (profiler.quantile99_nanoseconds_latency() / 1000000000.0) << " sec." << std::endl;
        std::cout << "Max latency " << std::setprecision(9) << std::fixed << (profiler.max_nanoseconds_latency() / 1000000000.0) << " sec." << std::endl;
        std::cout << std::endl;
    }
};

int32_t main()
{
    YourProfiler profiler1(OBSERVATIONS_COUNT);
    DefaultTransport default_transport(BUFFER_SIZE);
    BenchmarkRunner default_benchmark(default_transport, profiler1, OBSERVATIONS_COUNT);
    default_benchmark.start();
    default_benchmark.wait_for_end();

    YourProfiler profiler2(OBSERVATIONS_COUNT);
    YourTransport your_transport(BUFFER_SIZE);
    BenchmarkRunner your_benchmark(your_transport, profiler2, OBSERVATIONS_COUNT);
    your_benchmark.start();
    your_benchmark.wait_for_end();

    return 0;
}
