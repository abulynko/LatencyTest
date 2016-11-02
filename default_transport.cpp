#include "default_transport.hpp"
#include <atomic>

DefaultTransport::DefaultTransport(int32_t size) :
    page_size(size),
    consumer_page(0),
    consumer_index(0),
    producer_page(0),
    producer_index(0),
    mtx()
{
    array = new int32_t[size];
}

DefaultTransport::~DefaultTransport()
{
    delete [] array;
}

void DefaultTransport::put(uint32_t x)
{
    std::unique_lock<std::mutex> lk(mtx);
    while (consumer_page < producer_page && consumer_index <= producer_index)
        cv_space.wait(lk);

    array[producer_index] = x;
    producer_index++;

    if (producer_index == page_size)
    {
        ++producer_page;
        producer_index = 0;
    }

    cv_data.notify_all();
}

uint32_t DefaultTransport::get()
{
    int32_t result;
    std::unique_lock<std::mutex> lk(mtx);

    while (consumer_page == producer_page && consumer_index >= producer_index)
        cv_data.wait(lk);

    result = array[consumer_index];
    consumer_index++;

    if (consumer_index == page_size)
    {
        consumer_index = 0;
        ++consumer_page;
    }

    cv_space.notify_all();
    return result;
}

