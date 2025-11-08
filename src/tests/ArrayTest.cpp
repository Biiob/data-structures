#include <gtest/gtest.h>

#include "Array.h"

using ds::Array;

class ArrayTest : public ::testing::Test
{
  protected:
    Array<int> array;
};

// --- Constructors and assignments
TEST_F(ArrayTest, Constructor_Default_WhenCalled_ShouldCreateEmptyArray)
{
    EXPECT_TRUE(array.isEmpty());
}
TEST_F(ArrayTest, CopyConstructor_WhenArrayHasElements_ShouldDuplicateElements)
{
    array.pushBack(0);
    array.pushBack(1);

    Array<int> copiedArray(array);

    EXPECT_FALSE(copiedArray.isEmpty());
    EXPECT_EQ(copiedArray[0], 0);
    EXPECT_EQ(copiedArray[1], 1);
}
TEST_F(ArrayTest, CopyAssignment_WhenArrayHasElements_ShouldDuplicateElements)
{
    array.pushBack(0);
    array.pushBack(1);

    Array<int> copiedArray;
    copiedArray = array;

    EXPECT_FALSE(copiedArray.isEmpty());
    EXPECT_EQ(copiedArray[0], 0);
    EXPECT_EQ(copiedArray[1], 1);
}
TEST_F(ArrayTest, MoveConstructor_WhenArrayHasElements_ShouldTransferOwnership)
{
    array.pushBack(0);
    array.pushBack(1);

    Array<int> movedArray(std::move(array));

    EXPECT_FALSE(movedArray.isEmpty());
    EXPECT_EQ(movedArray[0], 0);
    EXPECT_EQ(movedArray[1], 1);
    EXPECT_TRUE(array.isEmpty());
}
TEST_F(ArrayTest, MoveAssignment_WhenArrayHasElements_ShouldTransferOwnership)
{
    array.pushBack(0);
    array.pushBack(1);

    Array<int> movedArray;
    movedArray = std::move(array);

    EXPECT_FALSE(movedArray.isEmpty());
    EXPECT_EQ(movedArray[0], 0);
    EXPECT_EQ(movedArray[1], 1);
    EXPECT_TRUE(array.isEmpty());
}

// --- Element access ---
TEST_F(ArrayTest, OperatorIndex_WhenValidIndex_ShouldReturnElement)
{
    array.pushBack(0);

    EXPECT_EQ(array[0], 0);
}
TEST_F(ArrayTest, At_WhenOutOfRange_ShouldThrow)
{
    array.pushBack(0);

    EXPECT_ANY_THROW(array.at(1));
}
TEST_F(ArrayTest, At_WhenValidIndex_ShouldReturnElement)
{
    array.pushBack(0);

    EXPECT_EQ(array.at(0), 0);
}

// --- State queries ---
TEST_F(ArrayTest, IsEmpty_WhenArrayEmpty_ShouldReturnTrue)
{
    EXPECT_TRUE(array.isEmpty());
}
TEST_F(ArrayTest, IsEmpty_WhenArrayNotEmpty_ShouldReturnFalse)
{
    array.pushBack(0);
    EXPECT_FALSE(array.isEmpty());
}
TEST_F(ArrayTest, Size_WhenArrayEmpty_ShouldReturnZero)
{
    EXPECT_EQ(array.size(), 0);
}
TEST_F(ArrayTest, Size_WhenArrayNotEmpty_ShouldReturnCount)
{
    array.pushBack(0);
    array.pushBack(1);

    EXPECT_EQ(array.size(), 2);
}
TEST_F(ArrayTest, Capacity_WhenCalled_ShouldReturnCurrentCapacity)
{
    array.reserve(128);

    EXPECT_EQ(array.capacity(), 128);
}

// --- Capacity management ---
TEST_F(ArrayTest, Reserve_WhenNewCapacityGreater_ShouldExpand)
{
    array.reserve(64);
    array.reserve(128);
    EXPECT_EQ(array.capacity(), 128);
}
TEST_F(ArrayTest, Reserve_WhenNewCapacitySmaller_ShouldDoNothing)
{
    array.reserve(64);
    array.reserve(32);
    EXPECT_EQ(array.capacity(), 64);
}
TEST_F(ArrayTest, Reserve_WhenCalled_ShouldPreserveElements)
{
    array.pushBack(0);
    array.reserve(128);
    EXPECT_EQ(array[0], 0);
}

// --- Clear ---
TEST_F(ArrayTest, Clear_WhenArrayNotEmpty_ShouldResetAll)
{
    array.pushBack(0);
    EXPECT_FALSE(array.isEmpty());
    array.clear();
    EXPECT_TRUE(array.isEmpty());
}
TEST_F(ArrayTest, Clear_WhenArrayAlreadyEmpty_ShouldDoNothing)
{
    array.clear();
    EXPECT_TRUE(array.isEmpty());
}

// --- PushBack ---
TEST_F(ArrayTest, PushBack_WhenArrayEmpty_ShouldAddElement)
{
    array.pushBack(0);
    EXPECT_EQ(array[0], 0);
}
TEST_F(ArrayTest, PushBack_WhenArrayFull_ShouldResizeAndAdd)
{
    array.reserve(2);
    array.pushBack(0);
    array.pushBack(1);
    array.pushBack(2);

    EXPECT_EQ(array.capacity(), 4);
    EXPECT_EQ(array[2], 2);
}
TEST_F(ArrayTest, PushBack_WhenCalledMultipleTimes_ShouldIncreaseCount)
{
    EXPECT_EQ(array.size(), 0);
    array.pushBack(0);
    EXPECT_EQ(array.size(), 1);
    array.pushBack(1);
    EXPECT_EQ(array.size(), 2);
}

// --- PopBack ---
TEST_F(ArrayTest, PopBack_WhenArrayEmpty_ShouldThrow)
{
    EXPECT_ANY_THROW(array.popBack());
}
TEST_F(ArrayTest, PopBack_WhenArrayHasOneElement_ShouldRemoveAndReturn)
{
    array.pushBack(0);
    EXPECT_EQ(array.popBack(), 0);
    EXPECT_TRUE(array.isEmpty());
}
TEST_F(ArrayTest, PopBack_WhenArrayHasMultipleElements_ShouldRemoveLast)
{
    array.pushBack(0);
    array.pushBack(1);
    EXPECT_EQ(array.popBack(), 1);
    EXPECT_EQ(array[0], 0);
}

// --- Iterators ---
TEST_F(ArrayTest, IteratorLoop_WhenIterating_ShouldVisitAllElementsInOrder)
{
    for (int i = 0; i < 5; i++)
    {
        array.pushBack(i);
    }

    int i = 0;
    for (auto it = array.begin(); it != array.end(); it++, i++)
    {
        EXPECT_EQ(*it, i);
    }
}

TEST_F(ArrayTest, IteratorLoop_WhenReverseIterating_ShouldVisitAllElementsInReverseOrder)
{
    for (int i = 0; i < 5; i++)
    {
        array.pushBack(i);
    }

    int i = 4;
    for (auto it = array.rbegin(); it != array.rend(); it--, i--)
    {
        EXPECT_EQ(*it, i);
    }
}