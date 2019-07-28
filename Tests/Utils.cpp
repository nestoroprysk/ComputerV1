#include "catch.hpp"

#include <Utils.hpp>

#include <cmath>

TEST_CASE("<sqrt><nearZero>")
{
    const auto delta = 0.00001;
    const auto nbCycles = 10000;
    for (auto i = 0; i < nbCycles; ++i)
        REQUIRE(Utils::eq(Utils::sqrt(i * delta), std::sqrt(i * delta)));
    REQUIRE(Utils::eq(Utils::sqrt(0.00000000000001), 0));
    REQUIRE(Utils::eq(Utils::sqrt(0.00000001), 0));
    REQUIRE(Utils::eq(Utils::sqrt(0.0000001), 0));
    REQUIRE(Utils::eq(Utils::sqrt(0.000001), std::sqrt(0.000001)));
    REQUIRE(Utils::eq(Utils::sqrt(0.00001), std::sqrt(0.00001)));
    REQUIRE(Utils::eq(Utils::sqrt(0.0001), std::sqrt(0.0001)));
    REQUIRE(Utils::eq(Utils::sqrt(0.001), std::sqrt(0.001)));
    REQUIRE(Utils::eq(Utils::sqrt(0.01), std::sqrt(0.01)));
    REQUIRE(Utils::eq(Utils::sqrt(0.1), std::sqrt(0.1)));
    REQUIRE(Utils::eq(Utils::sqrt(0), 0));
    REQUIRE(Utils::eq(Utils::sqrt(1), std::sqrt(1)));
}

TEST_CASE("<sqrt><bigNumbers>")
{
    const auto delta = 0.01;
    const auto nbCycles = 10000;
    const auto big = 10000;
    for (auto i = 0; i < nbCycles; ++i)
        REQUIRE(Utils::eq(Utils::sqrt(big * i * delta), std::sqrt(big * i * delta)));
}

TEST_CASE("<sqrt><invalid>")
{
    REQUIRE_THROWS(Utils::sqrt(-1));
}

TEST_CASE("<max>")
{
    REQUIRE(Utils::max(10, 20) == 20);
    REQUIRE(Utils::max(20, 10) == 20);
    REQUIRE(Utils::max(-20, 10) == 10);
}

TEST_CASE("<min>")
{
    REQUIRE(Utils::min(10, 20) == 10);
    REQUIRE(Utils::min(20, 10) == 10);
    REQUIRE(Utils::min(-20, 10) == -20);
}

TEST_CASE("<eq>")
{
    REQUIRE(!Utils::eq(10.0, 10.1));
    REQUIRE(Utils::eq(10.1, 10.1));
    REQUIRE(Utils::eq(10.0, 10.000001));
    REQUIRE(Utils::eq(10.000000001,  10.00000000001));
}

TEST_CASE("<abs>")
{
    REQUIRE(Utils::eq(Utils::abs(10), 10));
    REQUIRE(Utils::eq(Utils::abs(-10), 10));
}
