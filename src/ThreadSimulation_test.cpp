#include "ThreadSimulation.h"

#include <gtest/gtest.h>

namespace {

void noMustEatCountConstructor(int total, int die, int eat, int sleep) {
    ThreadSimulation simu(total, die, eat, sleep);
    EXPECT_EQ(simu.getTotalPhilosophers(), total);
}

void mustEatCountConstructor(int total, int die, int eat, int sleep, int mustEat) {
    ThreadSimulation simu(total, die, eat, sleep, mustEat);
    EXPECT_EQ(simu.getTotalPhilosophers(), total);
}

} // namespace

TEST(ThreadSimulationTest, constructor) {
    // Constructor without the mustEatCount specified
    {
        SCOPED_TRACE("ThreadSimulation(1, 2, 3, 4)");
        noMustEatCountConstructor(1, 2, 3, 4);
    }
    {
        SCOPED_TRACE("ThreadSimulation(500, 34, 455, 4)");
        noMustEatCountConstructor(500, 34, 455, 4);
    }
    {
        SCOPED_TRACE("ThreadSimulation(2, 5, 454, 356)");
        noMustEatCountConstructor(2, 5, 454, 356);
    }

    // Constructor with mustEatCount specified
    {
        SCOPED_TRACE("ThreadSimulation(1, 2, 3, 4, 5)");
        mustEatCountConstructor(1, 2, 3, 4, 5);
    }
    {
        SCOPED_TRACE("ThreadSimulation(4, 3, 3, 4, 5)");
        mustEatCountConstructor(4, 3, 3, 4, 5);
    }
    {
        SCOPED_TRACE("ThreadSimulation(100, 200, 300, 400, 550)");
        mustEatCountConstructor(100, 200, 300, 400, 550);
    }
}
