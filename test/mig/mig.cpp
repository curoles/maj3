#include "mig.h"

#include <cstdlib>
#include <cassert>
#include <cstdint>


void MigModule::init()
{
    //ff1_.output_ = 1;
    //ff2_.output_ = 1;
}

void MigModule::tick(uint64_t /*nr_cycles*/)
{
}

void MigModule::run(uint64_t /*nr_cycles*/)
{
#if 0
    //printf("%lu: %u %u\n", nr_cycles, ff1_.output_, ff2_.output_);

    if (nr_cycles & 1) {
        assert(ff1_.output_ + 1 == ff2_.output_);
    } else {
        assert(ff1_.output_ == ff2_.output_);
    }

    ff1_(ff2_.output_);
    ff2_(ff1_.output_ + 1);

    if (nr_cycles == 8) {
        Module::stop();
    }
#endif
}

