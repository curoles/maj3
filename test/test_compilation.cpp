#include <cstdlib>
#include <cassert>
#include <cstdint>

#include "maj3/maj3gate.h"

int main()
{
    using namespace maj::gate;

    assert(maj3(0b0101, 0b1100, 0b0011) == 0b0101);

    return EXIT_SUCCESS;
}
