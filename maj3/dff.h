#pragma once

#include "maj3/module.h"

namespace maj {

template<typename T>
class Dff : public Module
{
public:
    T output_;
    T next_output_;

public:
    Dff();

    void tick(uint64_t nr_cycles) override;

    void operator()(const T& input) {
        next_output_ = input;
    }
};

template<typename T>
Dff<T>::Dff()
{
}

template<typename T>
void Dff<T>::tick(uint64_t /*nr_cycles*/)
{
    //printf("%lu: tick %p\n", nr_cycles, this);
    output_ = next_output_;
}

} // namespace maj
