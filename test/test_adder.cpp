#include <cstdlib>
#include <cassert>
#include <cstdint>

#include "maj3/adder.h"

int main()
{
    using namespace maj::block;

    assert(one_bit_adder(0, 0, 0) == std::make_pair(0, 0));
    assert(one_bit_adder(0, 1, 0) == std::make_pair(1, 0));
    assert(one_bit_adder(1, 0, 0) == std::make_pair(1, 0));
    assert(one_bit_adder(1, 1, 0) == std::make_pair(0, 1));
    assert(one_bit_adder(1, 1, 1) == std::make_pair(1, 1));

    assert(ripple_adder(0,0) == std::make_pair(0, false));
    assert(ripple_adder(0,1) == std::make_pair(1, false));
    assert(ripple_adder(2,3) == std::make_pair(5, false));
    assert(ripple_adder(2,-3) == std::make_pair(-1, false));

    assert(ripple_adder<uint8_t>(254,1) == std::make_pair((uint8_t)255, false));
    assert(ripple_adder<uint8_t>(254,2) == std::make_pair((uint8_t)0, true));
    assert(ripple_adder<uint8_t>(254,3) == std::make_pair((uint8_t)1, true));

    assert((ripple_adder<uint8_t, 4>(2,3)) == std::make_pair((uint8_t)5, false));
    assert((ripple_adder<uint8_t, 4>(14,3)) == std::make_pair((uint8_t)1, true));

    { RippleAdder adder {.a_ = 1, .b_ = 2};
    assert(adder() == 3 and adder.overflow_ == false); }

    RippleAdder<uint8_t> adder {.a_ = 254, .b_ = 3};
    assert(adder() == 1 and adder.overflow_ == true);

    return EXIT_SUCCESS;
}
