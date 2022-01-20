#pragma once

#include "maj3/module.h"

struct MigModule : public maj::TopModule
{
    //Fetch fetch_;
    //Decode decode_;

    void tick(uint64_t nr_cycles) override;
    void init() override;
    void run(uint64_t nr_cycles) override;
};
