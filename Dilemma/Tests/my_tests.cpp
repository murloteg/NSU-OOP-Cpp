#include <iostream>
#include "GameController.h"
#include "gtest/gtest.h"

TEST(Strategies, trivial_always_c_test)
{
    auto strategy = StrategyFactory::createStrategy("TRIVIAL_ALWAYS_C", "FirstBuild");
    ASSERT_EQ("0", (std::to_string) (strategy->vote()));
    ASSERT_EQ("\"TRIVIAL_ALWAYS_C\"", strategy->getStrategyName());
}

TEST(Strategies, trivial_always_d_test)
{
    auto strategy = StrategyFactory::createStrategy("TRIVIAL_ALWAYS_D", "FirstBuild");
    ASSERT_EQ("1", (std::to_string) (strategy->vote()));
    ASSERT_EQ("\"TRIVIAL_ALWAYS_D\"", strategy->getStrategyName());
}

TEST(Strategies, trivial_random_test)
{
    auto strategy = StrategyFactory::createStrategy("TRIVIAL_RANDOM", "FirstBuild");
    ASSERT_EQ("\"TRIVIAL_RANDOM\"", strategy->getStrategyName());
}

TEST(Strategies, friendly_fool_test)
{
    auto strategy = StrategyFactory::createStrategy("FRIENDLY_FOOL", "ThirdBuild");
    ASSERT_EQ("\"FRIENDLY_FOOL\"", strategy->getStrategyName());
}

TEST(Strategies, probability_test)
{
    auto strategy = StrategyFactory::createStrategy("PROBABILITY", "FirstBuild");
    ASSERT_EQ("\"PROBABILITY\"", strategy->getStrategyName());
}

TEST(Strategies, dominator_test)
{
    auto strategy = StrategyFactory::createStrategy("DOMINATOR", "FirstBuild");
    ASSERT_EQ("\"DOMINATOR\"", strategy->getStrategyName());
}
