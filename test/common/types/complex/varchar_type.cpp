//
// Created by JinHai on 2022/11/13.
//

#include <gtest/gtest.h>
#include "base_test.h"
#include "common/types/value.h"
#include "main/logger.h"
#include "main/stats/global_resource_usage.h"

class VarcharTypeTest : public BaseTest {
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

TEST_F(VarcharTypeTest, TestInit) {
    using namespace infinity;
    String s1 = "Hello World";
    String s2 = "Hello World, welcome to c++";

    // Three Initialize function
    {
        VarcharType v1;
        v1.Initialize(s1);
        EXPECT_EQ(v1.length, s1.length());
        EXPECT_EQ(v1.ToString(), s1);
        v1.Reset();

        v1.Initialize(s2);
        EXPECT_EQ(v1.length, s2.length());
        EXPECT_EQ(v1.ToString(), s2);
        v1.Reset();

        v1.Initialize(s1.c_str());
        EXPECT_EQ(v1.length, s1.length());
        EXPECT_EQ(v1.ToString(), s1);
        v1.Reset();

        v1.Initialize(s2.c_str());
        EXPECT_EQ(v1.length, s2.length());
        EXPECT_EQ(v1.ToString(), s2);
        v1.Reset();

        v1.Initialize(s1.c_str(), s1.length());
        EXPECT_EQ(v1.length, s1.length());
        EXPECT_EQ(v1.ToString(), s1);
        v1.Reset();

        v1.Initialize(s2.c_str(), s2.length());
        EXPECT_EQ(v1.length, s2.length());
        EXPECT_EQ(v1.ToString(), s2);
        v1.Reset();

        v1.Initialize(s2.c_str(), s2.length());
        EXPECT_EQ(v1.length, s2.length());
        EXPECT_EQ(v1.ToString(), s2);
        EXPECT_THROW(v1.Initialize(s1.c_str(), s1.length()), TypeException);
        v1.Reset();

    }
}

TEST_F(VarcharTypeTest, TestConstructor1) {
    using namespace infinity;
    String s1 = "Hello World";
    String s2 = "Hello World, welcome to c++";

    // Constructor from string
    {
        LOG_TRACE("===============================");
        VarcharType v1(s1);
        EXPECT_EQ(v1.length, s1.length());
        EXPECT_EQ(v1.ToString(), s1);
        v1.Reset();

        VarcharType v2(s2);
        EXPECT_EQ(v2.length, s2.length());
        EXPECT_EQ(v2.ToString(), s2);
        v2.Reset();
    }
}

TEST_F(VarcharTypeTest, TestConstructor2) {
    using namespace infinity;
    String s1 = "Hello World";
    String s2 = "Hello World, welcome to c++";

    // Constructor from char*
    {
        LOG_TRACE("===============================");
        VarcharType v1(s1.c_str());
        EXPECT_EQ(v1.length, s1.length());
        EXPECT_EQ(v1.ToString(), s1);
        v1.Reset();

        VarcharType v2(s2.c_str());
        EXPECT_EQ(v2.length, s2.length());
        EXPECT_EQ(v2.ToString(), s2);
        v2.Reset();
    }
}

TEST_F(VarcharTypeTest, TestConstructor3) {
    using namespace infinity;
    String s1 = "Hello World";
    String s2 = "Hello World, welcome to c++";

    // Constructor from char* and length
    {
        LOG_TRACE("===============================");
        VarcharType v1(s1.c_str(), s1.length());
        EXPECT_EQ(v1.length, s1.length());
        EXPECT_EQ(v1.ToString(), s1);
        v1.Reset();

        VarcharType v2(s2.c_str(), s2.length());
        EXPECT_EQ(v2.length, s2.length());
        EXPECT_EQ(v2.ToString(), s2);
        v2.Reset();
    }
}

TEST_F(VarcharTypeTest, TestCopy) {
    using namespace infinity;
    String s1 = "Hello World";
    String s2 = "Hello World, welcome to c++";

    // Copy constructor
    {
        LOG_TRACE("===============================");
        VarcharType v1(s1);
        VarcharType v2 = v1;
        EXPECT_EQ(v1.length, s1.length());
        EXPECT_EQ(v1.ToString(), s1);
        EXPECT_EQ(v2.length, s1.length());
        EXPECT_EQ(v2.ToString(), s1);
    }

    {
        LOG_TRACE("================");
        VarcharType v1(s2);
        VarcharType v2 = v1;
        EXPECT_EQ(v1.length, s2.length());
        EXPECT_EQ(v1.ToString(), s2);
        EXPECT_EQ(v2.length, s2.length());
        EXPECT_EQ(v2.ToString(), s2);
    }
}

TEST_F(VarcharTypeTest, TestMove) {
    using namespace infinity;
    String s1 = "Hello World";
    String s2 = "Hello World, welcome to c++";

    // Move constructor 1
    {
        LOG_TRACE("===============================");
        VarcharType v1(s1);
        VarcharType v2 = std::move(v1);
        EXPECT_EQ(v1.length, 0);
        EXPECT_EQ(v1.ToString(), "");
        EXPECT_EQ(v2.length, s1.length());
        EXPECT_EQ(v2.ToString(), s1);
    }

    // Move constructor 2
    {
        LOG_TRACE("================");
        VarcharType v1(s2);
        VarcharType v2 = std::move(v1);
        EXPECT_EQ(v1.length, 0);
        EXPECT_EQ(v1.ptr, nullptr);
        EXPECT_EQ(v1.ToString(), "");
        EXPECT_EQ(v2.length, s2.length());
        EXPECT_EQ(v2.ToString(), s2);
    }
}

TEST_F(VarcharTypeTest, TestCopyAssignment) {
    using namespace infinity;
    String s1 = "Hello World";
    String s2 = "Hello World, welcome to c++";
    String s3 = "Hello World, Php is the best programming language in the world";

    // Copy Assignment 1
    {
        LOG_TRACE("===============================");
        VarcharType v1(s1);
        VarcharType v2;
        v2 = v1;
        EXPECT_EQ(v1.length, s1.length());
        EXPECT_EQ(v1.ToString(), s1);
        EXPECT_EQ(v2.length, s1.length());
        EXPECT_EQ(v2.ToString(), s1);
    }

    // Copy Assignment 2
    {
        LOG_TRACE("================");
        VarcharType v1(s2);
        VarcharType v2;
        v2 = v1;
        EXPECT_EQ(v1.length, s2.length());
        EXPECT_EQ(v1.ToString(), s2);
        EXPECT_EQ(v2.length, s2.length());
        EXPECT_EQ(v2.ToString(), s2);
    }

    // Copy Assignment 3
    {
        LOG_TRACE("================");
        VarcharType v1(s1);
        VarcharType v2(s2);
        VarcharType v3(s3);

        v2 = v1;

        EXPECT_EQ(v1.length, s1.length());
        EXPECT_EQ(v1.ToString(), s1);
        EXPECT_EQ(v2.length, s1.length());
        EXPECT_EQ(v2.ToString(), s1);

        v2 = v3;
        EXPECT_EQ(v2.length, s3.length());
        EXPECT_EQ(v2.ToString(), s3);
    }
}

TEST_F(VarcharTypeTest, TestMoveAssignment) {
    using namespace infinity;
    String s1 = "Hello World";
    String s2 = "Hello World, welcome to c++";
    String s3 = "Hello World, Php is the best programming language in the world";

    // Move constructor 1
    {
        LOG_TRACE("===============================");
        VarcharType v1(s1);
        VarcharType v2;
        v2 = std::move(v1);
        EXPECT_EQ(v1.length, 0);
        EXPECT_EQ(v1.ToString(), "");
        EXPECT_EQ(v2.length, s1.length());
        EXPECT_EQ(v2.ToString(), s1);
    }

    // Move constructor 2
    {
        LOG_TRACE("================");
        VarcharType v1(s2);
        VarcharType v2;
        v2 = std::move(v1);
        EXPECT_EQ(v1.length, 0);
        EXPECT_EQ(v1.ptr, nullptr);
        EXPECT_EQ(v1.ToString(), "");
        EXPECT_EQ(v2.length, s2.length());
        EXPECT_EQ(v2.ToString(), s2);
    }

    // Move Assignment 3
    {
        LOG_TRACE("================");
        VarcharType v1(s1);
        VarcharType v2(s2);
        VarcharType v3(s3);

        v2 = std::move(v1);

        EXPECT_EQ(v1.length, 0);
        EXPECT_EQ(v1.ToString(), "");
        EXPECT_EQ(v2.length, s1.length());
        EXPECT_EQ(v2.ToString(), s1);

        v2 = std::move(v3);
        EXPECT_EQ(v2.length, s3.length());
        EXPECT_EQ(v2.ToString(), s3);
        EXPECT_EQ(v3.length, 0);
        EXPECT_EQ(v3.ptr, nullptr);
    }
}
