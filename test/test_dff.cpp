#include <cstdlib>
#include <cassert>
#include <cstdint>

#include "maj3/dff.h"

struct TopModule : public maj::TopModule
{
    maj::Dff<uint32_t> ff1_;
    maj::Dff<uint32_t> ff2_;

    void tick(uint64_t /*nr_cycles*/) override {
    }

    void init() override;
    void run(uint64_t nr_cycles) override;
};

void TopModule::init()
{
    ff1_.output_ = 1;
    ff2_.output_ = 1;
}

void TopModule::run(uint64_t nr_cycles)
{
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
}

int main()
{
    using namespace maj;

    {
        ::TopModule top;
        assert(top.nr_modules() == 3);

        Module::start(10);
    }

    //printf("Number of modules: %lu\n", Module::nr_modules());
    assert(Module::nr_modules() == 0);

    return EXIT_SUCCESS;
}
