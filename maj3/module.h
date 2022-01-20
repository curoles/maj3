#pragma once

#include <vector>
#include <cstdint>
#include <cstdio>

namespace maj {

class Module
{
    static std::vector<Module*> registry_;
    static volatile bool stop_request_;

public:
    Module();
    virtual ~Module();

    static void tick_all(uint64_t nr_cycles);

    static void start(uint64_t nr_cycles);
    static void stop();

    static size_t nr_modules() {
        return registry_.size();
    }

public:
    virtual void tick(uint64_t nr_cycles) = 0;
};


class TopModule : public Module
{
public:
    virtual void init() = 0;
    virtual void run(uint64_t nr_cycles) = 0;
};



std::vector<Module*> Module::registry_;
volatile bool Module::stop_request_ = false;

Module::Module()
{
    //printf("constructed %p\n", this);
    registry_.emplace_back(this);
}

Module::~Module()
{
    if (stop_request_) {
        for (auto it = registry_.begin(); it != registry_.end(); ++it) {
            if (*it == this) {
                registry_.erase(it);
                break;
            }
        }
    }
    else {
        fprintf(stderr, "Error: do not destruct modules while running\n");
    }
}

void Module::tick_all(uint64_t nr_cycles)
{
    for (auto module : registry_) {
        module->tick(nr_cycles);
    }
}

void Module::start(uint64_t max_nr_cycles)
{
    if (registry_.empty()) {
        fprintf(stderr, "Error: list of modules is empty\n");
        return;
    }

    TopModule* top_module = dynamic_cast<TopModule*>(registry_.front());

    if (top_module == nullptr) {
        fprintf(stderr, "Error: top module is NULL\n");
        return;
    }

    top_module->init();

    stop_request_ = false;

    for (uint64_t nr_cycles = 0;
            nr_cycles < max_nr_cycles and !stop_request_;
            ++nr_cycles)
    {
        top_module->run(nr_cycles);
        tick_all(nr_cycles);
    }
}

void Module::stop()
{
    stop_request_ = true;
}

} // namespace maj
