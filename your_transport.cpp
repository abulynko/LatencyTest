#include "your_transport.hpp"

YourTransport::YourTransport(int32_t size)
{
    array_ = new uint32_t[size];
    array_len_ = size;
    put_index_ = -1;
    get_index_ = -1;
    put_frame_number_ = 0;
    get_frame_number_ = 0;
}

YourTransport::~YourTransport() {
    delete[] array_;
}

void YourTransport::put(uint32_t x) {
    while (true) {
        if ((put_index_ + (array_len_ * put_frame_number_))
            - (get_index_ + (array_len_ * get_frame_number_))
            < array_len_) {
            if (put_index_ == array_len_ - 1) {
                put_index_ = -1;
                put_frame_number_++;
            }
            array_[put_index_ + 1] = x;
            ++put_index_;
            break;
        }
    }
}

uint32_t YourTransport::get() {
    while (true) {
        if ((put_index_ + (array_len_ * put_frame_number_))
            > (get_index_ + (array_len_ * get_frame_number_))) {
            if (get_index_ == array_len_ - 1) {
                get_index_ = -1;
                get_frame_number_++;
            }
            uint32_t result = array_[get_index_ + 1];
            get_index_++;
            return result;
        }
    }
}
