#ifndef FIFO_H
#define FIFO_H

#include <type_traits>

template <class T, size_t N>
class FIFO
{
    static_assert(std::is_arithmetic<T>::value, "T must be numeric");

public:
    void add(T n)
    {
        buffer[cnt] = n;
        if (++cnt == N)
            cnt = 0;

        if(trackValues)
        {
            for(size_t i = 0; i < N; i++)
            {
                if(buffer[i] < min)
                    min = buffer[i];
                else if(buffer[i] > max)
                    max = buffer[i];
            }
        }
    }

    T get(size_t n)
    {
        if (n < N)
        {
            return buffer[(cnt + n) % N];
        }
        return 0;
    }

    T min = 0;
    T max = 0;
    bool trackValues = false;
private:
    size_t cnt = 0;
    T buffer[N] = { 0 };
};

#endif