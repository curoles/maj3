#pragma once

#include <vector>
#include <cstdint>

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


} // namespace maj
