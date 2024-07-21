#pragma once

#include <atomic>
#include <array>

namespace spsc
{

enum class op_status
{
    SUCCESS = 1,
    FULL = 2,
    EMPTY = 3
};

template <typename T, size_t S>
class queue
{
public:

    auto push(T value) -> op_status
    {
        if (write == read - 1 || (write == S - 1 && read == 0))
            return op_status::FULL;

        data[write] = value;

        if (write == S - 1)
            write = 0;
        else
            write++;

        return op_status::SUCCESS;
    }

    auto pop(T& ret) -> op_status
    {
        if (write == read)
            return op_status::EMPTY;

        ret = data[read];

        if (read == S - 1)
            read = 0;
        else
            read++;

        return op_status::SUCCESS;
    }

private:

    std::array<T, S> data;
    std::atomic<size_t> read = 0, write = 0;

};

}
