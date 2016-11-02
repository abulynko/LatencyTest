#ifndef _YOUR_TRANSPORT
#define _YOUR_TRANSPORT

#include "abstract_transport.hpp"

#include <atomic>

class YourTransport : public AbstractTransport {

public:
    YourTransport(int32_t size);

    virtual ~YourTransport() override;
    virtual void put(uint32_t x) override;
    virtual uint32_t get() override;

private:
    uint32_t *array_;
    int32_t array_len_;

    volatile std::atomic<int32_t> put_index_;
    volatile std::atomic<int32_t> get_index_;
    volatile std::atomic<int32_t> put_frame_number_;
    volatile std::atomic<int32_t> get_frame_number_;
};

#endif
