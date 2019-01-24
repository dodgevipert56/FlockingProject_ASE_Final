#include <iostream>
#include <gtest/gtest.h>
#include "Boid.h"
#include "Flock.h"

int main(int argc, char **argv) //arg count & array
{
    testing::InitGoogleTest(&argc, argv); // to pass command line args
    return RUN_ALL_TESTS();
}

TEST(Boid, defaultCtor) // Macro, - Test wer gonna run, test case
{
    Boid b;

    ngl::Vec3 pos;
    ngl::Vec3 dir;
    ngl::Vec3 scl;
    ngl::Vec3 rot;
    ngl::Vec4 col;

    ASSERT_NO_THROW(pos = b.getPosition());
    EXPECT_FLOAT_EQ(pos.m_x, 0.0f);
    EXPECT_FLOAT_EQ(pos.m_y, 0.0f);
    EXPECT_FLOAT_EQ(pos.m_z, 0.0f);

    ASSERT_NO_THROW(dir = b.getDirection());
    EXPECT_FLOAT_EQ(dir.m_x, 0.0f);
    EXPECT_FLOAT_EQ(dir.m_y, 0.0f);
    EXPECT_FLOAT_EQ(dir.m_z, 0.0f);

    ASSERT_NO_THROW(scl = b.getScale());
    EXPECT_FLOAT_EQ(scl.m_x, 0.0f);
    EXPECT_FLOAT_EQ(scl.m_y, 0.0f);
    EXPECT_FLOAT_EQ(scl.m_z, 0.0f);

    ASSERT_NO_THROW(rot = b.getRotation());
    EXPECT_FLOAT_EQ(rot.m_x, 0.0f);
    EXPECT_FLOAT_EQ(rot.m_y, 0.0f);
    EXPECT_FLOAT_EQ(rot.m_z, 0.0f);

    ASSERT_NO_THROW(col = b.getColour());
    EXPECT_FLOAT_EQ(col.m_r, 0.0f);
    EXPECT_FLOAT_EQ(col.m_g, 0.0f);
    EXPECT_FLOAT_EQ(col.m_b, 0.0f);
}

TEST(Boid, plusEquals)
{
    ngl::Vec3 a = {1.0f, 2.0f, 3.0f};
    ngl::Vec3 b = {1.0f, 1.0f, 1.0f};

    a+=b;

    EXPECT_FLOAT_EQ(a.m_x, 2.0f);
    EXPECT_FLOAT_EQ(a.m_y, 3.0f);
    EXPECT_FLOAT_EQ(a.m_z, 4.0f);
}

TEST(Boid, minusEquals)
{
    ngl::Vec3 a = {5.0f, 4.0f, 6.0f};
    ngl::Vec3 b = {1.0f, 1.0f, 1.0f};

    a-=b;

    EXPECT_FLOAT_EQ(a.m_x, 4.0f);
    EXPECT_FLOAT_EQ(a.m_y, 3.0f);
    EXPECT_FLOAT_EQ(a.m_z, 5.0f);
}


TEST(Boid, setPosition)
{
    Boid b;
    ngl::Vec3 pos;
    b.setPosition({0.5f, -0.2f, 12.303f}); //brace initialisation
    ASSERT_NO_THROW(pos = b.getPosition());
    EXPECT_FLOAT_EQ(pos.m_x, 0.5f);
    EXPECT_FLOAT_EQ(pos.m_y, -0.2f);
    EXPECT_FLOAT_EQ(pos.m_z, 12.303f);
}

TEST(Boid, setDirection)
{
    Boid b;
    ngl::Vec3 dir;
    b.setDirection({0.2f, -0.1f, 10.508f});

    ASSERT_NO_THROW(dir = b.getDirection());
    EXPECT_FLOAT_EQ(dir.m_x, 0.2f);
    EXPECT_FLOAT_EQ(dir.m_y, -0.1f);
    EXPECT_FLOAT_EQ(dir.m_z, 10.508f);
}

TEST(Boid, setScale)
{
    Boid b;
    ngl::Vec3 scl;
    b.setScale({0.5f, -2.5f, 5.0f});

    ASSERT_NO_THROW(scl = b.getScale());
    EXPECT_FLOAT_EQ(scl.m_x, 0.5f);
    EXPECT_FLOAT_EQ(scl.m_y, -2.5f);
    EXPECT_FLOAT_EQ(scl.m_z, 5.0f);
}

TEST(Boid, setRotation)
{
    Boid b;
    ngl::Vec3 dir;
    b.setRotation({2.0f, -4.6f, 20.707f});

    ASSERT_NO_THROW(dir = b.getRotation());
    EXPECT_FLOAT_EQ(dir.m_x, 2.0f);
    EXPECT_FLOAT_EQ(dir.m_y, -4.6f);
    EXPECT_FLOAT_EQ(dir.m_z, 20.707f);
}


TEST(Boid, setColour) // Macro, - Test wer gonna run, test case
{
    Boid b;
    ngl::Vec4 col;
    b.setColour({0.5f, 0.2f, 1.0f});

    ASSERT_NO_THROW(col = b.getColour());
    EXPECT_FLOAT_EQ(col.m_r, 0.5f);
    EXPECT_FLOAT_EQ(col.m_g, 0.2f);
    EXPECT_FLOAT_EQ(col.m_b, 1.0f);
}



