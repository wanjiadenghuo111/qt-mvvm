#include <gtest/gtest.h>
#include "TestSessionItem.h"
#include "TestAnother.h"
#include "TestSessionModel.h"
#include "TestPath.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    // run all google tests
    return RUN_ALL_TESTS();
}