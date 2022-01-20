#include <cstdlib>
#include <cassert>
#include <cstdint>
#include <cstdio>

#include "mig.h"

#include "maj3/module.h"

struct TopModule : public maj::TopModule
{
    MigModule mig_;

    void tick(uint64_t /*nr_cycles*/) override {
    }

    void init() override;
    void run(uint64_t nr_cycles) override;
};

void TopModule::init()
{
    mig_.init();
}

void TopModule::run(uint64_t nr_cycles)
{
    //printf("%lu: %u %u\n", nr_cycles, ff1_.output_, ff2_.output_);

    mig_.run(nr_cycles);
}

int main()
{
    using namespace maj;

    {
        ::TopModule top;

        top.start(10);
    }

    //printf("Number of modules: %lu\n", Module::nr_modules());
    assert(Module::nr_modules() == 0);

    return EXIT_SUCCESS;
}
