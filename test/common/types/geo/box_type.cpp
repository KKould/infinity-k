//
// Created by JinHai on 2022/11/15.
//

#include <gtest/gtest.h>
#include "base_test.h"
#include "common/types/value.h"
#include "main/logger.h"
#include "main/stats/global_resource_usage.h"

class BoxTypeTest : public BaseTest {
    void
    SetUp() override {
        infinity::Logger::Initialize();
        infinity::GlobalResourceUsage::Init();
    }

    void
    TearDown() override {
        infinity::Logger::Shutdown();
        EXPECT_EQ(infinity::GlobalResourceUsage::GetObjectCount(), 0);
        EXPECT_EQ(infinity::GlobalResourceUsage::GetRawMemoryCount(), 0);
        infinity::GlobalResourceUsage::UnInit();
    }
};

TEST_F(BoxTypeTest, point1) {
    using namespace infinity;

    BoxT b1;
    b1.upper_left.x = 1.0f;
    b1.upper_left.y = 2.0f;
    b1.lower_right.x = 3.0f;
    b1.lower_right.y = 4.0f;

    BoxT b2(b1);

    EXPECT_EQ(b2.upper_left.x, 1.0f);
    EXPECT_EQ(b2.upper_left.y, 2.0f);
    EXPECT_EQ(b2.lower_right.x, 3.0f);
    EXPECT_EQ(b2.lower_right.y, 4.0f);

    b1.Reset();

    EXPECT_EQ(b1.upper_left.x, 0);
    EXPECT_EQ(b1.upper_left.y, 0);
    EXPECT_EQ(b1.lower_right.x, 0);
    EXPECT_EQ(b1.lower_right.x, 0);
}