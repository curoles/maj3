#pragma once

#include <utility>
#include <tuple>
#include <cstdint>
#include <cassert>

#include "maj3/maj3gate.h"

namespace maj::block {

template<typename T>
constexpr std::pair<T,T> one_bit_adder(T a, T b, T c)
{
    using namespace maj::gate;
    T sum, carry_out;

    carry_out = maj3(a, b, c);
    T s2 = maj3(a, b, inv(c));
    sum = maj3(inv(carry_out), s2, c);

    return std::make_pair(sum, carry_out);
}

static inline void one_bit_adder_static_test()
{
    static_assert(one_bit_adder(0, 0, 0) == std::make_pair(0, 0));
    static_assert(one_bit_adder(0, 1, 0) == std::make_pair(1, 0));
    static_assert(one_bit_adder(1, 0, 0) == std::make_pair(1, 0));
    static_assert(one_bit_adder(1, 1, 0) == std::make_pair(0, 1));
    static_assert(one_bit_adder(1, 1, 1) == std::make_pair(1, 1));
}

template<typename T, unsigned int WIDTH=8*sizeof(T)>
constexpr std::pair<T,bool> ripple_adder(T a, T b)
{
    using namespace maj::gate;
    static_assert(WIDTH <= 8*sizeof(T));
    constexpr unsigned int NR_BITS = WIDTH;
    constexpr T MSBIT_MASK = (T)1 << (NR_BITS-1);
    T sum {0};
    T carry {0}, mask {1};

    for (unsigned int pos = 0; pos < NR_BITS; ++pos) {
        auto [sum_i,co_i] = one_bit_adder(a & mask, b & mask, (carry << 1) & mask);
        sum |= sum_i;
        carry = co_i;
        mask <<= 1;
    }

    return std::make_pair(sum, carry & MSBIT_MASK);
}

static inline void ripple_adder_static_test()
{
    static_assert(ripple_adder(0,0) == std::make_pair(0, false));
    static_assert(ripple_adder(0,1) == std::make_pair(1, false));
    static_assert(ripple_adder(2,3) == std::make_pair(5, false));
    static_assert(ripple_adder(2,-3) == std::make_pair(-1, false));

    static_assert(ripple_adder<uint8_t>(254,1) == std::make_pair((uint8_t)255, false));
    static_assert(ripple_adder<uint8_t>(254,2) == std::make_pair((uint8_t)0, true));
    static_assert(ripple_adder<uint8_t>(254,3) == std::make_pair((uint8_t)1, true));

    static_assert(ripple_adder<uint8_t, 4>(2,3) == std::make_pair((uint8_t)5, false));
    static_assert(ripple_adder<uint8_t, 4>(14,3) == std::make_pair((uint8_t)1, true));
}

template<typename T>
struct RippleAdder
{
    T a_, b_;
    T sum_ {0};
    bool overflow_ {false};

    T operator()() {
        std::tie(sum_, overflow_) = ripple_adder(a_, b_);
        return sum_;
    }
};

static inline void RippleAdder_static_test()
{
    RippleAdder adder {.a_ = 1, .b_ = 2};
    adder();
    assert(adder.sum_ == 3 and adder.overflow_ == false); 
}

} // namespace maj::block
