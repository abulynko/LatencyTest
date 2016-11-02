#ifndef _DEFAULT_TRANSPORT
#define _DEFAULT_TRANSPORT

#include "abstract_transport.hpp"
#include <mutex>
#include <condition_variable>

class DefaultTransport : public AbstractTransport
{
private:
    int32_t* array;
    int32_t page_size;
    volatile int32_t consumer_page;
    volatile int32_t consumer_index;
    volatile int32_t producer_page;
    volatile int32_t producer_index;
    std::mutex mtx;

    std::condition_variable cv_space;
    std::condition_variable cv_data;


public:
    DefaultTransport(int32_t size);
    virtual ~DefaultTransport() override;
    virtual void put(uint32_t  x) override;
    virtual uint32_t get() override;
};

#endif
