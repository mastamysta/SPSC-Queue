#include <iostream>
#include <thread>

#include "spsc.hpp"

using qtype = spsc::queue<uint32_t, 100>;

void produce(uint32_t messages, qtype& q)
{
    for (int i = 0; i < messages; i++)
    {
        if (q.push(i) != spsc::op_status::SUCCESS)
            i--;
    }
}

void consume(uint32_t messages, qtype& q)
{
    for (int i = 0; i < messages; i++)
    {
        uint32_t v;

        if (q.pop(v) != spsc::op_status::SUCCESS)
            i--;
    }
}

int main()
{
    std::cout << "Hello world.\n";

    qtype q;

    uint32_t msgs = 1000000;

    std::thread producer(produce, msgs, std::ref(q));
    std::thread consumer(consume, msgs, std::ref(q));

    producer.join();
    consumer.join();

    return 0;
}
