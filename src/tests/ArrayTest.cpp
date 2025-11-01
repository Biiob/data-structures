#include <gtest/gtest.h>

#include "Array.h"

using ds::Array;

class ArrayTest : public ::testing::Test
{
protected:
    Array<int> array;
};

// --- Constructors and assignments
TEST_F(ArrayTest, Constructor_Default_WhenCalled_ShouldCreateEmptyArray) {}
TEST_F(ArrayTest, CopyConstructor_WhenArrayHasElements_ShouldDuplicateElements) {}
TEST_F(ArrayTest, CopyAssignment_WhenArrayHasElements_ShouldDuplicateElements) {}
TEST_F(ArrayTest, CopyAssignment_WhenSelfAssigned_ShouldDoNothing) {}
TEST_F(ArrayTest, MoveConstructor_WhenArrayHasElements_ShouldTransferOwnership) {}
TEST_F(ArrayTest, MoveAssignment_WhenArrayHasElements_ShouldTransferOwnership) {}
TEST_F(ArrayTest, MoveAssignment_WhenSelfAssigned_ShouldDoNothing) {}

// --- Element access --- 
TEST_F(ArrayTest, OperatorIndex_WhenArrayEmpty_ShouldThrow) {}
TEST_F(ArrayTest, OperatorIndex_WhenValidIndex_ShouldReturnElement) {}
TEST_F(ArrayTest, At_WhenOutOfRange_ShouldThrow) {}
TEST_F(ArrayTest, At_WhenValidIndex_ShouldReturnElement) {}

// --- State queries ---
TEST_F(ArrayTest, IsEmpty_WhenArrayEmpty_ShouldReturnTrue) {}
TEST_F(ArrayTest, IsEmpty_WhenArrayNotEmpty_ShouldReturnFalse) {}
TEST_F(ArrayTest, Size_WhenArrayEmpty_ShouldReturnZero) {}
TEST_F(ArrayTest, Size_WhenArrayNotEmpty_ShouldReturnCount) {}
TEST_F(ArrayTest, Capacity_WhenCalled_ShouldReturnCurrentCapacity) {}

// --- Capacity management ---
TEST_F(ArrayTest, Reserve_WhenNewCapacityGreater_ShouldExpand) {}
TEST_F(ArrayTest, Reserve_WhenNewCapacitySmaller_ShouldDoNothing) {}
TEST_F(ArrayTest, Reserve_WhenCalled_ShouldPreserveElements) {}

// --- Clear ---
TEST_F(ArrayTest, Clear_WhenArrayNotEmpty_ShouldResetAll) {}
TEST_F(ArrayTest, Clear_WhenArrayAlreadyEmpty_ShouldDoNothing) {}

// --- PushBack ---
TEST_F(ArrayTest, PushBack_WhenArrayEmpty_ShouldAddElement) {}
TEST_F(ArrayTest, PushBack_WhenArrayFull_ShouldResizeAndAdd) {}
TEST_F(ArrayTest, PushBack_WhenCalledMultipleTimes_ShouldIncreaseCount) {}

// --- PopBack ---
TEST_F(ArrayTest, PopBack_WhenArrayEmpty_ShouldThrow) {}
TEST_F(ArrayTest, PopBack_WhenArrayHasOneElement_ShouldRemoveAndReturn) {}
TEST_F(ArrayTest, PopBack_WhenArrayHasMultipleElements_ShouldRemoveLast) {}
TEST_F(ArrayTest, PopBack_WhenCalledRepeatedly_ShouldEventuallyEmptyArray) {}