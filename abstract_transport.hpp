#ifndef _ABSTRACT_TRANSPORT
#define _ABSTRACT_TRANSPORT
#include <cstdint>

class AbstractTransport
{
public:
    virtual void put(uint32_t x) = 0;
    virtual uint32_t get() = 0;
    virtual ~AbstractTransport() { }
};

#endif
