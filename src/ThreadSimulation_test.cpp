#include "ThreadSimulation.h"

#include <gtest/gtest.h>

namespace {

void noMustEatCountConstructor(int die, int eat, int sleep) {
    ThreadSimulation simu(die, eat, sleep);
    EXPECT_EQ(simu.getTimeToDie(), die);
    EXPECT_EQ(simu.getTimeToEat(), eat);
    EXPECT_EQ(simu.getTimeToSleep(), sleep);
    EXPECT_EQ(simu.getMustEatCount(), -1);
}

void mustEatCountConstructor(int die, int eat, int sleep, int mustEat) {
    ThreadSimulation simu(die, eat, sleep, mustEat);
    EXPECT_EQ(simu.getTimeToDie(), die);
    EXPECT_EQ(simu.getTimeToEat(), eat);
    EXPECT_EQ(simu.getTimeToSleep(), sleep);
    EXPECT_EQ(simu.getMustEatCount(), mustEat);
}

} // namespace

TEST(ThreadSimulationTest, constructor) {
    // Constructor without the mustEatCount specified
    {
        SCOPED_TRACE("ThreadSimulation(1, 2, 3)");
        noMustEatCountConstructor(1, 2, 3);
    }
    {
        SCOPED_TRACE("ThreadSimulation(500, 34, 455)");
        noMustEatCountConstructor(500, 34, 455);
    }
    {
        SCOPED_TRACE("ThreadSimulation(2, 5, 454)");
        noMustEatCountConstructor(2, 5, 454);
    }

    // Constructor with mustEatCount specified
    {
        SCOPED_TRACE("ThreadSimulation(1, 2, 3, 4)");
        mustEatCountConstructor(1, 2, 3, 4);
    }
    {
        SCOPED_TRACE("ThreadSimulation(4, 3, 3, 4)");
        mustEatCountConstructor(4, 3, 3, 4);
    }
    {
        SCOPED_TRACE("ThreadSimulation(100, 200, 300, 400)");
        mustEatCountConstructor(100, 200, 300, 400);
    }
}
